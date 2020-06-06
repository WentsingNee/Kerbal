/**
 * @file       integer_sequence.hpp
 * @brief
 * @date       2020-6-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_INTEGER_SEQUENCE_HPP
#define KERBAL_UTILITY_INTEGER_SEQUENCE_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support \
for the ISO C++ 2011 standard.
#endif

#include <type_traits>

#include <cstddef>

namespace kerbal
{

	namespace utility
	{

		template <typename T, T ... Ints>
		struct integer_sequence
		{
				typedef T value_type;

				constexpr
				static size_t size() noexcept
				{
					return sizeof...(Ints);
				}
		};

		namespace detail
		{

			template <typename T, typename Seq, T i>
			struct concat_integer_sequence;

			template <typename T, T i, T ... Ints>
			struct concat_integer_sequence<T, integer_sequence<T, Ints...>, i>
			{
					typedef integer_sequence<T, Ints..., i> type;
			};

			template <typename T, T N>
			struct make_integer_sequence_helper;


			template <typename T, T N, bool end_of_loop>
			struct make_integer_sequence_helper_loop;

			template <typename T, T N>
			struct make_integer_sequence_helper_loop<T, N, false>
			{
					typedef typename concat_integer_sequence<
							T, typename make_integer_sequence_helper<T, N - 1>::type, N - 1
					>::type type;
			};

			template <typename T, T N>
			struct make_integer_sequence_helper_loop<T, N, true>
			{
					typedef integer_sequence<T, 0> type;
			};

			template <typename T, T N>
			struct make_integer_sequence_helper: make_integer_sequence_helper_loop<T, N, N == 1>
			{
			};

		} // namespace detail

		template <size_t ... Ints>
		using index_sequence = kerbal::utility::integer_sequence<size_t, Ints...>;

		template <typename T, T N>
		using make_integer_sequence = typename kerbal::utility::detail::make_integer_sequence_helper<T, N>::type;

		template <size_t N>
		using make_index_sequence = kerbal::utility::make_integer_sequence<size_t, N>;

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_INTEGER_SEQUENCE_HPP
