/**
 * @file       flat_map_base.hpp
 * @brief
 * @date       2019-12-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FLAT_MAP_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_FLAT_MAP_BASE_HPP

#include <kerbal/algorithm/binary_search.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Key, typename Value, typename Ordered>
			class flat_map_common_base
			{
				public:
					typedef typename Ordered::key_compare				key_compare;
					typedef typename Ordered::key_type					key_type;
					typedef typename Ordered::value_type::second_type	mapped_type;
					typedef typename Ordered::value_type				value_type;
					typedef typename Ordered::const_type				const_type;
					typedef typename Ordered::reference					reference;
					typedef typename Ordered::const_reference			const_reference;
					typedef typename Ordered::pointer					pointer;
					typedef typename Ordered::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
					typedef typename Ordered::rvalue_reference				rvalue_reference;
					typedef typename Ordered::const_rvalue_reference		const_rvalue_reference;
#		endif

					typedef typename Ordered::size_type						size_type;
					typedef typename Ordered::difference_type				difference_type;

					typedef typename Ordered::iterator						iterator;
					typedef typename Ordered::const_iterator				const_iterator;
					typedef typename Ordered::reverse_iterator				reverse_iterator;
					typedef typename Ordered::const_reverse_iterator		const_reverse_iterator;

				protected:

					Ordered ordered;

					key_compare& key_comp_obj()
					{
						return this->ordered.key_comp_obj();
					}

					const key_compare& key_comp_obj() const
					{
						return this->ordered.key_comp_obj();
					}

				public:

					const key_compare& key_comp() const
					{
						return this->ordered.key_comp();
					}

				protected:
					flat_map_common_base() :
							ordered()
					{
					}

					explicit flat_map_common_base(key_compare kc) :
							ordered(kc)
					{
					}

				public:

					iterator begin()
					{
						return this->ordered.begin();
					}

					const_iterator begin() const
					{
						return this->ordered.begin();
					}

					iterator end()
					{
						return this->ordered.end();
					}

					const_iterator end() const
					{
						return this->ordered.end();
					}

					const_iterator cbegin() const
					{
						return this->ordered.cbegin();
					}

					const_iterator cend() const
					{
						return this->ordered.cend();
					}

					reverse_iterator rbegin()
					{
						return this->ordered.rbegin();
					}

					const_reverse_iterator rbegin() const
					{
						return this->ordered.rbegin();
					}

					reverse_iterator rend()
					{
						return this->ordered.rend();
					}

					const_reverse_iterator rend() const
					{
						return this->ordered.rend();
					}

					const_reverse_iterator crbegin() const
					{
						return this->ordered.crbegin();
					}

					const_reverse_iterator crend() const
					{
						return this->ordered.crend();
					}

					iterator nth(size_type index)
					{
						return this->ordered.nth(index);
					}

					const_iterator nth(size_type index) const
					{
						return this->ordered.nth(index);
					}

					size_type index_of(const_iterator it) const
					{
						return this->ordered.index_of(it);
					}

					size_type size() const
					{
						return this->ordered.size();
					}

					KERBAL_CONSTEXPR
					size_type max_size() const KERBAL_NOEXCEPT
					{
						return this->ordered.max_size();
					}

					bool empty() const
					{
						return this->ordered.empty();
					}

					iterator lower_bound(const key_type & key)
					{
						return this->ordered.lower_bound(key);
					}

					const_iterator lower_bound(const key_type & key) const
					{
						return this->ordered.lower_bound(key);
					}

					iterator lower_bound(const key_type & key, const_iterator hint)
					{
						return this->ordered.lower_bound(key, hint);
					}

					const_iterator lower_bound(const key_type & key, const_iterator hint) const
					{
						return this->ordered.lower_bound(key, hint);
					}

					iterator upper_bound(const key_type & key)
					{
						return this->ordered.upper_bound(key);
					}

					const_iterator upper_bound(const key_type & key) const
					{
						return this->ordered.upper_bound(key);
					}

					iterator upper_bound(const key_type & key, const_iterator hint)
					{
						return this->ordered.upper_bound(key, hint);
					}

					const_iterator upper_bound(const key_type & key, const_iterator hint) const
					{
						return this->ordered.upper_bound(key, hint);
					}

					std::pair<iterator, iterator> equal_range(const key_type & key)
					{
						return this->ordered.equal_range(key);
					}

					std::pair<const_iterator, const_iterator> equal_range(const key_type & key) const
					{
						return this->ordered.equal_range(key);
					}

					iterator find(const key_type & key)
					{
						return this->ordered.find(key);
					}

					const_iterator find(const key_type & key) const
					{
						return this->ordered.find(key);
					}

					iterator find(const key_type & key, const_iterator hint)
					{
						return this->ordered.find(key, hint);
					}

					const_iterator find(const key_type & key, const_iterator hint) const
					{
						return this->ordered.find(key, hint);
					}

					bool contains(const key_type & key) const
					{
						return this->ordered.contains(key);
					}

					bool contains(const key_type & key, const_iterator hint) const
					{
						return this->ordered.contains(key, hint);
					}

					const_iterator erase(const_iterator pos)
					{
						return this->ordered.erase(pos);
					}

					const_iterator erase(const_iterator first, const_iterator last)
					{
						return this->ordered.erase(first, last);
					}

					void clear()
					{
						this->ordered.clear();
					}

			};

			template <typename Key, typename Value, typename Ordered>
			class flat_map_base: public flat_map_common_base<Key, Value, Ordered>
			{
				private:
					typedef flat_map_common_base<Key, Value, Ordered> super;

				public:
					typedef typename super::key_compare			key_compare;
					typedef typename super::key_type			key_type;
					typedef typename super::mapped_type			mapped_type;
					typedef typename super::value_type			value_type;
					typedef typename super::const_type			const_type;
					typedef typename super::reference			reference;
					typedef typename super::const_reference		const_reference;
					typedef typename super::pointer				pointer;
					typedef typename super::const_pointer		const_pointer;

#		if __cplusplus >= 201103L
					typedef typename super::rvalue_reference			rvalue_reference;
					typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

					typedef typename super::size_type					size_type;
					typedef typename super::difference_type				difference_type;

					typedef typename super::iterator					iterator;
					typedef typename super::const_iterator				const_iterator;
					typedef typename super::reverse_iterator			reverse_iterator;
					typedef typename super::const_reverse_iterator		const_reverse_iterator;

				protected:
					flat_map_base() :
							super()
					{
					}

					explicit flat_map_base(key_compare kc) :
							super(kc)
					{
					}

					template <typename InputIterator>
					flat_map_base(InputIterator first, InputIterator last,
								  typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super()
					{
						this->assign(first, last);
					}

					template <typename InputIterator>
					flat_map_base(InputIterator first, InputIterator last, key_compare kc,
								  typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super(kc)
					{
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L
					flat_map_base(std::initializer_list<value_type> src) :
							flat_map_base(src.begin(), src.end())
					{
					}

					flat_map_base(std::initializer_list<value_type> src, key_compare kc) :
							flat_map_base(src.begin(), src.end(), kc)
					{
					}
#			endif

				public:

					size_type count(const key_type & key) const
					{
						return this->contains(key) ? 1 : 0;
					}

					size_type count(const key_type & key, const_iterator hint) const
					{
						return this->contains(key, hint) ? 1 : 0;
					}

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last)
					{
						this->clear();
						this->insert(first, last);
					}

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->clear();
						this->key_comp_obj() = kc;
						this->insert(first, last);
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

					std::pair<const_iterator, bool> insert(const_reference src)
					{
						return this->ordered.try_insert(src);
					}

					std::pair<const_iterator, bool> insert(const_iterator hint, const_reference src)
					{
						return this->ordered.try_insert(hint, src);
					}

#			if __cplusplus >= 201103L

					std::pair<const_iterator, bool> insert(rvalue_reference src)
					{
						return this->ordered.try_insert(kerbal::compatibility::move(src));
					}

					std::pair<const_iterator, bool> insert(const_iterator hint, rvalue_reference src)
					{
						return this->ordered.try_insert(hint, kerbal::compatibility::move(src));
					}

#			endif

					template <typename InputIterator>
					void insert(InputIterator first, InputIterator last)
					{
						this->ordered.try_insert(first, last);
					}

					const_iterator erase(const key_type & key)
					{
						return this->ordered.erase_one(key);
					}

					const_iterator erase(const_iterator hint, const key_type & key)
					{
						return this->erase(this->find(key, hint));
					}

					mapped_type& operator[](const key_type& key)
					{
						const_iterator pos(this->find(key));
						if (pos == this->cend()) {
							return this->insert(std::make_pair(key, mapped_type())).first->second;
						} else {
							return pos->second;
						}
					}

					mapped_type& at(const key_type& key)
					{
						iterator pos(this->find(key));
						if (key == this->end()) {
							kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception("not found");
						}
						return pos->second;
					}

					const mapped_type& at(const key_type& key) const
					{
						const_iterator pos(this->find(key));
						if (key == this->cend()) {
							kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception("not found");
						}
						return pos->second;
					}

			};

			template <typename Key, typename Value, typename Ordered>
			class flat_multimap_base : public flat_map_common_base<Key, Value, Ordered>
			{
				private:
					typedef flat_map_common_base<Key, Value, Ordered> super;

				public:
					typedef typename super::key_compare			key_compare;
					typedef typename super::key_type			key_type;
					typedef typename super::mapped_type			mapped_type;
					typedef typename super::value_type			value_type;
					typedef typename super::const_type			const_type;
					typedef typename super::reference			reference;
					typedef typename super::const_reference		const_reference;
					typedef typename super::pointer				pointer;
					typedef typename super::const_pointer		const_pointer;

#		if __cplusplus >= 201103L
					typedef typename super::rvalue_reference			rvalue_reference;
					typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

					typedef typename super::size_type					size_type;
					typedef typename super::difference_type				difference_type;

					typedef typename super::iterator					iterator;
					typedef typename super::const_iterator				const_iterator;
					typedef typename super::reverse_iterator			reverse_iterator;
					typedef typename super::const_reverse_iterator		const_reverse_iterator;

				protected:
					flat_multimap_base() :
							super()
					{
					}

					explicit flat_multimap_base(key_compare kc) :
							super(kc)
					{
					}

					template <typename InputIterator>
					flat_multimap_base(InputIterator first, InputIterator last,
									   typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super()
					{
						this->assign(first, last);
					}

					template <typename InputIterator>
					flat_multimap_base(InputIterator first, InputIterator last, key_compare kc,
									   typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super(kc)
					{
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L
					flat_multimap_base(std::initializer_list<value_type> src) :
							flat_multimap_base(src.begin(), src.end())
					{
					}

					flat_multimap_base(std::initializer_list<value_type> src, key_compare kc) :
							flat_multimap_base(src.begin(), src.end(), kc)
					{
					}
#			endif

				public:

					size_type count(const key_type & key) const
					{
						return this->ordered.count(key);
					}

					size_type count(const key_type & key, const_iterator hint) const
					{
						return this->ordered.count(key, hint);
					}

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last)
					{
						this->ordered.assign(first, last);
					}

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->ordered.assign(first, last, kc);
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

					const_iterator insert(const_reference src)
					{
						return this->ordered.insert(src);
					}

					const_iterator insert(const_iterator hint, const_reference src)
					{
						return this->ordered.insert(hint, src);
					}

#			if __cplusplus >= 201103L

					const_iterator insert(rvalue_reference src)
					{
						return this->ordered.insert(kerbal::compatibility::move(src));
					}

					const_iterator insert(const_iterator hint, rvalue_reference src)
					{
						return this->ordered.insert(hint, kerbal::compatibility::move(src));
					}

#			endif

					template <typename InputIterator>
					void insert(InputIterator first, InputIterator last)
					{
						this->ordered.insert(first, last);
					}

					size_type erase(const key_type & key)
					{
						return this->ordered.erase(key);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_FLAT_MAP_BASE_HPP
