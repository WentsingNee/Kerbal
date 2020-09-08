/**
 * @file       thread.decl.hpp
 * @brief
 * @date       2022-05-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_THREAD_DECL_HPP
#define KERBAL_PARALLEL_THREAD_THREAD_DECL_HPP

#include <kerbal/parallel/thread/thread.fwd.hpp>

#if KERBAL_PARALLEL_THREAD_MODE == KERBAL_PARALLEL_THREAD_MODE_POSIX
#	include <kerbal/parallel/thread/detail/thread.posix.decl.part.hpp>
#	include <kerbal/parallel/thread/detail/thread.common.decl.part.hpp>
#elif KERBAL_PARALLEL_THREAD_MODE == KERBAL_PARALLEL_THREAD_MODE_WIN
#	include <kerbal/parallel/thread/detail/thread.win.decl.part.hpp>
#	include <kerbal/parallel/thread/detail/thread.common.decl.part.hpp>
#endif

#endif // KERBAL_PARALLEL_THREAD_THREAD_DECL_HPP
