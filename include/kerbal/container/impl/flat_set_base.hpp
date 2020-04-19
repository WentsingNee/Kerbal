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

#ifndef KERBAL_CONTAINER_IMPL_FLAT_SET_BASE_HPP
#define KERBAL_CONTAINER_IMPL_FLAT_SET_BASE_HPP

#include <kerbal/algorithm/binary_search.hpp>
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
			class __flat_set_common_base
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

					Ordered __data;

					Ordered& __ordered_agent()
					{
						return this->__data;
					}

					const Ordered& __ordered_agent() const
					{
						return this->__data;
					}

					key_compare& __key_comp()
					{
						return this->__ordered_agent().__key_comp();
					}

					const key_compare& __key_comp() const
					{
						return this->__ordered_agent().__key_comp();
					}

				public:

					const key_compare& key_comp() const
					{
						return this->__ordered_agent().key_comp();
					}

				protected:
					__flat_set_common_base() :
							__data()
					{
					}

					explicit __flat_set_common_base(key_compare kc) :
							__data(kc)
					{
					}

				public:

					const_iterator begin() const
					{
						return this->__ordered_agent().begin();
					}

					const_iterator end() const
					{
						return this->__ordered_agent().end();
					}

					const_iterator cbegin() const
					{
						return this->__ordered_agent().cbegin();
					}

					const_iterator cend() const
					{
						return this->__ordered_agent().cend();
					}

					const_reverse_iterator rbegin() const
					{
						return this->__ordered_agent().rbegin();
					}

					const_reverse_iterator rend() const
					{
						return this->__ordered_agent().rend();
					}

					const_reverse_iterator crbegin() const
					{
						return this->__ordered_agent().crbegin();
					}

					const_reverse_iterator crend() const
					{
						return this->__ordered_agent().crend();
					}

					const_iterator nth(size_type index) const
					{
						return this->__ordered_agent().nth(index);
					}

					size_type index_of(const_iterator it) const
					{
						return this->__ordered_agent().index_of(it);
					}

					size_type size() const
					{
						return this->__ordered_agent().size();
					}

					KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT
					{
						return this->__ordered_agent().max_size();
					}

					bool empty() const
					{
						return this->__ordered_agent().empty();
					}

					const_iterator lower_bound(const key_type & key) const
					{
						return this->__ordered_agent().lower_bound(key);
					}

					const_iterator lower_bound(const key_type & key, const_iterator hint) const
					{
						return this->__ordered_agent().lower_bound(key, hint);
					}

					const_iterator upper_bound(const key_type & key) const
					{
						return this->__ordered_agent().upper_bound(key);
					}

					const_iterator upper_bound(const key_type & key, const_iterator hint) const
					{
						return this->__ordered_agent().upper_bound(key, hint);
					}

					std::pair<const_iterator, const_iterator> equal_range(const key_type & key) const
					{
						return this->__ordered_agent().equal_range(key);
					}

					const_iterator find(const key_type & key) const
					{
						return this->__ordered_agent().find(key);
					}

					const_iterator find(const key_type & key, const_iterator hint) const
					{
						return this->__ordered_agent().find(key, hint);
					}

					bool contains(const key_type & key) const
					{
						return this->__ordered_agent().contains(key);
					}

					bool contains(const key_type & key, const_iterator hint) const
					{
						return this->__ordered_agent().contains(key, hint);
					}

					const_iterator erase(const_iterator pos)
					{
						return this->__ordered_agent().erase(pos);
					}

					const_iterator erase(const_iterator first, const_iterator last)
					{
						return this->__ordered_agent().erase(first, last);
					}

					void clear()
					{
						this->__ordered_agent().clear();
					}

			};

			template <typename Tp, typename Ordered>
			class __flat_set_base: public __flat_set_common_base<Tp, Ordered>
			{
				private:
					typedef __flat_set_common_base<Tp, Ordered> super;

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
					__flat_set_base() :
							super()
					{
					}

					explicit __flat_set_base(key_compare kc) :
							super(kc)
					{
					}

					template <typename InputIterator>
					__flat_set_base(InputIterator first, InputIterator last,
							typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super()
					{
						this->assign(first, last);
					}

					template <typename InputIterator>
					__flat_set_base(InputIterator first, InputIterator last, key_compare kc,
							typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super(kc)
					{
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L
					__flat_set_base(std::initializer_list<value_type> src) :
							__flat_set_base(src.begin(), src.end())
					{
					}

					__flat_set_base(std::initializer_list<value_type> src, key_compare kc) :
							__flat_set_base(src.begin(), src.end(), kc)
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
						this->__key_comp() = kc;
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
						return this->__ordered_agent().try_insert(src);
					}

					std::pair<const_iterator, bool> insert(const_iterator hint, const_reference src)
					{
						return this->__ordered_agent().try_insert(hint, src);
					}

#			if __cplusplus >= 201103L

					std::pair<const_iterator, bool> insert(rvalue_reference src)
					{
						return this->__ordered_agent().try_insert(std::move(src));
					}

					std::pair<const_iterator, bool> insert(const_iterator hint, rvalue_reference src)
					{
						return this->__ordered_agent().try_insert(hint, std::move(src));
					}

#			endif

					template <typename InputIterator>
					void insert(InputIterator first, InputIterator last)
					{
						this->__ordered_agent().try_insert(first, last);
					}

					const_iterator erase(const key_type & key)
					{
						return this->__ordered_agent().erase_one(key);
					}

					const_iterator erase(const_iterator hint, const key_type & key)
					{
						return this->erase(this->find(key, hint));
					}

			};

			template <typename Tp, typename Ordered>
			class __flat_multiset_base : public __flat_set_common_base<Tp, Ordered>
			{
				private:
					typedef __flat_set_common_base<Tp, Ordered> super;

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
					__flat_multiset_base() :
							super()
					{
					}

					explicit __flat_multiset_base(key_compare kc) :
							super(kc)
					{
					}

					template <typename InputIterator>
					__flat_multiset_base(InputIterator first, InputIterator last,
							typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super()
					{
						this->assign(first, last);
					}

					template <typename InputIterator>
					__flat_multiset_base(InputIterator first, InputIterator last, key_compare kc,
							typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super(kc)
					{
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L
					__flat_multiset_base(std::initializer_list<value_type> src) :
							__flat_multiset_base(src.begin(), src.end())
					{
					}

					__flat_multiset_base(std::initializer_list<value_type> src, key_compare kc) :
							__flat_multiset_base(src.begin(), src.end(), kc)
					{
					}
#			endif

				public:

					size_type count(const key_type & key) const
					{
						return this->__ordered_agent().count(key);
					}

					size_type count(const key_type & key, const_iterator hint) const
					{
						return this->__ordered_agent().count(key, hint);
					}

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last)
					{
						this->__ordered_agent().assign(first, last);
					}

					template <typename InputIterator>
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->__ordered_agent().assign(first, last, kc);
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
						return this->__ordered_agent().insert(src);
					}

					const_iterator insert(const_iterator hint, const_reference src)
					{
						return this->__ordered_agent().insert(hint, src);
					}

#			if __cplusplus >= 201103L

					const_iterator insert(rvalue_reference src)
					{
						return this->__ordered_agent().insert(std::move(src));
					}

					const_iterator insert(const_iterator hint, rvalue_reference src)
					{
						return this->__ordered_agent().insert(hint, std::move(src));
					}

#			endif

					template <typename InputIterator>
					void insert(InputIterator first, InputIterator last)
					{
						this->__ordered_agent().insert(first, last);
					}

					size_type erase(const key_type & key)
					{
						return this->__ordered_agent().erase(key);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_IMPL_FLAT_SET_BASE_HPP
