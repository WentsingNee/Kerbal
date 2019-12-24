/**
 * @file       static_flat_set.hpp
 * @brief
 * @date       2019-4-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_FLAT_SET_HPP_
#define KERBAL_CONTAINER_STATIC_FLAT_SET_HPP_

#include <kerbal/container/static_ordered.hpp>
#include <kerbal/container/impl/flat_set_base.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, std::size_t N, typename KeyCompare = std::less<Tp> >
		class static_flat_set:
				public kerbal::container::detail::__flat_set_base<Tp, kerbal::container::static_ordered<Tp, N, Tp, KeyCompare> >
		{
			private:
				typedef kerbal::container::static_ordered<Tp, N, Tp, KeyCompare> Ordered;
				typedef kerbal::container::detail::__flat_set_base<Tp, Ordered> super;

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

			public:

				static_flat_set() :
						super()
				{
				}

				explicit static_flat_set(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				static_flat_set(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last)
				{
				}

				template <typename InputIterator>
				static_flat_set(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L
				static_flat_set(std::initializer_list<value_type> src) :
						super(src)
				{
				}

				static_flat_set(std::initializer_list<value_type> src, key_compare kc) :
						super(src, kc)
				{
				}
#		endif

				void assign(const static_flat_set & src)
				{
					this->__ordered_agent().assign(src.__ordered_agent());
				}

				static_flat_set& operator=(const static_flat_set & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				static_flat_set& operator=(std::initializer_list<value_type> src)
				{
					this->assign(src);
					return *this;
				}

#		endif

				bool full() const
				{
					return this->__ordered_agent().full();
				}

				void swap(static_flat_set & ano)
				{
					this->__ordered_agent().swap(ano.__ordered_agent());
				}

				template <size_t M>
				friend bool operator==(const static_flat_set<Tp, M, KeyCompare> & lhs,
										const static_flat_set<Tp, N, KeyCompare> & rhs)
				{
					return lhs.__ordered_agent() == rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator!=(const static_flat_set<Tp, M, KeyCompare> & lhs,
										const static_flat_set<Tp, N, KeyCompare> & rhs)
				{
					return lhs.__ordered_agent() != rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator<(const static_flat_set<Tp, M, KeyCompare> & lhs,
										const static_flat_set<Tp, N, KeyCompare> & rhs)
				{
					return lhs.__ordered_agent() < rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator<=(const static_flat_set<Tp, M, KeyCompare> & lhs,
										const static_flat_set<Tp, N, KeyCompare> & rhs)
				{
					return lhs.__ordered_agent() <= rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator>(const static_flat_set<Tp, M, KeyCompare> & lhs,
										const static_flat_set<Tp, N, KeyCompare> & rhs)
				{
					return lhs.__ordered_agent() > rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator>=(const static_flat_set<Tp, M, KeyCompare> & lhs,
										const static_flat_set<Tp, N, KeyCompare> & rhs)
				{
					return lhs.__ordered_agent() >= rhs.__ordered_agent();
				}

		};

		template <typename Tp, std::size_t N, typename KeyCompare = std::less<Tp> >
		class static_flat_multiset:
				public kerbal::container::detail::__flat_multiset_base<Tp, kerbal::container::static_ordered<Tp, N, Tp, KeyCompare> >
		{
			private:
				typedef kerbal::container::static_ordered<Tp, N, Tp, KeyCompare> Ordered;
				typedef kerbal::container::detail::__flat_multiset_base<Tp, Ordered> super;

			public:
				typedef typename super::key_compare key_compare;
				typedef typename super::key_type key_type;
				typedef typename super::value_type value_type;
				typedef typename super::const_type const_type;
				typedef typename super::reference reference;
				typedef typename super::const_reference const_reference;
				typedef typename super::pointer pointer;
				typedef typename super::const_pointer const_pointer;

#		if __cplusplus >= 201103L
				typedef typename super::rvalue_reference rvalue_reference;
				typedef typename super::const_rvalue_reference const_rvalue_reference;
#		endif

				typedef typename super::size_type size_type;
				typedef typename super::difference_type difference_type;

				typedef typename super::const_iterator const_iterator;
				typedef typename super::const_reverse_iterator const_reverse_iterator;

			public:

				static_flat_multiset() :
						super()
				{
				}

				explicit static_flat_multiset(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				static_flat_multiset(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last)
				{
				}

				template <typename InputIterator>
				static_flat_multiset(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L

				static_flat_multiset(std::initializer_list<value_type> src) :
						super(src)
				{
				}

				static_flat_multiset(std::initializer_list<value_type> src, key_compare kc) :
						super(src, kc)
				{
				}

#		endif

				void assign(const static_flat_multiset& src)
				{
					this->__ordered_agent().assign(src.__ordered_agent());
				}

				static_flat_multiset& operator=(const static_flat_multiset& src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				static_flat_multiset& operator=(std::initializer_list<value_type> src)
				{
					this->assign(src);
					return *this;
				}

#		endif

				bool full() const
				{
					return this->__ordered_agent().full();
				}

				void swap(static_flat_multiset& ano)
				{
					this->__ordered_agent().swap(ano.__ordered_agent());
				}

				template <size_t M>
				friend bool operator==(const static_flat_multiset<Tp, M, KeyCompare>& lhs,
										const static_flat_multiset<Tp, N, KeyCompare>& rhs)
				{
					return lhs.__ordered_agent() == rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator!=(const static_flat_multiset<Tp, M, KeyCompare>& lhs,
										const static_flat_multiset<Tp, N, KeyCompare>& rhs)
				{
					return lhs.__ordered_agent() != rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator<(const static_flat_multiset<Tp, M, KeyCompare>& lhs,
										const static_flat_multiset<Tp, N, KeyCompare>& rhs)
				{
					return lhs.__ordered_agent() < rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator<=(const static_flat_multiset<Tp, M, KeyCompare>& lhs,
										const static_flat_multiset<Tp, N, KeyCompare>& rhs)
				{
					return lhs.__ordered_agent() <= rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator>(const static_flat_multiset<Tp, M, KeyCompare>& lhs,
										const static_flat_multiset<Tp, N, KeyCompare>& rhs)
				{
					return lhs.__ordered_agent() > rhs.__ordered_agent();
				}

				template <size_t M>
				friend bool operator>=(const static_flat_multiset<Tp, M, KeyCompare>& lhs,
										const static_flat_multiset<Tp, N, KeyCompare>& rhs)
				{
					return lhs.__ordered_agent() >= rhs.__ordered_agent();
				}

		};

	} // namespace container

} // namespace kerbal


#endif /* KERBAL_CONTAINER_STATIC_FLAT_SET_HPP_ */
