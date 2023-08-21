/**
 * @file       make_integer_sequence.integer_pack.part.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INTEGER_SEQUENCE_MAKE_INTEGER_SEQUENCE_INTEGER_PACK_PART_HPP
#define KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INTEGER_SEQUENCE_MAKE_INTEGER_SEQUENCE_INTEGER_PACK_PART_HPP

#include <kerbal/utility/integer_sequence/detail/cxx11/integer_sequence.part.hpp>


namespace kerbal
{

	namespace utility
	{

		template <typename T, T N>
		using make_integer_sequence = kerbal::utility::integer_sequence<T, __integer_pack(N)...>;

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INTEGER_SEQUENCE_MAKE_INTEGER_SEQUENCE_INTEGER_PACK_PART_HPP
