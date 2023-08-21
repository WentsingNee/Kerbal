/**
 * @file       integer_sequence.part.hpp
 * @brief
 * @date       2023-08-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_INTEGER_SEQUENCE_PART_HPP
#define KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_INTEGER_SEQUENCE_PART_HPP

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
				static std::size_t size() noexcept
				{
					return sizeof...(Ints);
				}
		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_INTEGER_SEQUENCE_DETAIL_CXX11_INTEGER_SEQUENCE_PART_HPP
