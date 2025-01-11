/**
 * @file       flat_set_common_base.hpp
 * @brief
 * @date       2024-04-07
 * @author     Peter
 * @remark     split from kerbal/container/detail/flat_set_base.hpp
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FLAT_SET_COMMON_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_FLAT_SET_COMMON_BASE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/compressed_pair.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Ordered>
			class flat_set_common_base
			{
				public:
					typedef typename Ordered::value_type				value_type;
					typedef typename Ordered::const_type				const_type;
					typedef typename Ordered::reference					reference;
					typedef typename Ordered::const_reference			const_reference;
					typedef typename Ordered::pointer					pointer;
					typedef typename Ordered::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
					typedef typename Ordered::rvalue_reference			rvalue_reference;
					typedef typename Ordered::const_rvalue_reference	const_rvalue_reference;
#		endif

					typedef typename Ordered::size_type					size_type;
					typedef typename Ordered::difference_type			difference_type;

					typedef typename Ordered::const_iterator			const_iterator;
					typedef typename Ordered::const_reverse_iterator	const_reverse_iterator;

					typedef typename Ordered::key_type					key_type;
					typedef typename Ordered::key_compare				key_compare;


				protected:

					Ordered ordered;

				public:

					KERBAL_CONSTEXPR14
					key_compare &
					key_comp() KERBAL_NOEXCEPT
					{
						return this->ordered.key_comp();
					}

					KERBAL_CONSTEXPR14
					const key_compare &
					key_comp() const KERBAL_NOEXCEPT
					{
						return this->ordered.key_comp();
					}


				//===================
				// construct/copy/destroy

				protected:

					KERBAL_CONSTEXPR
					flat_set_common_base() :
						ordered()
					{
					}

					KERBAL_CONSTEXPR
					explicit
					flat_set_common_base(key_compare kc) :
						ordered(kc)
					{
					}


				//===================
				// iterator

				public:

					KERBAL_CONSTEXPR14
					const_iterator
					begin() const
					{
						return this->ordered.begin();
					}

					KERBAL_CONSTEXPR14
					const_iterator
					end() const
					{
						return this->ordered.end();
					}

					KERBAL_CONSTEXPR14
					const_iterator
					cbegin() const
					{
						return this->ordered.cbegin();
					}

					KERBAL_CONSTEXPR14
					const_iterator
					cend() const
					{
						return this->ordered.cend();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator
					rbegin() const
					{
						return this->ordered.rbegin();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator
					rend() const
					{
						return this->ordered.rend();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator
					crbegin() const
					{
						return this->ordered.crbegin();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator
					crend() const
					{
						return this->ordered.crend();
					}

					KERBAL_CONSTEXPR14
					const_iterator
					nth(size_type index) const
					{
						return this->ordered.nth(index);
					}

					KERBAL_CONSTEXPR
					size_type
					index_of(const_iterator it) const
					{
						return this->ordered.index_of(it);
					}


				//===================
				// capacity

				public:

					KERBAL_CONSTEXPR
					size_type
					size() const
					{
						return this->ordered.size();
					}

					KERBAL_CONSTEXPR
					size_type
					max_size() const KERBAL_NOEXCEPT
					{
						return this->ordered.max_size();
					}

					KERBAL_CONSTEXPR
					bool
					empty() const
					{
						return this->ordered.empty();
					}


				//===================
				// lookup

				protected:
					template <
						typename Key, typename Result
					>
					struct enable_if_transparent_lookup :
						Ordered::template enable_if_transparent_lookup<Key, Result>
					{
					};

				public:

					KERBAL_CONSTEXPR14
					const_iterator
					lower_bound(const key_type & key) const
					{
						return this->ordered.lower_bound(key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					lower_bound(const Key & key) const
					{
						return this->ordered.lower_bound(key);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					lower_bound(const_iterator hint, const key_type & key) const
					{
						return this->ordered.lower_bound(hint, key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					lower_bound(const_iterator hint, const Key & key) const
					{
						return this->ordered.lower_bound(hint, key);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					upper_bound(const key_type & key) const
					{
						return this->ordered.upper_bound(key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					upper_bound(const Key & key) const
					{
						return this->ordered.upper_bound(key);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					upper_bound(const_iterator hint, const key_type & key) const
					{
						return this->ordered.upper_bound(hint, key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					upper_bound(const_iterator hint, const Key & key) const
					{
						return this->ordered.upper_bound(hint, key);
					}

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
					equal_range(const key_type & key) const
					{
						return this->ordered.equal_range(key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						kerbal::utility::compressed_pair<const_iterator, const_iterator>
					>::type
					equal_range(const Key & key) const
					{
						return this->ordered.equal_range(key);
					}

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
					equal_range(const_iterator hint, const key_type & key) const
					{
						return this->ordered.equal_range(hint, key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						kerbal::utility::compressed_pair<const_iterator, const_iterator>
					>::type
					equal_range(const_iterator hint, const Key & key) const
					{
						return this->ordered.equal_range(hint, key);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					find(const key_type & key) const
					{
						return this->ordered.find(key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					find(const Key & key) const
					{
						return this->ordered.find(key);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					find(const_iterator hint, const key_type & key) const
					{
						return this->ordered.find(hint, key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					find(const_iterator hint, const Key & key) const
					{
						return this->ordered.find(hint, key);
					}

					KERBAL_CONSTEXPR14
					bool
					contains(const key_type & key) const
					{
						return this->ordered.contains(key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						bool
					>::type
					contains(const Key & key) const
					{
						return this->ordered.contains(key);
					}

					KERBAL_CONSTEXPR14
					bool
					contains(const_iterator hint, const key_type & key) const
					{
						return this->ordered.contains(hint, key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						bool
					>::type
					contains(const_iterator hint, const Key & key) const
					{
						return this->ordered.contains(hint, key);
					}


				//===================
				// erase

				public:

					KERBAL_CONSTEXPR14
					const_iterator
					erase(const_iterator pos)
					{
						return this->ordered.erase(pos);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					erase(const_iterator first, const_iterator last)
					{
						return this->ordered.erase(first, last);
					}

					KERBAL_CONSTEXPR14
					void
					clear()
					{
						this->ordered.clear();
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_FLAT_SET_COMMON_BASE_HPP
