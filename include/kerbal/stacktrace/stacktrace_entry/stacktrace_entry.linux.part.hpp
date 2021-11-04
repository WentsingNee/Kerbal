/**
 * @file       stacktrace_entry.linux.part.hpp
 * @brief
 * @date       2021-11-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_STACKTRACE_STACKTRACE_ENTRY_STACKTRACE_ENTRY_LINUX_PART_HPP
#define KERBAL_STACKTRACE_STACKTRACE_ENTRY_STACKTRACE_ENTRY_LINUX_PART_HPP

#include <kerbal/stacktrace/stacktrace/stacktrace.fwd.hpp>
#include <kerbal/stacktrace/stacktrace_entry/stacktrace_entry.fwd.hpp>

#include <kerbal/compatibility/noexcept.hpp>

#include <string>

#include <cstdlib>
#include <execinfo.h>


namespace kerbal
{

	namespace stacktrace
	{

		class stacktrace_entry
		{
			protected:
				typedef void * native_handle_type;

				template <typename Allocator>
				friend class kerbal::stacktrace::basic_stacktrace;

			protected:
				native_handle_type k_native_handle;

			public:
				explicit stacktrace_entry(native_handle_type native_handle) KERBAL_NOEXCEPT :
					k_native_handle(native_handle)
				{
				}

			public:

				std::string description() const
				{
					char ** des_str = ::backtrace_symbols(&k_native_handle, 1);
					struct free_helper
					{
							char ** des_str;

							free_helper(char ** des_str) KERBAL_NOEXCEPT :
								des_str(des_str)
							{
							}

							~free_helper() KERBAL_NOEXCEPT
							{
								std::free(this->des_str);
							}

					} free_helper(des_str);

					return std::string(des_str[0]);
				}

				native_handle_type native_handle() const KERBAL_NOEXCEPT
				{
					return this->k_native_handle;
				}

		};

	} // namespace stacktrace

} // namespace kerbal

#endif // KERBAL_STACKTRACE_STACKTRACE_ENTRY_STACKTRACE_ENTRY_LINUX_PART_HPP
