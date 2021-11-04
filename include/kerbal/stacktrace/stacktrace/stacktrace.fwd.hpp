/**
 * @file       stacktrace.fwd.hpp
 * @brief
 * @date       2021-11-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_STACKTRACE_STACKTRACE_STACKTRACE_FWD_HPP
#define KERBAL_STACKTRACE_STACKTRACE_STACKTRACE_FWD_HPP

#include <kerbal/stacktrace/stacktrace_entry/stacktrace_entry.fwd.hpp>

#include <memory>


namespace kerbal
{

	namespace stacktrace
	{

		template <typename Allocator>
		class basic_stacktrace;

		typedef basic_stacktrace<
			std::allocator<kerbal::stacktrace::stacktrace_entry>
		> stacktrace;

	} // namespace stacktrace

} // namespace kerbal

#endif // KERBAL_STACKTRACE_STACKTRACE_STACKTRACE_FWD_HPP
