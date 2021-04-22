/**
 * @file       optional_settings.hpp
 * @brief
 * @date       2019-4-19
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_OPTIONAL_SETTINGS_HPP_
#define KERBAL_OPTIONAL_OPTIONAL_SETTINGS_HPP_

#if !defined(KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL)
#	if __cplusplus >= 201703L
#		define KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL 1
#	else
#		define KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL 0
#	endif
#endif


#if !defined(KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL)
#	define KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL 1
#endif

#if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL==1

#include <kerbal/compatibility/namespace_std_scope.hpp>

KERBAL_NAMESPACE_STD_BEGIN

	template <typename Type>
	class optional;

	struct nullopt_t;

	template <typename Type>
	class hash;

KERBAL_NAMESPACE_STD_END

#endif

#if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL==1

namespace boost
{
	template <typename Type>
	class optional;

	class none_t;
}

#endif

#endif /* KERBAL_OPTIONAL_OPTIONAL_SETTINGS_HPP_ */
