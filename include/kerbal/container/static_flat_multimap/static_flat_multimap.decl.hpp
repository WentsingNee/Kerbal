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

#include <kerbal/assign/assign_list.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/static_ordered.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/tuple_first_extractor.hpp>
#include <kerbal/container/associative_container_facility/map_data.hpp>

#include <cstddef>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/detail/flat_map_base.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Key, typename Value, std::size_t N, typename KeyCompare>
		class static_flat_multimap :
				public kerbal::container::detail::flat_multimap_base<
					kerbal::container::static_ordered<
						kerbal::container::map_data<Key, Value>, N,
						kerbal::container::tuple_first_extractor<kerbal::container::map_data<Key, Value>, Key>,
						KeyCompare
					>
				>
		{
			private:
				typedef kerbal::container::static_ordered<
					kerbal::container::map_data<Key, Value>, N,
					kerbal::container::tuple_first_extractor<kerbal::container::map_data<Key, Value>, Key>,
					KeyCompare
				> Ordered;
				typedef kerbal::container::detail::flat_multimap_base<Ordered> super;

			public:
				typedef typename super::key_compare			key_compare;
				typedef typename super::key_type			key_type;
				typedef typename super::mapped_type			mapped_type;
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

			public:

				KERBAL_CONSTEXPR
				static_flat_multimap() :
						super()
				{
				}

				KERBAL_CONSTEXPR
				explicit static_flat_multimap(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_flat_multimap(InputIterator first, InputIterator last,
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
				static_flat_multimap(InputIterator first, InputIterator last, key_compare kc,
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

				KERBAL_CONSTEXPR14
				void assign(const static_flat_multimap & src)
				{
					this->ordered.assign(src.ordered);
				}

				KERBAL_CONSTEXPR14
				static_flat_multimap& operator=(const static_flat_multimap & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_flat_multimap& operator=(std::initializer_list<value_type> ilist)
				{
					this->assign(ilist);
					return *this;
				}

				KERBAL_CONSTEXPR14
				void assign(std::initializer_list<value_type> ilist)
				{
					this->super::assign(ilist);
				}

#		else

				template <typename U>
				static_flat_multimap& operator=(const kerbal::assign::assign_list<U> & ilist)
				{
					this->assign(ilist);
					return *this;
				}

				template <typename U>
				void assign(const kerbal::assign::assign_list<U> & ilist)
				{
					this->super::assign(ilist);
				}

#		endif

				KERBAL_CONSTEXPR
				bool full() const
				{
					return this->ordered.full();
				}

				KERBAL_CONSTEXPR14
				void swap(static_flat_multimap & ano)
				{
					this->ordered.swap(ano.ordered);
				}


				template <typename Key2, typename Value2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend bool operator==(
						const static_flat_multimap<Key2, Value2, N1, KeyCompare2> & lhs,
						const static_flat_multimap<Key2, Value2, N2, KeyCompare2> & rhs
				);

				template <typename Key2, typename Value2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend bool operator!=(
						const static_flat_multimap<Key2, Value2, N1, KeyCompare2> & lhs,
						const static_flat_multimap<Key2, Value2, N2, KeyCompare2> & rhs
				);

				template <typename Key2, typename Value2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend bool operator<(
						const static_flat_multimap<Key2, Value2, N1, KeyCompare2> & lhs,
						const static_flat_multimap<Key2, Value2, N2, KeyCompare2> & rhs
				);

				template <typename Key2, typename Value2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend bool operator<=(
						const static_flat_multimap<Key2, Value2, N1, KeyCompare2> & lhs,
						const static_flat_multimap<Key2, Value2, N2, KeyCompare2> & rhs
				);

				template <typename Key2, typename Value2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend bool operator>(
						const static_flat_multimap<Key2, Value2, N1, KeyCompare2> & lhs,
						const static_flat_multimap<Key2, Value2, N2, KeyCompare2> & rhs
				);

				template <typename Key2, typename Value2, typename KeyCompare2, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend bool operator>=(
						const static_flat_multimap<Key2, Value2, N1, KeyCompare2> & lhs,
						const static_flat_multimap<Key2, Value2, N2, KeyCompare2> & rhs
				);

		};

		template <typename Key, typename Value, typename KeyCompare, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator==(
				const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
				const static_flat_multimap<Key, Value, N, KeyCompare> & rhs
		)
		{
			return lhs.ordered == rhs.ordered;
		}

		template <typename Key, typename Value, typename KeyCompare, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator!=(
				const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
				const static_flat_multimap<Key, Value, N, KeyCompare> & rhs
		)
		{
			return lhs.ordered != rhs.ordered;
		}

		template <typename Key, typename Value, typename KeyCompare, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator<(
				const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
				const static_flat_multimap<Key, Value, N, KeyCompare> & rhs
		)
		{
			return lhs.ordered < rhs.ordered;
		}

		template <typename Key, typename Value, typename KeyCompare, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator<=(
				const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
				const static_flat_multimap<Key, Value, N, KeyCompare> & rhs
		)
		{
			return lhs.ordered <= rhs.ordered;
		}

		template <typename Key, typename Value, typename KeyCompare, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator>(
				const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
				const static_flat_multimap<Key, Value, N, KeyCompare> & rhs
		)
		{
			return lhs.ordered > rhs.ordered;
		}

		template <typename Key, typename Value, typename KeyCompare, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator>=(
				const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
				const static_flat_multimap<Key, Value, N, KeyCompare> & rhs
		)
		{
			return lhs.ordered >= rhs.ordered;
		}

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_STATIC_FLAT_MULTIMAP_STATIC_FLAT_MULTIMAP_DECL_HPP
