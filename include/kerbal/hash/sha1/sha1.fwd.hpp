/**
 * @file       sha1.fwd.hpp
 * @brief
 * @date       2024-10-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_SHA1_SHA1_FWD_HPP
#define KERBAL_HASH_SHA1_SHA1_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>


namespace kerbal
{

	namespace hash
	{

		namespace detail
		{

			class SHA1_context_base;

			template <typename Policy>
			class SHA1_transform_overload;

		} // namespace detail

		KERBAL_MODULE_EXPORT
		class SHA1_result;

		KERBAL_MODULE_EXPORT
		struct SHA1_policy
		{
			struct fast {};
			struct size {};
		};

		KERBAL_MODULE_EXPORT
		template <typename Policy>
		class SHA1_context;

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_SHA1_SHA1_FWD_HPP
