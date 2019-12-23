/**
 * @file       static_ordered.hpp
 * @brief
 * @date       2019-8-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_ORDERED_HPP_
#define KERBAL_CONTAINER_STATIC_ORDERED_HPP_

#include <kerbal/container/impl/flat_ordered_base.hpp>
#include <kerbal/container/static_vector.hpp>

#include <cstddef>

namespace kerbal
{

	namespace container
	{

		template <typename Entity, size_t N, typename Key = Entity,
			typename KeyCompare = std::less<Key>, typename Extract = default_extract<Key, Entity> >
		class static_ordered:
				public kerbal::container::detail::__flat_ordered_base<
						Entity, Key, KeyCompare, Extract, typename kerbal::container::static_vector<Entity, N>
				>
		{
			public:
				typedef kerbal::container::static_vector<Entity, N> Sequence;

			private:
				typedef kerbal::container::detail::__flat_ordered_base<
										Entity, Key, KeyCompare, Extract, Sequence
								> super;

			public:
				typedef KeyCompare				key_compare;

				typedef Entity					value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef typename Sequence::size_type				size_type;
				typedef typename Sequence::difference_type			difference_type;

				typedef typename Sequence::iterator					iterator;
				typedef typename Sequence::const_iterator			const_iterator;
				typedef typename Sequence::reverse_iterator			reverse_iterator;
				typedef typename Sequence::const_reverse_iterator	const_reverse_iterator;

				static_ordered() :
						super()
				{
				}

				explicit static_ordered(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				static_ordered(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0):
						super(first, last)
				{
				}

				template <typename InputIterator>
				static_ordered(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0):
						super(first, last, kc)
				{
				}

#if		__cplusplus >= 201103L

				static_ordered(std::initializer_list<value_type> src) :
						super(src)
				{
				}

				static_ordered(std::initializer_list<value_type> src, key_compare kc) :
						super(src, kc)
				{
				}

#		endif

				void assign(const static_ordered& src)
				{
					this->assign(src.cbegin(), src.cend(), src.key_comp());
				}

				static_ordered& operator=(const static_ordered & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				static_ordered& operator=(std::initializer_list<value_type> src)
				{
					this->assign(src);
					return *this;
				}

#		endif

				void swap(static_ordered & ano)
				{
					this->__sequence().swap(ano.__sequence());
					std::swap(this->__key_comp(), ano.__key_comp());
				}

				template <size_t M>
				friend bool operator==(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs);

				template <size_t M>
				friend bool operator!=(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs);

				template <size_t M>
				friend bool operator<(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs);

				template <size_t M>
				friend bool operator<=(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs);

				template <size_t M>
				friend bool operator>(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs);

				template <size_t M>
				friend bool operator>=(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs);

		};

		template <typename Entity, size_t M, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool operator==(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
		{
			return lhs.__sequence() == rhs.__sequence();
		}

		template <typename Entity, size_t M, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool operator!=(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
		{
			return lhs.__sequence() != rhs.__sequence();
		}

		template <typename Entity, size_t M, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool operator<(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
		{
			return lhs.__sequence() < rhs.__sequence();
		}

		template <typename Entity, size_t M, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool operator<=(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
		{
			return lhs.__sequence() <= rhs.__sequence();
		}

		template <typename Entity, size_t M, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool operator>(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
		{
			return lhs.__sequence() > rhs.__sequence();
		}

		template <typename Entity, size_t M, size_t N, typename Key, typename KeyCompare, typename Extract>
		bool operator>=(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs, const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
		{
			return lhs.__sequence() >= rhs.__sequence();
		}

	} // namespace container

} // namespace kerbal

#endif /* KERBAL_CONTAINER_STATIC_ORDERED_HPP_ */
