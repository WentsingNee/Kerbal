/**
 * @file       static_ordered.decl.hpp
 * @brief
 * @date       2019-8-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_ORDERED_STATIC_ORDERED_DECL_HPP
#define KERBAL_CONTAINER_STATIC_ORDERED_STATIC_ORDERED_DECL_HPP

#include <kerbal/container/static_ordered/static_ordered.fwd.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/static_vector.hpp>

#include <kerbal/container/detail/flat_ordered_base.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		template <
			typename Entity,
			std::size_t N,
			typename Extract,
			typename KeyCompare
		>
		class static_ordered :
			public kerbal::container::detail::flat_ordered_base<
				Entity, Extract, KeyCompare, kerbal::container::static_vector<Entity, N>
			>
		{
			public:
				typedef kerbal::container::static_vector<Entity, N> Sequence;

			private:
				typedef kerbal::container::detail::flat_ordered_base<
					Entity, Extract, KeyCompare, Sequence
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
				explicit
				static_ordered(key_compare kc) :
					super(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_ordered(
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
				KERBAL_CONSTEXPR14
				static_ordered(
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

				KERBAL_CONSTEXPR14
				static_ordered(std::initializer_list<value_type> ilist) :
					super(ilist)
				{
				}

				KERBAL_CONSTEXPR14
				static_ordered(std::initializer_list<value_type> ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		else

				template <typename U>
				static_ordered(const kerbal::assign::assign_list<U> & ilist) :
					super(ilist)
				{
				}

				template <typename U>
				static_ordered(const kerbal::assign::assign_list<U> & ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		endif

				using super::assign;

				KERBAL_CONSTEXPR14
				void
				assign(const static_ordered & src)
				{
					this->assign(src.cbegin(), src.cend(), src.key_comp());
				}

				KERBAL_CONSTEXPR14
				static_ordered &
				operator=(const static_ordered & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_ordered &
				operator=(std::initializer_list<value_type> ilist)
				{
					this->assign(ilist);
					return *this;
				}

#		else

				template <typename U>
				static_ordered &
				operator=(const kerbal::assign::assign_list<U> & ilist)
				{
					this->assign(ilist);
					return *this;
				}

#		endif

				KERBAL_CONSTEXPR
				bool
				full() const
				{
					return this->sequence.full();
				}

				KERBAL_CONSTEXPR14
				void
				swap(static_ordered & ano)
				{
					this->sequence.swap(ano.sequence);
					kerbal::algorithm::swap(this->key_comp(), ano.key_comp());
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator==(
					const static_ordered<Entity, M, Extract, KeyCompare> & lhs,
					const static_ordered<Entity, N, Extract, KeyCompare> & rhs
				)
				{
					return lhs.sequence == rhs.sequence;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator!=(
					const static_ordered<Entity, M, Extract, KeyCompare> & lhs,
					const static_ordered<Entity, N, Extract, KeyCompare> & rhs
				)
				{
					return lhs.sequence != rhs.sequence;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator<(
					const static_ordered<Entity, M, Extract, KeyCompare> & lhs,
					const static_ordered<Entity, N, Extract, KeyCompare> & rhs
				)
				{
					return lhs.sequence < rhs.sequence;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator<=(
					const static_ordered<Entity, M, Extract, KeyCompare> & lhs,
					const static_ordered<Entity, N, Extract, KeyCompare> & rhs
				)
				{
					return lhs.sequence <= rhs.sequence;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator>(
					const static_ordered<Entity, M, Extract, KeyCompare> & lhs,
					const static_ordered<Entity, N, Extract, KeyCompare> & rhs
				)
				{
					return lhs.sequence > rhs.sequence;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator>=(
					const static_ordered<Entity, M, Extract, KeyCompare> & lhs,
					const static_ordered<Entity, N, Extract, KeyCompare> & rhs
				)
				{
					return lhs.sequence >= rhs.sequence;
				}

		};

	} // namespace container


	namespace algorithm
	{

		template <typename Entity, std::size_t N, typename Extract, typename KeyCompare>
		KERBAL_CONSTEXPR14
		void
		swap(
			kerbal::container::static_ordered<Entity, N, Extract, KeyCompare> & a,
			kerbal::container::static_ordered<Entity, N, Extract, KeyCompare> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Entity, std::size_t N, typename Extract, typename KeyCompare>
	KERBAL_CONSTEXPR14
	void
	swap(
		kerbal::container::static_ordered<Entity, N, Extract, KeyCompare> & a,
		kerbal::container::static_ordered<Entity, N, Extract, KeyCompare> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_STATIC_ORDERED_STATIC_ORDERED_DECL_HPP
