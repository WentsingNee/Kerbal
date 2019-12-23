/**
 * @file       flatset.hpp
 * @brief
 * @date       2019-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FLATSET_HPP_
#define KERBAL_CONTAINER_FLATSET_HPP_

#include <kerbal/container/flat_ordered.hpp>
#include <kerbal/container/impl/flatset_base.hpp>

#include <algorithm>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename KeyCompare = std::less<Tp>, typename Allocator = std::allocator<Tp> >
		class flatset:
				public kerbal::container::detail::__flatset_base<Tp, kerbal::container::flat_ordered<Tp, Tp, KeyCompare> >
		{
			private:
				typedef kerbal::container::flat_ordered<Tp, Tp, KeyCompare, default_extract<Tp, Tp>, Allocator> Ordered;
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

				flatset() :
						super()
				{
				}

				explicit flatset(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				flatset(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last)
				{
				}

				template <typename InputIterator>
				flatset(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L
				flatset(std::initializer_list<value_type> src) :
						super(src)
				{
				}

				flatset(std::initializer_list<value_type> src, key_compare kc) :
						super(src, kc)
				{
				}
#		endif

				void assign(const flatset & src)
				{
					this->__ordered_agent().assign(src.__ordered_agent());
				}

				flatset& operator=(const flatset & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				flatset& operator=(std::initializer_list<value_type> src)
				{
					this->assign(src);
					return *this;
				}

#		endif

				void swap(flatset & ano)
				{
					this->__ordered_agent().swap(ano.__ordered_agent());
				}

				friend bool operator==(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs);

				friend bool operator!=(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs);

				friend bool operator<(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs);

				friend bool operator<=(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs);

				friend bool operator>(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs);

				friend bool operator>=(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs);

		};

		template <typename Tp, typename KeyCompare, typename Allocator>
		bool operator==(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs)
		{
			return lhs.__ordered_agent() == rhs.__ordered_agent();
		}

		template <typename Tp, typename KeyCompare, typename Allocator>
		bool operator!=(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs)
		{
			return lhs.__ordered_agent() != rhs.__ordered_agent();
		}

		template <typename Tp, typename KeyCompare, typename Allocator>
		bool operator<(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs)
		{
			return lhs.__ordered_agent() < rhs.__ordered_agent();
		}

		template <typename Tp, typename KeyCompare, typename Allocator>
		bool operator<=(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs)
		{
			return lhs.__ordered_agent() <= rhs.__ordered_agent();
		}

		template <typename Tp, typename KeyCompare, typename Allocator>
		bool operator>(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs)
		{
			return lhs.__ordered_agent() > rhs.__ordered_agent();
		}

		template <typename Tp, typename KeyCompare, typename Allocator>
		bool operator>=(const flatset<Tp, KeyCompare, Allocator> & lhs, const flatset<Tp, KeyCompare, Allocator> & rhs)
		{
			return lhs.__ordered_agent() >= rhs.__ordered_agent();
		}

	}
}


#endif /* KERBAL_CONTAINER_FLATSET_HPP_ */
