/**
 * @file       md5.fwd.hpp
 * @brief
 * @date       2024-10-11
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_MD5_MD5_FWD_HPP
#define KERBAL_HASH_MD5_MD5_FWD_HPP

namespace kerbal
{

	namespace hash
	{

		namespace detail
		{

			class MD5_context_base;

			template <typename Policy>
			class MD5_transform_overload;

		} // namespace detail

		class MD5_result;

		struct MD5_policy
		{
			struct fast {};
			struct size {};
		};

		template <typename Policy>
		class MD5_context;

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_MD5_MD5_FWD_HPP
