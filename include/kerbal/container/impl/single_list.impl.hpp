/**
 * @file       single_list.impl.hpp
 * @brief      
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_SINGLE_LIST_IMPL_HPP_
#define KERBAL_CONTAINER_IMPL_SINGLE_LIST_IMPL_HPP_

#include <kerbal/memory/guard.hpp>
#include <kerbal/iterator/iterator.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__node_cast(__sl_node_base * base) KERBAL_NOEXCEPT
		{
			return static_cast<node*>(base);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR
		const typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__node_cast(const __sl_node_base * base) KERBAL_NOEXCEPT
		{
			return static_cast<const node*>(base);
		}

		template <typename Tp, typename Allocator>
		single_list<Tp, Allocator>::single_list() :
				__head(), __last(&this->__head), alloc()
		{
		}

		template <typename Tp, typename Allocator>
		single_list<Tp, Allocator>::single_list(const Allocator& alloc) :
				__head(), __last(&this->__head), alloc(alloc)
		{
		}

		template <typename Tp, typename Allocator>
		single_list<Tp, Allocator>::single_list(const single_list & src) :
				__head(), __last(&this->__head), alloc()
		{
			const_iterator first = src.cbegin();
			const const_iterator last = src.cend();

			while (first != last) {
				this->push_back(*first);
				++first;
			}
		}

		template <typename Tp, typename Allocator>
		single_list<Tp, Allocator>::single_list(const single_list & src, const Allocator& alloc) :
				__head(), __last(&this->__head), alloc(alloc)
		{
			const_iterator first = src.cbegin();
			const const_iterator last = src.cend();

			while (first != last) {
				this->push_back(*first);
				++first;
			}
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		single_list<Tp, Allocator>::single_list(InputIterator first, InputIterator last, const Allocator& alloc,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						, int
				>::type) :
				__head(), __last(&this->__head), alloc(alloc)
		{
			while (first != last) {
				this->push_back(*first);
				++first;
			}
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		single_list<Tp, Allocator>::single_list(single_list && src) :
				__head(std::move(src.__head)), __last(std::move(src.__last)), alloc(std::move(src.alloc))
		{
			src.__head.next == NULL;
			src.__last = src.begin();
		}

#	endif

		template <typename Tp, typename Allocator>
		single_list<Tp, Allocator>::~single_list()
		{
			this->clear();
		}


		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::front()
		{
			return *this->begin();
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::const_reference
		single_list<Tp, Allocator>::front() const
		{
			return *this->cbegin();
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::back()
		{
			return __node_cast(this->end().current)->value();
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::const_reference
		single_list<Tp, Allocator>::back() const
		{
			return __node_cast(this->cend().current)->value();
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::begin() KERBAL_NOEXCEPT
		{
			return iterator(&this->__head);
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::end() KERBAL_NOEXCEPT
		{
			return this->__last;
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::begin() const KERBAL_NOEXCEPT
		{
			return const_iterator(&this->__head);
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::end() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->__last);
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::cbegin() const KERBAL_NOEXCEPT
		{
			return const_iterator(&this->__head);
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::cend() const KERBAL_NOEXCEPT
		{
			return const_iterator(this->__last);
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::iterator
		single_list<Tp, Allocator>::nth(size_type index)
		{
			return kerbal::iterator::next(this->begin(), index);
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::const_iterator
		single_list<Tp, Allocator>::nth(size_type index) const
		{
			return kerbal::iterator::next(this->cbegin(), index);
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::index_of(iterator it)
		{
			return kerbal::iterator::distance(this->begin(), it);
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::index_of(const_iterator it) const
		{
			return kerbal::iterator::distance(this->cbegin(), it);
		}

		template <typename Tp, typename Allocator>
		bool single_list<Tp, Allocator>::empty() const KERBAL_NOEXCEPT
		{
			return this->cbegin() == this->cend();
		}

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::size_type
		single_list<Tp, Allocator>::size() const KERBAL_NOEXCEPT
		{
			return kerbal::iterator::distance(this->cbegin(), this->cend());
		}

		template <typename Tp, typename Allocator>
		void single_list<Tp, Allocator>::__insert_back_helper(node * p) KERBAL_NOEXCEPT
		{
			this->__last.current->next = p;
			++this->__last;
		}

		template <typename Tp, typename Allocator>
		void single_list<Tp, Allocator>::push_back(const_reference src)
		{
			this->emplace_back(src);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		void single_list<Tp, Allocator>::push_back(rvalue_reference src)
		{
			this->emplace_back(src);
		}

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(Args&& ...args)
		{
			node *p = this->__alloc_new_node(std::forward<Args>(args)...);
			this->__insert_back_helper(p);
			return p->value();
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back()
		{
			node *p = this->__alloc_new_node();
			this->__insert_back_helper(p);
			return p->value();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_back(const Arg0 arg0)
		{
			node *p = this->__alloc_new_node(arg0);
			this->__insert_back_helper(p);
			return p->value();
		}

#	endif

		template <typename Tp, typename Allocator>
		void single_list<Tp, Allocator>::__insert_front_helper(node * p) KERBAL_NOEXCEPT
		{
			bool is_empty_before = this->empty();
			p->next = this->__head.next;
			this->__head.next = p;
			if (is_empty_before) {
				++this->__last;
			}
		}

		template <typename Tp, typename Allocator>
		void single_list<Tp, Allocator>::push_front(const_reference src)
		{
			this->emplace_front(src);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		void single_list<Tp, Allocator>::push_front(rvalue_reference src)
		{
			this->emplace_front(src);
		}

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(Args&& ...args)
		{
			node *p = this->__alloc_new_node(std::forward<Args>(args)...);
			this->__insert_front_helper(p);
			return p->value();
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front()
		{
			node *p = this->__alloc_new_node();
			this->__insert_front_helper(p);
			return p->value();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::reference
		single_list<Tp, Allocator>::emplace_front(const Arg0 arg0)
		{
			node *p = this->__alloc_new_node(arg0);
			this->__insert_front_helper(p);
			return p->value();
		}

#	endif

		template <typename Tp, typename Allocator>
		void single_list<Tp, Allocator>::pop_front()
		{
			node *p = __node_cast(this->__head.next);
			this->__head.next = this->__head.next->next;
			if (this->__head.next == NULL) {
				this->__last = this->begin();
			}
			p->~node();
			this->alloc.deallocate(p, 1);
		}

		template <typename Tp, typename Allocator>
		void single_list<Tp, Allocator>::clear()
		{
			while (!this->empty()) {
				this->pop_front();
			}
		}


#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__alloc_new_node(Args&& ...args)
		{
			node *p = this->alloc.allocate(1);
			kerbal::memory::guard<node, release_uninit_res> gd(p, release_uninit_res(this->alloc));
			new (p) node(std::forward<Args>(args)...); // piece bug
			gd.release();
			return p;
		}

#	else

		template <typename Tp, typename Allocator>
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__alloc_new_node();

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__alloc_new_node(const Arg0 & arg0)
		{
			node *p = this->alloc.allocate(1);
			kerbal::memory::guard<node, release_uninit_res> gd(p, release_uninit_res(this->alloc));
			new (p) node(arg0); // piece bug
			gd.release();
			return p;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__alloc_new_node(const Arg0 & arg0, const Arg1 & arg1)
		{
			node *p = this->alloc.allocate(1);
			kerbal::memory::guard<node, release_uninit_res> gd(p, release_uninit_res(this->alloc));
			new (p) node(arg0, arg1); // piece bug
			gd.release();
			return p;
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename single_list<Tp, Allocator>::node*
		single_list<Tp, Allocator>::__alloc_new_node(const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
		{
			node *p = this->alloc.allocate(1);
			kerbal::memory::guard<node, release_uninit_res> gd(p, release_uninit_res(this->alloc));
			new (p) node(arg0, arg1, arg2); // piece bug
			gd.release();
			return p;
		}

#	endif

	} //namespace container

} //namespace kerbal


#endif /* KERBAL_CONTAINER_IMPL_SINGLE_LIST_IMPL_HPP_ */
