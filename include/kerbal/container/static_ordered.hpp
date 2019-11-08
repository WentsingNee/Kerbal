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

#ifndef KERBAL_CONTAINER_STATIC_ORDERED_HPP_
#define KERBAL_CONTAINER_STATIC_ORDERED_HPP_

#include <kerbal/algorithm/search.hpp>
#include <kerbal/container/static_vector.hpp>
#include <kerbal/utility/compressed_pair.hpp>

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

		template <typename Entity, size_t N, typename Key = Entity,
			typename KeyCompare = std::less<Key>, typename Extract = default_extract<Key, Entity> >
		class static_ordered
		{
			public:
				typedef kerbal::container::static_vector<Entity, N> Sequence;
				typedef KeyCompare				key_compare;
				typedef Entity					value_type;
				typedef const Entity			const_type;
				typedef Entity&					reference;
				typedef const Entity&			const_reference;
				typedef Sequence				container_type;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef typename Sequence::size_type				size_type;

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


				static_ordered();

				explicit static_ordered(key_compare kc);

				template <typename InputIterator, typename =
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						>::type
				>
				static_ordered(InputIterator first, InputIterator last);

				template <typename InputIterator, typename =
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						>::type
				>
				static_ordered(InputIterator first, InputIterator last, key_compare kc);

				iterator begin();

				const_iterator begin() const;

				iterator end();

				const_iterator end() const;

				const_iterator cbegin() const;

				const_iterator cend() const;

				reverse_iterator rbegin();

				const_reverse_iterator rbegin() const;

				reverse_iterator rend();

				const_reverse_iterator rend() const;

				const_reverse_iterator crbegin() const;

				const_reverse_iterator crend() const;

				size_type size() const;

				/**
				 * @brief Returns the size() of the largest possible static_vector.
				 */
				KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT;

				bool empty() const;

				bool full() const;

				const_iterator lower_bound(const Key& key) const;

				const_iterator lower_bound(const Key& key, const_iterator hint) const;

				const_iterator upper_bound(const Key& key) const;

				//const_iterator upper_bound(const Key& key, const_iterator hint) const;

				std::pair<const_iterator, const_iterator> equal_range(const Key & key) const;

				const_iterator find(const Key& key) const;

				const_iterator find(const Key& key, const_iterator hint) const;

				size_type count(const Key& key) const;

				size_type count(const Key& key, const_iterator hint) const;

				bool contains(const Key& key) const;

				bool contains(const Key& key, const_iterator hint) const;

#		if __cplusplus >= 201103L

				template <typename ... Args>
				std::pair<iterator, bool> unique_emplace(Args&& ... args);

				template <typename ... Args>
				std::pair<iterator, bool> unique_emplace_hint(const_iterator hint, Args&& ... args);

#		endif

				std::pair<iterator, bool> unique_insert(const_reference src);

				std::pair<iterator, bool> unique_insert(const_iterator hint, const_reference src);

#	if __cplusplus >= 201103L

				std::pair<iterator, bool> unique_insert(rvalue_reference src);

				std::pair<iterator, bool> unique_insert(const_iterator hint, rvalue_reference src);
#	endif

				template <typename InputIterator>
				void unique_insert(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				template <typename ... Args>
				iterator emplace(Args&& ... args);

				template <typename ... Args>
				iterator emplace_hint(const_iterator hint, Args&& ... args);

#		endif

				iterator insert(const_reference src);

				iterator insert(const_iterator hint, const_reference src);

#	if __cplusplus >= 201103L

				iterator insert(rvalue_reference src);

				iterator insert(const_iterator hint, rvalue_reference src);
#	endif

				template <typename InputIterator>
				void insert(InputIterator first, InputIterator last)
				{
					while (first != last && !this->full()) {
						this->insert(*first);
						++first;
					}
				}

				const_iterator erase(const_iterator pos);

				const_iterator erase(const_iterator first, const_iterator last);

				size_type erase(const_reference val);

				void clear();

		};

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/static_ordered.impl.hpp>

#endif /* KERBAL_CONTAINER_STATIC_ORDERED_HPP_ */
