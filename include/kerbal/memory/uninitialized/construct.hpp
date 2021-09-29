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
#include <kerbal/memory/uninitialized/destroy.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/conditional.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus > 201703L
#	include <memory>
#endif


namespace kerbal
{

	namespace memory
	{

	//==================
	// forward declare

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void uninitialized_value_construct(ForwardIterator first, ForwardIterator last);

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR20
		ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to);

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR20
		ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to);



#	if __cplusplus < 201103L

#	define _construct_at_body(p, ...) \
		do { \
			::new (const_cast<void*>(static_cast<const volatile void*>(p))) Tp (__VA_ARGS__); \
			return p; \
		} while (false)

		template <typename Tp>
		Tp * construct_at(Tp * p)
		{
			_construct_at_body(p);
		}

		template <typename Tp, typename Arg0>
		Tp * construct_at(Tp * p, const Arg0 & arg0)
		{
			_construct_at_body(p, arg0);
		}

		template <typename Tp, typename Arg0, typename Arg1>
		Tp * construct_at(Tp * p, const Arg0 & arg0, const Arg1 & arg1)
		{
			_construct_at_body(p, arg0, arg1);
		}

		template <typename Tp, typename Arg0, typename Arg1, typename Arg2>
		Tp * construct_at(Tp * p, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
		{
			_construct_at_body(p, arg0, arg1, arg2);
		}

		template <typename Tp, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
		Tp * construct_at(Tp * p, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3)
		{
			_construct_at_body(p, arg0, arg1, arg2, arg3);
		}

		template <typename Tp, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		Tp * construct_at(Tp * p, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4)
		{
			_construct_at_body(p, arg0, arg1, arg2, arg3, arg4);
		}

#	undef _construct_at_body


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
			Tp * _K_construct_at_impl(CONSTRUCT_AT_VER_DEFAULT, Tp * p, Args&& ... args)
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
			Tp * _K_construct_at_impl(CONSTRUCT_AT_VER_TRIVIAL, Tp * p, Args&& ... args) KERBAL_NOEXCEPT
			{
				*p = Tp(kerbal::utility::forward<Args>(args)...);
				return p;
			}

			template <typename Tp, typename ... Args>
			struct construct_at_impl_overload_ver
			{
					typedef typename kerbal::type_traits::conditional<
						(
							std::is_trivially_constructible<Tp, Args...>::value &&
							std::is_trivially_move_assignable<Tp>::value &&
							std::is_trivially_destructible<Tp>::value
						),
						CONSTRUCT_AT_VER_TRIVIAL,
						CONSTRUCT_AT_VER_DEFAULT
					>::type type;
			};

			template <typename Tp, typename ... Args>
			KERBAL_CONSTEXPR14
			Tp * _K_construct_at(Tp * p, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(_K_construct_at_impl(
							typename construct_at_impl_overload_ver<Tp, Args...>::type(),
							p, kerbal::utility::forward<Args>(args)...))
					)
			{
				typedef typename construct_at_impl_overload_ver<Tp, Args...>::type VER;
				return _K_construct_at_impl(VER(), p, kerbal::utility::forward<Args>(args)...);
			}

#	else

			template <typename Tp, typename ... Args>
			KERBAL_CONSTEXPR20
			Tp * _K_construct_at(Tp * p, Args&& ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(std::construct_at(p, kerbal::utility::forward<Args>(args)...))
					)
			{
				return std::construct_at(p, kerbal::utility::forward<Args>(args)...);
			}

#	endif // C++20


			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR20
			Tp (* _K_construct_at(Tp (*p) [N])) [N]
			{
				kerbal::memory::uninitialized_value_construct(*p, *p + N);
				return p;
			}


			template <typename Tp, typename Up, std::size_t N>
			KERBAL_CONSTEXPR20
			Tp (* _K_construct_at(Tp (*p) [N], Up (&&val) [N])) [N]
			{
				kerbal::memory::uninitialized_move(val + 0, val + N, *p + 0);
				return p;
			}


			template <typename Tp, typename Up, std::size_t N>
			KERBAL_CONSTEXPR20
			Tp (* _K_construct_at(Tp (*p) [N], Up (&val) [N])) [N]
			{
				kerbal::memory::uninitialized_copy(val + 0, val + N, *p + 0);
				return p;
			}


		} // namespace detail


		template <typename Tp, typename ... Args>
		KERBAL_CONSTEXPR14
		Tp * construct_at(Tp * p, Args&& ... args)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(detail::_K_construct_at(p, kerbal::utility::forward<Args>(args)...))
				)
		{
			return detail::_K_construct_at(p, kerbal::utility::forward<Args>(args)...);
		}

#	endif // __cplusplus >= 201103L



	//==================
	// uninitialized_value_construct

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_VAL_CONSTRUCT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_VAL_CONSTRUCT_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void _K_uninitialized_value_construct(ForwardIterator first, ForwardIterator last, UI_VAL_CONSTRUCT_VER_DEFAULT)
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

#		endif

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void _K_uninitialized_value_construct(ForwardIterator first, ForwardIterator last, UI_VAL_CONSTRUCT_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at(&*first); // new (&*first) Tp ();
					++first;
				}
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR20
		void uninitialized_value_construct(ForwardIterator first, ForwardIterator last)
		{

#	if __cpp_exceptions
			typedef detail::UI_VAL_CONSTRUCT_VER_DEFAULT VER;
#	else
			typedef detail::UI_VAL_CONSTRUCT_VER_NO_CATCH VER;
#	endif

			detail::_K_uninitialized_value_construct(first, last, VER());
		}



	//==================
	// uninitialized_value_construct_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_VAL_CONSTRUCT_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_VAL_CONSTRUCT_N_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_value_construct_n(ForwardIterator first, SizeType n, UI_VAL_CONSTRUCT_N_VER_DEFAULT)
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

#		endif

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_value_construct_n(ForwardIterator first, SizeType n, UI_VAL_CONSTRUCT_N_VER_NO_CATCH)
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
		KERBAL_CONSTEXPR20
		ForwardIterator uninitialized_value_construct_n(ForwardIterator first, SizeType n)
		{

#	if __cpp_exceptions
			typedef detail::UI_VAL_CONSTRUCT_N_VER_DEFAULT VER;
#	else
			typedef detail::UI_VAL_CONSTRUCT_N_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_value_construct_n(first, n, VER());
		}



	//==================
	// uninitialized_copy

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_CPY_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_CPY_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to, UI_CPY_VER_DEFAULT)
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
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					}
					throw;
				}
				return current;
			}

#		endif

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to, UI_CPY_VER_NO_CATCH)
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
		KERBAL_CONSTEXPR20
		ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to)
		{

#	if __cpp_exceptions
			typedef detail::UI_CPY_VER_DEFAULT VER;
#	else
			typedef detail::UI_CPY_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_copy(first, last, to, VER());
		}



	//==================
	// uninitialized_copy_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_CPY_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_CPY_N_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to, UI_CPY_N_VER_DEFAULT)
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

#		endif

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to, UI_CPY_N_VER_NO_CATCH)
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
		KERBAL_CONSTEXPR20
		ForwardIterator uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to)
		{

#	if __cpp_exceptions
			typedef detail::UI_CPY_N_VER_DEFAULT VER;
#	else
			typedef detail::UI_CPY_N_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_copy_n(first, n, to, VER());
		}



	//==================
	// uninitialized_move

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_MOV_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_MOV_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to, UI_MOV_VER_DEFAULT)
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
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(to, current);
					}
					throw;
				}
				return current;
			}

#		endif

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to, UI_MOV_VER_NO_CATCH)
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
		KERBAL_CONSTEXPR20
		ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to)
		{

#	if __cpp_exceptions
			typedef detail::UI_MOV_VER_DEFAULT VER;
#	else
			typedef detail::UI_MOV_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_move(first, last, to, VER());
		}



	//==================
	// uninitialized_move_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_MOV_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_MOV_N_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to, UI_MOV_N_VER_DEFAULT)
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

#		endif

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to, UI_MOV_N_VER_NO_CATCH)
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
		KERBAL_CONSTEXPR20
		ForwardIterator uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to)
		{

#	if __cpp_exceptions
			typedef detail::UI_MOV_N_VER_DEFAULT VER;
#	else
			typedef detail::UI_MOV_N_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_move_n(first, n, to, VER());
		}



	//==================
	// uninitialized_fill

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_FILL_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_FILL_VER_NO_CATCH;

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

#		endif

			template <typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR20
			void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value, UI_FILL_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::construct_at(&*first, value); // new (&*first) Tp (value);
					++first;
				}
			}

		} // namespace detail

		template <typename ForwardIterator, typename T>
		KERBAL_CONSTEXPR20
		void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value)
		{

#	if __cpp_exceptions
			typedef detail::UI_FILL_VER_DEFAULT VER;
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
			typedef kerbal::type_traits::integral_constant<int, 1> UI_FILL_N_VER_NO_CATCH;

#		if __cpp_exceptions

			template <typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value, UI_FILL_N_VER_DEFAULT)
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

#		endif

			template <typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value, UI_FILL_N_VER_NO_CATCH)
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
		KERBAL_CONSTEXPR20
		ForwardIterator uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value)
		{

#	if __cpp_exceptions
			typedef detail::UI_FILL_N_VER_DEFAULT VER;
#	else
			typedef detail::UI_FILL_N_VER_NO_CATCH VER;
#	endif

			return detail::_K_uninitialized_fill_n(first, n, value, VER());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_CONSTRUCT_HPP
