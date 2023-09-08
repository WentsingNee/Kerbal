/**
 * @file       member_compress_helper.fwd.hpp
 * @brief
 * @date       2022-07-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_FWD_HPP
#define KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t I = 0>
		class member_compress_helper;

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_FWD_HPP
