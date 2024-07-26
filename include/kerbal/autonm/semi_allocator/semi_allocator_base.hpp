/**
 * @file       semi_allocator_base.hpp
 * @brief
 * @date       2021-07-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_SEMI_ALLOCATOR_SEMI_ALLOCATOR_BASE_HPP
#define KERBAL_AUTONM_SEMI_ALLOCATOR_SEMI_ALLOCATOR_BASE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace autonm
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		class semi_allocator_base
		{
			public:
				typedef T					value_type;
				typedef value_type *		pointer;
				typedef std::size_t			size_type;

				KERBAL_CONSTEXPR14
				void destroy(pointer p) KERBAL_NOEXCEPT
				{
					// must be remained and keep empty, otherwise allocator_traits will
					// execute default destroy policy (aka kerbal::memory::destroy_at)
				}

		};

	} // namespace autonm

} // namespace kerbal


#endif // KERBAL_AUTONM_SEMI_ALLOCATOR_SEMI_ALLOCATOR_BASE_HPP
