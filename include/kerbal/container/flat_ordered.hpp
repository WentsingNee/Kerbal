/**
 * @file       flat_ordered.hpp
 * @brief
 * @date       2019-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FLAT_ORDERED_HPP_
#define KERBAL_CONTAINER_FLAT_ORDERED_HPP_

#include <kerbal/container/impl/flat_ordered_base.hpp>

#include <cstddef>
#include <vector>

namespace kerbal
{

	namespace container
	{

		template <typename Entity, typename Key = Entity, typename KeyCompare = std::less<Key>,
				typename Extract = default_extract<Key, Entity>, typename Allocator = std::allocator<Entity> >
		class flat_ordered:
				public kerbal::container::detail::__flat_ordered_base<
						Entity, Key, KeyCompare, Extract, typename std::vector<Entity, Allocator>
				>
		{
			public:
				typedef std::vector<Entity, Allocator> Sequence;

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

				flat_ordered() :
						super()
				{
				}

				explicit flat_ordered(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				flat_ordered(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0):
						super(first, last)
				{
				}

				template <typename InputIterator>
				flat_ordered(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0):
						super(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L

				flat_ordered(std::initializer_list<value_type> src) :
						super(src)
				{
				}

				flat_ordered(std::initializer_list<value_type> src, key_compare kc) :
						super(src, kc)
				{
				}

#		endif

				void assign(const flat_ordered& src)
				{
					this->assign(src.cbegin(), src.cend(), src.key_comp());
				}

				flat_ordered& operator=(const flat_ordered & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				flat_ordered& operator=(std::initializer_list<value_type> src)
				{
					this->assign(src);
					return *this;
				}

#		endif

				void swap(flat_ordered & ano)
				{
					this->__sequence().swap(ano.__sequence());
					std::swap(this->__key_comp(), ano.__key_comp());
				}

				friend bool operator==(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs);

				friend bool operator!=(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs);

				friend bool operator<(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs);

				friend bool operator<=(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs);

				friend bool operator>(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs);

				friend bool operator>=(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs);

		};

		template <typename Entity, typename Key, typename KeyCompare, typename Extract, typename Allocator>
		bool operator==(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs)
		{
			return lhs.__sequence() == rhs.__sequence();
		}

		template <typename Entity, typename Key, typename KeyCompare, typename Extract, typename Allocator>
		bool operator!=(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs)
		{
			return lhs.__sequence() != rhs.__sequence();
		}

		template <typename Entity, typename Key, typename KeyCompare, typename Extract, typename Allocator>
		bool operator<(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs)
		{
			return lhs.__sequence() < rhs.__sequence();
		}

		template <typename Entity, typename Key, typename KeyCompare, typename Extract, typename Allocator>
		bool operator<=(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs)
		{
			return lhs.__sequence() <= rhs.__sequence();
		}

		template <typename Entity, typename Key, typename KeyCompare, typename Extract, typename Allocator>
		bool operator>(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs)
		{
			return lhs.__sequence() > rhs.__sequence();
		}

		template <typename Entity, typename Key, typename KeyCompare, typename Extract, typename Allocator>
		bool operator>=(const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & lhs, const flat_ordered<Entity, Key, KeyCompare, Extract, Allocator> & rhs)
		{
			return lhs.__sequence() >= rhs.__sequence();
		}

	} // namespace container

} // namespace kerbal


#endif /* KERBAL_CONTAINER_FLAT_ORDERED_HPP_ */
