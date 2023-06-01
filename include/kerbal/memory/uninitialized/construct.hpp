/**
 * @file       construct.hpp
 * @brief
 * @date       2021-03-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_CONSTRUCT_HPP
#define KERBAL_MEMORY_UNINITIALIZED_CONSTRUCT_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/uninitialized/destroy.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_trivially_constructible.hpp>
#	include <kerbal/type_traits/is_trivially_move_assignable.hpp>
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

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_value_construct(ForwardIterator first, ForwardIterator last);

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to);

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to);



#	if __cplusplus < 201103L

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename Tp KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		Tp * construct_at(Tp * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
		{ \
			::new (const_cast<void*>(static_cast<const volatile void*>(p))) Tp (KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
			return p; \
		}

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY


		template <typename Tp, std::size_t N>
		Tp (* construct_at(Tp (*p) [N])) [N]
		{
			kerbal::memory::uninitialized_value_construct(*p, *p + N);
			return p;
		}

		template <typename Tp, typename Up, std::size_t N>
		Tp (* construct_at(Tp (*p) [N], Up (&val) [N])) [N]
		{
			kerbal::memory::uninitialized_copy(val + 0, val + N, *p + 0);
			return p;
		}


#	else

		namespace detail
		{

#	if __cplusplus <= 201703L

			typedef kerbal::type_traits::integral_constant<int, 0> CONSTRUCT_AT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> CONSTRUCT_AT_VER_TRIVIAL;

			template <typename Tp, typename ... Args>
			Tp * k_construct_at_impl(CONSTRUCT_AT_VER_DEFAULT, Tp * p, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(::new (const_cast<void*>(static_cast<const volatile void*>(p)))
							Tp (kerbal::utility::forward<Args>(args)...))
					)
			{
				return ::new (const_cast<void*>(static_cast<const volatile void*>(p)))
						Tp (kerbal::utility::forward<Args>(args)...);
			}

			template <typename Tp, typename ... Args>
			KERBAL_CONSTEXPR14
			Tp * k_construct_at_impl(CONSTRUCT_AT_VER_TRIVIAL, Tp * p, Args&& ... args) KERBAL_NOEXCEPT
			{
				*p = Tp(kerbal::utility::forward<Args>(args)...);
				return p;
			}

			template <typename Tp, typename ... Args>
			struct construct_at_impl_overload_ver
			{
					typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::tribool_is_true<
							typename kerbal::type_traits::tribool_conjunction<
								kerbal::type_traits::try_test_is_trivially_constructible<Tp, Args...>,
								kerbal::type_traits::try_test_is_trivially_move_assignable<Tp>,
								kerbal::type_traits::try_test_is_trivially_destructible<Tp>
							>::result
						>::value,
						CONSTRUCT_AT_VER_TRIVIAL,
						CONSTRUCT_AT_VER_DEFAULT
					>::type type;
			};

			template <typename Tp, typename ... Args>
			KERBAL_CONSTEXPR14
			Tp * k_construct_at(Tp * p, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(k_construct_at_impl(
							typename construct_at_impl_overload_ver<Tp, Args&&...>::type(),
							p, kerbal::utility::forward<Args>(args)...))
					)
			{
				typedef typename construct_at_impl_overload_ver<Tp, Args&&...>::type VER;
				return k_construct_at_impl(VER(), p, kerbal::utility::forward<Args>(args)...);
			}

#	else

			template <typename Tp, typename ... Args>
			KERBAL_CONSTEXPR20
			Tp * k_construct_at(Tp * p, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(std::construct_at(p, kerbal::utility::forward<Args>(args)...))
					)
			{
				return std::construct_at(p, kerbal::utility::forward<Args>(args)...);
			}

#	endif // C++20


			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR14
			Tp (* k_construct_at(Tp (*p) [N])) [N]
			{
				kerbal::memory::uninitialized_value_construct(*p, *p + N);
				return p;
			}


			template <typename Tp, typename Up, std::size_t N>
			KERBAL_CONSTEXPR14
			Tp (* k_construct_at(Tp (*p) [N], Up (&&val) [N])) [N]
			{
				kerbal::memory::uninitialized_move(val + 0, val + N, *p + 0);
				return p;
			}


			template <typename Tp, typename Up, std::size_t N>
			KERBAL_CONSTEXPR14
			Tp (* k_construct_at(Tp (*p) [N], Up (&val) [N])) [N]
			{
				kerbal::memory::uninitialized_copy(val + 0, val + N, *p + 0);
				return p;
			}


		} // namespace detail


		template <typename Tp, typename ... Args>
		KERBAL_CONSTEXPR14
		Tp * construct_at(Tp * p, Args&& ... args)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(detail::k_construct_at(p, kerbal::utility::forward<Args>(args)...))
				)
		{
			return detail::k_construct_at(p, kerbal::utility::forward<Args>(args)...);
		}

#	endif // __cplusplus >= 201103L



	//==================
	// uninitialized_value_construct

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_VAL_CONSTRUCT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_VAL_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_VAL_CONSTRUCT_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void k_uninitialized_value_construct(ForwardIterator first, ForwardIterator last, UI_VAL_CONSTRUCT_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (current != last) {
						iterator remain(current);
						kerbal::memory::construct_at(&*current); // new (&*current) Tp();
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void k_uninitialized_value_construct(ForwardIterator first, ForwardIterator last, UI_VAL_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (current != last) {
						kerbal::memory::construct_at(&*current); // new (&*current) Tp ();
						++current;
					}
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void k_uninitialized_value_construct(ForwardIterator first, ForwardIterator last, UI_VAL_CONSTRUCT_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at(&*first); // new (&*first) Tp ();
					++first;
				}
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_value_construct(ForwardIterator first, ForwardIterator last)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<value_type>
					>::value,
					detail::UI_VAL_CONSTRUCT_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::UI_VAL_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE,
							detail::UI_VAL_CONSTRUCT_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::UI_VAL_CONSTRUCT_VER_NO_CATCH VER;

#	endif

			detail::k_uninitialized_value_construct(first, last, VER());
		}



	//==================
	// uninitialized_value_construct_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_VAL_CONSTRUCT_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_VAL_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_VAL_CONSTRUCT_N_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_value_construct_n(ForwardIterator first, SizeType n, UI_VAL_CONSTRUCT_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::construct_at(&*current); // new (&*current) Tp();
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_value_construct_n(ForwardIterator first, SizeType n, UI_VAL_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::construct_at(&*current); // new (&*current) Tp();
						++current;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator k_uninitialized_value_construct_n(ForwardIterator first, SizeType n, UI_VAL_CONSTRUCT_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::construct_at(&*first); // new (&*first) Tp ();
					++first;
				}
				return first;
			}

		} // namespace detail

		template <typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_value_construct_n(ForwardIterator first, SizeType n)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<value_type>
					>::value,
					detail::UI_VAL_CONSTRUCT_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::UI_VAL_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE,
							detail::UI_VAL_CONSTRUCT_N_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::UI_VAL_CONSTRUCT_N_VER_NO_CATCH VER;

#	endif

			return detail::k_uninitialized_value_construct_n(first, n, VER());
		}



	//==================
	// uninitialized_copy

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_CPY_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_CPY_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_CPY_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to, UI_CPY_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (first != last) {
						iterator remain(current);
						kerbal::memory::construct_at(&*current, *first); // new (&*current) Tp (*first);
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					}
					throw;
				}
			}

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to, UI_CPY_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (first != last) {
						kerbal::memory::construct_at(&*current, *first); // new (&*current) Tp (*first);
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					throw;
				}
			}

#		endif

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator k_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to, UI_CPY_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at(&*to, *first); // new (&*to) Tp (*first);
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<value_type>
					>::value,
					detail::UI_CPY_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::UI_CPY_VER_NOTHROW_ITER_ADVANCE,
							detail::UI_CPY_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::UI_CPY_VER_NO_CATCH VER;

#	endif

			return detail::k_uninitialized_copy(first, last, to, VER());
		}



	//==================
	// uninitialized_copy_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_CPY_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_CPY_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_CPY_N_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to, UI_CPY_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::construct_at(&*current, *first); // new (&*current) Tp(*first);
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					}
					throw;
				}
			}

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to, UI_CPY_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::construct_at(&*current, *first); // new (&*current) Tp(*first);
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					throw;
				}
			}

#		endif

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator k_uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to, UI_CPY_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::construct_at(&*to, *first); // new (&*to) Tp (*first);
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename SizeType, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<value_type>
					>::value,
					detail::UI_CPY_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::UI_CPY_N_VER_NOTHROW_ITER_ADVANCE,
							detail::UI_CPY_N_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::UI_CPY_N_VER_NO_CATCH VER;

#	endif

			return detail::k_uninitialized_copy_n(first, n, to, VER());
		}



	//==================
	// uninitialized_move

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_MOV_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_MOV_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_MOV_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to, UI_MOV_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (first != last) {
						iterator remain(current);
						kerbal::memory::construct_at(&*current, kerbal::compatibility::to_xvalue(*first)); // new (&*current) Tp (kerbal::compatibility::to_xvalue(*first));
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					}
					throw;
				}
			}

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to, UI_MOV_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (first != last) {
						kerbal::memory::construct_at(&*current, kerbal::compatibility::to_xvalue(*first)); // new (&*current) Tp (kerbal::compatibility::to_xvalue(*first));
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					throw;
				}
			}

#		endif

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator k_uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to, UI_MOV_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at(&*to, kerbal::compatibility::to_xvalue(*first)); // new (&*to) Tp (kerbal::compatibility::to_xvalue(*first));
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<value_type>
					>::value,
					detail::UI_MOV_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::UI_MOV_VER_NOTHROW_ITER_ADVANCE,
							detail::UI_MOV_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::UI_MOV_VER_NO_CATCH VER;

#	endif

			return detail::k_uninitialized_move(first, last, to, VER());
		}



	//==================
	// uninitialized_move_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_MOV_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_MOV_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_MOV_N_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to, UI_MOV_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::construct_at(&*current, kerbal::compatibility::to_xvalue(*first)); // new (&*current) Tp(kerbal::compatibility::to_xvalue(*first));
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					}
					throw;
				}
			}

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to, UI_MOV_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::construct_at(&*current, kerbal::compatibility::to_xvalue(*first)); // new (&*current) Tp(kerbal::compatibility::to_xvalue(*first));
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					throw;
				}
			}

#		endif

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator k_uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to, UI_MOV_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::construct_at(&*to, kerbal::compatibility::to_xvalue(*first)); // new (&*to) Tp (kerbal::compatibility::to_xvalue(*first));
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename SizeType, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<value_type>
					>::value,
					detail::UI_MOV_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::UI_MOV_N_VER_NOTHROW_ITER_ADVANCE,
							detail::UI_MOV_N_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::UI_MOV_N_VER_NO_CATCH VER;

#	endif

			return detail::k_uninitialized_move_n(first, n, to, VER());
		}



	//==================
	// uninitialized_fill

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_FILL_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_FILL_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_FILL_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR20
			void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value, UI_FILL_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (current != last) {
						iterator remain(current);
						kerbal::memory::construct_at(&*current, value); // new (&*current) Tp (value);
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR20
			void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value, UI_FILL_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (current != last) {
						kerbal::memory::construct_at(&*current, value); // new (&*current) Tp (value);
						++current;
					}
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR14
			void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value, UI_FILL_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at(&*first, value); // new (&*first) Tp (value);
					++first;
				}
			}

		} // namespace detail

		template <typename ForwardIterator, typename T>
		KERBAL_CONSTEXPR14
		void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<value_type>
					>::value,
					detail::UI_FILL_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::UI_FILL_VER_NOTHROW_ITER_ADVANCE,
							detail::UI_FILL_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::UI_FILL_VER_NO_CATCH VER;

#	endif

			detail::uninitialized_fill(first, last, value, VER());
		}



	//==================
	// uninitialized_fill_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_FILL_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_FILL_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_FILL_N_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value, UI_FILL_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::construct_at(&*current, value); // new (&*current) Tp(value);
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value, UI_FILL_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::construct_at(&*current, value); // new (&*current) Tp(value);
						++current;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR14
			ForwardIterator k_uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value, UI_FILL_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::construct_at(&*first, value); // new (&*first) Tp (value);
					++first;
				}
				return first;
			}

		} // namespace detail

		template <typename ForwardIterator, typename SizeType, typename T>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value)
		{

#	if __cpp_exceptions

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<value_type>
					>::value,
					detail::UI_FILL_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::UI_FILL_N_VER_NOTHROW_ITER_ADVANCE,
							detail::UI_FILL_N_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::UI_FILL_N_VER_NO_CATCH VER;

#	endif

			return detail::k_uninitialized_fill_n(first, n, value, VER());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_CONSTRUCT_HPP
