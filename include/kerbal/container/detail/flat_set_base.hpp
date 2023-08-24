/**
 * @file       flat_set_base.hpp
 * @brief
 * @date       2019-12-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FLAT_SET_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_FLAT_SET_BASE_HPP

#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp, typename Ordered>
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
					std::pair<const_iterator, const_iterator> equal_range(const key_type & key) const
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

			template <typename Tp, typename Ordered>
			class flat_set_base: public flat_set_common_base<Tp, Ordered>
			{
				private:
					typedef flat_set_common_base<Tp, Ordered> super;

				public:
					typedef typename super::key_compare			key_compare;
					typedef typename super::key_type			key_type;
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

					typedef typename super::const_iterator				const_iterator;
					typedef typename super::const_reverse_iterator		const_reverse_iterator;

				protected:
					KERBAL_CONSTEXPR
					flat_set_base() :
							super()
					{
					}

					KERBAL_CONSTEXPR
					explicit flat_set_base(key_compare kc) :
							super(kc)
					{
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_set_base(InputIterator first, InputIterator last,
								  typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super()
					{
						this->assign(first, last);
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_set_base(InputIterator first, InputIterator last, key_compare kc,
								  typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super(kc)
					{
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					flat_set_base(std::initializer_list<value_type> src) :
							flat_set_base(src.begin(), src.end())
					{
					}

					KERBAL_CONSTEXPR14
					flat_set_base(std::initializer_list<value_type> src, key_compare kc) :
							flat_set_base(src.begin(), src.end(), kc)
					{
					}

#			endif

				public:

					KERBAL_CONSTEXPR14
					size_type count(const key_type & key) const
					{
						return this->contains(key) ? 1 : 0;
					}

					KERBAL_CONSTEXPR14
					size_type count(const key_type & key, const_iterator hint) const
					{
						return this->contains(key, hint) ? 1 : 0;
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last)
					{
						this->clear();
						this->insert(first, last);
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
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
					std::pair<const_iterator, bool> insert(const_reference src)
					{
						return this->ordered.try_insert(src);
					}

					KERBAL_CONSTEXPR14
					std::pair<const_iterator, bool> insert(const_iterator hint, const_reference src)
					{
						return this->ordered.try_insert(hint, src);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					std::pair<const_iterator, bool> insert(rvalue_reference src)
					{
						return this->ordered.try_insert(kerbal::compatibility::move(src));
					}

					KERBAL_CONSTEXPR14
					std::pair<const_iterator, bool> insert(const_iterator hint, rvalue_reference src)
					{
						return this->ordered.try_insert(hint, kerbal::compatibility::move(src));
					}

#			endif

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					void insert(InputIterator first, InputIterator last)
					{
						this->ordered.try_insert(first, last);
					}

					KERBAL_CONSTEXPR14
					const_iterator erase(const key_type & key)
					{
						return this->ordered.erase_one(key);
					}

					KERBAL_CONSTEXPR14
					const_iterator erase(const_iterator hint, const key_type & key)
					{
						return this->erase(this->find(key, hint));
					}

			};

			template <typename Tp, typename Ordered>
			class flat_multiset_base : public flat_set_common_base<Tp, Ordered>
			{
				private:
					typedef flat_set_common_base<Tp, Ordered> super;

				public:
					typedef typename super::key_compare			key_compare;
					typedef typename super::key_type			key_type;
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

					typedef typename super::const_iterator				const_iterator;
					typedef typename super::const_reverse_iterator		const_reverse_iterator;

				protected:
					KERBAL_CONSTEXPR
					flat_multiset_base() :
							super()
					{
					}

					KERBAL_CONSTEXPR
					explicit flat_multiset_base(key_compare kc) :
							super(kc)
					{
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_multiset_base(InputIterator first, InputIterator last,
									   typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super()
					{
						this->assign(first, last);
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_multiset_base(InputIterator first, InputIterator last, key_compare kc,
									   typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super(kc)
					{
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					flat_multiset_base(std::initializer_list<value_type> src) :
							flat_multiset_base(src.begin(), src.end())
					{
					}

					KERBAL_CONSTEXPR14
					flat_multiset_base(std::initializer_list<value_type> src, key_compare kc) :
							flat_multiset_base(src.begin(), src.end(), kc)
					{
					}

#			endif

				public:

					KERBAL_CONSTEXPR14
					size_type count(const key_type & key) const
					{
						return this->ordered.count(key);
					}

					KERBAL_CONSTEXPR14
					size_type count(const key_type & key, const_iterator hint) const
					{
						return this->ordered.count(key, hint);
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last)
					{
						this->ordered.assign(first, last);
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->ordered.assign(first, last, kc);
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
					const_iterator insert(const_reference src)
					{
						return this->ordered.insert(src);
					}

					KERBAL_CONSTEXPR14
					const_iterator insert(const_iterator hint, const_reference src)
					{
						return this->ordered.insert(hint, src);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					const_iterator insert(rvalue_reference src)
					{
						return this->ordered.insert(kerbal::compatibility::move(src));
					}

					KERBAL_CONSTEXPR14
					const_iterator insert(const_iterator hint, rvalue_reference src)
					{
						return this->ordered.insert(hint, kerbal::compatibility::move(src));
					}

#			endif

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					void insert(InputIterator first, InputIterator last)
					{
						this->ordered.insert(first, last);
					}

					KERBAL_CONSTEXPR14
					size_type erase(const key_type & key)
					{
						return this->ordered.erase(key);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_FLAT_SET_BASE_HPP
