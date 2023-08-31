/**
 * @file       uninitialized_copy_n.hpp
 * @brief
 * @date       2023-10-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_COPY_N_HPP
#define KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_COPY_N_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/memory/uninitialized/construct_at.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if KERBAL_HAS_EXCEPTIONS_SUPPORT
#	include <kerbal/memory/detail/can_be_nothrow_advance_iterator.hpp>

#	include <kerbal/iterator/iterator_traits.hpp>
#	include <kerbal/memory/uninitialized/destroy_on.hpp>
#	include <kerbal/memory/uninitialized/uninitialized_transaction_failed_destroy.hpp>
#	include <kerbal/type_traits/conditional.hpp>
#	include <kerbal/type_traits/is_trivially_destructible.hpp>
#	include <kerbal/type_traits/tribool_constant.hpp>
#endif


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_CPY_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_CPY_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_CPY_N_VER_NO_CATCH;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

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
						kerbal::memory::construct_at(&*current, *first); // new (&*current) T(*first);
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
						kerbal::memory::construct_at(&*current, *first); // new (&*current) T(*first);
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
					kerbal::memory::construct_at(&*to, *first); // new (&*to) T (*first);
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

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					kerbal::memory::detail::UI_CPY_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
						kerbal::memory::detail::can_be_nothrow_advance_iterator<iterator>::value,
						kerbal::memory::detail::UI_CPY_N_VER_NOTHROW_ITER_ADVANCE,
						kerbal::memory::detail::UI_CPY_N_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef kerbal::memory::detail::UI_CPY_N_VER_NO_CATCH VER;

#	endif

			return kerbal::memory::detail::k_uninitialized_copy_n(first, n, to, VER());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_COPY_N_HPP
