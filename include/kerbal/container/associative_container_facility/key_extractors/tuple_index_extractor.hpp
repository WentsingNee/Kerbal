/**
 * @file       tuple_index_extractor.hpp
 * @brief
 * @date       2023-11-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_TUPLE_INDEX_EXTRACTOR_HPP
#define KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_TUPLE_INDEX_EXTRACTOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/utility/tuple.hpp> // fwd

#include <tuple>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		template <typename Tuple, std::size_t I>
		struct tuple_index_extractor
		{
			typedef Tuple value_type;
			typedef typename std::tuple_element<I, value_type>::type key_type;

			KERBAL_CONSTEXPR
			auto & operator()(Tuple & tuple) const
			{
				return std::get<I>(tuple);
			}
		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_TUPLE_INDEX_EXTRACTOR_HPP
