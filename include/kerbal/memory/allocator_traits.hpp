/**
 * @file       allocator_traits.hpp
 * @brief
 * @date       2020-03-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <kerbal/memory/allocator_traits/pointer_type.hpp>
#include <kerbal/memory/allocator_traits/const_pointer_type.hpp>
#include <kerbal/memory/allocator_traits/void_pointer_type.hpp>
#include <kerbal/memory/allocator_traits/const_void_pointer_type.hpp>
#include <kerbal/memory/allocator_traits/size_type.hpp>
#include <kerbal/memory/allocator_traits/difference_type.hpp>
#include <kerbal/memory/allocator_traits/propagate_on_container_copy_assignment.hpp>
#include <kerbal/memory/allocator_traits/propagate_on_container_move_assignment.hpp>
#include <kerbal/memory/allocator_traits/propagate_on_container_swap.hpp>
#include <kerbal/memory/allocator_traits/is_always_equal.hpp>
#include <kerbal/memory/allocator_traits/rebind_alloc.hpp>
#include <kerbal/memory/allocator_traits/allocate_one.hpp>
#include <kerbal/memory/allocator_traits/minimum_alignment.hpp>
#include <kerbal/memory/allocator_traits/deallocate_one.hpp>
#include <kerbal/memory/allocator_traits/allow_deallocate_null.hpp>
#include <kerbal/memory/allocator_traits/reallocate.hpp>
#include <kerbal/memory/allocator_traits/construct.hpp>
#include <kerbal/memory/allocator_traits/destroy.hpp>
#include <kerbal/memory/allocator_traits/max_size.hpp>


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc>
		struct allocator_traits :
				public kerbal::memory::detail::allocator_traits_reallocate_helper<Alloc>
		{
				typedef Alloc allocator_type;

				typedef typename allocator_type::value_type value_type;

				typedef typename kerbal::memory::detail::allocator_pointer_traits_helper<allocator_type>::type pointer;

				typedef typename kerbal::memory::detail::allocator_const_pointer_traits_helper<allocator_type>::type const_pointer;

				typedef typename kerbal::memory::detail::allocator_void_pointer_traits_helper<allocator_type>::type void_pointer;

				typedef typename kerbal::memory::detail::allocator_const_void_pointer_traits_helper<allocator_type>::type const_void_pointer;

				typedef typename kerbal::memory::detail::allocator_difference_type_traits_helper<allocator_type>::type difference_type;

				typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<allocator_type>::type size_type;

				typedef kerbal::memory::detail::allocator_propagate_on_container_copy_assignment_traits_helper<allocator_type> propagate_on_container_copy_assignment;

				typedef kerbal::memory::detail::allocator_propagate_on_container_move_assignment_traits_helper<allocator_type> propagate_on_container_move_assignment;

				typedef kerbal::memory::detail::allocator_propagate_on_container_swap_traits_helper<allocator_type> propagate_on_container_swap;

				typedef kerbal::memory::detail::allocator_is_always_equal_traits_helper<allocator_type> is_always_equal;

				template <typename U>
				struct rebind_alloc
				{
						typedef typename kerbal::memory::detail::allocator_traits_rebind_alloc_helper<Alloc, U>::type other;
				};

				template <typename U>
				struct rebind_traits
				{
						typedef kerbal::memory::allocator_traits<typename rebind_alloc<U>::other> other;
				};

				typedef kerbal::memory::allocator_has_reallocate<Alloc, value_type> has_reallocate;

				KERBAL_CONSTEXPR14
				static pointer allocate(allocator_type & alloc, size_type n)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(alloc.allocate(n))
						)
				{
					return alloc.allocate(n);
				}

				KERBAL_CONSTEXPR14
				static pointer allocate_one(allocator_type & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::detail::allocator_traits_allocate_one_helper<Alloc>::allocate_one(alloc))
						)
				{
					return kerbal::memory::detail::allocator_traits_allocate_one_helper<Alloc>::allocate_one(alloc);
				}

				KERBAL_CONSTEXPR14
				static size_type minimum_alignment(const allocator_type & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::detail::allocator_traits_minimum_alignment_helper<Alloc>::minimum_alignment(alloc))
						)
				{
					return kerbal::memory::detail::allocator_traits_minimum_alignment_helper<Alloc>::minimum_alignment(alloc);
				}

				KERBAL_CONSTEXPR14
				static void deallocate(allocator_type & alloc, pointer p, size_type n)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(alloc.deallocate(p, n))
						)
				{
					alloc.deallocate(p, n);
				}

				KERBAL_CONSTEXPR14
				static void deallocate_one(allocator_type & alloc, pointer p)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::detail::allocator_traits_deallocate_one_helper<Alloc, pointer>::deallocate_one(alloc, p))
						)
				{
					kerbal::memory::detail::allocator_traits_deallocate_one_helper<Alloc, pointer>::deallocate_one(alloc, p);
				}

				typedef kerbal::memory::detail::allocator_allow_deallocate_null_traits_helper<allocator_type> allow_deallocate_null;

#		if __cplusplus >= 201103L

				template <typename T, typename ... Args>
				KERBAL_CONSTEXPR14
				static void construct(Alloc & alloc, T * p, Args&& ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::detail::allocator_traits_construct_helper<Alloc>::construct(alloc, p, kerbal::utility::forward<Args>(args)...)
							)
						)
				{
					kerbal::memory::detail::allocator_traits_construct_helper<Alloc>::construct(alloc, p, kerbal::utility::forward<Args>(args)...);
				}

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				static void construct(Alloc & alloc, T * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					kerbal::memory::detail::allocator_traits_construct_helper<Alloc>::construct(alloc, p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		endif // __cplusplus >= 201103L

				template <typename T>
				KERBAL_CONSTEXPR14
				static void destroy(Alloc & alloc, T * p)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::detail::allocator_traits_destroy_helper<Alloc>::destroy(alloc, p))
						)
				{
					kerbal::memory::detail::allocator_traits_destroy_helper<Alloc>::destroy(alloc, p);
				}

				KERBAL_CONSTEXPR
				static size_type max_size(const Alloc & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::detail::allocator_traits_max_size_helper<Alloc>::max_size(alloc))
						)
				{
					return kerbal::memory::detail::allocator_traits_max_size_helper<Alloc>::max_size(alloc);
				}

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_HPP
