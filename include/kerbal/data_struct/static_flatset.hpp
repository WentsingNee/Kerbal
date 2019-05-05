/*
 * static_flatset.hpp
 *
 *  Created on: 2019年4月22日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_STATIC_FLATSET_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_STATIC_FLATSET_HPP_

#include <kerbal/data_struct/static_array.hpp>
#include <kerbal/algorithm/search.hpp>
#include <algorithm>

namespace kerbal
{
	namespace data_struct
	{

		template <typename Tp, std::size_t N, typename KeyCompare = std::less<Tp>, typename Sequence = kerbal::data_struct::static_array<Tp, N> >
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

				template <typename InputIterator, typename =
						typename kerbal::type_traits::enable_if<
								kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::input_iterator_tag>::value
						>::type
				>
				static_flatset(InputIterator begin, InputIterator end) :
					c(), kc()
				{
					this->insert(begin, end);
				}

				template <typename InputIterator, typename =
						typename kerbal::type_traits::enable_if<
								kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::input_iterator_tag>::value
						>::type
				>
				static_flatset(InputIterator begin, InputIterator end, key_compare kc) :
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

				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::algorithm::is_compatible_iterator_type_of<InputIterator, std::input_iterator_tag>::value
				>::type
				assign(InputIterator begin, InputIterator end)
				{
					this->clear();
					this->insert(begin, end);
				}

				void assign(const static_flatset & src)
				{
					this->assign(src.cbegin(), src.cend());
				}

#	if __cplusplus >= 201103L

				void assign(std::initializer_list<value_type> src)
				{
					this->assign(src.begin(), src.end());
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
					return kerbal::algorithm::lower_bound(this->cbegin(), this->cend(), val, kc);
				}

				const_iterator find(const_reference val) const
				{
					const_iterator __i = this->lower_bound(val);
					return kc(val, *__i) ? this->cend() : __i;
				}

				std::pair<const_iterator, bool> insert(const_reference src)
				{
					const_iterator first = kerbal::algorithm::lower_bound(this->cbegin(), this->cend(), src, kc);
					bool inserted = false;
					if (first == this->cend() || kc(src, *first)) { // src < *first
						first = const_iterator(c.insert(first, src));
						inserted = true;
					}
					return std::pair<const_iterator, bool>(first, inserted);
				}

#	if __cplusplus >= 201103L
				std::pair<const_iterator, bool> insert(rvalue_reference src)
				{
					const_iterator first = kerbal::algorithm::lower_bound(this->cbegin(), this->cend(), src, kc);
					bool inserted = false;
					if (first == this->cend() || this->kc(src, *first)) { // src < *first
						first = c.insert(first, std::move(src));
						inserted = true;
					}
					return std::pair<const_iterator, bool>(first, inserted);
				}
#	endif

				template <typename InputIterator>
				void insert(InputIterator begin, InputIterator end)
				{
					while (begin != end && !c.full()) {
						{
							const_reference src = *begin;
							const_iterator first = kerbal::algorithm::lower_bound(this->cbegin(), this->cend(), src, kc);
							if (first == this->cend() || kc(src, *first)) { // src < *first
								c.insert(first, src);
							}
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

				size_type size() const
				{
					return c.size();
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
