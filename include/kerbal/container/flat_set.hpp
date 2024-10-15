/**
 * @file       flat_set.hpp
 * @brief
 * @date       2019-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FLAT_SET_HPP
#define KERBAL_CONTAINER_FLAT_SET_HPP

#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/container/flat_ordered.hpp>

#include <kerbal/container/detail/flat_set_base.hpp>

#include <memory>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		template <
			typename T,
			typename KeyCompare = kerbal::compare::less<T>,
			typename Allocator = std::allocator<T>
		>
		class flat_set :
			public kerbal::container::detail::flat_set_base<
				kerbal::container::flat_ordered<T, kerbal::container::identity_extractor<T>, KeyCompare, Allocator>
			>
		{
			private:
				typedef kerbal::container::flat_ordered<T, kerbal::container::identity_extractor<T>, KeyCompare, Allocator> Ordered;
				typedef kerbal::container::detail::flat_set_base<Ordered> super;

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

				typedef Allocator					allocator_type;

				typedef typename super::size_type					size_type;
				typedef typename super::difference_type				difference_type;

				typedef typename super::const_iterator				const_iterator;
				typedef typename super::const_reverse_iterator		const_reverse_iterator;

				typedef typename super::key_type			key_type;
				typedef typename super::key_compare			key_compare;

			public:

				flat_set() :
					super()
				{
				}

				explicit flat_set(key_compare kc) :
					super(kc)
				{
				}

				template <typename InputIterator>
				flat_set(
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
				flat_set(
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

				flat_set(std::initializer_list<value_type> ilist) :
					super(ilist)
				{
				}

				flat_set(std::initializer_list<value_type> ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		endif


			//===================
			// assign

				flat_set & operator=(const flat_set & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				flat_set & operator=(std::initializer_list<value_type> ilist)
				{
					this->super::assign(ilist);
					return *this;
				}

#		endif

				using super::assign;

				void assign(const flat_set & src)
				{
					this->ordered.assign(src.ordered);
				}

				void reserve(size_type new_cap)
				{
					this->ordered.reserve(new_cap);
				}

				void swap(flat_set & ano)
				{
					this->ordered.swap(ano.ordered);
				}

				template <typename Allocator2>
				friend
				bool operator==(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered == rhs.ordered;
				}

				template <typename Allocator2>
				friend
				bool operator!=(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered != rhs.ordered;
				}

				template <typename Allocator2>
				friend
				bool operator<(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered < rhs.ordered;
				}

				template <typename Allocator2>
				friend
				bool operator<=(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered <= rhs.ordered;
				}

				template <typename Allocator2>
				friend
				bool operator>(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered > rhs.ordered;
				}

				template <typename Allocator2>
				friend
				bool operator>=(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered >= rhs.ordered;
				}

		};

	} // namespace container


	namespace algorithm
	{

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR14
		void swap(
			kerbal::container::flat_set<T, KeyCompare, Allocator> & a,
			kerbal::container::flat_set<T, KeyCompare, Allocator> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename KeyCompare, typename Allocator>
	KERBAL_CONSTEXPR14
	void swap(
		kerbal::container::flat_set<T, KeyCompare, Allocator> & a,
		kerbal::container::flat_set<T, KeyCompare, Allocator> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_FLAT_SET_HPP
