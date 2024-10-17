/**
 * @file       static_flat_multimap.decl.hpp
 * @brief
 * @date       2024-03-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_FLAT_MULTIMAP_STATIC_FLAT_MULTIMAP_DECL_HPP
#define KERBAL_CONTAINER_STATIC_FLAT_MULTIMAP_STATIC_FLAT_MULTIMAP_DECL_HPP

#include <kerbal/container/static_flat_multimap/static_flat_multimap.fwd.hpp>

#include <kerbal/container/detail/flat_multimap_base.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/tuple_first_extractor.hpp>
#include <kerbal/container/associative_container_facility/map_data.hpp>
#include <kerbal/container/static_ordered.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		template <
			typename K, typename M,
			std::size_t N,
			typename KeyCompare
		>
		class static_flat_multimap :
			public kerbal::container::detail::flat_multimap_base<
				kerbal::container::static_ordered<
					kerbal::container::map_data<K, M>, N,
					kerbal::container::tuple_first_extractor<kerbal::container::map_data<K, M>, K const>,
					KeyCompare
				>
			>
		{
			private:
				typedef kerbal::container::static_ordered<
					kerbal::container::map_data<K, M>, N,
					kerbal::container::tuple_first_extractor<kerbal::container::map_data<K, M>, K const>,
					KeyCompare
				> Ordered;
				typedef kerbal::container::detail::flat_multimap_base<Ordered> super;

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

				typedef typename super::size_type					size_type;
				typedef typename super::difference_type				difference_type;

				typedef typename super::iterator					iterator;
				typedef typename super::const_iterator				const_iterator;
				typedef typename super::reverse_iterator			reverse_iterator;
				typedef typename super::const_reverse_iterator		const_reverse_iterator;

				typedef typename super::key_type			key_type;
				typedef typename super::key_compare			key_compare;
				typedef typename super::mapped_type			mapped_type;


			//===================
			// construct/copy/destroy

			public:

				KERBAL_CONSTEXPR
				static_flat_multimap() :
					super()
				{
				}

				KERBAL_CONSTEXPR
				explicit
				static_flat_multimap(key_compare kc) :
					super(kc)
				{
				}

#		if __cplusplus >= 201103L

				static_flat_multimap(const static_flat_multimap & src) = default;
				static_flat_multimap(static_flat_multimap && src) = default;

#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_flat_multimap(
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
				static_flat_multimap(
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
				static_flat_multimap(std::initializer_list<value_type> ilist) :
					super(ilist)
				{
				}

				KERBAL_CONSTEXPR14
				static_flat_multimap(std::initializer_list<value_type> ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		else

				template <typename U>
				static_flat_multimap(const kerbal::assign::assign_list<U> & ilist) :
					super(ilist)
				{
				}

				template <typename U>
				static_flat_multimap(const kerbal::assign::assign_list<U> & ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		endif


			//===================
			// assign

			public:

				using super::assign;

				KERBAL_CONSTEXPR14
				void
				assign(const static_flat_multimap & src)
				{
					this->ordered.assign(src.ordered);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void
				assign(static_flat_multimap && src)
				{
					this->ordered.assign(kerbal::compatibility::move(src.ordered));
				}

#		endif

				KERBAL_CONSTEXPR14
				static_flat_multimap &
				operator=(const static_flat_multimap & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_flat_multimap &
				operator=(static_flat_multimap && src)
				{
					this->assign(kerbal::compatibility::move(src));
					return *this;
				}

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_flat_multimap &
				operator=(std::initializer_list<value_type> ilist)
				{
					this->super::assign(ilist);
					return *this;
				}

#		else

				template <typename U>
				static_flat_multimap &
				operator=(const kerbal::assign::assign_list<U> & ilist)
				{
					this->super::assign(ilist);
					return *this;
				}

#		endif


			//===================
			// capacity

				KERBAL_CONSTEXPR
				bool
				full() const
				{
					return this->ordered.full();
				}


			//===================
			// operation

				KERBAL_CONSTEXPR14
				void
				swap(static_flat_multimap & ano)
				{
					this->ordered.swap(ano.ordered);
				}


				template <typename K2, typename M2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator==(
					const static_flat_multimap<K2, M2, N1, KeyCompare2> & lhs,
					const static_flat_multimap<K2, M2, N2, KeyCompare2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator!=(
					const static_flat_multimap<K2, M2, N1, KeyCompare2> & lhs,
					const static_flat_multimap<K2, M2, N2, KeyCompare2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator<(
					const static_flat_multimap<K2, M2, N1, KeyCompare2> & lhs,
					const static_flat_multimap<K2, M2, N2, KeyCompare2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator<=(
					const static_flat_multimap<K2, M2, N1, KeyCompare2> & lhs,
					const static_flat_multimap<K2, M2, N2, KeyCompare2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator>(
					const static_flat_multimap<K2, M2, N1, KeyCompare2> & lhs,
					const static_flat_multimap<K2, M2, N2, KeyCompare2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				bool
				operator>=(
					const static_flat_multimap<K2, M2, N1, KeyCompare2> & lhs,
					const static_flat_multimap<K2, M2, N2, KeyCompare2> & rhs
				);

		};

		template <typename K, typename M, typename KeyCompare, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		bool
		operator==(
			const static_flat_multimap<K, M, N1, KeyCompare> & lhs,
			const static_flat_multimap<K, M, N2, KeyCompare> & rhs
		)
		{
			return lhs.ordered == rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		bool
		operator!=(
			const static_flat_multimap<K, M, N1, KeyCompare> & lhs,
			const static_flat_multimap<K, M, N2, KeyCompare> & rhs
		)
		{
			return lhs.ordered != rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		bool
		operator<(
			const static_flat_multimap<K, M, N1, KeyCompare> & lhs,
			const static_flat_multimap<K, M, N2, KeyCompare> & rhs
		)
		{
			return lhs.ordered < rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		bool
		operator<=(
			const static_flat_multimap<K, M, N1, KeyCompare> & lhs,
			const static_flat_multimap<K, M, N2, KeyCompare> & rhs
		)
		{
			return lhs.ordered <= rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		bool
		operator>(
			const static_flat_multimap<K, M, N1, KeyCompare> & lhs,
			const static_flat_multimap<K, M, N2, KeyCompare> & rhs
		)
		{
			return lhs.ordered > rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, std::size_t N1, std::size_t N2>
		KERBAL_CONSTEXPR14
		bool
		operator>=(
			const static_flat_multimap<K, M, N1, KeyCompare> & lhs,
			const static_flat_multimap<K, M, N2, KeyCompare> & rhs
		)
		{
			return lhs.ordered >= rhs.ordered;
		}

	} // namespace container


	namespace algorithm
	{

		template <typename K, typename M, std::size_t N, typename KeyCompare>
		KERBAL_CONSTEXPR14
		void
		swap(
			kerbal::container::static_flat_multimap<K, M, N, KeyCompare> & a,
			kerbal::container::static_flat_multimap<K, M, N, KeyCompare> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename K, typename M, std::size_t N, typename KeyCompare>
	KERBAL_CONSTEXPR14
	void
	swap(
		kerbal::container::static_flat_multimap<K, M, N, KeyCompare> & a,
		kerbal::container::static_flat_multimap<K, M, N, KeyCompare> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_STATIC_FLAT_MULTIMAP_STATIC_FLAT_MULTIMAP_DECL_HPP
