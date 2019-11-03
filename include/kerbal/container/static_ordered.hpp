/**
 * @file       static_ordered.hpp
 * @brief      
 * @date       2019-8-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ORDERED_HPP_
#define KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ORDERED_HPP_

#include <kerbal/data_struct/static_vector.hpp>
#include <kerbal/algorithm/search.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#include <algorithm>

namespace kerbal
{
	namespace data_struct
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

		template <typename Key, typename Entity, size_t N,
			typename KeyCompare = std::less<Key>, typename Extract = default_extract<Key, Entity> >
		class static_ordered
		{
			public:
				typedef kerbal::data_struct::static_vector<Entity, N> Sequence;
				typedef KeyCompare				key_compare;
				typedef Entity					value_type;
				typedef const Entity			const_type;
				typedef Entity&				reference;
				typedef const Entity&			const_reference;
				typedef Sequence				container_type;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef typename Sequence::size_type				size_type;

				typedef typename Sequence::const_iterator			const_iterator;
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

				struct lower_bound_kc_adapter
				{
						bool operator()(const_reference item, const Key& key) const
						{
							return __key_comp(Extract()(item), key);
						}
				};

				struct upper_bound_kc_adapter
				{
						bool operator()(const Key& key, const_reference item) const
						{
							return __key_comp(key, Extract()(item));
						}
				};

			public:
				/**
				 * @brief Returns the comparison object with which the %set was constructed.
				 */
				const key_compare & key_comp() const
				{
					return this->__data.second();
				}


				static_ordered() :
						__data()
				{
				}

				explicit static_ordered(key_compare kc) :
						__data(kerbal::utility::compressed_pair_default_construct_tag(), kc)
				{
				}

				void clear()
				{
					this->__sequence().clear();
				}

				const_iterator begin() const
				{
					return this->__sequence().cbegin();
				}

				const_iterator end() const
				{
					return this->__sequence().cend();
				}

				const_iterator cbegin() const
				{
					return this->__sequence().cbegin();
				}

				const_iterator cend() const
				{
					return this->__sequence().cend();
				}

				const_reverse_iterator rbegin() const
				{
					return this->__sequence().crbegin();
				}

				const_reverse_iterator rend() const
				{
					return this->__sequence().crend();
				}

				const_reverse_iterator crbegin() const
				{
					return this->__sequence().crbegin();
				}

				const_reverse_iterator crend() const
				{
					return this->__sequence().crend();
				}

				size_type size() const
				{
					return this->__sequence().size();
				}

				/**
				 * @brief Returns the size() of the largest possible static_vector.
				 */
				KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT
				{
					return this->__sequence().max_size();
				}

				bool empty() const
				{
					return this->__sequence().empty();
				}

				bool full() const
				{
					return this->__sequence().full();
				}

				const_iterator lower_bound(const Key& key) const
				{
					return kerbal::algorithm::lower_bound(this->cbegin(), this->cend(), key, lower_bound_kc_adapter());
				}

				const_iterator lower_bound(const Key& key, const_iterator hint) const
				{
					return kerbal::algorithm::lower_bound_hint(this->cbegin(), this->cend(), key, hint, lower_bound_kc_adapter());
				}

				const_iterator upper_bound(const Key& key) const
				{
					return kerbal::algorithm::upper_bound(this->cbegin(), this->cend(), key, upper_bound_kc_adapter());
				}

				std::pair<const_iterator, const_iterator> equal_range(const Key & key) const
				{
					return std::make_pair(this->lower_bound(key), this->upper_bound(key));
				}

				const_iterator find(const Key& key) const
				{
					const_iterator i = this->lower_bound(key);
					const_iterator end_it = this->cend();
					if (i != end_it && this->__key_comp()(key, Extract()(*i))) {
						i = end_it;
					}
					return i;
				}

				const_iterator find(const Key& key, const_iterator hint) const
				{
					const_iterator i = this->lower_bound(key, hint);
					const_iterator end_it = this->cend();
					if (i != end_it && this->__key_comp()(key, Extract()(*i))) {
						i = end_it;
					}
					return i;
				}

				size_type count(const Key& key) const
				{
					return kerbal::iterator::distance(this->lower_bound(key), this->upper_bound(key));
				}

				size_type count(const Key& key, const_iterator hint) const
				{
					return kerbal::iterator::distance(this->lower_bound(key, hint), this->upper_bound(key));
				}

				bool contains(const Key& key) const
				{
					return this->find(key) != this->cend();
				}

				bool contains(const Key& key, const_iterator hint) const
				{
					return this->find(key, hint) != this->cend();
				}

				const_iterator erase(const_iterator iterator)
				{
					return ((iterator == this->cend()) ? this->cend() : this->__sequence().erase(iterator));
				}

		};

	} // namespace data_struct

} // namespace kerbal


#endif /* KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ORDERED_HPP_ */
