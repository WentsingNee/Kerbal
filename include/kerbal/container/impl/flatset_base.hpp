/**
 * @file       flatset_base.hpp
 * @brief
 * @date       2019-12-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_FLATSET_BASE_HPP_
#define KERBAL_CONTAINER_IMPL_FLATSET_BASE_HPP_

#include <kerbal/algorithm/search.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp, typename Ordered>
			class __flatset_base
			{
				public:
					typedef Tp						value_type;
					typedef const value_type		const_type;
					typedef value_type&				reference;
					typedef const value_type&		const_reference;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type&&			rvalue_reference;
					typedef const value_type&&		const_rvalue_reference;
#			endif

					typedef typename Ordered::size_type					size_type;
					typedef typename Ordered::difference_type				difference_type;

					typedef typename Ordered::const_iterator				const_iterator;
					typedef typename Ordered::const_reverse_iterator		const_reverse_iterator;
					typedef typename Ordered::key_compare					key_compare;

				protected:

					Ordered __data;

					typename Ordered::Sequence & __sequence()
					{
						return this->__data.__sequence();
					}

					const typename Ordered::Sequence & __sequence() const
					{
						return this->__data.__sequence();
					}

					Ordered & __ordered_agent()
					{
						return this->__data;
					}

					const Ordered & __ordered_agent() const
					{
						return this->__data;
					}

					key_compare & __key_comp()
					{
						return this->__ordered_agent().__key_comp();
					}

					const key_compare & __key_comp() const
					{
						return this->__ordered_agent().__key_comp();
					}

				public:

					const key_compare & key_comp() const
					{
						return this->__ordered_agent().key_comp();
					}

				protected:
					__flatset_base() :
							__data()
					{
					}

					explicit __flatset_base(key_compare kc) :
							__data(kc)
					{
					}

					template <typename InputIterator>
					__flatset_base(InputIterator first, InputIterator last,
							typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							__data(first, last)
					{
					}

					template <typename InputIterator>
					__flatset_base(InputIterator first, InputIterator last, key_compare kc,
							typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							__data(first, last, kc)
					{
					}

#			if __cplusplus >= 201103L
					__flatset_base(std::initializer_list<value_type> src) :
							__data(src.begin(), src.end())
					{
					}

					__flatset_base(std::initializer_list<value_type> src, key_compare kc) :
							__data(src.begin(), src.end(), kc)
					{
					}
#			endif

				public:

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last)
					{
						this->__ordered_agent().assign(first, last);
					}

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->__ordered_agent().assign(first, last, kc);
					}

#			if __cplusplus >= 201103L

					void assign(std::initializer_list<value_type> src)
					{
						this->assign(src.begin(), src.end());
					}

					void assign(std::initializer_list<value_type> src, key_compare kc)
					{
						this->assign(src.begin(), src.end(), kc);
					}

#			endif

					const_iterator begin() const
					{
						return this->__ordered_agent().begin();
					}

					const_iterator end() const
					{
						return this->__ordered_agent().end();
					}

					const_iterator cbegin() const
					{
						return this->__ordered_agent().cbegin();
					}

					const_iterator cend() const
					{
						return this->__ordered_agent().cend();
					}

					const_reverse_iterator rbegin() const
					{
						return this->__ordered_agent().rbegin();
					}

					const_reverse_iterator rend() const
					{
						return this->__ordered_agent().rend();
					}

					const_reverse_iterator crbegin() const
					{
						return this->__ordered_agent().crbegin();
					}

					const_reverse_iterator crend() const
					{
						return this->__ordered_agent().crend();
					}

					const_iterator nth(size_type index) const
					{
						return this->__ordered_agent().nth(index);
					}

					size_type index_of(const_iterator it) const
					{
						return this->__ordered_agent().index_of(it);
					}

					size_type size() const
					{
						return this->__ordered_agent().size();
					}

					KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT
					{
						return this->__ordered_agent().max_size();
					}

					bool empty() const
					{
						return this->__ordered_agent().empty();
					}

					const_iterator lower_bound(const_reference key) const
					{
						return this->__ordered_agent().lower_bound(key);
					}

					const_iterator lower_bound(const_reference key, const_iterator hint) const
					{
						return this->__ordered_agent().lower_bound(key, hint);
					}

					const_iterator upper_bound(const_reference key) const
					{
						return this->__ordered_agent().upper_bound(key);
					}

					const_iterator upper_bound(const_reference key, const_iterator hint) const
					{
						return this->__ordered_agent().upper_bound(key, hint);
					}

					std::pair<const_iterator, const_iterator> equal_range(const_reference key) const
					{
						return this->__ordered_agent().equal_range(key);
					}

					const_iterator find(const_reference key) const
					{
						return this->__ordered_agent().find(key);
					}

					const_iterator find(const_reference key, const_iterator hint) const
					{
						return this->__ordered_agent().find(key, hint);
					}

					size_type count(const_reference key) const
					{
						return this->contains(key) ? 1 : 0;
					}

					size_type count(const_reference key, const_iterator hint) const
					{
						return this->contains(key, hint) ? 1 : 0;
					}

					bool contains(const_reference key) const
					{
						return this->__ordered_agent().contains(key);
					}

					bool contains(const_reference key, const_iterator hint) const
					{
						return this->__ordered_agent().contains(key, hint);
					}

#			if __cplusplus >= 201103L

					template <typename ... Args>
					std::pair<const_iterator, bool> emplace(Args&& ... args)
					{
						value_type val(std::forward<Args>(args)...);
						std::pair<const_iterator, bool> ret(this->lower_bound(val), false); // first, inserted
						const_iterator & first = ret.first;
						bool & inserted = ret.second;
						if (first == this->cend() || this->__key_comp()(val, *first)) { // src < *first
							first = const_iterator(this->__sequence().insert(first, std::move(val)));
							inserted = true;
						}
						return ret;
					}

					template <typename ... Args>
					std::pair<const_iterator, bool> emplace_hint(const_iterator hint, Args&& ... args)
					{
						value_type val(std::forward<Args>(args)...);
						std::pair<const_iterator, bool> ret(this->lower_bound(val, hint), false); // first, inserted
						const_iterator & first = ret.first;
						bool & inserted = ret.second;
						if (first == this->cend() || this->__key_comp()(val, *first)) { // src < *first
							first = const_iterator(this->__sequence().insert(first, std::move(val)));
							inserted = true;
						}
						return ret;
					}

#			endif

					std::pair<const_iterator, bool> insert(const_reference src)
					{
						return this->__ordered_agent().unique_insert(src);
					}

					std::pair<const_iterator, bool> insert(const_iterator hint, const_reference src)
					{
						return this->__ordered_agent().unique_insert(hint, src);
					}

#			if __cplusplus >= 201103L

					std::pair<const_iterator, bool> insert(rvalue_reference src)
					{
						return this->__ordered_agent().unique_insert(std::move(src));
					}

					std::pair<const_iterator, bool> insert(const_iterator hint, rvalue_reference src)
					{
						return this->__ordered_agent().unique_insert(hint, std::move(src));
					}

#			endif

					template <typename InputIterator>
					void insert(InputIterator first, InputIterator last)
					{
						this->__ordered_agent().unique_insert(first, last);
					}

//					template <typename InputIterator>
//					void nearly_ordered_insert(InputIterator first, InputIterator last)
//					{
//						const_iterator pos = this->cbegin();
//						while (first != last && !this->full()) {
//							const_reference src = *first;
//							pos = this->lower_bound(src, pos);
//							if (pos == this->cend() || this->__key_comp()(src, *pos)) { // src < *pos
//								pos = this->__sequence().insert(pos, src);
//							}
//							++first;
//						}
//					}

					const_iterator erase(const_iterator pos)
					{
						return this->__ordered_agent().erase(pos);
					}

					const_iterator erase(const_iterator first, const_iterator last)
					{
						return this->__ordered_agent().erase(first, last);
					}

					const_iterator erase(const_reference val)
					{
						return this->__ordered_agent().erase_one(val);
					}

					const_iterator erase(const_iterator hint, const_reference val)
					{
						const_iterator pos = this->find(val, hint);
						return this->erase(pos);
					}

					void clear()
					{
						this->__ordered_agent().clear();
					}

			};

		}
	}
}


#endif /* KERBAL_CONTAINER_IMPL_FLATSET_BASE_HPP_ */
