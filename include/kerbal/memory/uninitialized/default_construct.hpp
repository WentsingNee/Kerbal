/**
 * @file       default_construct.hpp
 * @brief
 * @date       2021-03-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/uninitialized/destroy.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_default_constructible.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>

#include <cstddef>

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
		void uninitialized_default_construct(ForwardIterator first, ForwardIterator last);



	//==================
	// default_construct_at

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0>		DFT_CNSTRCT_AT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		DFT_CNSTRCT_AT_VER_TRIVIALLY;

#	if __cplusplus <= 201703L

			template <typename T>
			T * k_default_construct_at(T * p, DFT_CNSTRCT_AT_VER_DEFAULT)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(::new(const_cast<void *>(static_cast<const volatile void *>(p))) T)
				)
			{
				::new(const_cast<void *>(static_cast<const volatile void *>(p))) T;
				return p;
			}

#	else

			template <typename T>
			KERBAL_CONSTEXPR20
			T * k_default_construct_at(T * p, DFT_CNSTRCT_AT_VER_DEFAULT)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(std::construct_at(p))
				)
			{
				std::construct_at(p);
				return p;
			}

#	endif

			template <typename T, std::size_t N>
			KERBAL_CONSTEXPR20
			T (* k_default_construct_at(T (* p)[N], DFT_CNSTRCT_AT_VER_DEFAULT)) [N]
			{
				kerbal::memory::uninitialized_default_construct(*p + 0, *p + N);
				return p;
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			T * k_default_construct_at(T * p, DFT_CNSTRCT_AT_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
				return p;
			}

		} // namespace detail

		template <typename T>
		struct default_construct_at_overload_version :
			kerbal::type_traits::conditional<
				kerbal::type_traits::try_test_is_trivially_default_constructible<T>::IS_TRUE::value,
				detail::DFT_CNSTRCT_AT_VER_TRIVIALLY,
				detail::DFT_CNSTRCT_AT_VER_DEFAULT
			>::type
		{
		};

		template <typename T>
		KERBAL_CONSTEXPR14
		T * default_construct_at(T * p)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(detail::k_default_construct_at(p, default_construct_at_overload_version<T>()))
			)
		{
			return detail::k_default_construct_at(p, default_construct_at_overload_version<T>());
		}



	//==================
	// uninitialized_default_construct

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_DFT_CONSTRUCT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_DFT_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_DFT_CONSTRUCT_VER_NO_CATCH;
			typedef kerbal::type_traits::integral_constant<int, 3> UI_DFT_CONSTRUCT_VER_TRIVIALLY;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void
			k_uninitialized_default_construct(
				ForwardIterator first, ForwardIterator last,
				UI_DFT_CONSTRUCT_VER_DEFAULT
			)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (current != last) {
						iterator remain(current);
						kerbal::memory::default_construct_at(&*current); // new (&*current) T;
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
			void
			k_uninitialized_default_construct(
				ForwardIterator first, ForwardIterator last,
				UI_DFT_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE
			)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (current != last) {
						kerbal::memory::default_construct_at(&*current); // new (&*current) T;
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
			void
			k_uninitialized_default_construct(
				ForwardIterator first, ForwardIterator last,
				UI_DFT_CONSTRUCT_VER_NO_CATCH
			)
			{
				while (first != last) {
					kerbal::memory::default_construct_at(&*first); // new (&*first) T;
					++first;
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void
			k_uninitialized_default_construct(
				ForwardIterator /*first*/, ForwardIterator /*last*/,
				UI_DFT_CONSTRUCT_VER_TRIVIALLY
			)
			{
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_default_construct(ForwardIterator first, ForwardIterator last)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef typename kerbal::type_traits::conditional<
				kerbal::type_traits::try_test_is_trivially_default_constructible<value_type>::IS_TRUE::value,
				detail::UI_DFT_CONSTRUCT_VER_TRIVIALLY,
				typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::UI_DFT_CONSTRUCT_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
						detail::can_be_nothrow_advance_iterator<iterator>::value,
						detail::UI_DFT_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE,
						detail::UI_DFT_CONSTRUCT_VER_DEFAULT
					>::type
				>::type
			>::type VER;

#	else

			typedef typename kerbal::type_traits::conditional<
				kerbal::type_traits::try_test_is_trivially_default_constructible<value_type>::IS_TRUE::value,
				detail::UI_DFT_CONSTRUCT_VER_TRIVIALLY,
				detail::UI_DFT_CONSTRUCT_VER_NO_CATCH
			>::type VER;

#	endif

			detail::k_uninitialized_default_construct(first, last, VER());
		}



	//==================
	// uninitialized_default_construct_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_DFT_CONSTRUCT_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_DFT_CONSTRUCT_N_VER_NO_CATCH;
			typedef kerbal::type_traits::integral_constant<int, 3> UI_DFT_CONSTRUCT_N_VER_TRIVIALLY;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator
			k_uninitialized_default_construct_n(
				ForwardIterator first, SizeType n,
				UI_DFT_CONSTRUCT_N_VER_DEFAULT
			)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::default_construct_at(&*current); // new (&*current) T;
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
			ForwardIterator
			k_uninitialized_default_construct_n(
				ForwardIterator first, SizeType n,
				UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE
			)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::default_construct_at(&*current); // new (&*current) T;
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
			ForwardIterator
			k_uninitialized_default_construct_n(
				ForwardIterator first, SizeType n,
				UI_DFT_CONSTRUCT_N_VER_NO_CATCH
			)
			{
				while (n > 0) {
					--n;
					kerbal::memory::default_construct_at(&*first); // new (&*first) T;
					++first;
				}
				return first;
			}

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator
			k_uninitialized_default_construct_n(
				ForwardIterator first, SizeType n,
				UI_DFT_CONSTRUCT_N_VER_TRIVIALLY
			)
			{
				return kerbal::iterator::next(first, n);
			}

		} // namespace detail

		template <typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_default_construct_n(ForwardIterator first, SizeType n)
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef typename kerbal::type_traits::conditional<
				kerbal::type_traits::try_test_is_trivially_default_constructible<value_type>::IS_TRUE::value,
				detail::UI_DFT_CONSTRUCT_N_VER_TRIVIALLY,
				typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::UI_DFT_CONSTRUCT_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
						detail::can_be_nothrow_advance_iterator<iterator>::value,
						detail::UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE,
						detail::UI_DFT_CONSTRUCT_N_VER_DEFAULT
					>::type
				>::type
			>::type VER;

#	else

			typedef typename kerbal::type_traits::conditional<
				kerbal::type_traits::try_test_is_trivially_default_constructible<value_type>::IS_TRUE::value,
				detail::UI_DFT_CONSTRUCT_N_VER_TRIVIALLY,
				detail::UI_DFT_CONSTRUCT_N_VER_NO_CATCH
			>::type VER;

#	endif

			return detail::k_uninitialized_default_construct_n(first, n, VER());
		}


	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
