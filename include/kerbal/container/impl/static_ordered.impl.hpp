/**
 * @file       static_ordered.impl.hpp
 * @brief
 * @date       2019-8-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_STATIC_ORDERED_IMPL_HPP_
#define KERBAL_CONTAINER_IMPL_STATIC_ORDERED_IMPL_HPP_

namespace kerbal
{

	namespace container
	{

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::static_ordered() :
				__data()
		{
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		explicit static_ordered<Entity, N, Key, KeyCompare, Extract>::static_ordered(key_compare kc) :
				__data(kerbal::utility::compressed_pair_default_construct_tag(), kc)
		{
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		template <typename InputIterator, typename =
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
		>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::static_ordered(InputIterator first, InputIterator last) :
				__data()
		{
			try {
				this->__sequence().assign(first, last);
				std::sort(this->__sequence().begin(), this->__sequence().end());
			} catch (...) {
				this->clear();
				throw;
			}
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		template <typename InputIterator, typename =
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
		>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::static_ordered(InputIterator first, InputIterator last, key_compare kc) :
				__data(kerbal::utility::compressed_pair_default_construct_tag(), kc)
		{
			try {
				this->__sequence().assign(first, last);
				std::sort(this->__sequence().begin(), this->__sequence().end());
			} catch (...) {
				this->clear();
				throw;
			}
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::begin()
		{
			return this->__sequence().begin();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::begin() const
		{
			return this->__sequence().begin();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::end()
		{
			return this->__sequence().end();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::end() const
		{
			return this->__sequence().end();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::cbegin() const
		{
			return this->__sequence().cbegin();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::cend() const
		{
			return this->__sequence().cend();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::reverse_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::rbegin()
		{
			return this->__sequence().rbegin();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_reverse_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::rbegin() const
		{
			return this->__sequence().rbegin();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::reverse_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::rend()
		{
			return this->__sequence().rend();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_reverse_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::rend() const
		{
			return this->__sequence().rend();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_reverse_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::crbegin() const
		{
			return this->__sequence().crbegin();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_reverse_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::crend() const
		{
			return this->__sequence().crend();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::size_type
		static_ordered<Entity, N, Key, KeyCompare, Extract>::size() const
		{
			return this->__sequence().size();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		KERBAL_CONSTEXPR
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::size_type
		static_ordered<Entity, N, Key, KeyCompare, Extract>::max_size() const KERBAL_NOEXCEPT
		{
			return this->__sequence().max_size();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool static_ordered<Entity, N, Key, KeyCompare, Extract>::empty() const
		{
			return this->__sequence().empty();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool static_ordered<Entity, N, Key, KeyCompare, Extract>::full() const
		{
			return this->__sequence().full();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::lower_bound(const Key& key) const
		{
			return kerbal::algorithm::lower_bound(this->cbegin(), this->cend(), key, lower_bound_kc_adapter());
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::lower_bound(const Key& key, const_iterator hint) const
		{
			return kerbal::algorithm::lower_bound_hint(this->cbegin(), this->cend(), key, hint, lower_bound_kc_adapter());
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::upper_bound(const Key& key) const
		{
			return kerbal::algorithm::upper_bound(this->cbegin(), this->cend(), key, upper_bound_kc_adapter());
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		std::pair<
				typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator,
				typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::equal_range(const Key & key) const
		{
			return std::make_pair(this->lower_bound(key), this->upper_bound(key));
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::find(const Key& key) const
		{
			const_iterator i = this->lower_bound(key);
			const_iterator end_it = this->cend();
			if (i != end_it && this->__key_comp()(key, Extract()(*i))) {
				i = end_it;
			}
			return i;
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::find(const Key& key, const_iterator hint) const
		{
			const_iterator i = this->lower_bound(key, hint);
			const_iterator end_it = this->cend();
			if (i != end_it && this->__key_comp()(key, Extract()(*i))) {
				i = end_it;
			}
			return i;
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::size_type
		static_ordered<Entity, N, Key, KeyCompare, Extract>::count(const Key& key) const
		{
			std::pair<const_iterator, const_iterator> p(this->equal_range(key));
			return kerbal::iterator::distance(p.first, p.second);
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::size_type
		static_ordered<Entity, N, Key, KeyCompare, Extract>::count(const Key& key, const_iterator hint) const
		{
			return kerbal::iterator::distance(this->lower_bound(key, hint), this->upper_bound(key));
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool static_ordered<Entity, N, Key, KeyCompare, Extract>::contains(const Key& key) const
		{
			return this->find(key) != this->cend();
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool static_ordered<Entity, N, Key, KeyCompare, Extract>::contains(const Key& key, const_iterator hint) const
		{
			return this->find(key, hint) != this->cend();
		}


#	if __cplusplus >= 201103L

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		template <typename ... Args>
		std::pair<
			typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator,
			bool
		>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::unique_emplace(Args&& ... args)
		{
			value_type val(std::forward<Args>(args)...);
			std::pair<iterator, bool> ret(this->lower_bound(val), false); // first, inserted
			iterator & first = ret.first;
			bool & inserted = ret.second;
			if (first == this->cend() || this->__key_comp()(val, *first)) { // src < *first
				first = this->__sequence().insert(first, std::move(val));
				inserted = true;
			}
			return ret;
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		template <typename ... Args>
		std::pair<
			typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator,
			bool
		>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::unique_emplace_hint(const_iterator hint, Args&& ... args)
		{
			value_type val(std::forward<Args>(args)...);
			std::pair<iterator, bool> ret(this->lower_bound(val, hint), false); // first, inserted
			iterator & first = ret.first;
			bool & inserted = ret.second;
			if (first == this->cend() || this->__key_comp()(val, *first)) { // src < *first
				first = this->__sequence().insert(first, std::move(val));
				inserted = true;
			}
			return ret;
		}

#	endif

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		std::pair<
			typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator,
			bool
		>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::unique_insert(const_reference src)
		{
			std::pair<iterator, bool> ret(this->lower_bound(src), false); // first, inserted
			iterator & first = ret.first;
			bool & inserted = ret.second;
			if (first == this->cend() || this->__key_comp()(src, *first)) { // src < *first
				first = this->__sequence().insert(first, src);
				inserted = true;
			}
			return ret;
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		std::pair<
			typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator,
			bool
		>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::unique_insert(const_iterator hint, const_reference src)
		{
			std::pair<iterator, bool> ret(this->lower_bound(src, hint), false); // first, inserted
			iterator & first = ret.first;
			bool & inserted = ret.second;
			if (first == this->cend() || this->__key_comp()(src, *first)) { // src < *first
				first = this->__sequence().insert(first, src);
				inserted = true;
			}
			return ret;
		}

#	if __cplusplus >= 201103L

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		std::pair<
			typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator,
			bool
		>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::unique_insert(rvalue_reference src)
		{
			std::pair<iterator, bool> ret(this->lower_bound(src), false); // first, inserted
			iterator & first = ret.first;
			bool & inserted = ret.second;
			if (first == this->cend() || this->__key_comp()(src, *first)) { // src < *first
				first = this->__sequence().insert(first, std::move(src));
				inserted = true;
			}
			return ret;
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		std::pair<
			typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator,
			bool
		>
		static_ordered<Entity, N, Key, KeyCompare, Extract>::unique_insert(const_iterator hint, rvalue_reference src)
		{
			std::pair<iterator, bool> ret(this->lower_bound(src, hint), false); // first, inserted
			iterator & first = ret.first;
			bool & inserted = ret.second;
			if (first == this->cend() || this->__key_comp()(src, *first)) { // src < *first
				first = this->__sequence().insert(first, std::move(src));
				inserted = true;
			}
			return ret;
		}
#	endif

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		template <typename InputIterator>
		void static_ordered<Entity, N, Key, KeyCompare, Extract>::unique_insert(InputIterator first, InputIterator last)
		{
			while (first != last && !this->full()) {
				this->unique_insert(*first);
				++first;
			}
		}

#	if __cplusplus >= 201103L

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		template <typename ... Args>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::emplace(Args&& ... args)
		{
			value_type val(std::forward<Args>(args)...);
			return this->__sequence().insert(this->upper_bound(val), std::move(val));
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		template <typename ... Args>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::emplace_hint(const_iterator hint, Args&& ... args)
		{
			value_type val(std::forward<Args>(args)...);
			return this->__sequence().insert(this->upper_bound(val), std::move(val)); // no hint
		}

#	endif

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::insert(const_reference src)
		{
			return this->__sequence().insert(this->upper_bound(src), src);
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::insert(const_iterator hint, const_reference src)
		{
			return this->__sequence().insert(this->upper_bound(src), src); // no hint
		}

#	if __cplusplus >= 201103L

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::insert(rvalue_reference src)
		{
			return this->__sequence().insert(this->upper_bound(src), src);
		}

		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::insert(const_iterator hint, rvalue_reference src)
		{
			return this->__sequence().insert(this->upper_bound(src), src); // no hint
		}
#	endif

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		template <typename InputIterator>
		void static_ordered<Entity, N, Key, KeyCompare, Extract>::insert(InputIterator first, InputIterator last)
		{
			while (first != last && !this->full()) {
				this->insert(*first);
				++first;
			}
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		typename static_ordered<Entity, N, Key, KeyCompare, Extract>::const_iterator
		static_ordered<Entity, N, Key, KeyCompare, Extract>::erase(const_iterator pos)
		{
			return ((pos == this->cend()) ? this->cend() : this->__sequence().erase(pos));
		}

		template <typename Entity, size_t N, typename Key, typename KeyCompare, typename Extract>
		void static_ordered<Entity, N, Key, KeyCompare, Extract>::clear()
		{
			this->__sequence().clear();
		}

	} // namespace container

} // namespace kerbal


#endif /* KERBAL_CONTAINER_IMPL_STATIC_ORDERED_IMPL_HPP_ */
