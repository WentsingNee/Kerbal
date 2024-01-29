/**
 * @file       member_compress_helper_impl.fwd.hpp
 * @brief
 * @date       2024-01-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_IMPL_FWD_HPP
#define KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_IMPL_FWD_HPP

#include <kerbal/type_traits/can_be_empty_base.hpp>


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <
				typename T,
				bool =
					kerbal::type_traits::try_test_can_be_empty_base<T>::IS_TRUE::value
			>
			class member_compress_helper_impl;

		} // namespace detail

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_IMPL_FWD_HPP
