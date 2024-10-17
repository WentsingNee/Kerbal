/**
 * @file       map_data_iterator_traits.hpp
 * @brief
 * @date       2024-10-17
 * @author     peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_MAP_DATA_ITERATOR_TRAITS_HPP
#define KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_MAP_DATA_ITERATOR_TRAITS_HPP

#include <kerbal/type_traits/remove_const.hpp>
#include <kerbal/iterator/iterator_traits.hpp>


#if __cplusplus >= 201703L
#	include <tuple>
#endif


namespace kerbal
{

	namespace container
	{

		template <typename InputIterator>
		struct map_data_iterator_traits
		{
			private:
				typedef typename kerbal::iterator::iterator_traits<InputIterator>::value_type k_entity_type;

			public:
				typedef typename kerbal::type_traits::remove_const<
					typename std::tuple_element<0, k_entity_type>::type
				>::type key_type;

				typedef std::tuple_element<1, k_entity_type> mapped_type;
		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_MAP_DATA_ITERATOR_TRAITS_HPP
