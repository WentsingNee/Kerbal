/**
 * @file       static_stack.hpp
 * @brief
 * @date       2018-5-2
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_STACK_HPP
#define KERBAL_CONTAINER_STATIC_STACK_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/static_vector.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		/**
		 * @brief Stack with flexible length that stored on automatic storage duration
		 * @details The class is an encapsulation class of stack that could be stored on
		 *          automatic storage duration. It is more effective than std::stack because
		 *          std::stack store elements on heap storage duration (that's required memory
		 *          allocate and deallocate).
		 * @tparam T Type of the elements.
		 * @tparam N The maximum number of elements that the stack can hold.
		 */
		template <typename T, std::size_t N>
		class static_stack
		{
			public:
				typedef kerbal::container::static_vector<T, N>		container_type;

				typedef T						value_type;
				typedef const T					const_type;
				typedef T&						reference;
				typedef const T&				const_reference;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef typename container_type::size_type					size_type;

				typedef typename container_type::const_iterator				const_iterator;
				typedef typename container_type::const_reverse_iterator		const_reverse_iterator;

			private:
				container_type c;

			public:
				KERBAL_CONSTEXPR
				static_stack() :
						c()
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_stack(std::initializer_list<value_type> ilist) :
						c(ilist)
				{
				}

#		endif

				KERBAL_CONSTEXPR
				bool empty() const
				{
					return c.empty();
				}

				KERBAL_CONSTEXPR
				bool full() const
				{
					return c.full();
				}

				KERBAL_CONSTEXPR
				size_type size() const
				{
					return c.size();
				}

				KERBAL_CONSTEXPR
				size_type max_size() const
				{
					return c.max_size();
				}

				KERBAL_CONSTEXPR14
				reference top()
				{
					return c.back();
				}

				KERBAL_CONSTEXPR14
				const_reference top() const
				{
					return c.back();
				}

				KERBAL_CONSTEXPR14
				void push(const_reference val)
				{
					c.push_back(val);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void push(rvalue_reference val)
				{
					c.push_back(kerbal::compatibility::move(val));
				}

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				reference emplace(Args&& ... args)
				{
					return c.emplace_back(kerbal::utility::forward<Args>(args)...);
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
					return c.emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
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

				KERBAL_CONSTEXPR14
				void pop()
				{
					c.pop_back();
				}

				KERBAL_CONSTEXPR
				const_iterator begin() const
				{
					return c.cbegin();
				}

				KERBAL_CONSTEXPR
				const_iterator end() const
				{
					return c.cend();
				}

				KERBAL_CONSTEXPR
				const_iterator cbegin() const
				{
					return c.cbegin();
				}

				KERBAL_CONSTEXPR
				const_iterator cend() const
				{
					return c.cend();
				}

				KERBAL_CONSTEXPR
				const_reverse_iterator rbegin() const
				{
					return c.crbegin();
				}

				KERBAL_CONSTEXPR
				const_reverse_iterator rend() const
				{
					return c.crend();
				}

				KERBAL_CONSTEXPR
				const_reverse_iterator crbegin() const
				{
					return c.crbegin();
				}

				KERBAL_CONSTEXPR
				const_reverse_iterator crend() const
				{
					return c.crend();
				}

				KERBAL_CONSTEXPR14
				void clear()
				{
					c.clear();
				}

				KERBAL_CONSTEXPR14
				void swap(static_stack & with)
				{
					c.swap(with.c);
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator==(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs);

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator!=(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs);

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator<(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs);

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator<=(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs);

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator>(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs);

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator>=(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs);

		};

		/**
		 * Judge whether the stack is equal to the other one.
		 * @param rhs another stack
		 */
		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator==(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs)
		{
			return lhs.c == rhs.c;
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator!=(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs)
		{
			return lhs.c != rhs.c;
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator<(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs)
		{
			return lhs.c < rhs.c;
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator<=(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs)
		{
			return lhs.c <= rhs.c;
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator>(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs)
		{
			return lhs.c > rhs.c;
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator>=(const static_stack<T, M> & lhs, const static_stack<T, N> & rhs)
		{
			return lhs.c >= rhs.c;
		}

	} // namespace container


	namespace algorithm
	{

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		void swap(kerbal::container::static_stack<T, N> & a, kerbal::container::static_stack<T, N> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, std::size_t N>
	KERBAL_CONSTEXPR14
	void swap(kerbal::container::static_stack<T, N> & a, kerbal::container::static_stack<T, N> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_STATIC_STACK_HPP
