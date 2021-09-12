/**
 * @file       linked_stack.hpp
 * @brief
 * @date       2019-11-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_LINKED_STACK_HPP
#define KERBAL_CONTAINER_LINKED_STACK_HPP

#include <kerbal/container/forward_list.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Sequence = kerbal::container::forward_list<Tp> >
		class linked_stack
		{
			public:
				typedef Tp						value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef typename Sequence::allocator_type			allocator_type;

				typedef typename Sequence::size_type				size_type;
				typedef typename Sequence::difference_type			difference_type;

			private:
				Sequence c;

			public:
				KERBAL_CONSTEXPR20
				linked_stack()
						: c()
				{
				}

				KERBAL_CONSTEXPR20
				explicit
				linked_stack(const allocator_type & alloc)
						: c(alloc)
				{
				}

				KERBAL_CONSTEXPR20
				bool empty() const
				{
					return c.empty();
				}

				KERBAL_CONSTEXPR20
				size_type size() const
				{
					return c.size();
				}

				KERBAL_CONSTEXPR
				size_type max_size() const
				{
					return c.max_size();
				}

				KERBAL_CONSTEXPR20
				reference top()
				{
					return c.front();
				}

				KERBAL_CONSTEXPR20
				const_reference top() const
				{
					return c.front();
				}

				KERBAL_CONSTEXPR20
				void push(const_reference val)
				{
					c.push_front(val);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push(rvalue_reference val)
				{
					c.push_front(kerbal::compatibility::move(val));
				}

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				reference emplace(Args&& ... args)
				{
					return c.emplace_front(kerbal::utility::forward<Args>(args)...);
				}

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				reference emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					return c.emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		endif

				KERBAL_CONSTEXPR20
				void pop()
				{
					c.pop_front();
				}

				KERBAL_CONSTEXPR20
				void clear()
				{
					c.clear();
				}

				KERBAL_CONSTEXPR20
				void swap(linked_stack & with)
				{
					c.swap(with.c);
				}

				/**
				 * Judge whether the stack is equal to the other one.
				 * @param rhs another stack
				 */
				KERBAL_CONSTEXPR20
				friend bool operator==(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c == rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator!=(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c != rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator<(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c < rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator<=(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c <= rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator>(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c > rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend bool operator>=(const linked_stack<Tp, Sequence> & lhs, const linked_stack<Tp, Sequence> & rhs)
				{
					return lhs.c >= rhs.c;
				}

		};

#	if __cplusplus >= 201703L

#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename Tp>
			using linked_stack = kerbal::container::linked_stack<Tp, kerbal::container::pmr::forward_list<Tp> >;
		}

#	endif

#	endif

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_LINKED_STACK_HPP
