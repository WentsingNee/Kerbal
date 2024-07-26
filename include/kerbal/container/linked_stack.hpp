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

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/forward_list.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace container
	{

		KERBAL_MODULE_EXPORT
		template <typename T, typename Sequence = kerbal::container::forward_list<T> >
		class linked_stack
		{
			public:
				typedef T						value_type;
				typedef const value_type		const_type;
				typedef value_type &			reference;
				typedef const value_type &		const_reference;
				typedef value_type *			pointer;
				typedef const value_type *		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type &&			rvalue_reference;
				typedef const value_type &&		const_rvalue_reference;
#		endif

				typedef typename Sequence::allocator_type			allocator_type;

				typedef typename Sequence::size_type				size_type;
				typedef typename Sequence::difference_type			difference_type;

			private:
				Sequence c;

			public:

			//===================
			// construct/copy/destroy

				KERBAL_CONSTEXPR20
				linked_stack() :
					c()
				{
				}

				KERBAL_CONSTEXPR20
				explicit
				linked_stack(const allocator_type & alloc) :
					c(alloc)
				{
				}


			//===================
			// element access

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


			//===================
			// capacity

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


			//===================
			// insert

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				reference emplace(Args && ... args)
				{
					return c.emplace_front(kerbal::utility::forward<Args>(args)...);
				}

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				reference emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					return c.emplace_front(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
				} \

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


			//===================
			// erase

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


			//===================
			// operation

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
				friend
				bool operator==(
					const linked_stack<T, Sequence> & lhs,
					const linked_stack<T, Sequence> & rhs
				)
				{
					return lhs.c == rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend
				bool operator!=(
					const linked_stack<T, Sequence> & lhs,
					const linked_stack<T, Sequence> & rhs
				)
				{
					return lhs.c != rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend
				bool operator<(
					const linked_stack<T, Sequence> & lhs,
					const linked_stack<T, Sequence> & rhs
				)
				{
					return lhs.c < rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend
				bool operator<=(
					const linked_stack<T, Sequence> & lhs,
					const linked_stack<T, Sequence> & rhs
				)
				{
					return lhs.c <= rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend
				bool operator>(
					const linked_stack<T, Sequence> & lhs,
					const linked_stack<T, Sequence> & rhs
				)
				{
					return lhs.c > rhs.c;
				}

				KERBAL_CONSTEXPR20
				friend
				bool operator>=(
					const linked_stack<T, Sequence> & lhs,
					const linked_stack<T, Sequence> & rhs
				)
				{
					return lhs.c >= rhs.c;
				}

		};

#	if __cplusplus >= 201703L

#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename T>
			using linked_stack = kerbal::container::linked_stack<T, kerbal::container::pmr::forward_list<T> >;
		}

#	endif

#	endif

	} // namespace container


	namespace algorithm
	{

		template <typename T, typename Sequence>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::container::linked_stack<T, Sequence> & a,
			kerbal::container::linked_stack<T, Sequence> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename Sequence>
	KERBAL_CONSTEXPR14
	void swap(
		kerbal::container::linked_stack<T, Sequence> & a,
		kerbal::container::linked_stack<T, Sequence> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_LINKED_STACK_HPP
