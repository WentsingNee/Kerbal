/**
 * @file       discard_deallocate_semi_allocator.hpp
 * @brief
 * @date       2021-07-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_SEMI_ALLOCATOR_DISCARD_DEALLOCATE_SEMI_ALLOCATOR_HPP
#define KERBAL_AUTONM_SEMI_ALLOCATOR_DISCARD_DEALLOCATE_SEMI_ALLOCATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/autonm/semi_allocator/semi_allocator_base.hpp>


namespace kerbal
{

	namespace autonm
	{

		template <typename T = void>
		class discard_deallocate_semi_allocator :
			public semi_allocator_base<T>
		{
			private:
				typedef semi_allocator_base<T> super;

			public:
				typedef typename super::value_type			value_type;
				typedef typename super::pointer				pointer;
				typedef typename super::size_type			size_type;

				KERBAL_CONSTEXPR14
				void deallocate(pointer, size_type) KERBAL_NOEXCEPT
				{
				}
		};

	} // namespace autonm

} // namespace kerbal

#endif // KERBAL_AUTONM_SEMI_ALLOCATOR_DISCARD_DEALLOCATE_SEMI_ALLOCATOR_HPP
