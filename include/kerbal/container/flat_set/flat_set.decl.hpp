/**
 * @file       flat_set.decl.hpp
 * @brief
 * @date       2019-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FLAT_SET_FLAT_SET_DECL_HPP
#define KERBAL_CONTAINER_FLAT_SET_FLAT_SET_DECL_HPP

#include <kerbal/container/flat_set/flat_set.fwd.hpp>

#include <kerbal/container/detail/flat_set_base.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/container/flat_ordered.hpp>
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
			typename T,
			typename KeyCompare,
			typename Allocator
		>
		class flat_set :
			public kerbal::container::detail::flat_set_base<
				kerbal::container::flat_ordered<
					T,
					kerbal::container::identity_extractor<T>,
					KeyCompare,
					Allocator
				>
			>
		{
			private:
				typedef kerbal::container::flat_ordered<
					T,
					kerbal::container::identity_extractor<T>,
					KeyCompare,
					Allocator
				> Ordered;
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

				typedef Allocator									allocator_type;

				typedef typename super::size_type					size_type;
				typedef typename super::difference_type				difference_type;

				typedef typename super::const_iterator				const_iterator;
				typedef typename super::const_reverse_iterator		const_reverse_iterator;

				typedef typename super::key_type			key_type;
				typedef typename super::key_compare			key_compare;


			//===================
			// construct/copy/destroy

			public:

				KERBAL_CONSTEXPR20
				flat_set() :
					super()
				{
				}

				KERBAL_CONSTEXPR20
				explicit
				flat_set(key_compare kc) :
					super(kc)
				{
				}

#		if __cplusplus >= 201103L

				flat_set(const flat_set & src) = default;
				flat_set(flat_set && src) = default;

#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
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
				KERBAL_CONSTEXPR20
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

				KERBAL_CONSTEXPR20
				flat_set(std::initializer_list<value_type> ilist) :
					super(ilist)
				{
				}

				KERBAL_CONSTEXPR20
				flat_set(std::initializer_list<value_type> ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		else

				template <typename U>
				flat_set(const kerbal::assign::assign_list<U> & ilist) :
					super(ilist)
				{
				}

				template <typename U>
				flat_set(const kerbal::assign::assign_list<U> & ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		endif


			//===================
			// assign

			public:

				using super::assign;

				KERBAL_CONSTEXPR20
				void
				assign(const flat_set & src)
				{
					this->ordered.assign(src.ordered);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void
				assign(flat_set && src)
				{
					this->ordered.assign(kerbal::compatibility::move(src.ordered));
				}

#		endif

				KERBAL_CONSTEXPR20
				flat_set &
				operator=(const flat_set & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				flat_set &
				operator=(flat_set && src)
				{
					this->assign(kerbal::compatibility::move(src));
					return *this;
				}

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				flat_set &
				operator=(std::initializer_list<value_type> ilist)
				{
					this->super::assign(ilist);
					return *this;
				}

#		else

				template <typename U>
				flat_set &
				operator=(const kerbal::assign::assign_list<U> & ilist)
				{
					this->super::assign(ilist);
					return *this;
				}

#		endif


			//===================
			// capacity

				KERBAL_CONSTEXPR20
				void
				reserve(size_type new_cap)
				{
					this->ordered.reserve(new_cap);
				}


			//===================
			// operation

				KERBAL_CONSTEXPR20
				void
				swap(flat_set & ano)
				{
					this->ordered.swap(ano.ordered);
				}


				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator==(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered == rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator!=(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered != rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator<(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered < rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator<=(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered <= rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator>(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered > rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator>=(
					const flat_set<T, KeyCompare, Allocator> & lhs,
					const flat_set<T, KeyCompare, Allocator2> & rhs
				)
				{
					return lhs.ordered >= rhs.ordered;
				}

		};


#	if __cplusplus >= 201703L

		template <typename InputIterator>
		flat_set(
			InputIterator, InputIterator
		) ->
		flat_set<
			typename kerbal::iterator::iterator_traits<InputIterator>::value_type
		>;

		template <
			typename InputIterator,
			typename KeyCompare
		>
		flat_set(
			InputIterator, InputIterator,
			const KeyCompare &
		) ->
		flat_set<
			typename kerbal::iterator::iterator_traits<InputIterator>::value_type,
			KeyCompare
		>;


		template <typename T>
		flat_set(
			std::initializer_list<T>
		) ->
		flat_set<T>;

		template <
			typename T, typename KeyCompare
		>
		flat_set(
			std::initializer_list<T>,
			const KeyCompare &
		) ->
		flat_set<T, KeyCompare>;

#	endif // if __cplusplus >= 201703L


	} // namespace container


	namespace algorithm
	{

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		swap(
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
	KERBAL_CONSTEXPR20
	void
	swap(
		kerbal::container::flat_set<T, KeyCompare, Allocator> & a,
		kerbal::container::flat_set<T, KeyCompare, Allocator> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_FLAT_SET_FLAT_SET_DECL_HPP
