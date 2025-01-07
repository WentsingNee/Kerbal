/**
 * @file       flat_ordered.decl.hpp
 * @brief
 * @date       2019-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FLAT_ORDERED_FLAT_ORDERED_DECL_HPP
#define KERBAL_CONTAINER_FLAT_ORDERED_FLAT_ORDERED_DECL_HPP

#include <kerbal/container/flat_ordered/flat_ordered.fwd.hpp>

#include <kerbal/container/detail/flat_ordered_base.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		template <
			typename Entity,
			typename Extract,
			typename KeyCompare,
			typename Allocator
		>
		class flat_ordered:
			public kerbal::container::detail::flat_ordered_base<
				Entity, Extract, KeyCompare, kerbal::container::vector<Entity, Allocator>
			>
		{
			public:
				typedef kerbal::container::vector<Entity, Allocator> Sequence;

			private:
				typedef kerbal::container::detail::flat_ordered_base<
					Entity, Extract, KeyCompare, Sequence
				> super;

			public:
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

				typedef Allocator									allocator_type;

				typedef typename super::size_type					size_type;
				typedef typename super::difference_type				difference_type;

				typedef typename super::iterator					iterator;
				typedef typename super::const_iterator				const_iterator;
				typedef typename super::reverse_iterator			reverse_iterator;
				typedef typename super::const_reverse_iterator		const_reverse_iterator;

				typedef typename super::key_type			key_type;
				typedef typename super::key_compare			key_compare;


			//===================
			// construct/copy/destroy

			public:

				flat_ordered() :
					super()
				{
				}

				explicit
				flat_ordered(key_compare kc) :
					super(kc)
				{
				}

				template <typename InputIterator>
				flat_ordered(
					InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				) :
					super(first, last)
				{
				}

				template <typename InputIterator>
				flat_ordered(
					InputIterator first, InputIterator last, key_compare kc,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				) :
					super(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L

				flat_ordered(std::initializer_list<value_type> ilist) :
					super(ilist)
				{
				}

				flat_ordered(std::initializer_list<value_type> ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		else

				template <typename U>
				flat_ordered(const kerbal::assign::assign_list<U> & ilist) :
					super(ilist)
				{
				}

				template <typename U>
				flat_ordered(const kerbal::assign::assign_list<U> & ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		endif


			//===================
			// assign

			public:

				using super::assign;

				void
				assign(const flat_ordered & src)
				{
					this->assign(src.cbegin(), src.cend(), src.key_comp());
				}

				flat_ordered &
				operator=(const flat_ordered & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				flat_ordered &
				operator=(std::initializer_list<value_type> ilist)
				{
					this->assign(ilist);
					return *this;
				}

#		else

				template <typename U>
				flat_ordered &
				operator=(const kerbal::assign::assign_list<U> & ilist)
				{
					this->assign(ilist);
					return *this;
				}

#		endif


			//===================
			// capacity

				void
				reserve(size_type new_cap)
				{
					this->sequence.reserve(new_cap);
				}


			//===================
			// operation

				void
				swap(flat_ordered & ano)
				{
					this->sequence.swap(ano.sequence);
					kerbal::algorithm::swap(this->key_comp(), ano.key_comp());
				}

				template <typename Allocator2>
				friend
				bool
				operator==(
					const flat_ordered<Entity, Extract, KeyCompare, Allocator> & lhs,
					const flat_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.sequence == rhs.sequence;
				}

				template <typename Allocator2>
				friend
				bool
				operator!=(
					const flat_ordered<Entity, Extract, KeyCompare, Allocator> & lhs,
					const flat_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.sequence != rhs.sequence;
				}

				template <typename Allocator2>
				friend
				bool
				operator<(
					const flat_ordered<Entity, Extract, KeyCompare, Allocator> & lhs,
					const flat_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.sequence < rhs.sequence;
				}

				template <typename Allocator2>
				friend
				bool
				operator<=(
					const flat_ordered<Entity, Extract, KeyCompare, Allocator> & lhs,
					const flat_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.sequence <= rhs.sequence;
				}

				template <typename Allocator2>
				friend
				bool
				operator>(
					const flat_ordered<Entity, Extract, KeyCompare, Allocator> & lhs,
					const flat_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.sequence > rhs.sequence;
				}

				template <typename Allocator2>
				friend
				bool
				operator>=(
					const flat_ordered<Entity, Extract, KeyCompare, Allocator> & lhs,
					const flat_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.sequence >= rhs.sequence;
				}

		};

	} // namespace container


	namespace algorithm
	{

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR14
		void
		swap(
			kerbal::container::flat_ordered<Entity, Extract, KeyCompare, Allocator> & a,
			kerbal::container::flat_ordered<Entity, Extract, KeyCompare, Allocator> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
	KERBAL_CONSTEXPR14
	void
	swap(
		kerbal::container::flat_ordered<Entity, Extract, KeyCompare, Allocator> & a,
		kerbal::container::flat_ordered<Entity, Extract, KeyCompare, Allocator> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_FLAT_ORDERED_FLAT_ORDERED_DECL_HPP
