/**
 * @file       destroy.hpp
 * @brief
 * @date       2021-03-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DESTROY_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DESTROY_HPP

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

			typedef kerbal::type_traits::integral_constant<int, 0>		DESTROY_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		DESTROY_VER_TRIVIALLY;

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void destroy_impl(ForwardIterator first, ForwardIterator last, DESTROY_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				while (first != last) {
					kerbal::memory::destroy_on(*first);
					++first;
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void destroy_impl(ForwardIterator /*first*/, ForwardIterator /*last*/, DESTROY_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
			}

			template <typename T>
			struct destroy_overload_version:
					kerbal::type_traits::conditional<
						kerbal::type_traits::try_test_is_trivially_destructible<T>::IS_TRUE::value,
						DESTROY_VER_TRIVIALLY,
						DESTROY_VER_DEFAULT
					>::type
			{
			};

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void destroy(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			kerbal::memory::detail::destroy_impl(first, last, kerbal::memory::detail::destroy_overload_version<value_type>());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DESTROY_HPP
