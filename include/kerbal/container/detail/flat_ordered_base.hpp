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

#ifndef KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_HPP

#include <kerbal/algorithm/binary_search/equal_range.hpp>
#include <kerbal/algorithm/binary_search/lower_bound.hpp>
#include <kerbal/algorithm/binary_search/lower_bound_hint.hpp>
#include <kerbal/algorithm/binary_search/upper_bound.hpp>
#include <kerbal/algorithm/binary_search/upper_bound_hint.hpp>
#include <kerbal/algorithm/modifier/unique.hpp>
#include <kerbal/algorithm/sort.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>
#include <kerbal/utility/as_const.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_copy_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#endif

#include <utility> // std::pair


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

			template <typename KeyCompare>
			class flat_ordered_key_compare_overload:
					private kerbal::utility::member_compress_helper<KeyCompare>
			{
				private:
					typedef kerbal::utility::member_compress_helper<KeyCompare> super;

				protected:
					typedef KeyCompare				key_compare;

				protected:
					KERBAL_CONSTEXPR
					flat_ordered_key_compare_overload()
							KERBAL_CONDITIONAL_NOEXCEPT(
									kerbal::type_traits::tribool_is_true<
										kerbal::type_traits::is_nothrow_default_constructible<super>
									>::value
							)
							: super(kerbal::utility::in_place_t())
					{
					}

					KERBAL_CONSTEXPR
					explicit
					flat_ordered_key_compare_overload(const key_compare & kc)
							KERBAL_CONDITIONAL_NOEXCEPT(
									kerbal::type_traits::tribool_is_true<
										kerbal::type_traits::is_nothrow_copy_constructible<super>
									>::value
							)
							: super(kerbal::utility::in_place_t(), kc)
					{
					}

					KERBAL_CONSTEXPR14
					key_compare& key_comp_obj() KERBAL_NOEXCEPT
					{
						return super::member();
					}

					KERBAL_CONSTEXPR14
					const key_compare& key_comp_obj() const KERBAL_NOEXCEPT
					{
						return super::member();
					}

			};


			template <typename Entity, typename Key, typename KeyCompare, typename Extract, typename Sequence>
			class flat_ordered_base:
					private flat_ordered_key_compare_overload<KeyCompare>
			{
				private:
					typedef flat_ordered_key_compare_overload<KeyCompare> key_compare_overload;

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
					Sequence sequence;

					using key_compare_overload::key_comp_obj;

					KERBAL_CONSTEXPR14
					void k_sort()
					{
						kerbal::algorithm::sort(sequence.begin(), sequence.end(), this->value_comp());
					}

//#			if __cplusplus >= 201402L
//
//					KERBAL_CONSTEXPR14
//					auto lower_bound_adapter() const
//					{
//						return [this](const_reference item, const key_type & key) -> bool {
//							return this->key_comp_obj()(Extract()(item), Extract()(key));
//						};
//					}
//
//#			else

					friend struct lower_bound_kc_adapter;

					struct lower_bound_kc_adapter
					{
						private:
							const flat_ordered_base * self;

						public:
							KERBAL_CONSTEXPR
							explicit lower_bound_kc_adapter(const flat_ordered_base * self) KERBAL_NOEXCEPT
								: self(self)
							{
							}

							KERBAL_CONSTEXPR14
							bool operator()(const_reference item, const key_type & key) const
							{
								return self->key_comp_obj()(Extract()(item), key);
							}
					};

//#			endif


//#			if __cplusplus >= 201402L
//
//					KERBAL_CONSTEXPR14
//					auto upper_bound_adapter() const
//					{
//						return [this](const key_type & key, const_reference item) -> bool {
//							return this->key_comp_obj()(key, Extract()(item));
//						};
//					}
//
//#			else

					friend struct upper_bound_kc_adapter;

					struct upper_bound_kc_adapter
					{
						private:
							const flat_ordered_base * self;

						public:
							KERBAL_CONSTEXPR
							explicit upper_bound_kc_adapter(const flat_ordered_base * self) KERBAL_NOEXCEPT
								: self(self)
							{
							}

							KERBAL_CONSTEXPR14
							bool operator()(const key_type & key, const_reference item) const
							{
								return self->key_comp_obj()(key, Extract()(item));
							}
					};


//#			endif


					friend struct equal_range_kc_adapter;

				private:
					struct equal_range_kc_adapter_not_same
					{
						private:
							const flat_ordered_base * self;

						protected:
							KERBAL_CONSTEXPR
							explicit equal_range_kc_adapter_not_same(const flat_ordered_base * self) KERBAL_NOEXCEPT
								: self(self)
							{
							}

						public:
							bool operator()(const_reference item, const key_type & key) const
							{
								return self->key_comp_obj()(Extract()(item), key);
							}

							bool operator()(const key_type & key, const_reference item) const
							{
								return self->key_comp_obj()(key, Extract()(item));
							}
					};

					struct equal_range_kc_adapter_same
					{
						private:
							const flat_ordered_base * self;

						protected:
							KERBAL_CONSTEXPR
							explicit equal_range_kc_adapter_same(const flat_ordered_base * self) KERBAL_NOEXCEPT
								: self(self)
							{
							}

						public:
							bool operator()(const_reference item, const key_type & key) const
							{
								return self->key_comp_obj()(Extract()(item), key);
							}
					};

				protected:
					struct equal_range_kc_adapter:
									kerbal::type_traits::conditional<
											kerbal::type_traits::is_same<
												const key_type &,
												const_reference
											>::value,
											equal_range_kc_adapter_same,
											equal_range_kc_adapter_not_same
									>::type
					{
						private:
							typedef typename
							kerbal::type_traits::conditional<
									kerbal::type_traits::is_same<
											const key_type &,
											const_reference
									>::value,
									equal_range_kc_adapter_same,
									equal_range_kc_adapter_not_same
							>::type super;

						public:
							KERBAL_CONSTEXPR
							explicit equal_range_kc_adapter(const flat_ordered_base * self) KERBAL_NOEXCEPT
								: super(self)
							{
							}
					};


				public:

					/**
					 * @brief Returns the comparison object with which the %set was constructed.
					 */
					KERBAL_CONSTEXPR14
					const key_compare & key_comp() const
					{
						return this->key_comp_obj();
					}

#			if __cplusplus >= 201402L

					KERBAL_CONSTEXPR14
					auto value_comp() const
					{
						return [this](const_reference lhs, const_reference rhs) -> bool {
							return this->key_comp_obj()(Extract()(lhs), Extract()(rhs));
						};
					}

#			else

					class value_compare
					{
							friend class flat_ordered_base;

							const flat_ordered_base *self;

							KERBAL_CONSTEXPR
							explicit value_compare(const flat_ordered_base * self) KERBAL_NOEXCEPT
									: self(self)
							{
							}

						public:
							bool operator()(const_reference lhs, const_reference rhs) const
							{
								return self->key_comp_obj()(Extract()(lhs), Extract()(rhs));
							}
					};

					value_compare value_comp() const
					{
						return value_compare(this);
					}

#			endif

				protected:

					KERBAL_CONSTEXPR
					flat_ordered_base() :
							key_compare_overload(), sequence()
					{
					}

					KERBAL_CONSTEXPR
					explicit flat_ordered_base(key_compare kc) :
							key_compare_overload(kc), sequence()
					{
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_ordered_base(InputIterator first, InputIterator last,
									  typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							key_compare_overload(), sequence(first, last)
					{
						this->k_sort();
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_ordered_base(InputIterator first, InputIterator last, key_compare kc,
									  typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							key_compare_overload(kc), sequence(first, last)
					{
						this->k_sort();
					}


#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					flat_ordered_base(std::initializer_list<value_type> src) :
							flat_ordered_base(src.begin(), src.end())
					{
					}

					KERBAL_CONSTEXPR14
					flat_ordered_base(std::initializer_list<value_type> src, key_compare kc) :
							flat_ordered_base(src.begin(), src.end(), kc)
					{
					}

#			endif

				public:
					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last)
					{
						sequence.assign(first, last);
						this->k_sort();
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->key_comp_obj() = kc;
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					void assign(std::initializer_list<value_type> src)
					{
						this->assign(src.begin(), src.end());
					}

					KERBAL_CONSTEXPR14
					void assign(std::initializer_list<value_type> src, key_compare kc)
					{
						this->assign(src.begin(), src.end(), kc);
					}

#			endif

					KERBAL_CONSTEXPR14
					iterator begin()
					{
						return sequence.begin();
					}

					KERBAL_CONSTEXPR14
					const_iterator begin() const
					{
						return sequence.begin();
					}

					KERBAL_CONSTEXPR14
					iterator end()
					{
						return sequence.end();
					}

					KERBAL_CONSTEXPR14
					const_iterator end() const
					{
						return sequence.end();
					}

					KERBAL_CONSTEXPR
					const_iterator cbegin() const
					{
						return sequence.begin();
					}

					KERBAL_CONSTEXPR
					const_iterator cend() const
					{
						return sequence.end();
					}

					KERBAL_CONSTEXPR14
					reverse_iterator rbegin()
					{
						return sequence.rbegin();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator rbegin() const
					{
						return sequence.rbegin();
					}

					KERBAL_CONSTEXPR14
					reverse_iterator rend()
					{
						return sequence.rend();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator rend() const
					{
						return sequence.rend();
					}

					KERBAL_CONSTEXPR
					const_reverse_iterator crbegin() const
					{
						return sequence.rbegin();
					}

					KERBAL_CONSTEXPR
					const_reverse_iterator crend() const
					{
						return sequence.rend();
					}

					KERBAL_CONSTEXPR14
					iterator nth(size_type index)
					{
						return sequence.nth(index);
					}

					KERBAL_CONSTEXPR14
					const_iterator nth(size_type index) const
					{
						return sequence.nth(index);
					}

					KERBAL_CONSTEXPR14
					size_type index_of(iterator it)
					{
						return sequence.index_of(it);
					}

					KERBAL_CONSTEXPR
					size_type index_of(const_iterator it) const
					{
						return sequence.index_of(it);
					}

					KERBAL_CONSTEXPR
					size_type size() const
					{
						return sequence.size();
					}

					KERBAL_CONSTEXPR
					size_type max_size() const KERBAL_NOEXCEPT
					{
						return sequence.max_size();
					}

					KERBAL_CONSTEXPR
					bool empty() const
					{
						return sequence.empty();
					}

					KERBAL_CONSTEXPR14
					iterator lower_bound(const key_type & key)
					{
						return kerbal::algorithm::lower_bound(this->begin(), this->end(), key,
															  lower_bound_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					const_iterator lower_bound(const key_type & key) const
					{
						return kerbal::algorithm::lower_bound(this->cbegin(), this->cend(), key,
															  lower_bound_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					iterator lower_bound(const key_type & key, const_iterator hint)
					{
						return kerbal::algorithm::lower_bound_hint(this->begin(), this->end(), key, hint.cast_to_mutable(),
																	 lower_bound_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					const_iterator lower_bound(const key_type & key, const_iterator hint) const
					{
						return kerbal::algorithm::lower_bound_hint(this->cbegin(), this->cend(), key, hint,
																   lower_bound_kc_adapter(this));
					}


					KERBAL_CONSTEXPR14
					iterator upper_bound(const key_type & key)
					{
						return kerbal::algorithm::upper_bound(this->begin(), this->end(), key,
															  upper_bound_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					const_iterator upper_bound(const key_type & key) const
					{
						return kerbal::algorithm::upper_bound(this->cbegin(), this->cend(), key,
															  upper_bound_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					iterator upper_bound(const key_type & key, const_iterator hint)
					{
						return kerbal::algorithm::upper_bound_hint(this->begin(), this->end(), key, hint,
															  upper_bound_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					const_iterator upper_bound(const key_type & key, const_iterator hint) const
					{
						return kerbal::algorithm::upper_bound_hint(this->cbegin(), this->cend(), key, hint,
															  upper_bound_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					std::pair<iterator, iterator>
					equal_range(const key_type & key)
					{
						return kerbal::algorithm::equal_range(this->begin(), this->end(), key,
															  equal_range_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					std::pair<const_iterator, const_iterator>
					equal_range(const key_type & key) const
					{
						return kerbal::algorithm::equal_range(this->cbegin(), this->cend(), key,
															  equal_range_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					std::pair<iterator, iterator>
					equal_range(const key_type & key, const_iterator hint)
					{
						return kerbal::algorithm::equal_range(this->begin(), this->end(), key,
															  equal_range_kc_adapter(this));
					}

					KERBAL_CONSTEXPR14
					std::pair<const_iterator, const_iterator>
					equal_range(const key_type & key, const_iterator hint) const
					{
						return kerbal::algorithm::equal_range(this->cbegin(), this->cend(), key,
															  equal_range_kc_adapter(this));
					}

				protected:
					KERBAL_CONSTEXPR14
					const_iterator k_find_impl(const_iterator lower_bound_pos, const key_type & key) const
					{
						const_iterator end_it(this->cend());
						if (lower_bound_pos != end_it && this->key_comp_obj()(key, Extract()(*lower_bound_pos))) {
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
					KERBAL_CONSTEXPR14
					const_iterator find(const key_type & key) const
					{
						return this->k_find_impl(this->lower_bound(key), key);
					}

					KERBAL_CONSTEXPR14
					const_iterator find(const key_type & key, const_iterator hint) const
					{
						return this->k_find_impl(this->lower_bound(key, hint), key);
					}

					KERBAL_CONSTEXPR14
					size_type count(const key_type & key) const
					{
						std::pair<const_iterator, const_iterator> p(this->equal_range(key));
						return kerbal::iterator::distance(p.first, p.second);
					}

					KERBAL_CONSTEXPR14
					size_type count(const key_type & key, const_iterator hint) const
					{
						std::pair<const_iterator, const_iterator> p(this->equal_range(key, hint));
						return kerbal::iterator::distance(p.first, p.second);
					}

					KERBAL_CONSTEXPR14
					bool contains(const key_type & key) const
					{
						return this->find(key) != this->cend();
					}

					KERBAL_CONSTEXPR14
					bool contains(const key_type & key, const_iterator hint) const
					{
						return this->find(key, hint) != this->cend();
					}

				protected:
					KERBAL_CONSTEXPR14
					std::pair<iterator, bool>
					k_try_insert_impl(iterator ub, const_reference src)
					{
						Extract extract;
						bool inserted = false;
						if (static_cast<bool>(ub == this->cbegin()) ||
							static_cast<bool>(this->key_comp_obj()(extract(*kerbal::iterator::prev(ub)), extract(src)))) {
							// ub[-1] < src
							ub = sequence.insert(ub, src);
							inserted = true;
						}
						return std::make_pair(ub, inserted);
					}

				public:
					KERBAL_CONSTEXPR14
					std::pair<iterator, bool> try_insert(const_reference src)
					{
						return this->k_try_insert_impl(this->upper_bound(Extract()(src)), src);
					}

					KERBAL_CONSTEXPR14
					std::pair<iterator, bool> try_insert(const_iterator hint, const_reference src)
					{
						return this->k_try_insert_impl(this->upper_bound(Extract()(src), hint), src);
					}

#			if __cplusplus >= 201103L

				protected:
					KERBAL_CONSTEXPR14
					std::pair<iterator, bool>
					k_try_insert_impl(iterator ub, rvalue_reference src)
					{
						Extract extract;
						bool inserted = false;
						if (static_cast<bool>(ub == this->cbegin()) ||
							static_cast<bool>(this->key_comp_obj()(extract(*kerbal::iterator::prev(ub)), extract(src)))) {
							// ub[-1] < src
							ub = sequence.insert(ub, kerbal::compatibility::move(src));
							inserted = true;
						}
						return std::make_pair(ub, inserted);
					}

				public:
					KERBAL_CONSTEXPR14
					std::pair<iterator, bool> try_insert(rvalue_reference src)
					{
						return this->k_try_insert_impl(this->upper_bound(Extract()(src)), kerbal::compatibility::move(src));
					}

					KERBAL_CONSTEXPR14
					std::pair<iterator, bool> try_insert(const_iterator hint, rvalue_reference src)
					{
						return this->k_try_insert_impl(this->upper_bound(Extract()(src), hint), kerbal::compatibility::move(src));
					}

#			endif

					struct equal_adapter
					{
						private:
							const flat_ordered_base * self;

						public:
							KERBAL_CONSTEXPR
							explicit equal_adapter(const flat_ordered_base * self) KERBAL_NOEXCEPT
									: self(self)
							{
							}

							KERBAL_CONSTEXPR14
							bool operator()(const_reference lhs, const_reference rhs) const
							{
								Extract e;
								return !static_cast<bool>(self->key_comp_obj()(e(lhs), e(rhs))) &&
										!static_cast<bool>(self->key_comp_obj()(e(rhs), e(lhs)));
							}
					};

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							InputIterator
					>::type
					try_insert(InputIterator first, InputIterator last)
					{
						while (first != last && this->size() != this->max_size()) {
							sequence.push_back(*first);
							++first;
						}
						this->k_sort();
						iterator unique_last(kerbal::algorithm::unique(
											sequence.begin(),
											sequence.end(), equal_adapter(this)));
						sequence.erase(unique_last, sequence.end());

						while (first != last && this->size() != this->max_size()) {
							this->try_insert(*first);
							++first;
						}
						return first;
					}

					KERBAL_CONSTEXPR14
					iterator insert(const_reference src)
					{
						return sequence.insert(this->upper_bound(Extract()(src)), src);
					}

					KERBAL_CONSTEXPR14
					iterator insert(const_iterator hint, const_reference src)
					{
						return sequence.insert(this->upper_bound(Extract()(src), hint), src);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					iterator insert(rvalue_reference src)
					{
						iterator pos(this->upper_bound(Extract()(src)));
						return sequence.insert(pos, kerbal::compatibility::move(src));
					}

					KERBAL_CONSTEXPR14
					iterator insert(const_iterator hint, rvalue_reference src)
					{
						iterator pos(this->upper_bound(Extract()(src), hint));
						return sequence.insert(pos, kerbal::compatibility::move(src));
					}

#			endif

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
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

					KERBAL_CONSTEXPR14
					const_iterator erase(const_iterator pos)
					{
						return pos == sequence.cend() ? pos : sequence.erase(pos);
					}

					KERBAL_CONSTEXPR14
					const_iterator erase(const_iterator first, const_iterator last)
					{
						return sequence.erase(first, last);
					}

					KERBAL_CONSTEXPR14
					size_type erase(const key_type & key)
					{
						std::pair<iterator, iterator> p(this->equal_range(key));
						size_type dis(kerbal::iterator::distance(p.first, p.second));
						this->erase(p.first, p.second);
						return dis;
					}

					KERBAL_CONSTEXPR14
					const_iterator erase_one(const key_type & key)
					{
						return this->erase(this->find(key));
					}

					KERBAL_CONSTEXPR14
					void clear()
					{
						sequence.clear();
					}

			};


		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_HPP
