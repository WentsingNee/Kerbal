/**
 * @file       make_integer_sequence.default.part.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INTEGER_SEQUENCE_MAKE_INTEGER_SEQUENCE_DEFAULT_PART_HPP
#define KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INTEGER_SEQUENCE_MAKE_INTEGER_SEQUENCE_DEFAULT_PART_HPP

#include <kerbal/utility/integer_sequence/detail/cxx11/integer_sequence.part.hpp>


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename T, typename Seq, T i>
			struct concat_integer_sequence;

			template <typename T, T i, T ... Ints>
			struct concat_integer_sequence<T, kerbal::utility::integer_sequence<T, Ints...>, i>
			{
					typedef kerbal::utility::integer_sequence<T, Ints..., i> type;
			};

			template <typename T, T N>
			struct make_integer_sequence_helper;


			template <typename T, T N, bool end_of_loop>
			struct make_integer_sequence_helper_loop;

			template <typename T, T N>
			struct make_integer_sequence_helper_loop<T, N, false> :
					kerbal::utility::detail::concat_integer_sequence<
						T, typename kerbal::utility::detail::make_integer_sequence_helper<T, N - 1>::type, N - 1
					>
			{
			};

			template <typename T, T N>
			struct make_integer_sequence_helper_loop<T, N, true>
			{
					typedef kerbal::utility::integer_sequence<T> type;
			};

			template <typename T, T N>
			struct make_integer_sequence_helper: kerbal::utility::detail::make_integer_sequence_helper_loop<T, N, N == 0>
			{
			};

		} // namespace detail

		template <typename T, T N>
		using make_integer_sequence = typename kerbal::utility::detail::make_integer_sequence_helper<T, N>::type;

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INTEGER_SEQUENCE_MAKE_INTEGER_SEQUENCE_DEFAULT_PART_HPP
