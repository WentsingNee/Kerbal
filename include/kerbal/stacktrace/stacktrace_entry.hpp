/**
 * @file       stacktrace_entry.hpp
 * @brief
 * @date       2021-11-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_STACKTRACE_STACKTRACE_ENTRY_HPP
#define KERBAL_STACKTRACE_STACKTRACE_ENTRY_HPP

#include <kerbal/config/system.hpp>

#if KERBAL_SYSTEM == KERBAL_SYSTEM_LINUX
#	include <kerbal/stacktrace/stacktrace_entry/stacktrace_entry.linux.part.hpp>
#endif

#endif // KERBAL_STACKTRACE_STACKTRACE_ENTRY_HPP
