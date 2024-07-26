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

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/alignas.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		KERBAL_MODULE_EXPORT
		template <std::size_t Len, std::size_t Alignment>
		struct aligned_storage
		{
				union type
				{
						unsigned char k_data[Len];

						struct KERBAL_ALIGNAS(Alignment)
						{
						} k_align;
				};
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_ALIGNED_STORAGE_HPP
