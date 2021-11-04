/**
 * @file       stacktrace.linux.part.hpp
 * @brief
 * @date       2021-11-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_STACKTRACE_STACKTRACE_STACKTRACE_LINUX_PART_HPP
#define KERBAL_STACKTRACE_STACKTRACE_STACKTRACE_LINUX_PART_HPP

#include <kerbal/stacktrace/stacktrace_entry.hpp>

#include <kerbal/container/detail/container_allocator_overload.hpp>
#include <kerbal/container/detail/vector_base.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>
#include <execinfo.h>


namespace kerbal
{

	namespace stacktrace
	{

		template <typename Allocator>
		class basic_stacktrace :
			protected kerbal::container::detail::vector_type_only<
				kerbal::stacktrace::stacktrace_entry
			>,
			protected kerbal::container::detail::container_allocator_overload<Allocator>
		{
			private:
				typedef kerbal::container::detail::vector_type_only<
					kerbal::stacktrace::stacktrace_entry
				>													vector_type_only;
				typedef kerbal::container::detail::container_allocator_overload<Allocator>
																	container_allocator_overload;

			public:
				typedef vector_type_only::value_type				value_type;
				typedef vector_type_only::pointer					pointer;
				typedef vector_type_only::const_pointer				const_pointer;
				typedef vector_type_only::iterator					iterator;
				typedef vector_type_only::const_iterator			const_iterator;
				typedef vector_type_only::reverse_iterator			reverse_iterator;
				typedef vector_type_only::const_reverse_iterator	const_reverse_iterator;
				typedef vector_type_only::size_type					size_type;
				typedef typename value_type::native_handle_type		native_handle_type;

			protected:
				using container_allocator_overload::alloc;

			protected:
				basic_stacktrace(
					native_handle_type const * first,
					native_handle_type const * last
				) :
					vector_type_only(this->alloc(), first, last)
				{
				}

			public:

#	if __cplusplus < 201103L

				basic_stacktrace()
				{
				}

#	else

				basic_stacktrace() = default;

#	endif


#	if __cplusplus >= 201103L

				basic_stacktrace(basic_stacktrace && src) :
					vector_type_only(
						this->alloc(),
						kerbal::compatibility::move(src.alloc()),
						static_cast<vector_type_only &&>(src)
					)
				{
				}

#	endif

				~basic_stacktrace()
				{
					this->vector_type_only::k_destroy_using_allocator(this->alloc());
				}

			public:

				using vector_type_only::begin;
				using vector_type_only::end;
				using vector_type_only::cbegin;
				using vector_type_only::cend;

				using vector_type_only::rbegin;
				using vector_type_only::rend;
				using vector_type_only::crbegin;
				using vector_type_only::crend;

				using vector_type_only::operator[];
				using vector_type_only::size;

				static
				basic_stacktrace current()
				{
					typedef kerbal::type_traits::integral_constant<std::size_t, 128> MAX_STATIC_BUFFER;
					typename value_type::native_handle_type static_buffer[MAX_STATIC_BUFFER::value];
					size_type sz = ::backtrace(static_buffer, MAX_STATIC_BUFFER::value);
					return basic_stacktrace(static_buffer + 0, static_buffer + sz);
				}

		};

	} // namespace stacktrace

} // namespace kerbal

#endif // KERBAL_STACKTRACE_STACKTRACE_STACKTRACE_LINUX_PART_HPP
