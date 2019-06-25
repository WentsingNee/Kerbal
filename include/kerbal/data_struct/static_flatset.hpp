/*
 * static_flatset.hpp
 *
 *  Created on: 2019年4月22日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_STATIC_FLATSET_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_STATIC_FLATSET_HPP_

#include <kerbal/data_struct/static_vector.hpp>
#include <kerbal/algorithm/search.hpp>
#include <algorithm>

namespace kerbal
{
	namespace data_struct
	{

		template <typename Tp, std::size_t N, typename KeyCompare = std::less<Tp>, typename Sequence = kerbal::data_struct::static_vector<Tp, N> >
		class static_flatset
		{
			public:
				typedef Tp value_type;
				typedef const Tp const_type;
				typedef Tp& reference;
				typedef const Tp& const_reference;
				typedef Sequence container_type;

#		if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
#		endif

				typedef typename Sequence::size_type size_type;

				typedef typename Sequence::const_iterator const_iterator;
				typedef typename Sequence::const_reverse_iterator const_reverse_iterator;

				typedef KeyCompare key_compare;

			private:
				Sequence c;
				key_compare kc;

			public:
				static_flatset() :
						c(), kc()
				{
				}

				explicit static_flatset(key_compare kc) :
						c(), kc(kc)
				{
				}

				template <typename InputCompatibleIterator, typename =
						typename kerbal::type_traits::enable_if<
								kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value
						>::type
				>
				static_flatset(InputCompatibleIterator begin, InputCompatibleIterator end) :
					c(), kc()
				{
					this->insert(begin, end);
				}

				template <typename InputCompatibleIterator, typename =
						typename kerbal::type_traits::enable_if<
								kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value
						>::type
				>
				static_flatset(InputCompatibleIterator begin, InputCompatibleIterator end, key_compare kc) :
					c(), kc(kc)
				{
					this->insert(begin, end);
				}

#if __cplusplus >= 201103L
				static_flatset(std::initializer_list<value_type> src) :
						static_flatset(src.begin(), src.end())
				{
				}

				static_flatset(std::initializer_list<value_type> src, key_compare kc) :
						static_flatset(src.begin(), src.end(), kc)
				{
				}
#endif

				template <typename InputCompatibleIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value
				>::type
				assign(InputCompatibleIterator begin, InputCompatibleIterator end)
				{
					this->clear();
					this->insert(begin, end);
				}

				template <typename InputCompatibleIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value
				>::type
				assign(InputCompatibleIterator begin, InputCompatibleIterator end, key_compare kc)
				{
					this->clear();
					this->kc = kc;
					this->insert(begin, end);
				}

				void assign(const static_flatset & src)
				{
					this->assign(src.cbegin(), src.cend(), src.kc);
				}

#	if __cplusplus >= 201103L

				void assign(std::initializer_list<value_type> src)
				{
					this->assign(src.begin(), src.end());
				}

				void assign(std::initializer_list<value_type> src, key_compare kc)
				{
					this->assign(src.begin(), src.end(), kc);
				}

#	endif

				static_flatset& operator=(const static_flatset & src)
				{
					this->assign(src);
					return *this;
				}

#	if __cplusplus >= 201103L

				static_flatset& operator=(std::initializer_list<value_type> src)
				{
					this->assign(src);
					return *this;
				}

#	endif

				void clear()
				{
					c.clear();
				}

				const_iterator begin() const
				{
					return c.cbegin();
				}

				const_iterator end() const
				{
					return c.cend();
				}

				const_iterator cbegin() const
				{
					return c.cbegin();
				}

				const_iterator cend() const
				{
					return c.cend();
				}

				const_reverse_iterator rbegin() const
				{
					return c.crbegin();
				}

				const_reverse_iterator rend() const
				{
					return c.crend();
				}

				const_reverse_iterator crbegin() const
				{
					return c.crbegin();
				}

				const_reverse_iterator crend() const
				{
					return c.crend();
				}

				const_iterator lower_bound(const_reference val) const
				{
					return kerbal::algorithm::lower_bound(this->cbegin(), this->cend(), val, this->kc);
				}

				const_iterator upper_bound(const_reference val) const
				{
					return kerbal::algorithm::upper_bound(this->cbegin(), this->cend(), val, this->kc);
				}

				const_iterator lower_bound(const_reference val, const_iterator hint) const
				{
					return kerbal::algorithm::lower_bound_hint(this->cbegin(), this->cend(), val, hint, this->kc);
				}

				const_iterator find(const_reference val) const
				{
					const_iterator i = this->lower_bound(val);
					const_iterator end_it = this->cend();
					if (i != end_it && this->kc(val, *i)) {
						i = end_it;
					}
					return i;
				}

				const_iterator find(const_reference val, const_iterator hint) const
				{
					const_iterator i = this->lower_bound(val, hint);
					const_iterator end_it = this->cend();
					if (i != end_it && this->kc(val, *i)) {
						i = end_it;
					}
					return i;
				}

				bool contains(const_reference val) const
				{
					const_iterator __i = this->lower_bound(val);
					if (__i == this->cend()) {
						return false;
					}
					return this->kc(val, *__i) ? false : true;
				}

				bool contains(const_reference val, const_iterator hint) const
				{
					const_iterator __i = this->lower_bound(val, hint);
					if (__i == this->cend()) {
						return false;
					}
					return this->kc(val, *__i) ? false : true;
				}

				size_type count(const_reference val) const
				{
					return this->contains(val) ? 1 : 0;
				}

				size_type count(const_reference val, const_iterator hint) const
				{
					return this->contains(val, hint) ? 1 : 0;
				}

#		if __cplusplus >= 201103L

				template <typename ... Args>
				std::pair<const_iterator, bool> emplace(Args&& ... args)
				{
					value_type val(std::forward<Args>(args)...);
					std::pair<const_iterator, bool> ret(this->lower_bound(val), false); // first, inserted
					const_iterator & first = ret.first;
					bool & inserted = ret.second;
					if (first == this->cend() || this->kc(val, *first)) { // src < *first
						first = const_iterator(c.insert(first, std::move(val)));
						inserted = true;
					}
					return ret;
				}

				template <typename ... Args>
				std::pair<const_iterator, bool> emplace_hint(const_iterator hint, Args&& ... args)
				{
					value_type val(std::forward<Args>(args)...);
					std::pair<const_iterator, bool> ret(this->lower_bound(val, hint), false); // first, inserted
					const_iterator & first = ret.first;
					bool & inserted = ret.second;
					if (first == this->cend() || this->kc(val, *first)) { // src < *first
						first = const_iterator(c.insert(first, std::move(val)));
						inserted = true;
					}
					return ret;
				}

#		endif

				std::pair<const_iterator, bool> insert(const_reference src)
				{
					std::pair<const_iterator, bool> ret(this->lower_bound(src), false); // first, inserted
					const_iterator & first = ret.first;
					bool & inserted = ret.second;
					if (first == this->cend() || this->kc(src, *first)) { // src < *first
						first = const_iterator(c.insert(first, src));
						inserted = true;
					}
					return ret;
				}

				std::pair<const_iterator, bool> insert(const_iterator hint, const_reference src)
				{
					std::pair<const_iterator, bool> ret(this->lower_bound(src, hint), false); // first, inserted
					const_iterator & first = ret.first;
					bool & inserted = ret.second;
					if (first == this->cend() || this->kc(src, *first)) { // src < *first
						first = const_iterator(c.insert(first, src));
						inserted = true;
					}
					return ret;
				}

#	if __cplusplus >= 201103L
				std::pair<const_iterator, bool> insert(rvalue_reference src)
				{
					std::pair<const_iterator, bool> ret(this->lower_bound(src), false); // first, inserted
					const_iterator & first = ret.first;
					bool & inserted = ret.second;
					if (first == this->cend() || this->kc(src, *first)) { // src < *first
						first = const_iterator(c.insert(first, std::move(src)));
						inserted = true;
					}
					return ret;
				}

				std::pair<const_iterator, bool> insert(const_iterator hint, rvalue_reference src)
				{
					std::pair<const_iterator, bool> ret(this->lower_bound(src, hint), false); // first, inserted
					const_iterator & first = ret.first;
					bool & inserted = ret.second;
					if (first == this->cend() || this->kc(src, *first)) { // src < *first
						first = const_iterator(c.insert(first, std::move(src)));
						inserted = true;
					}
					return ret;
				}
#	endif

				template <typename InputIterator>
				void insert(InputIterator begin, InputIterator end)
				{
					while (begin != end && !c.full()) {
						const_reference src = *begin;
						const_iterator first = this->lower_bound(src);
						if (first == this->cend() || this->kc(src, *first)) { // src < *first
							c.insert(first, src);
						}
						++begin;
					}
				}

				template <typename InputIterator>
				void nearly_ordered_insert(InputIterator begin, InputIterator end)
				{
					const_iterator first = this->cbegin();
					while (begin != end && !c.full()) {
						const_reference src = *begin;
						first = this->lower_bound(src, first);
						if (first == this->cend() || this->kc(src, *first)) { // src < *first
							first = c.insert(first, src);
						}
						++begin;
					}
				}

				const_iterator erase(const_iterator iterator)
				{
					return c.erase(iterator);
				}

				const_iterator erase(const_reference val)
				{
					return c.erase(this->find(val));
				}

				const_iterator erase(const_iterator hint, const_reference val)
				{
					return c.erase(this->find(val, hint));
				}

				size_type size() const
				{
					return c.size();
				}

				/**
				 * @brief Returns the size() of the largest possible static_vector.
				 */
				KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT
				{
					return c.max_size();
				}

				bool empty() const
				{
					return c.empty();
				}

				bool full() const
				{
					return c.full();
				}

				/**
				 * @brief Returns the comparison object with which the %set was constructed.
				 */
				const key_compare & key_comp() const
				{
					return kc;
				}

				void swap(static_flatset & ano)
				{
					this->c.swap(ano.c);
					std::swap(this->kc, ano.kc);
				}

				template <size_t M>
				friend bool operator==(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs);

				template <size_t M>
				friend bool operator!=(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs);

				template <size_t M>
				friend bool operator<(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs);

				template <size_t M>
				friend bool operator<=(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs);

				template <size_t M>
				friend bool operator>(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs);

				template <size_t M>
				friend bool operator>=(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs);

		};

		template <typename Tp, size_t M, size_t N>
		bool operator==(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs)
		{
			return lhs.c == rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator!=(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs)
		{
			return lhs.c != rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator<(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs)
		{
			return lhs.c < rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator<=(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs)
		{
			return lhs.c <= rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator>(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs)
		{
			return lhs.c > rhs.c;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator>=(const static_flatset<Tp, M> & lhs, const static_flatset<Tp, N> & rhs)
		{
			return lhs.c >= rhs.c;
		}

	}
}


#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_FLATSET_HPP_ */
