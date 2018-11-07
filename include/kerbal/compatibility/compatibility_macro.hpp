/**
 * @file		compatibility_macro.hpp
 * @brief
 * @date		2018年6月10日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_COMPATIBILITY_COMPATIBILITY_MACRO_HPP_
#define INCLUDE_KERBAL_COMPATIBILITY_COMPATIBILITY_MACRO_HPP_


#ifdef KERBAL_CONSTEXPR
#	undef KERBAL_CONSTEXPR
#endif
#if __cplusplus >= 201103L
#	define KERBAL_CONSTEXPR constexpr
#else
#	define KERBAL_CONSTEXPR
#endif

#ifdef KERBAL_NOEXCEPT
#	undef KERBAL_NOEXCEPT
#endif
#if __cplusplus >= 201103L
#	define KERBAL_NOEXCEPT noexcept
#else
#	define KERBAL_NOEXCEPT throw()
#endif

#ifdef KERBAL_REFERENCE_OVERLOAD_TAG
#	undef KERBAL_REFERENCE_OVERLOAD_TAG
#endif
#if __cplusplus < 201103L
#	define KERBAL_REFERENCE_OVERLOAD_TAG
#else
#	define KERBAL_REFERENCE_OVERLOAD_TAG &
#endif


#endif /* INCLUDE_KERBAL_COMPATIBILITY_COMPATIBILITY_MACRO_HPP_ */
