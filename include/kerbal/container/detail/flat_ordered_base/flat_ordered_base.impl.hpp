/**
 * @file       flat_ordered_base.impl.hpp
 * @brief
 * @date       2019-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_FLAT_ORDERED_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_FLAT_ORDERED_BASE_IMPL_HPP

#include <kerbal/container/detail/flat_ordered_base/flat_ordered_base.decl.hpp>

#include <kerbal/algorithm/binary_search/equal_range.hpp>
#include <kerbal/algorithm/binary_search/lower_bound.hpp>
#include <kerbal/algorithm/binary_search/lower_bound_hint.hpp>
#include <kerbal/algorithm/binary_search/upper_bound.hpp>
#include <kerbal/algorithm/binary_search/upper_bound_hint.hpp>
#include <kerbal/algorithm/modifier/unique.hpp>
#include <kerbal/algorithm/sort/sort.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/compressed_pair.hpp>

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
			KERBAL_CONSTEXPR14
			void
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			k_sort()
			{
				kerbal::algorithm::sort(sequence.begin(), sequence.end(), this->value_comp());
			}

#		if __cplusplus < 201103L

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			flat_ordered_base()
			{
			}

#		endif

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			flat_ordered_base(key_compare kc) :
				key_compare_compress_helper(kerbal::utility::in_place_t(), kc),
				sequence()
			{
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename InputIterator>
			KERBAL_CONSTEXPR14
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			flat_ordered_base(
				InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					int
				>::type
			) :
				sequence(first, last)
			{
				this->k_sort();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename InputIterator>
			KERBAL_CONSTEXPR14
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			flat_ordered_base(
				InputIterator first, InputIterator last,
				key_compare kc,
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					int
				>::type
			) :
				key_compare_compress_helper(kerbal::utility::in_place_t(), kc),
				sequence(first, last)
			{
				this->k_sort();
			}


#		if __cplusplus >= 201103L

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			flat_ordered_base(
				std::initializer_list<value_type> ilist
			) :
				flat_ordered_base(ilist.begin(), ilist.end())
			{
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			flat_ordered_base(
				std::initializer_list<value_type> ilist, key_compare kc
			) :
				flat_ordered_base(ilist.begin(), ilist.end(), kc)
			{
			}

#		endif

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename InputIterator>
			KERBAL_CONSTEXPR14
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
			>::type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			assign(
				InputIterator first, InputIterator last
			)
			{
				sequence.assign(first, last);
				this->k_sort();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename InputIterator>
			KERBAL_CONSTEXPR14
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
			>::type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			assign(
				InputIterator first, InputIterator last,
				key_compare kc
			)
			{
				this->key_comp() = kc;
				this->assign(first, last);
			}

#		if __cplusplus >= 201103L

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			void
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			assign(std::initializer_list<value_type> ilist)
			{
				this->assign(ilist.begin(), ilist.end());
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			void
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			assign(std::initializer_list<value_type> ilist, key_compare kc)
			{
				this->assign(ilist.begin(), ilist.end(), kc);
			}

#		endif

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			begin()
			{
				return sequence.begin();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			begin() const
			{
				return sequence.begin();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			end()
			{
				return sequence.end();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			end() const
			{
				return sequence.end();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			cbegin() const
			{
				return sequence.begin();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			cend() const
			{
				return sequence.end();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::reverse_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			rbegin()
			{
				return sequence.rbegin();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_reverse_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			rbegin() const
			{
				return sequence.rbegin();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::reverse_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			rend()
			{
				return sequence.rend();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_reverse_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			rend() const
			{
				return sequence.rend();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_reverse_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			crbegin() const
			{
				return sequence.rbegin();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_reverse_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			crend() const
			{
				return sequence.rend();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			nth(size_type index)
			{
				return sequence.nth(index);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			nth(size_type index) const
			{
				return sequence.nth(index);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::size_type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			index_of(iterator it)
			{
				return sequence.index_of(it);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::size_type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			index_of(const_iterator it) const
			{
				return sequence.index_of(it);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::size_type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			size() const
			{
				return sequence.size();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::size_type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			max_size() const KERBAL_NOEXCEPT
			{
				return sequence.max_size();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR
			bool
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			empty() const
			{
				return sequence.empty();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			lower_bound(const key_type & key)
			{
				return kerbal::algorithm::lower_bound(
					this->begin(), this->end(), key,
					lower_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			lower_bound(const key_type & key) const
			{
				return kerbal::algorithm::lower_bound(
					this->cbegin(), this->cend(), key,
					lower_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			lower_bound(const key_type & key, const_iterator hint)
			{
				return kerbal::algorithm::lower_bound_hint(
					this->begin(), this->end(), key,
					hint.cast_to_mutable(), // TODO
					lower_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			lower_bound(const key_type & key, const_iterator hint) const
			{
				return kerbal::algorithm::lower_bound_hint(
					this->cbegin(), this->cend(), key,
					hint,
					lower_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename Key>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::template enable_if_transparent_lookup<
				Key,
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			>::type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			lower_bound(const Key & key)
			{
				return kerbal::algorithm::lower_bound(
					this->begin(), this->end(), key,
					lower_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename Key>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::template enable_if_transparent_lookup<
				Key,
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			>::type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			lower_bound(const Key & key) const
			{
				return kerbal::algorithm::lower_bound(
					this->cbegin(), this->cend(), key,
					lower_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename Key>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::template enable_if_transparent_lookup<
				Key,
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			>::type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			lower_bound(const Key & key, const_iterator hint)
			{
				return kerbal::algorithm::lower_bound_hint(
					this->begin(), this->end(), key, hint,
					lower_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename Key>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::template enable_if_transparent_lookup<
				Key,
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			>::type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			lower_bound(const Key & key, const_iterator hint) const
			{
				return kerbal::algorithm::lower_bound(
					this->cbegin(), this->cend(), key, hint,
					lower_bound_kc_adapter(this)
				);
			}


			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			upper_bound(const key_type & key)
			{
				return kerbal::algorithm::upper_bound(
					this->begin(), this->end(), key,
					upper_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			upper_bound(const key_type & key) const
			{
				return kerbal::algorithm::upper_bound(
					this->cbegin(), this->cend(), key,
					upper_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			upper_bound(const key_type & key, const_iterator hint)
			{
				return kerbal::algorithm::upper_bound_hint(
					this->begin(), this->end(), key,
					hint, // TODO
					upper_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			upper_bound(const key_type & key, const_iterator hint) const
			{
				return kerbal::algorithm::upper_bound_hint(
					this->cbegin(), this->cend(), key,
					hint,
					upper_bound_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator,
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			>
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			equal_range(const key_type & key)
			{
				return kerbal::algorithm::equal_range(
					this->begin(), this->end(), key,
					equal_range_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator,
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			>
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			equal_range(const key_type & key) const
			{
				return kerbal::algorithm::equal_range(
					this->cbegin(), this->cend(), key,
					equal_range_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator,
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			>
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			equal_range(const key_type & key, const_iterator hint)
			{
				return kerbal::algorithm::equal_range(
					this->begin(), this->end(), key,
					equal_range_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			kerbal::utility::compressed_pair<
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator,
				typename flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			>
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			equal_range(const key_type & key, const_iterator hint) const
			{
				return kerbal::algorithm::equal_range(
					this->cbegin(), this->cend(), key,
					equal_range_kc_adapter(this)
				);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			k_find_impl(const_iterator lower_bound_pos, const key_type & key) const
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

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			find(const key_type & key) const
			{
				return this->k_find_impl(this->lower_bound(key), key);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			find(const key_type & key, const_iterator hint) const
			{
				return this->k_find_impl(this->lower_bound(key, hint), key);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::size_type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			count(const key_type & key) const
			{
				kerbal::utility::compressed_pair<const_iterator, const_iterator> p(this->equal_range(key));
				return kerbal::iterator::distance(p.first(), p.second());
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::size_type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			count(const key_type & key, const_iterator hint) const
			{
				kerbal::utility::compressed_pair<const_iterator, const_iterator> p(this->equal_range(key, hint));
				return kerbal::iterator::distance(p.first(), p.second());
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			bool
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			contains(const key_type & key) const
			{
				return this->find(key) != this->cend();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			bool
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			contains(const key_type & key, const_iterator hint) const
			{
				return this->find(key, hint) != this->cend();
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::unique_insert_r
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			k_insert_unique_impl(iterator ub, const_reference src)
			{
				Extract extract;
				bool inserted = false;
				if (static_cast<bool>(ub == this->cbegin()) ||
					static_cast<bool>(this->key_comp()(extract(*kerbal::iterator::prev(ub)), extract(src)))) {
					// ub[-1] < src
					ub = sequence.insert(ub, src);
					inserted = true;
				}
				return unique_insert_r(ub, inserted);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::unique_insert_r
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert_unique(const_reference src)
			{
				return this->k_insert_unique_impl(this->upper_bound(this->extract()(src)), src);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::unique_insert_r
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert_unique(const_iterator hint, const_reference src)
			{
				return this->k_insert_unique_impl(this->upper_bound(this->extract()(src), hint), src);
			}

#		if __cplusplus >= 201103L

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::unique_insert_r
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			k_insert_unique_impl(iterator ub, rvalue_reference src)
			{
				Extract extract;
				bool inserted = false;
				if (static_cast<bool>(ub == this->cbegin()) ||
					static_cast<bool>(this->key_comp()(extract(*kerbal::iterator::prev(ub)), extract(src)))) {
					// ub[-1] < src
					ub = sequence.insert(ub, kerbal::compatibility::move(src));
					inserted = true;
				}
				return unique_insert_r(ub, inserted);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::unique_insert_r
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert_unique(rvalue_reference src)
			{
				return this->k_insert_unique_impl(this->upper_bound(this->extract()(src)), kerbal::compatibility::move(src));
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::unique_insert_r
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert_unique(const_iterator hint, rvalue_reference src)
			{
				return this->k_insert_unique_impl(this->upper_bound(this->extract()(src), hint), kerbal::compatibility::move(src));
			}

#		endif

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename InputIterator>
			KERBAL_CONSTEXPR14
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				InputIterator
			>::type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert_unique(InputIterator first, InputIterator last)
			{
				while (first != last && this->size() != this->max_size()) {
					sequence.push_back(*first);
					++first;
				}
				this->k_sort();
				iterator unique_last(
					kerbal::algorithm::unique(
						sequence.begin(), sequence.end(), equal_adapter(this)
					)
				);
				sequence.erase(unique_last, sequence.end());

				while (first != last && this->size() != this->max_size()) {
					this->insert_unique(*first);
					++first;
				}
				return first;
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert(const_reference src)
			{
				return sequence.insert(this->upper_bound(this->extract()(src)), src);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert(const_iterator hint, const_reference src)
			{
				return sequence.insert(this->upper_bound(this->extract()(src), hint), src);
			}

#		if __cplusplus >= 201103L

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert(rvalue_reference src)
			{
				iterator pos(this->upper_bound(this->extract()(src)));
				return sequence.insert(pos, kerbal::compatibility::move(src));
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert(const_iterator hint, rvalue_reference src)
			{
				iterator pos(this->upper_bound(this->extract()(src), hint));
				return sequence.insert(pos, kerbal::compatibility::move(src));
			}

#		endif

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			template <typename InputIterator>
			KERBAL_CONSTEXPR14
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				InputIterator
			>::type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			insert(InputIterator first, InputIterator last)
			{
				while (first != last && !this->full()) {
					this->insert(*first);
					++first;
				}
				return first;
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			erase(const_iterator pos)
			{
				return pos == sequence.cend() ? pos : sequence.erase(pos);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			erase(const_iterator first, const_iterator last)
			{
				return sequence.erase(first, last);
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::size_type
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			erase(const key_type & key)
			{
				kerbal::utility::compressed_pair<iterator, iterator> p(this->equal_range(key));
				size_type dis(kerbal::iterator::distance(p.first(), p.second()));
				this->erase(p.first(), p.second());
				return dis;
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			typename
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::const_iterator
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			erase_one(const key_type & key)
			{
				return this->erase(this->find(key));
			}

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			KERBAL_CONSTEXPR14
			void
			flat_ordered_base<Entity, Extract, KeyCompare, Sequence>::
			clear()
			{
				sequence.clear();
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_FLAT_ORDERED_BASE_IMPL_HPP
