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

#ifndef KERBAL_CONTAINER_STATIC_FLAT_SET_HPP
#define KERBAL_CONTAINER_STATIC_FLAT_SET_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/container/static_ordered.hpp>

#include <kerbal/container/detail/flat_set_base.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		KERBAL_MODULE_EXPORT
		template <
			typename T,
			std::size_t N,
			typename KeyCompare = kerbal::compare::less<T>
		>
		class static_flat_set :
			public kerbal::container::detail::flat_set_base<
				kerbal::container::static_ordered<T, N, kerbal::container::identity_extractor<T>, KeyCompare>
			>
		{
			private:
				typedef kerbal::container::static_ordered<T, N, kerbal::container::identity_extractor<T>, KeyCompare> Ordered;
				typedef kerbal::container::detail::flat_set_base<Ordered> super;

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

				KERBAL_CONSTEXPR
				static_flat_set() :
					super()
				{
				}

				KERBAL_CONSTEXPR
				explicit static_flat_set(key_compare kc) :
					super(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_flat_set(
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
				static_flat_set(
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
				static_flat_set(std::initializer_list<value_type> ilist) :
					super(ilist)
				{
				}

				KERBAL_CONSTEXPR14
				static_flat_set(std::initializer_list<value_type> ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		else

				template <typename U>
				static_flat_set(const kerbal::assign::assign_list<U> & ilist) :
					super(ilist)
				{
				}

				template <typename U>
				static_flat_set(const kerbal::assign::assign_list<U> & ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		endif

				using super::assign;

				KERBAL_CONSTEXPR14
				void assign(const static_flat_set & src)
				{
					this->ordered.assign(src.ordered);
				}

				KERBAL_CONSTEXPR14
				static_flat_set & operator=(const static_flat_set & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_flat_set & operator=(std::initializer_list<value_type> ilist)
				{
					this->super::assign(ilist);
					return *this;
				}

#		else

				template <typename U>
				static_flat_set & operator=(const kerbal::assign::assign_list<U> & ilist)
				{
					this->super::assign(ilist);
					return *this;
				}

#		endif

				KERBAL_CONSTEXPR
				bool full() const
				{
					return this->ordered.full();
				}

				KERBAL_CONSTEXPR14
				void swap(static_flat_set & ano)
				{
					this->ordered.swap(ano.ordered);
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool operator==(
					const static_flat_set<T, M, KeyCompare> & lhs,
					const static_flat_set<T, N, KeyCompare> & rhs
				)
				{
					return lhs.ordered == rhs.ordered;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool operator!=(
					const static_flat_set<T, M, KeyCompare> & lhs,
					const static_flat_set<T, N, KeyCompare> & rhs
				)
				{
					return lhs.ordered != rhs.ordered;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool operator<(
					const static_flat_set<T, M, KeyCompare> & lhs,
					const static_flat_set<T, N, KeyCompare> & rhs
				)
				{
					return lhs.ordered < rhs.ordered;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool operator<=(
					const static_flat_set<T, M, KeyCompare> & lhs,
					const static_flat_set<T, N, KeyCompare> & rhs
				)
				{
					return lhs.ordered <= rhs.ordered;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool operator>(
					const static_flat_set<T, M, KeyCompare> & lhs,
					const static_flat_set<T, N, KeyCompare> & rhs
				)
				{
					return lhs.ordered > rhs.ordered;
				}

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				friend
				bool operator>=(
					const static_flat_set<T, M, KeyCompare> & lhs,
					const static_flat_set<T, N, KeyCompare> & rhs
				)
				{
					return lhs.ordered >= rhs.ordered;
				}

		};

	} // namespace container


	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N, typename KeyCompare>
		KERBAL_CONSTEXPR14
		void swap(
			kerbal::container::static_flat_set<T, N, KeyCompare> & a,
			kerbal::container::static_flat_set<T, N, KeyCompare> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	KERBAL_MODULE_EXPORT
	template <typename T, std::size_t N, typename KeyCompare>
	KERBAL_CONSTEXPR14
	void swap(
		kerbal::container::static_flat_set<T, N, KeyCompare> & a,
		kerbal::container::static_flat_set<T, N, KeyCompare> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_STATIC_FLAT_SET_HPP
