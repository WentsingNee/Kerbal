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

#ifndef KERBAL_CONTAINER_STATIC_ORDERED_HPP
#define KERBAL_CONTAINER_STATIC_ORDERED_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/container/detail/flat_ordered_base.hpp>
#include <kerbal/container/static_vector.hpp>

#include <cstddef>

namespace kerbal
{

	namespace container
	{

		template <typename Entity, size_t N, typename Key = Entity,
			typename KeyCompare = std::less<Key>, typename Extract = default_extract<Key, Entity> >
		class static_ordered:
				public kerbal::container::detail::flat_ordered_base<
						Entity, Key, KeyCompare, Extract, kerbal::container::static_vector<Entity, N>
				>
		{
			public:
				typedef kerbal::container::static_vector<Entity, N> Sequence;

			private:
				typedef kerbal::container::detail::flat_ordered_base<
										Entity, Key, KeyCompare, Extract, Sequence
								> super;

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

				typedef typename super::iterator					iterator;
				typedef typename super::const_iterator				const_iterator;
				typedef typename super::reverse_iterator			reverse_iterator;
				typedef typename super::const_reverse_iterator		const_reverse_iterator;

				KERBAL_CONSTEXPR
				static_ordered() :
						super()
				{
				}

				KERBAL_CONSTEXPR
				explicit static_ordered(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_ordered(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0):
						super(first, last)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_ordered(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0):
						super(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_ordered(std::initializer_list<value_type> src) :
						super(src)
				{
				}

				KERBAL_CONSTEXPR14
				static_ordered(std::initializer_list<value_type> src, key_compare kc) :
						super(src, kc)
				{
				}

#		endif

				using super::assign;

				KERBAL_CONSTEXPR14
				void assign(const static_ordered& src)
				{
					this->assign(src.cbegin(), src.cend(), src.key_comp_obj());
				}

				KERBAL_CONSTEXPR14
				static_ordered& operator=(const static_ordered & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_ordered& operator=(std::initializer_list<value_type> src)
				{
					this->assign(src);
					return *this;
				}

#		endif

				KERBAL_CONSTEXPR
				bool full() const
				{
					return this->sequence.full();
				}

				KERBAL_CONSTEXPR14
				void swap(static_ordered & ano)
				{
					this->sequence.swap(ano.sequence);
					kerbal::algorithm::swap(this->key_comp_obj(), ano.key_comp_obj());
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator==(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs,
										const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
				{
					return lhs.sequence == rhs.sequence;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator!=(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs,
										const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
				{
					return lhs.sequence != rhs.sequence;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator<(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs,
										const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
				{
					return lhs.sequence < rhs.sequence;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator<=(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs,
										const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
				{
					return lhs.sequence <= rhs.sequence;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator>(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs,
										const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
				{
					return lhs.sequence > rhs.sequence;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator>=(const static_ordered<Entity, M, Key, KeyCompare, Extract> & lhs,
										const static_ordered<Entity, N, Key, KeyCompare, Extract> & rhs)
				{
					return lhs.sequence >= rhs.sequence;
				}

		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_STATIC_ORDERED_HPP
