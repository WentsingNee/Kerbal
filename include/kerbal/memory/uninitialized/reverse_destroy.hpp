/**
 * @file       reverse_destroy.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_REVERSE_DESTROY_HPP
#define KERBAL_MEMORY_UNINITIALIZED_REVERSE_DESTROY_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/uninitialized/destroy_on.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0>		RE_DESTROY_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		RE_DESTROY_VER_TRIVIALLY;

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR20
			void reverse_destroy_impl(BidirectionalIterator first, BidirectionalIterator last, RE_DESTROY_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				while (first != last) {
					--last;
					kerbal::memory::destroy_on(*last);
				}
			}

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void reverse_destroy_impl(BidirectionalIterator /*first*/, BidirectionalIterator /*last*/, RE_DESTROY_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
			}

			template <typename T>
			struct reverse_destroy_overload_version:
					kerbal::type_traits::conditional<
						kerbal::type_traits::try_test_is_trivially_destructible<T>::IS_TRUE::value,
						RE_DESTROY_VER_TRIVIALLY,
						RE_DESTROY_VER_DEFAULT
					>::type
			{
			};

		} // namespace detail

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void reverse_destroy(BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef kerbal::memory::detail::reverse_destroy_overload_version<value_type> VER;
			kerbal::memory::detail::reverse_destroy_impl(first, last, VER());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_REVERSE_DESTROY_HPP
