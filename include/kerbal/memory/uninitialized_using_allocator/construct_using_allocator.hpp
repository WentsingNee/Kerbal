/**
 * @file       construct_using_allocator.hpp
 * @brief
 * @date       2021-08-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_CONSTRUCT_USING_ALLOCATOR_HPP
#define KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_CONSTRUCT_USING_ALLOCATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/uninitialized_using_allocator/destroy_using_allocator.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/conditional.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus > 201703L
#	include <memory>
#endif

#include <kerbal/memory/detail/can_be_nothrow_advance_iterator.hpp>


namespace kerbal
{

	namespace memory
	{

	//==================
	// forward declare

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_value_construct_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last);

		template <typename Allocator, typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_copy_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to);

		template <typename Allocator, typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_move_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to);



#	if __cplusplus < 201103L

#	define EMPTY
#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename Allocator, typename Tp KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		Tp * construct_at_using_allocator(Allocator & alloc, Tp * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
			allocator_traits::construct(alloc, p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
			return p; \
		}

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	else

		namespace detail
		{

			template <typename Allocator, typename Tp, typename ... Args>
			KERBAL_CONSTEXPR14
			Tp * _K_construct_at_using_allocator(Allocator & alloc, Tp * p, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::memory::allocator_traits<Allocator>::construct(alloc, p, kerbal::utility::forward<Args>(args)...))
					)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
				allocator_traits::construct(alloc, p, kerbal::utility::forward<Args>(args)...);
				return p;
			}

		} // namespace detail


		template <typename Allocator, typename Tp, typename ... Args>
		KERBAL_CONSTEXPR14
		Tp * construct_at_using_allocator(Allocator & alloc, Tp * p, Args&& ... args)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(detail::_K_construct_at_using_allocator(alloc, p, kerbal::utility::forward<Args>(args)...))
				)
		{
			return detail::_K_construct_at_using_allocator(alloc, p, kerbal::utility::forward<Args>(args)...);
		}

#	endif // __cplusplus >= 201103L



	//==================
	// uninitialized_value_construct_using_allocator

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_VAL_CONSTRUCT_UA_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_VAL_CONSTRUCT_UA_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_VAL_CONSTRUCT_UA_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void _K_uninitialized_value_construct_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, UI_VAL_CONSTRUCT_UA_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (current != last) {
						iterator remain(current);
						kerbal::memory::construct_at_using_allocator(alloc, &*current); // new (&*current) Tp();
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on_using_allocator(alloc, *remain);
							kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, current);
					}
					throw;
				}
			}

			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void _K_uninitialized_value_construct_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, UI_VAL_CONSTRUCT_UA_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (current != last) {
						kerbal::memory::construct_at_using_allocator(alloc, &*current); // new (&*current) Tp();
						++current;
					}
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, current);
					throw;
				}
			}

#		endif

			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void _K_uninitialized_value_construct_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, UI_VAL_CONSTRUCT_UA_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at_using_allocator(alloc, &*first); // new (&*first) Tp ();
					++first;
				}
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_value_construct_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;

			typedef typename kerbal::type_traits::conditional<
					detail::can_be_nothrow_advance_iterator<iterator>::value,
					detail::UI_VAL_CONSTRUCT_UA_VER_NOTHROW_ITER_ADVANCE,
					detail::UI_VAL_CONSTRUCT_UA_VER_DEFAULT
			>::type VER;

#	else
			typedef detail::UI_VAL_CONSTRUCT_UA_VER_NO_CATCH VER;
#	endif

			detail::_K_uninitialized_value_construct_using_allocator(alloc, first, last, VER());
		}



	//==================
	// uninitialized_value_construct_n_using_allocator

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_VAL_CONSTRUCT_N_UA_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_VAL_CONSTRUCT_N_UA_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_VAL_CONSTRUCT_N_UA_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename Allocator, typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_value_construct_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n, UI_VAL_CONSTRUCT_N_UA_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::construct_at_using_allocator(alloc, &*current); // new (&*current) Tp();
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on_using_allocator(alloc, *remain);
							kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, current);
					}
					throw;
				}
			}

			template <typename Allocator, typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_value_construct_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n, UI_VAL_CONSTRUCT_N_UA_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::construct_at_using_allocator(alloc, &*current); // new (&*current) Tp();
						++current;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, current);
					throw;
				}
			}

#		endif

			template <typename Allocator, typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator _K_uninitialized_value_construct_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n, UI_VAL_CONSTRUCT_N_UA_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::construct_at_using_allocator(alloc, &*first); // new (&*first) Tp ();
					++first;
				}
				return first;
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_value_construct_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;

			typedef typename kerbal::type_traits::conditional<
					detail::can_be_nothrow_advance_iterator<iterator>::value,
					detail::UI_VAL_CONSTRUCT_N_UA_VER_NOTHROW_ITER_ADVANCE,
					detail::UI_VAL_CONSTRUCT_N_UA_VER_DEFAULT
			>::type VER;

#	else
			typedef detail::UI_VAL_CONSTRUCT_N_UA_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_value_construct_n_using_allocator(alloc, first, n, VER());
		}



	//==================
	// uninitialized_copy_using_allocator

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_CPY_UA_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_CPY_UA_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_CPY_UA_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename Allocator, typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_copy_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to, UI_CPY_UA_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (first != last) {
						iterator remain(current);
						kerbal::memory::construct_at_using_allocator(alloc, &*current, *first); // new (&*current) Tp (*first);
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on_using_allocator(alloc, *remain);
							kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, current);
					}
					throw;
				}
			}

			template <typename Allocator, typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_copy_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to, UI_CPY_UA_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (first != last) {
						kerbal::memory::construct_at_using_allocator(alloc, &*current, *first); // new (&*current) Tp (*first);
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, current);
					throw;
				}
			}

#		endif

			template <typename Allocator, typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator _K_uninitialized_copy_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to, UI_CPY_UA_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at_using_allocator(alloc, &*to, *first); // new (&*to) Tp (*first);
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename Allocator, typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_copy_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;

			typedef typename kerbal::type_traits::conditional<
					detail::can_be_nothrow_advance_iterator<iterator>::value,
					detail::UI_CPY_UA_VER_NOTHROW_ITER_ADVANCE,
					detail::UI_CPY_UA_VER_DEFAULT
			>::type VER;

#	else
			typedef detail::UI_CPY_UA_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_copy_using_allocator(alloc, first, last, to, VER());
		}



	//==================
	// uninitialized_copy_n_using_allocator

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_CPY_N_UA_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_CPY_N_UA_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_CPY_N_UA_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename Allocator, typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_copy_n_using_allocator(Allocator & alloc, InputIterator first, SizeType n, ForwardIterator to, UI_CPY_N_UA_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::construct_at_using_allocator(alloc, &*current, *first); // new (&*current) Tp(*first);
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on_using_allocator(alloc, *remain);
							kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, current);
					}
					throw;
				}
			}

			template <typename Allocator, typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_copy_n_using_allocator(Allocator & alloc, InputIterator first, SizeType n, ForwardIterator to, UI_CPY_N_UA_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::construct_at_using_allocator(alloc, &*current, *first); // new (&*current) Tp(*first);
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, current);
					throw;
				}
			}

#		endif

			template <typename Allocator, typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator _K_uninitialized_copy_n_using_allocator(Allocator & alloc, InputIterator first, SizeType n, ForwardIterator to, UI_CPY_N_UA_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::construct_at_using_allocator(alloc, &*to, *first); // new (&*to) Tp (*first);
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename Allocator, typename InputIterator, typename SizeType, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_copy_n_using_allocator(Allocator & alloc, InputIterator first, SizeType n, ForwardIterator to)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;

			typedef typename kerbal::type_traits::conditional<
					detail::can_be_nothrow_advance_iterator<iterator>::value,
					detail::UI_CPY_N_UA_VER_NOTHROW_ITER_ADVANCE,
					detail::UI_CPY_N_UA_VER_DEFAULT
			>::type VER;

#	else
			typedef detail::UI_CPY_N_UA_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_copy_n_using_allocator(alloc, first, n, to, VER());
		}



	//==================
	// uninitialized_move_using_allocator

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_MOV_UA_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_MOV_UA_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_MOV_UA_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename Allocator, typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_move_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to, UI_MOV_UA_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (first != last) {
						iterator remain(current);
						kerbal::memory::construct_at_using_allocator(alloc, &*current, kerbal::compatibility::to_xvalue(*first)); // new (&*current) Tp (kerbal::compatibility::to_xvalue(*first));
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on_using_allocator(alloc, *remain);
							kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, current);
					}
					throw;
				}
			}

			template <typename Allocator, typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_move_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to, UI_MOV_UA_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (first != last) {
						kerbal::memory::construct_at_using_allocator(alloc, &*current, kerbal::compatibility::to_xvalue(*first)); // new (&*current) Tp (kerbal::compatibility::to_xvalue(*first));
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, current);
					throw;
				}
			}

#		endif

			template <typename Allocator, typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator _K_uninitialized_move_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to, UI_MOV_UA_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at_using_allocator(alloc, &*to, kerbal::compatibility::to_xvalue(*first)); // new (&*to) Tp (kerbal::compatibility::to_xvalue(*first));
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename Allocator, typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_move_using_allocator(Allocator & alloc, InputIterator first, InputIterator last, ForwardIterator to)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;

			typedef typename kerbal::type_traits::conditional<
					detail::can_be_nothrow_advance_iterator<iterator>::value,
					detail::UI_MOV_UA_VER_NOTHROW_ITER_ADVANCE,
					detail::UI_MOV_UA_VER_DEFAULT
			>::type VER;

#	else
			typedef detail::UI_MOV_UA_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_move_using_allocator(alloc, first, last, to, VER());
		}



	//==================
	// uninitialized_move_n_using_allocator

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_MOV_N_UA_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_MOV_N_UA_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_MOV_N_UA_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename Allocator, typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_move_n_using_allocator(Allocator & alloc, InputIterator first, SizeType n, ForwardIterator to, UI_MOV_N_UA_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::construct_at_using_allocator(alloc, &*current, kerbal::compatibility::to_xvalue(*first)); // new (&*current) Tp(kerbal::compatibility::to_xvalue(*first));
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on_using_allocator(alloc, *remain);
							kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, current);
					}
					throw;
				}
			}

			template <typename Allocator, typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_move_n_using_allocator(Allocator & alloc, InputIterator first, SizeType n, ForwardIterator to, UI_MOV_N_UA_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::construct_at_using_allocator(alloc, &*current, kerbal::compatibility::to_xvalue(*first)); // new (&*current) Tp(kerbal::compatibility::to_xvalue(*first));
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, to, current);
					throw;
				}
			}

#		endif

			template <typename Allocator, typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator _K_uninitialized_move_n_using_allocator(Allocator & alloc, InputIterator first, SizeType n, ForwardIterator to, UI_MOV_N_UA_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::construct_at_using_allocator(alloc, &*to, kerbal::compatibility::to_xvalue(*first)); // new (&*to) Tp (kerbal::compatibility::to_xvalue(*first));
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename Allocator, typename InputIterator, typename SizeType, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_move_n_using_allocator(Allocator & alloc, InputIterator first, SizeType n, ForwardIterator to)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;

			typedef typename kerbal::type_traits::conditional<
					detail::can_be_nothrow_advance_iterator<iterator>::value,
					detail::UI_MOV_N_UA_VER_NOTHROW_ITER_ADVANCE,
					detail::UI_MOV_N_UA_VER_DEFAULT
			>::type VER;

#	else
			typedef detail::UI_MOV_N_UA_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_move_n_using_allocator(alloc, first, n, to, VER());
		}



	//==================
	// uninitialized_fill_using_allocator

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_FILL_UA_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_FILL_UA_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_FILL_UA_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename Allocator, typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR20
			void uninitialized_fill_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, const T & value, UI_FILL_UA_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (current != last) {
						iterator remain(current);
						kerbal::memory::construct_at_using_allocator(alloc, &*current, value); // new (&*current) Tp (value);
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on_using_allocator(alloc, *remain);
							kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, current);
					}
					throw;
				}
			}

			template <typename Allocator, typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR20
			void uninitialized_fill_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, const T & value, UI_FILL_UA_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (current != last) {
						kerbal::memory::construct_at_using_allocator(alloc, &*current, value); // new (&*current) Tp (value);
						++current;
					}
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, current);
					throw;
				}
			}

#		endif

			template <typename Allocator, typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR14
			void uninitialized_fill_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, const T & value, UI_FILL_UA_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at_using_allocator(alloc, &*first, value); // new (&*first) Tp (value);
					++first;
				}
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator, typename T>
		KERBAL_CONSTEXPR14
		void uninitialized_fill_using_allocator(Allocator & alloc, ForwardIterator first, ForwardIterator last, const T & value)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;

			typedef typename kerbal::type_traits::conditional<
					detail::can_be_nothrow_advance_iterator<iterator>::value,
					detail::UI_FILL_UA_VER_NOTHROW_ITER_ADVANCE,
					detail::UI_FILL_UA_VER_DEFAULT
			>::type VER;

#	else
			typedef detail::UI_FILL_UA_VER_NO_CATCH VER;
#	endif

			detail::uninitialized_fill_using_allocator(alloc, first, last, value, VER());
		}



	//==================
	// uninitialized_fill_n_using_allocator

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_FILL_N_UA_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_FILL_N_UA_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_FILL_N_UA_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename Allocator, typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_fill_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n, const T & value, UI_FILL_N_UA_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::construct_at_using_allocator(alloc, &*current, value); // new (&*current) Tp(value);
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on_using_allocator(alloc, *remain);
							kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, current);
					}
					throw;
				}
			}

			template <typename Allocator, typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_fill_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n, const T & value, UI_FILL_N_UA_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::construct_at_using_allocator(alloc, &*current, value); // new (&*current) Tp(value);
						++current;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy_using_allocator(alloc, first, current);
					throw;
				}
			}

#		endif

			template <typename Allocator, typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR14
			ForwardIterator _K_uninitialized_fill_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n, const T & value, UI_FILL_N_UA_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::construct_at_using_allocator(alloc, &*first, value); // new (&*first) Tp (value);
					++first;
				}
				return first;
			}

		} // namespace detail

		template <typename Allocator, typename ForwardIterator, typename SizeType, typename T>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_fill_n_using_allocator(Allocator & alloc, ForwardIterator first, SizeType n, const T & value)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;

			typedef typename kerbal::type_traits::conditional<
					detail::can_be_nothrow_advance_iterator<iterator>::value,
					detail::UI_FILL_N_UA_VER_NOTHROW_ITER_ADVANCE,
					detail::UI_FILL_N_UA_VER_DEFAULT
			>::type VER;

#	else
			typedef detail::UI_FILL_N_UA_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_fill_n_using_allocator(alloc, first, n, value, VER());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_USING_ALLOCATOR_CONSTRUCT_USING_ALLOCATOR_HPP
