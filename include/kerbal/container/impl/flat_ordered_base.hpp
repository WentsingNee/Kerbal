/**
 * @file       flat_ordered_base.hpp
 * @brief
 * @date       2019-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_FLAT_ORDERED_BASE_HPP
#define KERBAL_CONTAINER_IMPL_FLAT_ORDERED_BASE_HPP

#include <kerbal/algorithm/binary_search.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/is_same.hpp>
#include <kerbal/utility/as_const.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#include <algorithm>
#include <utility>

namespace kerbal
{

	namespace container
	{

		template <typename Key, typename Entity>
		struct default_extract;

		template <typename Key, typename Value>
		struct default_extract<Key, std::pair<Key, Value> >
		{
				typedef std::pair<Key, Value> Pair;

				KERBAL_CONSTEXPR
				Key& operator()(Pair & p) const KERBAL_NOEXCEPT
				{
					return p.first;
				}

				KERBAL_CONSTEXPR
				const Key& operator()(const Pair & p) const KERBAL_NOEXCEPT
				{
					return p.first;
				}
		};

		template <typename Key>
		struct default_extract<Key, Key>
		{
				KERBAL_CONSTEXPR
				Key& operator()(Key & key) const KERBAL_NOEXCEPT
				{
					return key;
				}

				KERBAL_CONSTEXPR
				const Key& operator()(const Key & key) const KERBAL_NOEXCEPT
				{
					return key;
				}
		};

		namespace detail
		{

			template <typename Entity, typename Key, typename KeyCompare, typename Extract, typename Sequence>
			class __flat_ordered_base
			{
				public:
					typedef KeyCompare				key_compare;
					typedef Key						key_type;
					typedef Entity					value_type;
					typedef const value_type		const_type;
					typedef value_type&				reference;
					typedef const value_type&		const_reference;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type&&			rvalue_reference;
					typedef const value_type&&		const_rvalue_reference;
#			endif

					typedef typename Sequence::size_type				size_type;
					typedef typename Sequence::difference_type			difference_type;

					typedef typename Sequence::iterator					iterator;
					typedef typename Sequence::const_iterator			const_iterator;
					typedef typename Sequence::reverse_iterator			reverse_iterator;
					typedef typename Sequence::const_reverse_iterator	const_reverse_iterator;

				protected:
					kerbal::utility::compressed_pair<Sequence, key_compare> __data;

					/**
					 * @brief Returns the comparison object with which the %set was constructed.
					 */
					Sequence & __sequence()
					{
						return this->__data.first();
					}

					const Sequence & __sequence() const
					{
						return this->__data.first();
					}

					key_compare & __key_comp()
					{
						return this->__data.second();
					}

					const key_compare & __key_comp() const
					{
						return this->__data.second();
					}

					void __sort()
					{
						std::sort(this->__sequence().begin(), this->__sequence().end(), this->value_comp());
					}

					friend struct lower_bound_kc_adapter;

					struct lower_bound_kc_adapter
					{
						private:
							const __flat_ordered_base * self;

						public:
							KERBAL_CONSTEXPR
							explicit lower_bound_kc_adapter(const __flat_ordered_base * self) KERBAL_NOEXCEPT
								: self(self)
							{
							}

							bool operator()(const_reference item, const key_type & key) const
							{
								return self->__key_comp()(Extract()(item), key);
							}
					};

					friend struct upper_bound_kc_adapter;

					struct upper_bound_kc_adapter
					{
						private:
							const __flat_ordered_base * self;

						public:
							KERBAL_CONSTEXPR
							explicit upper_bound_kc_adapter(const __flat_ordered_base * self) KERBAL_NOEXCEPT
								: self(self)
							{
							}

							bool operator()(const key_type & key, const_reference item) const
							{
								return self->__key_comp()(key, Extract()(item));
							}
					};


					friend struct equal_range_kc_adapter;

				private:
					struct __equal_range_kc_adapter_not_same
					{
						private:
							const __flat_ordered_base * self;

						protected:
							KERBAL_CONSTEXPR
							explicit __equal_range_kc_adapter_not_same(const __flat_ordered_base * self) KERBAL_NOEXCEPT
								: self(self)
							{
							}

						public:
							bool operator()(const_reference item, const key_type & key) const
							{
								return self->__key_comp()(Extract()(item), key);
							}

							bool operator()(const key_type & key, const_reference item) const
							{
								return self->__key_comp()(key, Extract()(item));
							}
					};

					struct __equal_range_kc_adapter_same
					{
						private:
							const __flat_ordered_base * self;

						protected:
							KERBAL_CONSTEXPR
							explicit __equal_range_kc_adapter_same(const __flat_ordered_base * self) KERBAL_NOEXCEPT
								: self(self)
							{
							}

						public:
							bool operator()(const_reference item, const key_type & key) const
							{
								return self->__key_comp()(Extract()(item), key);
							}
					};

				protected:
					struct equal_range_kc_adapter:
									kerbal::type_traits::conditional<
											kerbal::type_traits::is_same<
												const key_type &,
												const_reference
											>::value,
											__equal_range_kc_adapter_same,
											__equal_range_kc_adapter_not_same
									>::type
					{
						private:
							typedef typename
							kerbal::type_traits::conditional<
									kerbal::type_traits::is_same<
											const key_type &,
											const_reference
									>::value,
									__equal_range_kc_adapter_same,
									__equal_range_kc_adapter_not_same
							>::type super;

						public:
							KERBAL_CONSTEXPR
							explicit equal_range_kc_adapter(const __flat_ordered_base * self) KERBAL_NOEXCEPT
								: super(self)
							{
							}
					};


				public:
					/**
					 * @brief Returns the comparison object with which the %set was constructed.
					 */
					const key_compare & key_comp() const
					{
						return this->__key_comp();
					}

					class value_compare
					{
							friend class __flat_ordered_base;

							const __flat_ordered_base *self;

							KERBAL_CONSTEXPR
							explicit value_compare(const __flat_ordered_base * self) KERBAL_NOEXCEPT
									: self(self)
							{
							}

						public:
							bool operator()(const_reference lhs, const_reference rhs) const
							{
								return self->__key_comp()(Extract()(lhs), Extract()(rhs));
							}
					};

					value_compare value_comp() const
					{
						return value_compare(this);
					}

				protected:
					__flat_ordered_base() :
							__data()
					{
					}

					explicit __flat_ordered_base(key_compare kc) :
							__data(kerbal::utility::compressed_pair_default_construct_tag(), kc)
					{
					}

					template <typename InputIterator>
					__flat_ordered_base(InputIterator first, InputIterator last,
							typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0)
					{
						try {
							this->__sequence().assign(first, last);
							this->__sort();
						} catch (...) {
							this->clear();
							throw;
						}
					}

					template <typename InputIterator>
					__flat_ordered_base(InputIterator first, InputIterator last, key_compare kc,
							typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0)
					{
						try {
							this->__sequence().assign(first, last);
							this->__sort();
						} catch (...) {
							this->clear();
							throw;
						}
					}


#			if __cplusplus >= 201103L

					__flat_ordered_base(std::initializer_list<value_type> src) :
							__flat_ordered_base(src.begin(), src.end())
					{
					}

					__flat_ordered_base(std::initializer_list<value_type> src, key_compare kc) :
							__flat_ordered_base(src.begin(), src.end(), kc)
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
						this->__sequence().assign(first, last);
						this->__sort();
					}

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->__key_comp() = kc;
						this->assign(first, last);
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

					iterator begin()
					{
						return this->__sequence().begin();
					}

					const_iterator begin() const
					{
						return this->__sequence().begin();
					}

					iterator end()
					{
						return this->__sequence().end();
					}

					const_iterator end() const
					{
						return this->__sequence().end();
					}

					const_iterator cbegin() const
					{
						return kerbal::utility::as_const(this->__sequence()).begin();
					}

					const_iterator cend() const
					{
						return kerbal::utility::as_const(this->__sequence()).end();
					}

					reverse_iterator rbegin()
					{
						return this->__sequence().rbegin();
					}

					const_reverse_iterator rbegin() const
					{
						return this->__sequence().rbegin();
					}

					reverse_iterator rend()
					{
						return this->__sequence().rend();
					}

					const_reverse_iterator rend() const
					{
						return this->__sequence().rend();
					}

					const_reverse_iterator crbegin() const
					{
						return kerbal::utility::as_const(this->__sequence()).crbegin();
					}

					const_reverse_iterator crend() const
					{
						return kerbal::utility::as_const(this->__sequence()).crend();
					}

					iterator nth(size_type index)
					{
						return this->__sequence().nth(index);
					}

					const_iterator nth(size_type index) const
					{
						return this->__sequence().nth(index);
					}

					size_type index_of(iterator it)
					{
						return this->__sequence().index_of(it);
					}

					size_type index_of(const_iterator it) const
					{
						return this->__sequence().index_of(it);
					}

					size_type size() const
					{
						return this->__sequence().size();
					}

					KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT
					{
						return this->__sequence().max_size();
					}

					bool empty() const
					{
						return this->__sequence().empty();
					}

					iterator lower_bound(const key_type & key)
					{
						return kerbal::algorithm::lower_bound(this->begin(), this->end(), key,
															  lower_bound_kc_adapter(this));
					}

					const_iterator lower_bound(const key_type & key) const
					{
						return kerbal::algorithm::lower_bound(this->cbegin(), this->cend(), key,
															  lower_bound_kc_adapter(this));
					}

					iterator lower_bound(const key_type & key, const_iterator hint)
					{
						return kerbal::algorithm::lower_bound_hint(this->begin(), this->end(), key,
																   this->nth(this->index_of(hint)),
																			 lower_bound_kc_adapter(this));
					}

					const_iterator lower_bound(const key_type & key, const_iterator hint) const
					{
						return kerbal::algorithm::lower_bound_hint(this->cbegin(), this->cend(), key, hint,
																   lower_bound_kc_adapter(this));
					}


					iterator upper_bound(const key_type & key)
					{
						return kerbal::algorithm::upper_bound(this->begin(), this->end(), key,
															  upper_bound_kc_adapter(this));
					}

					const_iterator upper_bound(const key_type & key) const
					{
						return kerbal::algorithm::upper_bound(this->cbegin(), this->cend(), key,
															  upper_bound_kc_adapter(this));
					}

					iterator upper_bound(const key_type & key, const_iterator hint)
					{
						return kerbal::algorithm::upper_bound(this->begin(), this->end(), key,
															  upper_bound_kc_adapter(this));
					}

					const_iterator upper_bound(const key_type & key, const_iterator hint) const
					{
						return kerbal::algorithm::upper_bound(this->cbegin(), this->cend(), key,
															  upper_bound_kc_adapter(this));
					}

					std::pair<iterator, iterator>
					equal_range(const key_type & key)
					{
						return kerbal::algorithm::equal_range(this->begin(), this->end(), key,
															  equal_range_kc_adapter(this));
					}

					std::pair<const_iterator, const_iterator>
					equal_range(const key_type & key) const
					{
						return kerbal::algorithm::equal_range(this->cbegin(), this->cend(), key,
															  equal_range_kc_adapter(this));
					}

					std::pair<iterator, iterator>
					equal_range(const key_type & key, const_iterator hint)
					{
						return kerbal::algorithm::equal_range(this->begin(), this->end(), key,
															  equal_range_kc_adapter(this));
					}

					std::pair<const_iterator, const_iterator>
					equal_range(const key_type & key, const_iterator hint) const
					{
						return kerbal::algorithm::equal_range(this->cbegin(), this->cend(), key,
															  equal_range_kc_adapter(this));
					}

				protected:
					const_iterator __find_helper(const_iterator lower_bound_pos, const key_type & key) const
					{
						const_iterator end_it = this->cend();
						if (lower_bound_pos != end_it && this->__key_comp()(key, Extract()(*lower_bound_pos))) {
							// key < *lower_bound_pos
							/*
							* 1 1 1 3 3 3
							*       ^
							*/
							return end_it;
						} else {
							return lower_bound_pos;
						}
					}

				public:
					const_iterator find(const key_type & key) const
					{
						return this->__find_helper(this->lower_bound(key), key);
					}

					const_iterator find(const key_type & key, const_iterator hint) const
					{
						return this->__find_helper(this->lower_bound(key, hint), key);
					}

					size_type count(const key_type & key) const
					{
						std::pair<const_iterator, const_iterator> p(this->equal_range(key));
						return kerbal::iterator::distance(p.first, p.second);
					}

					size_type count(const key_type & key, const_iterator hint) const
					{
						std::pair<const_iterator, const_iterator> p(this->equal_range(key, hint));
						return kerbal::iterator::distance(p.first, p.second);
					}

					bool contains(const key_type & key) const
					{
						return this->find(key) != this->cend();
					}

					bool contains(const key_type & key, const_iterator hint) const
					{
						return this->find(key, hint) != this->cend();
					}

				protected:
					std::pair<iterator, bool>
					__try_insert_helper(iterator lower_bound_pos, const_reference src)
					{
						Extract extract;
						bool inserted = false;
						if (static_cast<bool>(lower_bound_pos == this->cend()) ||
							static_cast<bool>(this->__key_comp()(extract(src), extract(*lower_bound_pos)))) {
							// src < *lower_bound_pos
							lower_bound_pos = this->__sequence().insert(lower_bound_pos, src);
							inserted = true;
						} else {
							inserted = false;
						}
						return std::make_pair(lower_bound_pos, inserted);
					}

				public:
					std::pair<iterator, bool> try_insert(const_reference src)
					{
						return this->__try_insert_helper(this->lower_bound(Extract()(src)), src);
					}

					std::pair<iterator, bool> try_insert(const_iterator hint, const_reference src)
					{
						return this->__try_insert_helper(this->lower_bound(Extract()(src), hint), src);
					}

#			if __cplusplus >= 201103L

				protected:
					std::pair<iterator, bool>
					__try_insert_helper(iterator lower_bound_pos, rvalue_reference src)
					{
						Extract extract;
						bool inserted = false;
						if (static_cast<bool>(lower_bound_pos == this->cend()) ||
							static_cast<bool>(this->__key_comp()(extract(src), extract(*lower_bound_pos)))) {
							// src < *lower_bound_pos
							lower_bound_pos = this->__sequence().insert(lower_bound_pos, std::move(src));
							inserted = true;
						} else {
							inserted = false;
						}
						return std::make_pair(lower_bound_pos, inserted);
					}

				public:
					std::pair<iterator, bool> try_insert(rvalue_reference src)
					{
						return this->__try_insert_helper(this->lower_bound(Extract()(src)), src);
					}

					std::pair<iterator, bool> try_insert(const_iterator hint, rvalue_reference src)
					{
						return this->__try_insert_helper(this->lower_bound(Extract()(src), hint), src);
					}
#			endif

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							InputIterator
					>::type
					try_insert(InputIterator first, InputIterator last)
					{
						while (first != last && this->size() != this->max_size()) {
							this->try_insert(*first);
							++first;
						}
						return first;
					}

					iterator insert(const_reference src)
					{
						return this->__sequence().insert(this->upper_bound(Extract()(src)), src);
					}

					iterator insert(const_iterator hint, const_reference src)
					{
						return this->__sequence().insert(this->upper_bound(Extract()(src), hint), src);
					}

#			if __cplusplus >= 201103L

					iterator insert(rvalue_reference src)
					{
						iterator pos(this->upper_bound(Extract()(src)));
						return this->__sequence().insert(pos, std::move(src));
					}

					iterator insert(const_iterator hint, rvalue_reference src)
					{
						iterator pos(this->upper_bound(Extract()(src), hint));
						return this->__sequence().insert(pos, std::move(src));
					}
#			endif

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							InputIterator
					>::type
					insert(InputIterator first, InputIterator last)
					{
						while (first != last && !this->full()) {
							this->insert(*first);
							++first;
						}
						return first;
					}

					const_iterator erase(const_iterator pos)
					{
						return pos == this->__sequence().end() ? pos : this->__sequence().erase(pos);
					}

					const_iterator erase(const_iterator first, const_iterator last)
					{
						return this->__sequence().erase(first, last);
					}

					size_type erase(const key_type & key)
					{
						std::pair<iterator, iterator> p(this->equal_range(key));
						size_type dis(kerbal::iterator::distance(p.first, p.second));
						this->erase(p.first, p.second);
						return dis;
					}

					const_iterator erase_one(const key_type & key)
					{
						return this->erase(this->find(key));
					}

					void clear()
					{
						this->__sequence().clear();
					}

			};


		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_IMPL_FLAT_ORDERED_BASE_HPP
