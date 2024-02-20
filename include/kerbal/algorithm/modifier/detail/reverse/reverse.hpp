/**
 * @file       reverse.hpp
 * @brief
 * @date       2024-02-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_HPP
#define KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_HPP

#if __AVX2__
#	include <kerbal/algorithm/modifier/detail/reverse/reverse.avx2.hpp>
#endif

#if __SSSE3__
#	include <kerbal/algorithm/modifier/detail/reverse/reverse.ssse3.hpp>
#endif

#if __SSE2__
#	include <kerbal/algorithm/modifier/detail/reverse/reverse.sse2.hpp>
#endif

#include <kerbal/algorithm/modifier/detail/reverse/reverse.plain.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_arithmetic.hpp>

#include <cstddef>


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			inline
			void k_reverse_width_dispatch(void * first, void * last, kerbal::type_traits::integral_constant<std::size_t, 1>) KERBAL_NOEXCEPT
			{
				typedef kerbal::compatibility::uint8_t * iterator;
				iterator rfirst = reinterpret_cast<iterator>(first);
				iterator rlast = reinterpret_cast<iterator>(last);

#			if 0
				// pass
#			elif __AVX2__
				kerbal::algorithm::detail::avx2::reverse(rfirst, rlast);
#			else
				kerbal::algorithm::detail::plain::reverse(rfirst, rlast);
#			endif

			}

			inline
			void k_reverse_width_dispatch(void * first, void * last, kerbal::type_traits::integral_constant<std::size_t, 2>) KERBAL_NOEXCEPT
			{
				typedef kerbal::compatibility::uint16_t * iterator;
				iterator rfirst = reinterpret_cast<iterator>(first);
				iterator rlast = reinterpret_cast<iterator>(last);

#			if 0
				// pass
#			elif __AVX2__
				kerbal::algorithm::detail::avx2::reverse(rfirst, rlast);
#			elif __SSSE3__
				kerbal::algorithm::detail::ssse3::reverse(rfirst, rlast);
#			elif __SSE2__
				kerbal::algorithm::detail::sse2::reverse(rfirst, rlast);
#			else
				kerbal::algorithm::detail::plain::reverse(rfirst, rlast);
#			endif

			}

			inline
			void k_reverse_width_dispatch(void * first, void * last, kerbal::type_traits::integral_constant<std::size_t, 4>) KERBAL_NOEXCEPT
			{
				typedef kerbal::compatibility::uint32_t * iterator;
				iterator rfirst = reinterpret_cast<iterator>(first);
				iterator rlast = reinterpret_cast<iterator>(last);

#			if 0
				// pass
#			elif __AVX2__
				kerbal::algorithm::detail::avx2::reverse(rfirst, rlast);
#			elif __SSE2__
				kerbal::algorithm::detail::sse2::reverse(rfirst, rlast);
#			else
				kerbal::algorithm::detail::plain::reverse(rfirst, rlast);
#			endif

			}

			inline
			void k_reverse_width_dispatch(void * first, void * last, kerbal::type_traits::integral_constant<std::size_t, 8>) KERBAL_NOEXCEPT
			{
				typedef kerbal::compatibility::uint64_t * iterator;
				iterator rfirst = reinterpret_cast<iterator>(first);
				iterator rlast = reinterpret_cast<iterator>(last);

#			if 0
				// pass
#			elif __AVX2__
				kerbal::algorithm::detail::avx2::reverse(rfirst, rlast);
#			else
				kerbal::algorithm::detail::plain::reverse(rfirst, rlast);
#			endif

			}

			template <typename ContiguousIterator>
			void k_reverse_width_dispatch(ContiguousIterator first, ContiguousIterator last)
			{
				typedef ContiguousIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				k_reverse_width_dispatch(first, last, kerbal::type_traits::integral_constant<std::size_t, sizeof(value_type)>());
			}



			template <typename ContiguousIterator, typename T>
			void k_reverse_type_dispatch(ContiguousIterator first, ContiguousIterator last, kerbal::type_traits::false_type)
			{
				kerbal::algorithm::detail::plain::reverse(first, last);
			}

			template <typename ContiguousIterator>
			void k_reverse_type_dispatch(ContiguousIterator first, ContiguousIterator last, kerbal::type_traits::true_type)
			{
				k_reverse_width_dispatch(first, last);
			}

			template <typename ContiguousIterator>
			void k_reverse_type_dispatch(ContiguousIterator first, ContiguousIterator last)
			{
				typedef ContiguousIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				k_reverse_type_dispatch(first, last, kerbal::type_traits::is_arithmetic<value_type>());
			}



			template <typename BidirectionalIterator>
			void k_reverse_itercate_dispatch(BidirectionalIterator first, BidirectionalIterator last, kerbal::type_traits::false_type)
			{
				kerbal::algorithm::detail::plain::reverse(first, last);
			}

			template <typename RandomAccessIterator>
			void k_reverse_itercate_dispatch(RandomAccessIterator first, RandomAccessIterator last, kerbal::type_traits::true_type)
			{
				kerbal::algorithm::detail::k_reverse_type_dispatch(first, last);
			}

			template <typename BidirectionalIterator>
			void k_reverse_itercate_dispatch(BidirectionalIterator first, BidirectionalIterator last)
			{
				typedef BidirectionalIterator iterator;
				kerbal::algorithm::detail::k_reverse_itercate_dispatch(first, last, kerbal::iterator::is_contiguous_iterator<iterator>());
			}



			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void k_reverse_consteval_dispatch(BidirectionalIterator first, BidirectionalIterator last)
			{

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT

				if (KERBAL_IS_CONSTANT_EVALUATED()) {
					kerbal::algorithm::detail::plain::reverse(first, last);
				} else {
					kerbal::algorithm::detail::k_reverse_itercate_dispatch(first, last);
				}

#		else
				kerbal::algorithm::detail::k_reverse_itercate_dispatch(first, last);
#		endif

			}

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_DETAIL_REVERSE_REVERSE_HPP
