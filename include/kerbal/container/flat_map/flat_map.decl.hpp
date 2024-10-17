/**
 * @file       flat_map.decl.hpp
 * @brief
 * @date       2024-10-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FLAT_MAP_FLAT_MAP_DECL_HPP
#define KERBAL_CONTAINER_FLAT_MAP_FLAT_MAP_DECL_HPP

#include <kerbal/container/flat_map/flat_map.fwd.hpp>

#include <kerbal/container/detail/flat_map_base.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/tuple_first_extractor.hpp>
#include <kerbal/container/associative_container_facility/map_data.hpp>
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
			typename K, typename M,
			typename KeyCompare,
			typename Allocator
		>
		class flat_map :
			public kerbal::container::detail::flat_map_base<
				kerbal::container::flat_ordered<
					kerbal::container::map_data<K, M>,
					kerbal::container::tuple_first_extractor<kerbal::container::map_data<K, M>, K const>,
					KeyCompare,
					Allocator
				>
			>
		{
			private:
				typedef kerbal::container::flat_ordered<
					kerbal::container::map_data<K, M>,
					kerbal::container::tuple_first_extractor<kerbal::container::map_data<K, M>, K const>,
					KeyCompare,
					Allocator
				> Ordered;
				typedef kerbal::container::detail::flat_map_base<Ordered> super;

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
				typedef typename super::mapped_type			mapped_type;


			//===================
			// construct/copy/destroy

			public:

				KERBAL_CONSTEXPR20
				flat_map() :
					super()
				{
				}

				KERBAL_CONSTEXPR20
				explicit
				flat_map(key_compare kc) :
					super(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				flat_map(
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
				flat_map(
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
				flat_map(std::initializer_list<value_type> ilist) :
					super(ilist)
				{
				}

				KERBAL_CONSTEXPR20
				flat_map(std::initializer_list<value_type> ilist, key_compare kc) :
					super(ilist, kc)
				{
				}

#		else

				template <typename U>
				flat_map(const kerbal::assign::assign_list<U> & ilist) :
					super(ilist)
				{
				}

				template <typename U>
				flat_map(const kerbal::assign::assign_list<U> & ilist, key_compare kc) :
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
				assign(const flat_map & src)
				{
					this->ordered.assign(src.ordered);
				}

				KERBAL_CONSTEXPR20
				flat_map &
				operator=(const flat_map & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				flat_map &
				operator=(std::initializer_list<value_type> ilist)
				{
					this->super::assign(ilist);
					return *this;
				}

#		else

				template <typename U>
				flat_map &
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
				swap(flat_map & ano)
				{
					this->ordered.swap(ano.ordered);
				}


				template <typename K2, typename M2, typename KeyCompare2, typename Allocator1, typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator==(
					const flat_map<K2, M2, KeyCompare2, Allocator1> & lhs,
					const flat_map<K2, M2, KeyCompare2, Allocator2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, typename Allocator1, typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator!=(
					const flat_map<K2, M2, KeyCompare2, Allocator1> & lhs,
					const flat_map<K2, M2, KeyCompare2, Allocator2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, typename Allocator1, typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator<(
					const flat_map<K2, M2, KeyCompare2, Allocator1> & lhs,
					const flat_map<K2, M2, KeyCompare2, Allocator2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, typename Allocator1, typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator<=(
					const flat_map<K2, M2, KeyCompare2, Allocator1> & lhs,
					const flat_map<K2, M2, KeyCompare2, Allocator2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, typename Allocator1, typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator>(
					const flat_map<K2, M2, KeyCompare2, Allocator1> & lhs,
					const flat_map<K2, M2, KeyCompare2, Allocator2> & rhs
				);

				template <typename K2, typename M2, typename KeyCompare2, typename Allocator1, typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				bool
				operator>=(
					const flat_map<K2, M2, KeyCompare2, Allocator1> & lhs,
					const flat_map<K2, M2, KeyCompare2, Allocator2> & rhs
				);

		};

		template <typename K, typename M, typename KeyCompare, typename Allocator1, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool
		operator==(
			const flat_map<K, M, KeyCompare, Allocator1> & lhs,
			const flat_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return lhs.ordered == rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator1, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool
		operator!=(
			const flat_map<K, M, KeyCompare, Allocator1> & lhs,
			const flat_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return lhs.ordered != rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator1, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool
		operator<(
			const flat_map<K, M, KeyCompare, Allocator1> & lhs,
			const flat_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return lhs.ordered < rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator1, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool
		operator<=(
			const flat_map<K, M, KeyCompare, Allocator1> & lhs,
			const flat_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return lhs.ordered <= rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator1, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool
		operator>(
			const flat_map<K, M, KeyCompare, Allocator1> & lhs,
			const flat_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return lhs.ordered > rhs.ordered;
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator1, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool
		operator>=(
			const flat_map<K, M, KeyCompare, Allocator1> & lhs,
			const flat_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return lhs.ordered >= rhs.ordered;
		}

	} // namespace container


	namespace algorithm
	{

		template <typename K, typename M, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		swap(
			kerbal::container::flat_map<K, M, KeyCompare, Allocator> & a,
			kerbal::container::flat_map<K, M, KeyCompare, Allocator> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename K, typename M, typename KeyCompare, typename Allocator>
	KERBAL_CONSTEXPR20
	void
	swap(
		kerbal::container::flat_map<K, M, KeyCompare, Allocator> & a,
		kerbal::container::flat_map<K, M, KeyCompare, Allocator> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_FLAT_MAP_FLAT_MAP_DECL_HPP
