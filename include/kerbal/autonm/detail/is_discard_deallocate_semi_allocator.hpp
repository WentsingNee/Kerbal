/**
 * @file       is_discard_deallocate_semi_allocator.hpp
 * @brief
 * @date       2023-05-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_DETAIL_IS_DISCARD_DEALLOCATE_SEMI_ALLOCATOR_HPP
#define KERBAL_AUTONM_DETAIL_IS_DISCARD_DEALLOCATE_SEMI_ALLOCATOR_HPP

#include <kerbal/autonm/semi_allocator/discard_deallocate_semi_allocator.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace autonm
	{

		template <typename T>
		struct is_discard_deallocate_semi_allocator :
			kerbal::type_traits::false_type
		{
		};

		template <typename T>
		struct is_discard_deallocate_semi_allocator<
			kerbal::autonm::discard_deallocate_semi_allocator<T>
		> :
			kerbal::type_traits::true_type
		{
		};

	} // namespace autonm

} // namespace kerbal


#endif // KERBAL_AUTONM_DETAIL_IS_DISCARD_DEALLOCATE_SEMI_ALLOCATOR_HPP
