/**
 * @file       priority_queue.hpp
 * @brief
 * @date       2021-08-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_PRIORITY_QUEUE_HPP
#define KERBAL_CONTAINER_PRIORITY_QUEUE_HPP

#include <kerbal/algorithm/heap.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		template <typename T, typename KeyCompare = kerbal::compare::less<T>, typename Container = kerbal::container::vector<T> >
		class priority_queue :
				private kerbal::utility::member_compress_helper<KeyCompare>
		{
			private:
				typedef kerbal::utility::member_compress_helper<KeyCompare> kc_compress_helper;

			public:
				typedef Container		container_type;
				typedef KeyCompare		value_compare;

				typedef T											value_type;
				typedef typename container_type::const_type			const_type;
				typedef typename container_type::reference			reference;
				typedef typename container_type::const_reference	const_reference;
				typedef typename container_type::pointer			pointer;
				typedef typename container_type::const_pointer		const_pointer;

#		if __cplusplus >= 201103L
				typedef typename container_type::rvalue_reference			rvalue_reference;
				typedef typename container_type::const_rvalue_reference		const_rvalue_reference;
#		endif

				typedef typename container_type::size_type					size_type;
				typedef typename container_type::difference_type			difference_type;

				typedef typename container_type::const_iterator				const_iterator;
				typedef typename container_type::const_reverse_iterator		const_reverse_iterator;

			private:
				KERBAL_STATIC_ASSERT(
						(kerbal::type_traits::is_same<
								typename Container::value_type,
								value_type
						>::value),
						"Container::value_type should be same as T"
				);

			private:
				container_type c;

				KERBAL_CONSTEXPR14
				value_compare & vc() KERBAL_NOEXCEPT
				{
					return kc_compress_helper::member();
				}

				KERBAL_CONSTEXPR
				const value_compare & vc() const KERBAL_NOEXCEPT
				{
					return kc_compress_helper::member();
				}

			public:

			//===================
			// construct/copy/destroy

				KERBAL_CONSTEXPR20
				priority_queue() :
						kc_compress_helper(kerbal::utility::in_place_t()), c()
				{
				}

				KERBAL_CONSTEXPR20
				explicit priority_queue(const value_compare & vc) :
						kc_compress_helper(kerbal::utility::in_place_t(), vc), c()
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				priority_queue(InputIterator first, InputIterator last,
								typename kerbal::type_traits::enable_if<
										kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
										int
								>::type = 0) :
						kc_compress_helper(kerbal::utility::in_place_t()), c(first, last)
				{
					kerbal::algorithm::make_heap(c.begin(), c.end(), this->vc());
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				priority_queue(InputIterator first, InputIterator last, const value_compare & vc,
								typename kerbal::type_traits::enable_if<
										kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
										int
								>::type = 0) :
						kc_compress_helper(kerbal::utility::in_place_t(), vc), c(first, last)
				{
					kerbal::algorithm::make_heap(c.begin(), c.end(), this->vc());
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				priority_queue(std::initializer_list<value_type> ilist) :
						priority_queue(ilist.begin(), ilist.end())
				{
				}

				KERBAL_CONSTEXPR20
				priority_queue(std::initializer_list<value_type> ilist, const value_compare & vc) :
						priority_queue(ilist.begin(), ilist.end(), vc)
				{
				}

#		else

				priority_queue(const kerbal::assign::assign_list<void> & ilist) :
						kc_compress_helper(kerbal::utility::in_place_t()), c()
				{
				}

				template <typename U>
				priority_queue(const kerbal::assign::assign_list<U> & ilist) :
						kc_compress_helper(kerbal::utility::in_place_t()), c(ilist.cbegin(), ilist.cend())
				{
					kerbal::algorithm::make_heap(c.begin(), c.end(), this->vc());
				}

				priority_queue(const kerbal::assign::assign_list<void> & ilist, const value_compare & vc) :
						kc_compress_helper(kerbal::utility::in_place_t(), vc), c()
				{
				}

				template <typename U>
				priority_queue(const kerbal::assign::assign_list<U> & ilist, const value_compare & vc) :
						kc_compress_helper(kerbal::utility::in_place_t(), vc), c(ilist.cbegin(), ilist.cend())
				{
					kerbal::algorithm::make_heap(c.begin(), c.end(), this->vc());
				}

#		endif


			//===================
			// element access

				KERBAL_CONSTEXPR20
				const_reference top() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.front())
						)
				{
					return c.front();
				}


			//===================
			// iterator

				KERBAL_CONSTEXPR
				const_iterator begin() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.cbegin())
						)
				{
					return c.cbegin();
				}

				KERBAL_CONSTEXPR
				const_iterator end() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.cend())
						)
				{
					return c.cend();
				}

				KERBAL_CONSTEXPR
				const_iterator cbegin() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.cbegin())
						)
				{
					return c.cbegin();
				}

				KERBAL_CONSTEXPR
				const_iterator cend() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.cend())
						)
				{
					return c.cend();
				}

				KERBAL_CONSTEXPR14
				const_reverse_iterator rbegin() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.crbegin())
						)
				{
					return c.crbegin();
				}

				KERBAL_CONSTEXPR14
				const_reverse_iterator rend() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.crend())
						)
				{
					return c.crend();
				}

				KERBAL_CONSTEXPR14
				const_reverse_iterator crbegin() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.crbegin())
						)
				{
					return c.crbegin();
				}

				KERBAL_CONSTEXPR14
				const_reverse_iterator crend() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.crend())
						)
				{
					return c.crend();
				}


			//===================
			// capacity

				KERBAL_CONSTEXPR
				bool empty() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.empty())
						)
				{
					return c.empty();
				}

				KERBAL_CONSTEXPR
				size_type size() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.size())
						)
				{
					return c.size();
				}

				KERBAL_CONSTEXPR
				size_type max_size() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(c.max_size())
						)
				{
					return c.max_size();
				}


			//===================
			// modifiers

				KERBAL_CONSTEXPR20
				void push(const_reference val)
				{
					c.push_back(val);
					kerbal::algorithm::push_heap(c.begin(), c.end(), this->vc());
				}


#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push(rvalue_reference val)
				{
					c.push_back(kerbal::compatibility::move(val));
					kerbal::algorithm::push_heap(c.begin(), c.end(), this->vc());
				}

#		endif


				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				void push(InputIterator first, InputIterator last)
				{
					while (first != last) {
						this->push(*first);
						++first;
					}
				}


#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push(std::initializer_list<value_type> ilist)
				{
					this->push(ilist.begin(), ilist.end());
				}

#		else

				void push(const kerbal::assign::assign_list<void> & ilist)
				{
				}

				template <typename U>
				void push(const kerbal::assign::assign_list<U> & ilist)
				{
					this->push(ilist.cbegin(), ilist.cend());
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				void emplace(Args&& ... args)
				{
					c.emplace_back(kerbal::utility::forward<Args>(args)...);
					kerbal::algorithm::push_heap(c.begin(), c.end(), this->vc());
				}

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				void emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					c.emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
					kerbal::algorithm::push_heap(c.begin(), c.end(), this->vc()); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		endif


				KERBAL_CONSTEXPR20
				void pop()
				{
					kerbal::algorithm::pop_heap(c.begin(), c.end(), this->vc());
					c.pop_back();
				}


			//===================
			// operation

				KERBAL_CONSTEXPR20
				void swap(priority_queue & with)
				{
					c.swap(with.c);
					kerbal::algorithm::swap(this->vc(), with.vc());
				}

		};

	} // namespace container


	namespace algorithm
	{

		template <typename T, typename KeyCompare, typename Container>
		KERBAL_CONSTEXPR20
		void swap(kerbal::container::priority_queue<T, KeyCompare, Container> & a, kerbal::container::priority_queue<T, KeyCompare, Container> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename KeyCompare, typename Container>
	KERBAL_CONSTEXPR20
	void swap(kerbal::container::priority_queue<T, KeyCompare, Container> & a, kerbal::container::priority_queue<T, KeyCompare, Container> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_PRIORITY_QUEUE_HPP
