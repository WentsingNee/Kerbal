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

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/container/detail/container_allocator_overload.hpp>
#include <kerbal/container/detail/vector_base.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <execinfo.h>


namespace kerbal
{

	namespace stacktrace
	{

		template <typename Allocator>
		class basic_stacktrace :
				protected kerbal::container::detail::vector_allocator_unrelated<kerbal::stacktrace::stacktrace_entry>,
				protected kerbal::container::detail::container_allocator_overload<Allocator>
		{
			private:
				typedef kerbal::container::detail::vector_allocator_unrelated<kerbal::stacktrace::stacktrace_entry> vector_allocator_unrelated;
				typedef kerbal::container::detail::container_allocator_overload<Allocator>							container_allocator_overload;

			public:
				typedef vector_allocator_unrelated::value_type value_type;
				typedef vector_allocator_unrelated::pointer pointer;
				typedef vector_allocator_unrelated::const_pointer const_pointer;
				typedef vector_allocator_unrelated::iterator iterator;
				typedef vector_allocator_unrelated::const_iterator const_iterator;
				typedef vector_allocator_unrelated::reverse_iterator reverse_iterator;
				typedef vector_allocator_unrelated::const_reverse_iterator const_reverse_iterator;
				typedef vector_allocator_unrelated::size_type size_type;
				typedef typename value_type::native_handle_type native_handle_type;

			protected:
				using container_allocator_overload::alloc;

			protected:
				basic_stacktrace(const native_handle_type * first, const native_handle_type * last) :
						vector_allocator_unrelated(this->alloc(), first, last)
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
						vector_allocator_unrelated(this->alloc(), kerbal::compatibility::move(src.alloc()), static_cast<vector_allocator_unrelated&&>(src))
				{
				}

#	endif

				~basic_stacktrace()
				{
					vector_allocator_unrelated::destroy_using_allocator(this->alloc());
				}

			public:

				using vector_allocator_unrelated::begin;
				using vector_allocator_unrelated::end;
				using vector_allocator_unrelated::cbegin;
				using vector_allocator_unrelated::cend;

				using vector_allocator_unrelated::rbegin;
				using vector_allocator_unrelated::rend;
				using vector_allocator_unrelated::crbegin;
				using vector_allocator_unrelated::crend;

				using vector_allocator_unrelated::operator[];
				using vector_allocator_unrelated::size;

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
