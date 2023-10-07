/**
 * @file       make_index_sequence.part.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @remark     move from kerbal/utility/integer_sequence.hpp, 2023-08-25
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INDEX_SEQUENCE_PART_HPP
#define KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INDEX_SEQUENCE_PART_HPP

#include <kerbal/utility/integer_sequence/detail/cxx11/make_integer_sequence.part.hpp>

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

		template <std::size_t N>
		using make_index_sequence = kerbal::utility::make_integer_sequence<std::size_t, N>;

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_MAKE_INDEX_SEQUENCE_PART_HPP
