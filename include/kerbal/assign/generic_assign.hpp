/**
 * @file       generic_assign.hpp
 * @brief
 * @date       2020-6-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ASSIGN_GENERIC_ASSIGN_HPP
#define KERBAL_ASSIGN_GENERIC_ASSIGN_HPP

#include <kerbal/assign/generic_assign/generic_assign.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/extent.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_array.hpp>
#include <kerbal/type_traits/logical.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/remove_reference.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace assign
	{

		namespace detail
		{

			template <typename InputIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			void copy(InputIterator first, InputIterator last, OutputIterator out);

			template <typename InputIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			void k_copy(
				InputIterator first, InputIterator last, OutputIterator out,
				kerbal::type_traits::false_type
			)
			{
				while (first != last) {
					kerbal::assign::generic_assign(*out, *first);
					++first;
					++out;
				}
			}

			template <typename InputIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			void k_copy(
				InputIterator first, InputIterator last, OutputIterator out,
				kerbal::type_traits::true_type
			)
			{
				typedef InputIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type array_type;
				typedef kerbal::type_traits::extent<array_type> extent;

				copy(&((*first)[0]), &((*(last - 1))[extent::value - 1]) + 1, &((*out)[0]));
			}

			template <typename InputIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			void copy(InputIterator first, InputIterator last, OutputIterator out)
			{
				typedef typename kerbal::iterator::iterator_traits<InputIterator>::value_type input_value_type;
				typedef typename kerbal::iterator::iterator_traits<OutputIterator>::value_type output_value_type;
				typedef kerbal::type_traits::extent<input_value_type> input_extent;
				typedef kerbal::type_traits::extent<output_value_type> output_extent;
				KERBAL_STATIC_ASSERT(
					input_extent::value == output_extent::value,
					"input and output must have same length"
				);

				typedef kerbal::type_traits::conjunction<
					kerbal::iterator::is_contiguous_iterator<InputIterator>,
					kerbal::iterator::is_contiguous_iterator<OutputIterator>,
					kerbal::type_traits::is_array<input_value_type>,
					kerbal::type_traits::is_array<output_value_type>
				> EXPAND;
				k_copy(first, last, out, EXPAND());
			}

		} // namespace detail


		template <typename T, typename U>
		KERBAL_CONSTEXPR14
		T & generic_assign(T & lhs, const U & rhs)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(lhs = rhs)
			)
		{
			lhs = rhs;
			return lhs;
		}

		template <typename T, typename U, std::size_t N>
		KERBAL_CONSTEXPR14
		T (& generic_assign(T (& lhs)[N], const U (& rhs)[N]))[N]
		{
//			for (std::size_t i = 0; i < N; ++i) {
//				kerbal::assign::generic_assign(lhs[i], rhs[i]);
//			}
			kerbal::assign::detail::copy(rhs + 0, rhs + N, lhs + 0);
			return lhs;
		}

#	if __cplusplus >= 201103L

		namespace detail
		{

			template <typename T, typename U>
			KERBAL_CONSTEXPR14
			void k_generic_assign(T & lhs, U && rhs, kerbal::type_traits::false_type)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(lhs = kerbal::utility::forward<U>(rhs))
				)
			{
				lhs = kerbal::utility::forward<U>(rhs);
			}

			template <typename T, typename U>
			KERBAL_CONSTEXPR14
			void k_generic_assign(T & lhs, U && rhs, kerbal::type_traits::true_type)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(
						kerbal::assign::generic_assign(
							lhs[0],
							kerbal::utility::forward<decltype(rhs[0])>(rhs[0])
						)
					)
				)
			{
				typedef kerbal::type_traits::extent<T, 0> TP_EXTENT;
				typedef kerbal::type_traits::extent<
					typename kerbal::type_traits::remove_reference<U>::type, 0
				> UP_EXTENT;
				KERBAL_STATIC_ASSERT(TP_EXTENT::value == UP_EXTENT::value, "T and U must have same length");
				for (std::size_t i = 0; i < TP_EXTENT::value; ++i) {
					kerbal::assign::generic_assign(
						lhs[i],
						kerbal::utility::forward<decltype(rhs[i])>(rhs[i])
					);
				}
			}

		} // namespace detail

		template <typename T, typename U>
		KERBAL_CONSTEXPR14
		T & generic_assign(T & lhs, U && rhs)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(
					kerbal::assign::detail::k_generic_assign(
						lhs, kerbal::utility::forward<U>(rhs), kerbal::type_traits::is_array<T>()
					)
				)
			)
		{
			kerbal::assign::detail::k_generic_assign(
				lhs,
				kerbal::utility::forward<U>(rhs),
				kerbal::type_traits::is_array<T>()
			);
			return lhs;
		}

#	endif

	} // namespace assign

} // namespace kerbal

#endif // KERBAL_ASSIGN_GENERIC_ASSIGN_HPP
