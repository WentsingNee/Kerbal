/**
 * @file       member_ptr_vnull.hpp
 * @brief
 * @date       2023-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_V2_DETAIL_MEMBER_PTR_VNULL_HPP
#define KERBAL_CONTAINER_V2_DETAIL_MEMBER_PTR_VNULL_HPP

namespace kerbal
{

	namespace container_v2
	{

		namespace detail
		{

			template <typename T>
			struct member_ptr_vnull
			{
					T null;
			};

		} // namespace detail

	} // namespace container_v2

} // namespace kerbal

#endif // KERBAL_CONTAINER_V2_DETAIL_MEMBER_PTR_VNULL_HPP
