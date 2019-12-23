/**
 * @file       static_flatset.hpp
 * @brief
 * @date       2019-4-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_FLATSET_HPP_
#define KERBAL_CONTAINER_STATIC_FLATSET_HPP_

#include <kerbal/container/static_ordered.hpp>
#include <kerbal/container/impl/flatset_base.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, std::size_t N, typename KeyCompare = std::less<Tp> >
		class static_flatset:
				public kerbal::container::detail::__flatset_base<Tp, kerbal::container::static_ordered<Tp, N, Tp, KeyCompare> >
		{
			private:
				typedef kerbal::container::static_ordered<Tp, N, Tp, KeyCompare> Ordered;
				typedef kerbal::container::detail::__flatset_base<Tp, Ordered> super;

			public:
				typedef Tp						value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef typename super::size_type					size_type;
				typedef typename super::difference_type			difference_type;

				typedef typename super::const_iterator				const_iterator;
				typedef typename super::const_reverse_iterator		const_reverse_iterator;
				typedef typename super::key_compare				key_compare;

			public:

				static_flatset() :
						super()
				{
				}

				explicit static_flatset(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				static_flatset(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last)
				{
				}

				template <typename InputIterator>
				static_flatset(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L
				static_flatset(std::initializer_list<value_type> src) :
						super(src)
				{
				}

				static_flatset(std::initializer_list<value_type> src, key_compare kc) :
						super(src, kc)
				{
				}
#		endif

				void assign(const static_flatset & src)
				{
					this->__ordered_agent().assign(src.__ordered_agent());
				}

				static_flatset& operator=(const static_flatset & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				static_flatset& operator=(std::initializer_list<value_type> src)
				{
					this->assign(src);
					return *this;
				}

#		endif

				bool full() const
				{
					return this->__ordered_agent().full();
				}

				void swap(static_flatset & ano)
				{
					this->__ordered_agent().swap(ano.__ordered_agent());
				}

				template <size_t M>
				friend bool operator==(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs);

				template <size_t M>
				friend bool operator!=(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs);

				template <size_t M>
				friend bool operator<(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs);

				template <size_t M>
				friend bool operator<=(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs);

				template <size_t M>
				friend bool operator>(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs);

				template <size_t M>
				friend bool operator>=(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs);

		};

		template <typename Tp, size_t M, size_t N, typename KeyCompare>
		bool operator==(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs)
		{
			return lhs.__ordered_agent() == rhs.__ordered_agent();
		}

		template <typename Tp, size_t M, size_t N, typename KeyCompare>
		bool operator!=(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs)
		{
			return lhs.__ordered_agent() != rhs.__ordered_agent();
		}

		template <typename Tp, size_t M, size_t N, typename KeyCompare>
		bool operator<(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs)
		{
			return lhs.__ordered_agent() < rhs.__ordered_agent();
		}

		template <typename Tp, size_t M, size_t N, typename KeyCompare>
		bool operator<=(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs)
		{
			return lhs.__ordered_agent() <= rhs.__ordered_agent();
		}

		template <typename Tp, size_t M, size_t N, typename KeyCompare>
		bool operator>(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs)
		{
			return lhs.__ordered_agent() > rhs.__ordered_agent();
		}

		template <typename Tp, size_t M, size_t N, typename KeyCompare>
		bool operator>=(const static_flatset<Tp, M, KeyCompare> & lhs, const static_flatset<Tp, N, KeyCompare> & rhs)
		{
			return lhs.__ordered_agent() >= rhs.__ordered_agent();
		}

	}
}


#endif /* KERBAL_CONTAINER_STATIC_FLATSET_HPP_ */
