/**
 * @file       destroy_n.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DESTROY_N_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DESTROY_N_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
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

			typedef kerbal::type_traits::integral_constant<int, 0>		DESTROY_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		DESTROY_N_VER_TRIVIALLY;

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator destroy_n_impl(ForwardIterator first, SizeType n, DESTROY_N_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				while (n > 0) {
					--n;
					kerbal::memory::destroy_on(*first);
					++first;
				}
				return first;
			}

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator destroy_n_impl(ForwardIterator first, SizeType n, DESTROY_N_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(first, n);
			}

			template <typename T>
			struct destroy_n_overload_version:
					kerbal::type_traits::conditional<
						kerbal::type_traits::try_test_is_trivially_destructible<T>::IS_TRUE::value,
						DESTROY_N_VER_TRIVIALLY,
						DESTROY_N_VER_DEFAULT
					>::type
			{
			};

		} // namespace detail

		template <typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator destroy_n(ForwardIterator first, SizeType n) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return kerbal::memory::detail::destroy_n_impl(first, n, kerbal::memory::detail::destroy_n_overload_version<value_type>());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DESTROY_N_HPP
