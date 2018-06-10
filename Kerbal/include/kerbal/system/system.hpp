/**
 * @file		system.hpp
 * @brief
 * @date		2018年3月1日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_SYSTEM_SYSTEM_HPP_
#define INCLUDE_KERBAL_SYSTEM_SYSTEM_HPP_

#ifdef __linux
#	include "linux.hpp"
#endif

#if (defined __WINDOWS_) || (defined _WIN32)
#	include "windows.hpp"
#endif

#endif /* INCLUDE_KERBAL_SYSTEM_SYSTEM_HPP_ */
