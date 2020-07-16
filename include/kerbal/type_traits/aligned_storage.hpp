/**
 * @file       aligned_storage.hpp
 * @brief
 * @date       2019-4-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP
#define KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP

#include <kerbal/compatibility/alignas.hpp>

#include <cstddef>

namespace kerbal
{

	namespace type_traits
	{

		template <size_t Len, size_t Alignment>
		struct aligned_storage
		{
			union type
			{
				unsigned char _data[Len];

				struct KERBAL_ALIGNAS(Alignment)
				{
				} _align;
			};
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP
