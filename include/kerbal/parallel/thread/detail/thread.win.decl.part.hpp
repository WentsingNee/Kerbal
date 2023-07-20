/**
 * @file       thread.win.decl.part.hpp
 * @brief
 * @date       2022-09-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_DETAIL_THREAD_WIN_DECL_PART_HPP
#define KERBAL_PARALLEL_THREAD_DETAIL_THREAD_WIN_DECL_PART_HPP

#include <windows.h>


namespace kerbal
{

	namespace parallel
	{

		namespace detail
		{
			typedef HANDLE thread_native_handle_type;
		}

	} // namespace parallel

} // namespace kerbal


#endif // KERBAL_PARALLEL_THREAD_DETAIL_THREAD_WIN_DECL_PART_HPP
