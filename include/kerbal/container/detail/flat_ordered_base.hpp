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
#include <kerbal/algorithm/sort/sort.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/container/associative_container_facility/key_compare_is_transparent.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/transform_iterator.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/compressed_pair.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			class flat_ordered_base :
				private kerbal::utility::member_compress_helper<Extract>,
				private kerbal::utility::member_compress_helper<KeyCompare>
			{
				private:
					typedef kerbal::utility::member_compress_helper<Extract>	extract_compress_helper;
					typedef kerbal::utility::member_compress_helper<KeyCompare>	key_compare_compress_helper;

				public:
					typedef Entity					value_type;
					typedef const value_type		const_type;
					typedef value_type &			reference;
					typedef const value_type &		const_reference;
					typedef value_type *			pointer;
					typedef const value_type *		const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type &&			rvalue_reference;
					typedef const value_type &&		const_rvalue_reference;
#			endif

					typedef typename Sequence::size_type				size_type;
					typedef typename Sequence::difference_type			difference_type;

					typedef typename Sequence::iterator					iterator;
					typedef typename Sequence::const_iterator			const_iterator;
					typedef typename Sequence::reverse_iterator			reverse_iterator;
					typedef typename Sequence::const_reverse_iterator	const_reverse_iterator;
					typedef kerbal::container::associative_unique_insert_r<iterator>
																		unique_insert_r;

					typedef typename Extract::key_type					key_type;
					typedef KeyCompare									key_compare;

				protected:
					Sequence sequence;

					KERBAL_CONSTEXPR14
					void
					k_sort()
					{
						kerbal::algorithm::sort(
							this->sequence.begin(),
							this->sequence.end(),
							this->value_comp()
						);
					}

				public:

					KERBAL_CONSTEXPR14
					Extract &
					extract() KERBAL_NOEXCEPT
					{
						return extract_compress_helper::member();
					}

					KERBAL_CONSTEXPR
					const Extract &
					extract() const KERBAL_NOEXCEPT
					{
						return extract_compress_helper::member();
					}

					KERBAL_CONSTEXPR14
					key_compare &
					key_comp() KERBAL_NOEXCEPT
					{
						return key_compare_compress_helper::member();
					}

					/**
					 * @brief Returns the comparison object with which the %set was constructed.
					 */
					KERBAL_CONSTEXPR
					const key_compare &
					key_comp() const KERBAL_NOEXCEPT
					{
						return key_compare_compress_helper::member();
					}

					class value_compare
					{
							friend class flat_ordered_base;

							const flat_ordered_base * self;

							KERBAL_CONSTEXPR
							explicit
							value_compare(const flat_ordered_base * self) KERBAL_NOEXCEPT :
								self(self)
							{
							}

						public:
							KERBAL_CONSTEXPR
							bool
							operator()(const_reference lhs, const_reference rhs) const
							{
								return self->key_comp()(self->extract()(lhs), self->extract()(rhs));
							}
					};

					KERBAL_CONSTEXPR
					value_compare
					value_comp() const
					{
						return value_compare(this);
					}


				//===================
				// construct/copy/destroy

				protected:

					KERBAL_CONSTEXPR
					flat_ordered_base() :
						key_compare_compress_helper(), sequence()
					{
					}

					KERBAL_CONSTEXPR
					explicit
					flat_ordered_base(key_compare kc) :
						key_compare_compress_helper(kerbal::utility::in_place_t(), kc), sequence()
					{
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_ordered_base(
						InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0
					) :
						key_compare_compress_helper(), sequence(first, last)
					{
						this->k_sort();
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_ordered_base(
						InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0
					) :
						key_compare_compress_helper(kerbal::utility::in_place_t(), kc), sequence(first, last)
					{
						this->k_sort();
					}


#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					flat_ordered_base(std::initializer_list<value_type> ilist) :
						flat_ordered_base(ilist.begin(), ilist.end())
					{
					}

					KERBAL_CONSTEXPR14
					flat_ordered_base(std::initializer_list<value_type> ilist, key_compare kc) :
						flat_ordered_base(ilist.begin(), ilist.end(), kc)
					{
					}

#			else

					flat_ordered_base(const kerbal::assign::assign_list<void> & ilist) :
						key_compare_compress_helper(),
						sequence()
					{
					}

					flat_ordered_base(const kerbal::assign::assign_list<void> & ilist, key_compare kc) :
						key_compare_compress_helper(kerbal::utility::in_place_t(), kc),
						sequence()
					{
					}

					template <typename U>
					flat_ordered_base(const kerbal::assign::assign_list<U> & ilist) :
						key_compare_compress_helper(),
						sequence(ilist.cbegin(), ilist.cend())
					{
						this->k_sort();
					}

					template <typename U>
					flat_ordered_base(const kerbal::assign::assign_list<U> & ilist, key_compare kc) :
						key_compare_compress_helper(kerbal::utility::in_place_t(), kc),
						sequence(ilist.cbegin(), ilist.cend())
					{
						this->k_sort();
					}

#			endif


				//===================
				// assign

				protected:

					KERBAL_CONSTEXPR14
					void
					assign(const flat_ordered_base & src)
					{
						this->assign(src.cbegin(), src.cend(), src.key_comp());
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					void
					assign(flat_ordered_base && src)
					{
						this->key_comp() = kerbal::compatibility::move(src.key_comp());
						this->sequence = kerbal::compatibility::move(src.sequence);
						this->k_sort();
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
						this->sequence.assign(first, last);
						this->k_sort();
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->key_comp() = kc;
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					void
					assign(std::initializer_list<value_type> ilist)
					{
						this->assign(ilist.begin(), ilist.end());
					}

					KERBAL_CONSTEXPR14
					void
					assign(std::initializer_list<value_type> ilist, key_compare kc)
					{
						this->assign(ilist.begin(), ilist.end(), kc);
					}

#			else

					void
					assign(const kerbal::assign::assign_list<void> & ilist)
					{
						this->clear();
					}

					void
					assign(const kerbal::assign::assign_list<void> & ilist, key_compare kc)
					{
						this->clear();
						this->key_comp() = kc;
					}

					template <typename U>
					void
					assign(const kerbal::assign::assign_list<U> & ilist)
					{
						this->assign(ilist.cbegin(), ilist.cend());
					}

					template <typename U>
					void
					assign(const kerbal::assign::assign_list<U> & ilist, key_compare kc)
					{
						this->assign(ilist.cbegin(), ilist.cend(), kc);
					}

#			endif


				//===================
				// iterator

				public:

					KERBAL_CONSTEXPR14
					iterator
					begin()
					{
						return this->sequence.begin();
					}

					KERBAL_CONSTEXPR
					const_iterator
					begin() const
					{
						return this->sequence.begin();
					}

					KERBAL_CONSTEXPR14
					iterator
					end()
					{
						return this->sequence.end();
					}

					KERBAL_CONSTEXPR
					const_iterator
					end() const
					{
						return this->sequence.end();
					}

					KERBAL_CONSTEXPR
					const_iterator
					cbegin() const
					{
						return this->sequence.begin();
					}

					KERBAL_CONSTEXPR
					const_iterator
					cend() const
					{
						return this->sequence.end();
					}

					KERBAL_CONSTEXPR14
					reverse_iterator
					rbegin()
					{
						return this->sequence.rbegin();
					}

					KERBAL_CONSTEXPR
					const_reverse_iterator
					rbegin() const
					{
						return this->sequence.rbegin();
					}

					KERBAL_CONSTEXPR14
					reverse_iterator
					rend()
					{
						return this->sequence.rend();
					}

					KERBAL_CONSTEXPR
					const_reverse_iterator
					rend() const
					{
						return this->sequence.rend();
					}

					KERBAL_CONSTEXPR
					const_reverse_iterator
					crbegin() const
					{
						return this->sequence.rbegin();
					}

					KERBAL_CONSTEXPR
					const_reverse_iterator
					crend() const
					{
						return this->sequence.rend();
					}

					KERBAL_CONSTEXPR14
					iterator
					nth(size_type index)
					{
						return this->sequence.nth(index);
					}

					KERBAL_CONSTEXPR
					const_iterator
					nth(size_type index) const
					{
						return this->sequence.nth(index);
					}

					KERBAL_CONSTEXPR14
					size_type
					index_of(iterator it)
					{
						return this->sequence.index_of(it);
					}

					KERBAL_CONSTEXPR
					size_type
					index_of(const_iterator it) const
					{
						return this->sequence.index_of(it);
					}


				//===================
				// capacity

				public:

					KERBAL_CONSTEXPR
					size_type
					size() const
					{
						return this->sequence.size();
					}

					KERBAL_CONSTEXPR
					size_type
					max_size() const KERBAL_NOEXCEPT
					{
						return this->sequence.max_size();
					}

					KERBAL_CONSTEXPR
					bool
					empty() const
					{
						return this->sequence.empty();
					}


				//===================
				// lookup

				protected:
					friend struct key_view_iterator_extract_adapter;

					struct key_view_iterator_extract_adapter
					{
						public:
							typedef typename Extract::key_type const & result_type;

						private:
							const flat_ordered_base * k_self;

						public:
							KERBAL_CONSTEXPR
							explicit
							key_view_iterator_extract_adapter(const flat_ordered_base * self) KERBAL_NOEXCEPT :
								k_self(self)
							{
							}

							KERBAL_CONSTEXPR
							result_type
							operator()(const_reference item) const
							{
								return k_self->extract()(item);
							}
					};

					template <typename Iterator>
					KERBAL_CONSTEXPR
					kerbal::iterator::transform_iterator<Iterator, key_view_iterator_extract_adapter>
					make_key_view_iterator(Iterator iterator) const
					{
						return kerbal::iterator::transform_iterator<Iterator, key_view_iterator_extract_adapter>(
							iterator,
							key_view_iterator_extract_adapter(this)
						);
					}

					typedef kerbal::iterator::transform_iterator<iterator, key_view_iterator_extract_adapter>		key_view_iterator;
					typedef kerbal::iterator::transform_iterator<const_iterator, key_view_iterator_extract_adapter>	key_view_const_iterator;

					KERBAL_CONSTEXPR14
					key_view_iterator
					key_view_begin()
					{
						return this->make_key_view_iterator(this->begin());
					}

					KERBAL_CONSTEXPR
					key_view_const_iterator
					key_view_begin() const
					{
						return this->make_key_view_iterator(this->begin());
					}

					KERBAL_CONSTEXPR
					key_view_const_iterator
					key_view_cbegin() const
					{
						return this->make_key_view_iterator(this->begin());
					}

					KERBAL_CONSTEXPR14
					key_view_iterator
					key_view_end()
					{
						return this->make_key_view_iterator(this->end());
					}

					KERBAL_CONSTEXPR
					key_view_const_iterator
					key_view_end() const
					{
						return this->make_key_view_iterator(this->end());
					}

					KERBAL_CONSTEXPR
					key_view_const_iterator
					key_view_cend() const
					{
						return this->make_key_view_iterator(this->end());
					}

				public:

					template <
						typename Key, typename Result
					>
					struct enable_if_transparent_lookup :
						kerbal::type_traits::enable_if<
							(
								kerbal::container::key_compare_is_transparent<KeyCompare>::value &&
								!kerbal::type_traits::is_same<const Key &, const typename Extract::key_type &>::value &&
								!kerbal::type_traits::is_same<Key, const_iterator>::value &&
								!kerbal::type_traits::is_same<Key, iterator>::value
							),
							Result
						>
					{
					};


				public:

					KERBAL_CONSTEXPR14
					iterator
					lower_bound(const key_type & key)
					{
						return kerbal::algorithm::lower_bound(
							this->key_view_begin(), this->key_view_end(), key,
							this->key_comp()
						).base();
					}

					KERBAL_CONSTEXPR14
					const_iterator
					lower_bound(const key_type & key) const
					{
						return kerbal::algorithm::lower_bound(
							this->key_view_cbegin(), this->key_view_cend(), key,
							this->key_comp()
						).base();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						iterator
					>::type
					lower_bound(const Key & key)
					{
						return kerbal::algorithm::lower_bound(
							this->key_view_begin(), this->key_view_end(), key,
							this->key_comp()
						).base();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					lower_bound(const Key & key) const
					{
						return kerbal::algorithm::lower_bound(
							this->key_view_cbegin(), this->key_view_cend(), key,
							this->key_comp()
						).base();
					}

					KERBAL_CONSTEXPR14
					iterator
					lower_bound(const_iterator hint, const key_type & key)
					{
						return kerbal::algorithm::lower_bound_hint(
							this->key_view_begin(), this->key_view_end(), key,
							this->make_key_view_iterator(
								kerbal::container::nth(*this, kerbal::container::index_of(*this, hint))
							),
							this->key_comp()
						).base();
					}

					KERBAL_CONSTEXPR14
					const_iterator
					lower_bound(const_iterator hint, const key_type & key) const
					{
						return kerbal::algorithm::lower_bound_hint(
							this->key_view_cbegin(), this->key_view_cend(), key,
							this->make_key_view_iterator(hint),
							this->key_comp()
						).base();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						iterator
					>::type
					lower_bound(const_iterator hint, const Key & key)
					{
						return kerbal::algorithm::lower_bound_hint(
							this->key_view_begin(), this->key_view_end(), key,
							this->make_key_view_iterator(
								kerbal::container::nth(*this, kerbal::container::index_of(*this, hint))
							),
							this->key_comp()
						).base();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					lower_bound(const_iterator hint, const Key & key) const
					{
						return kerbal::algorithm::lower_bound_hint(
							this->key_view_cbegin(), this->key_view_cend(), key,
							this->make_key_view_iterator(hint),
							this->key_comp()
						).base();
					}


					KERBAL_CONSTEXPR14
					iterator
					upper_bound(const key_type & key)
					{
						return kerbal::algorithm::upper_bound(
							this->key_view_begin(), this->key_view_end(), key,
							this->key_comp()
						).base();
					}

					KERBAL_CONSTEXPR14
					const_iterator
					upper_bound(const key_type & key) const
					{
						return kerbal::algorithm::upper_bound(
							this->key_view_cbegin(), this->key_view_cend(), key,
							this->key_comp()
						).base();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						iterator
					>::type
					upper_bound(const Key & key)
					{
						return kerbal::algorithm::upper_bound(
							this->key_view_begin(), this->key_view_end(), key,
							this->key_comp()
						).base();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					upper_bound(const Key & key) const
					{
						return kerbal::algorithm::upper_bound(
							this->key_view_cbegin(), this->key_view_cend(), key,
							this->key_comp()
						).base();
					}

					KERBAL_CONSTEXPR14
					iterator
					upper_bound(const_iterator hint, const key_type & key)
					{
						return kerbal::algorithm::upper_bound_hint(
							this->key_view_begin(), this->key_view_end(), key,
							this->make_key_view_iterator(
								kerbal::container::nth(*this, kerbal::container::index_of(*this, hint))
							),
							this->key_comp()
						).base();
					}

					KERBAL_CONSTEXPR14
					const_iterator
					upper_bound(const_iterator hint, const key_type & key) const
					{
						return kerbal::algorithm::upper_bound_hint(
							this->key_view_cbegin(), this->key_view_cend(), key,
							this->make_key_view_iterator(hint),
							this->key_comp()
						).base();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						iterator
					>::type
					upper_bound(const_iterator hint, const Key & key)
					{
						return kerbal::algorithm::upper_bound_hint(
							this->key_view_begin(), this->key_view_end(), key,
							this->make_key_view_iterator(
								kerbal::container::nth(*this, kerbal::container::index_of(*this, hint))
							),
							this->key_comp()
						).base();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					upper_bound(const_iterator hint, const Key & key) const
					{
						return kerbal::algorithm::upper_bound_hint(
							this->key_view_cbegin(), this->key_view_cend(), key,
							this->make_key_view_iterator(hint),
							this->key_comp()
						).base();
					}

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<iterator, iterator>
					equal_range(const key_type & key)
					{
						kerbal::utility::compressed_pair<key_view_iterator, key_view_iterator> eqr(
							kerbal::algorithm::equal_range(
								this->key_view_begin(), this->key_view_end(), key,
								this->key_comp()
							)
						);
						return kerbal::utility::compressed_pair<iterator, iterator>(
							eqr.first().base(),
							eqr.second().base()
						);
					}

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
					equal_range(const key_type & key) const
					{
						kerbal::utility::compressed_pair<key_view_const_iterator, key_view_const_iterator> eqr(
							kerbal::algorithm::equal_range(
								this->key_view_cbegin(), this->key_view_cend(), key,
								this->key_comp()
							)
						);
						return kerbal::utility::compressed_pair<const_iterator, const_iterator>(
							eqr.first().base(),
							eqr.second().base()
						);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						kerbal::utility::compressed_pair<iterator, iterator>
					>::type
					equal_range(const Key & key)
					{
						kerbal::utility::compressed_pair<key_view_iterator, key_view_iterator> eqr(
							kerbal::algorithm::equal_range(
								this->key_view_begin(), this->key_view_end(), key,
								this->key_comp()
							)
						);
						return kerbal::utility::compressed_pair<iterator, iterator>(
							eqr.first().base(),
							eqr.second().base()
						);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						kerbal::utility::compressed_pair<const_iterator, const_iterator>
					>::type
					equal_range(const Key & key) const
					{
						kerbal::utility::compressed_pair<key_view_const_iterator, key_view_const_iterator> eqr(
							kerbal::algorithm::equal_range(
								this->key_view_cbegin(), this->key_view_cend(), key,
								this->key_comp()
							)
						);
						return kerbal::utility::compressed_pair<const_iterator, const_iterator>(
							eqr.first().base(),
							eqr.second().base()
						);
					}

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<iterator, iterator>
					equal_range(const_iterator hint, const key_type & key)
					{
						kerbal::utility::compressed_pair<key_view_iterator, key_view_iterator> eqr(
							kerbal::algorithm::equal_range(
								this->key_view_begin(), this->key_view_end(), key,
								this->key_comp()
							)
						);
						return kerbal::utility::compressed_pair<iterator, iterator>(
							eqr.first().base(),
							eqr.second().base()
						);
					}

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
					equal_range(const_iterator hint, const key_type & key) const
					{
						kerbal::utility::compressed_pair<key_view_const_iterator, key_view_const_iterator> eqr(
							kerbal::algorithm::equal_range(
								this->key_view_cbegin(), this->key_view_cend(), key,
								this->key_comp()
							)
						);
						return kerbal::utility::compressed_pair<const_iterator, const_iterator>(
							eqr.first().base(),
							eqr.second().base()
						);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						kerbal::utility::compressed_pair<iterator, iterator>
					>::type
					equal_range(const_iterator hint, const Key & key)
					{
						kerbal::utility::compressed_pair<key_view_iterator, key_view_iterator> eqr(
							kerbal::algorithm::equal_range(
								this->key_view_begin(), this->key_view_end(), key,
								this->key_comp()
							)
						);
						return kerbal::utility::compressed_pair<iterator, iterator>(
							eqr.first().base(),
							eqr.second().base()
						);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						kerbal::utility::compressed_pair<const_iterator, const_iterator>
					>::type
					equal_range(const_iterator hint, const Key & key) const
					{
						kerbal::utility::compressed_pair<key_view_const_iterator, key_view_const_iterator> eqr(
							kerbal::algorithm::equal_range(
								this->key_view_cbegin(), this->key_view_cend(), key,
								this->key_comp()
							)
						);
						return kerbal::utility::compressed_pair<const_iterator, const_iterator>(
							eqr.first().base(),
							eqr.second().base()
						);
					}

				protected:
					template <typename Key>
					KERBAL_CONSTEXPR14
					iterator
					k_find_impl(iterator lower_bound_pos, const Key & key)
					{
						iterator end_it(this->end());
						if (lower_bound_pos != end_it && this->key_comp()(key, this->extract()(*lower_bound_pos))) {
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

					template <typename Key>
					KERBAL_CONSTEXPR14
					const_iterator
					k_find_impl(const_iterator lower_bound_pos, const Key & key) const
					{
						const_iterator end_it(this->cend());
						if (lower_bound_pos != end_it && this->key_comp()(key, this->extract()(*lower_bound_pos))) {
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
					iterator
					find(const key_type & key)
					{
						return this->k_find_impl(this->lower_bound(key), key);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					find(const key_type & key) const
					{
						return this->k_find_impl(this->lower_bound(key), key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						iterator
					>::type
					find(const Key & key)
					{
						return this->k_find_impl(this->lower_bound(key), key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					find(const Key & key) const
					{
						return this->k_find_impl(this->lower_bound(key), key);
					}

					KERBAL_CONSTEXPR14
					iterator
					find(const_iterator hint, const key_type & key)
					{
						return this->k_find_impl(this->lower_bound(hint, key), key);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					find(const_iterator hint, const key_type & key) const
					{
						return this->k_find_impl(this->lower_bound(hint, key), key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						iterator
					>::type
					find(const_iterator hint, const Key & key)
					{
						return this->k_find_impl(this->lower_bound(hint, key), key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					find(const_iterator hint, const Key & key) const
					{
						return this->k_find_impl(this->lower_bound(hint, key), key);
					}

					KERBAL_CONSTEXPR14
					size_type
					count(const key_type & key) const
					{
						kerbal::utility::compressed_pair<const_iterator, const_iterator> p(this->equal_range(key));
						return kerbal::iterator::distance(p.first(), p.second());
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						size_type
					>::type
					count(const Key & key) const
					{
						kerbal::utility::compressed_pair<const_iterator, const_iterator> p(this->equal_range(key));
						return kerbal::iterator::distance(p.first(), p.second());
					}

					KERBAL_CONSTEXPR14
					size_type
					count(const_iterator hint, const key_type & key) const
					{
						kerbal::utility::compressed_pair<const_iterator, const_iterator> p(this->equal_range(hint, key));
						return kerbal::iterator::distance(p.first(), p.second());
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						size_type
					>::type
					count(const_iterator hint, const Key & key) const
					{
						kerbal::utility::compressed_pair<const_iterator, const_iterator> p(this->equal_range(hint, key));
						return kerbal::iterator::distance(p.first(), p.second());
					}

					KERBAL_CONSTEXPR14
					bool
					contains(const key_type & key) const
					{
						return this->find(key) != this->cend();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						bool
					>::type
					contains(const Key & key) const
					{
						return this->find(key) != this->cend();
					}

					KERBAL_CONSTEXPR14
					bool
					contains(const_iterator hint, const key_type & key) const
					{
						return this->find(hint, key) != this->cend();
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						bool
					>::type
					contains(const_iterator hint, const Key & key) const
					{
						return this->find(hint, key) != this->cend();
					}


				//===================
				// insert

				protected:
					KERBAL_CONSTEXPR14
					unique_insert_r
					k_insert_unique_impl(iterator ub, const_reference src)
					{
						Extract & e = this->extract();
						bool inserted = false;
						if (static_cast<bool>(ub == this->cbegin()) ||
							static_cast<bool>(this->key_comp()(e(*kerbal::iterator::prev(ub)), e(src)))) {
							// ub[-1] < src
							ub = this->sequence.insert(ub, src);
							inserted = true;
						}
						return unique_insert_r(ub, inserted);
					}

				public:
					KERBAL_CONSTEXPR14
					unique_insert_r
					insert_unique(const_reference src)
					{
						return this->k_insert_unique_impl(this->upper_bound(this->extract()(src)), src);
					}

					KERBAL_CONSTEXPR14
					unique_insert_r
					insert_unique(const_iterator hint, const_reference src)
					{
						return this->k_insert_unique_impl(this->upper_bound(hint, this->extract()(src)), src);
					}

#			if __cplusplus >= 201103L

				protected:
					KERBAL_CONSTEXPR14
					unique_insert_r
					k_insert_unique_impl(iterator ub, rvalue_reference src)
					{
						Extract & e = this->extract();
						bool inserted = false;
						if (static_cast<bool>(ub == this->cbegin()) ||
							static_cast<bool>(this->key_comp()(e(*kerbal::iterator::prev(ub)), e(src)))) {
							// ub[-1] < src
							ub = this->sequence.insert(ub, kerbal::compatibility::move(src));
							inserted = true;
						}
						return unique_insert_r(ub, inserted);
					}

				public:
					KERBAL_CONSTEXPR14
					unique_insert_r
					insert_unique(rvalue_reference src)
					{
						return this->k_insert_unique_impl(this->upper_bound(this->extract()(src)), kerbal::compatibility::move(src));
					}

					KERBAL_CONSTEXPR14
					unique_insert_r
					insert_unique(const_iterator hint, rvalue_reference src)
					{
						return this->k_insert_unique_impl(this->upper_bound(hint, this->extract()(src)), kerbal::compatibility::move(src));
					}

#			endif

					struct equal_adapter
					{
						private:
							const flat_ordered_base * self;

						public:
							KERBAL_CONSTEXPR
							explicit
							equal_adapter(const flat_ordered_base * self) KERBAL_NOEXCEPT :
								self(self)
							{
							}

							KERBAL_CONSTEXPR14
							bool
							operator()(const_reference lhs, const_reference rhs) const
							{
								Extract const & e = self->extract();
								return
									!static_cast<bool>(self->key_comp()(e(lhs), e(rhs))) &&
									!static_cast<bool>(self->key_comp()(e(rhs), e(lhs)))
								;
							}
					};

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						InputIterator
					>::type
					insert_unique(InputIterator first, InputIterator last)
					{
						while (first != last && this->size() != this->max_size()) {
							this->sequence.push_back(*first);
							++first;
						}
						this->k_sort();
						iterator unique_last(
							kerbal::algorithm::unique(
								this->sequence.begin(), this->sequence.end(), equal_adapter(this)
							)
						);
						this->sequence.erase(unique_last, this->sequence.end());

						while (first != last && this->size() != this->max_size()) {
							this->insert_unique(*first);
							++first;
						}
						return first;
					}

					KERBAL_CONSTEXPR14
					iterator
					insert(const_reference src)
					{
						return this->sequence.insert(this->upper_bound(this->extract()(src)), src);
					}

					KERBAL_CONSTEXPR14
					iterator
					insert(const_iterator hint, const_reference src)
					{
						return this->sequence.insert(this->upper_bound(hint, this->extract()(src)), src);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					iterator
					insert(rvalue_reference src)
					{
						iterator pos(this->upper_bound(this->extract()(src)));
						return this->sequence.insert(pos, kerbal::compatibility::move(src));
					}

					KERBAL_CONSTEXPR14
					iterator
					insert(const_iterator hint, rvalue_reference src)
					{
						iterator pos(this->upper_bound(hint, this->extract()(src)));
						return this->sequence.insert(pos, kerbal::compatibility::move(src));
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


				//===================
				// erase

				public:

					KERBAL_CONSTEXPR14
					const_iterator
					erase(const_iterator pos)
					{
						return pos == this->sequence.cend() ? pos : this->sequence.erase(pos);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					erase(const_iterator first, const_iterator last)
					{
						return this->sequence.erase(first, last);
					}

					KERBAL_CONSTEXPR14
					size_type
					erase(const key_type & key)
					{
						kerbal::utility::compressed_pair<iterator, iterator> p(this->equal_range(key));
						size_type dis(kerbal::iterator::distance(p.first(), p.second()));
						this->erase(p.first(), p.second());
						return dis;
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						size_type
					>::type
					erase(const Key & key)
					{
						kerbal::utility::compressed_pair<iterator, iterator> p(this->equal_range(key));
						size_type dis(kerbal::iterator::distance(p.first(), p.second()));
						this->erase(p.first(), p.second());
						return dis;
					}

					KERBAL_CONSTEXPR14
					size_type
					erase(const_iterator hint, const key_type & key)
					{
						kerbal::utility::compressed_pair<iterator, iterator> p(this->equal_range(hint, key));
						size_type dis(kerbal::iterator::distance(p.first(), p.second()));
						this->erase(p.first(), p.second());
						return dis;
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						size_type
					>::type
					erase(const_iterator hint, const Key & key)
					{
						kerbal::utility::compressed_pair<iterator, iterator> p(this->equal_range(hint, key));
						size_type dis(kerbal::iterator::distance(p.first(), p.second()));
						this->erase(p.first(), p.second());
						return dis;
					}

					KERBAL_CONSTEXPR14
					const_iterator
					erase_one(const key_type & key)
					{
						return this->erase(this->find(key));
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					erase_one(const Key & key)
					{
						return this->erase(this->find(key));
					}

					KERBAL_CONSTEXPR14
					const_iterator
					erase_one(const_iterator hint, const key_type & key)
					{
						return this->erase(this->find(hint, key));
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					erase_one(const_iterator hint, const Key & key)
					{
						return this->erase(this->find(hint, key));
					}

					KERBAL_CONSTEXPR14
					void
					clear()
					{
						this->sequence.clear();
					}

			};


		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_HPP
