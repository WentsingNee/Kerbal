/**
 * @file       static_priority_queue.hpp
 * @brief
 * @date       2019-5-7
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_PRIORITY_QUEUE_HPP
#define KERBAL_CONTAINER_STATIC_PRIORITY_QUEUE_HPP

#include <kerbal/algorithm/heap.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/static_vector.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>
#include <stdexcept>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		template <typename T, std::size_t N, typename KeyCompare = kerbal::compare::less<T> >
		class static_priority_queue
		{
			public:
				typedef kerbal::container::static_vector<T, N>		container_type;
				typedef KeyCompare									value_compare;

				typedef T							value_type;
				typedef const value_type			const_type;
				typedef value_type &				reference;
				typedef const value_type &			const_reference;
				typedef value_type *				pointer;
				typedef const value_type *			const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type &&				rvalue_reference;
				typedef const value_type &&			const_rvalue_reference;
#		endif

				typedef typename container_type::size_type					size_type;
				typedef typename container_type::difference_type			difference_type;

				typedef typename container_type::const_iterator				const_iterator;
				typedef typename container_type::const_reverse_iterator		const_reverse_iterator;


			private:
				container_type c;
				value_compare vc;

			public:
				KERBAL_CONSTEXPR
				static_priority_queue() :
					c(), vc()
				{
				}

				KERBAL_CONSTEXPR
				explicit static_priority_queue(value_compare kc) :
					c(), vc(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_priority_queue(
					InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				) :
					c(first, last), vc()
				{
					kerbal::algorithm::make_heap(c.begin(), c.end(), this->vc);
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_priority_queue(
					InputIterator first, InputIterator last, value_compare kc,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				) :
					c(first, last), vc(kc)
				{
					kerbal::algorithm::make_heap(c.begin(), c.end(), this->vc);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_priority_queue(std::initializer_list<value_type> ilist) :
					static_priority_queue(ilist.begin(), ilist.end())
				{
				}

				KERBAL_CONSTEXPR14
				static_priority_queue(std::initializer_list<value_type> ilist, value_compare vc) :
					static_priority_queue(ilist.begin(), ilist.end(), vc)
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
				const_reference top() const
				{
					return c.front();
				}

				KERBAL_CONSTEXPR14
				void push_unsafe(const_reference val)
				{
					c.push_back_unsafe(val);
					kerbal::algorithm::push_heap(c.begin(), c.end(), vc);
				}

				KERBAL_CONSTEXPR20
				void push(const_reference val)
				{
					if (this->full()) {
						kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
							+"Out of storage space"
						);
					}
					this->push_unsafe(val);
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				void push_unsafe(InputIterator first, InputIterator last)
				{
					while (first != last) {
						this->push_unsafe(*first);
						++first;
					}
				}

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

				KERBAL_CONSTEXPR14
				void push_unsafe(rvalue_reference val)
				{
					c.push_back_unsafe(kerbal::compatibility::move(val));
					kerbal::algorithm::push_heap(c.begin(), c.end(), vc);
				}

				KERBAL_CONSTEXPR20
				void push(rvalue_reference val)
				{
					if (this->full()) {
						kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
							+"Out of storage space"
						);
					}
					this->push_unsafe(kerbal::compatibility::move(val));
				}

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				void emplace_unsafe(Args && ... args)
				{
					c.emplace_back_unsafe(kerbal::utility::forward<Args>(args)...);
					kerbal::algorithm::push_heap(c.begin(), c.end(), vc);
				}

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				void emplace(Args && ... args)
				{
					if (this->full()) {
						kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
							+"Out of storage space"
						);
					}
					this->emplace_unsafe(kerbal::utility::forward<Args>(args)...);
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
				void emplace_unsafe(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					c.emplace_back_unsafe(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
					kerbal::algorithm::push_heap(c.begin(), c.end(), vc); \
				} \
 \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				void emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					if (this->full()) { \
						kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception( \
							+"Out of storage space" \
						); \
					} \
					this->emplace_unsafe(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
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

				KERBAL_CONSTEXPR14
				void pop_unsafe()
				{
					kerbal::algorithm::pop_heap(c.begin(), c.end(), vc);
					c.pop_back_unsafe();
				}

				KERBAL_CONSTEXPR20
				void pop()
				{
					if (c.empty()) {
						kerbal::utility::throw_this_exception_helper<std::logic_error>::throw_this_exception(
							+"Static priority queue is empty"
						);
					}
					this->pop_unsafe();
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				void swap(static_priority_queue<T, M> & with)
				{
					c.swap(with);
					kerbal::algorithm::swap(this->vc, with.vc);
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

		};

	} // namespace container


	namespace algorithm
	{

		template <typename T, std::size_t N, typename KeyCompare>
		KERBAL_CONSTEXPR14
		void swap(
			kerbal::container::static_priority_queue<T, N, KeyCompare> & a,
			kerbal::container::static_priority_queue<T, N, KeyCompare> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, std::size_t N, typename KeyCompare>
	KERBAL_CONSTEXPR14
	void swap(
		kerbal::container::static_priority_queue<T, N, KeyCompare> & a,
		kerbal::container::static_priority_queue<T, N, KeyCompare> & b
	)
	KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_STATIC_PRIORITY_QUEUE_HPP
