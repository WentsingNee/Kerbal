/**
 * @file       size_compressed_type.hpp
 * @brief
 * @date       2023-12-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_SIZE_COMPRESSED_TYPE_HPP
#define KERBAL_TYPE_TRAITS_SIZE_COMPRESSED_TYPE_HPP

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/numeric/numeric_limits.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		template <std::size_t N>
		struct size_compressed_type
		{
				typedef typename
				kerbal::type_traits::conditional<
					N <= kerbal::numeric::numeric_limits<unsigned short>::MAX::value,
					unsigned short,
					typename kerbal::type_traits::conditional<
						N <= kerbal::numeric::numeric_limits<unsigned int>::MAX::value,
						unsigned int,
						std::size_t
					>::type
				>::type type;
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_SIZE_COMPRESSED_TYPE_HPP
