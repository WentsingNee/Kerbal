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

			template <typename T, typename Ordered>
			class flat_set_common_base
			{
				public:
					typedef typename Ordered::key_compare			key_compare;
					typedef typename Ordered::key_type				key_type;
					typedef typename Ordered::value_type			value_type;
					typedef typename Ordered::const_type			const_type;
					typedef typename Ordered::reference				reference;
					typedef typename Ordered::const_reference		const_reference;
					typedef typename Ordered::pointer				pointer;
					typedef typename Ordered::const_pointer			const_pointer;

#		if __cplusplus >= 201103L
					typedef typename Ordered::rvalue_reference				rvalue_reference;
					typedef typename Ordered::const_rvalue_reference		const_rvalue_reference;
#		endif

					typedef typename Ordered::size_type						size_type;
					typedef typename Ordered::difference_type				difference_type;

					typedef typename Ordered::const_iterator				const_iterator;
					typedef typename Ordered::const_reverse_iterator		const_reverse_iterator;

				protected:

					Ordered ordered;

					KERBAL_CONSTEXPR14
					key_compare& key_comp_obj()
					{
						return ordered.key_comp_obj();
					}

					KERBAL_CONSTEXPR14
					const key_compare& key_comp_obj() const
					{
						return ordered.key_comp_obj();
					}

				public:

					KERBAL_CONSTEXPR14
					const key_compare& key_comp() const
					{
						return ordered.key_comp();
					}

				protected:
					KERBAL_CONSTEXPR
					flat_set_common_base() :
							ordered()
					{
					}

					KERBAL_CONSTEXPR
					explicit flat_set_common_base(key_compare kc) :
							ordered(kc)
					{
					}

				public:

					KERBAL_CONSTEXPR14
					const_iterator begin() const
					{
						return ordered.begin();
					}

					KERBAL_CONSTEXPR14
					const_iterator end() const
					{
						return ordered.end();
					}

					KERBAL_CONSTEXPR14
					const_iterator cbegin() const
					{
						return ordered.cbegin();
					}

					KERBAL_CONSTEXPR14
					const_iterator cend() const
					{
						return ordered.cend();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator rbegin() const
					{
						return ordered.rbegin();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator rend() const
					{
						return ordered.rend();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator crbegin() const
					{
						return ordered.crbegin();
					}

					KERBAL_CONSTEXPR14
					const_reverse_iterator crend() const
					{
						return ordered.crend();
					}

					KERBAL_CONSTEXPR14
					const_iterator nth(size_type index) const
					{
						return ordered.nth(index);
					}

					KERBAL_CONSTEXPR
					size_type index_of(const_iterator it) const
					{
						return ordered.index_of(it);
					}

					KERBAL_CONSTEXPR
					size_type size() const
					{
						return ordered.size();
					}

					KERBAL_CONSTEXPR
					size_type max_size() const KERBAL_NOEXCEPT
					{
						return ordered.max_size();
					}

					KERBAL_CONSTEXPR
					bool empty() const
					{
						return ordered.empty();
					}

					KERBAL_CONSTEXPR14
					const_iterator lower_bound(const key_type & key) const
					{
						return ordered.lower_bound(key);
					}

					KERBAL_CONSTEXPR14
					const_iterator lower_bound(const key_type & key, const_iterator hint) const
					{
						return ordered.lower_bound(key, hint);
					}

					KERBAL_CONSTEXPR14
					const_iterator upper_bound(const key_type & key) const
					{
						return ordered.upper_bound(key);
					}

					KERBAL_CONSTEXPR14
					const_iterator upper_bound(const key_type & key, const_iterator hint) const
					{
						return ordered.upper_bound(key, hint);
					}

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
					equal_range(const key_type & key) const
					{
						return ordered.equal_range(key);
					}

					KERBAL_CONSTEXPR14
					const_iterator find(const key_type & key) const
					{
						return ordered.find(key);
					}

					KERBAL_CONSTEXPR14
					const_iterator find(const key_type & key, const_iterator hint) const
					{
						return ordered.find(key, hint);
					}

					KERBAL_CONSTEXPR14
					bool contains(const key_type & key) const
					{
						return ordered.contains(key);
					}

					KERBAL_CONSTEXPR14
					bool contains(const key_type & key, const_iterator hint) const
					{
						return ordered.contains(key, hint);
					}

					KERBAL_CONSTEXPR14
					const_iterator erase(const_iterator pos)
					{
						return ordered.erase(pos);
					}

					KERBAL_CONSTEXPR14
					const_iterator erase(const_iterator first, const_iterator last)
					{
						return ordered.erase(first, last);
					}

					KERBAL_CONSTEXPR14
					void clear()
					{
						ordered.clear();
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_FLAT_SET_COMMON_BASE_HPP
