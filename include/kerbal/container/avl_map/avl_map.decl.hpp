/**
 * @file       avl_map.decl.hpp
 * @brief
 * @date       2022-09-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_AVL_MAP_AVL_MAP_DECL_HPP
#define KERBAL_CONTAINER_AVL_MAP_AVL_MAP_DECL_HPP

#include <kerbal/container/avl_map/avl_map.fwd.hpp>
#include <kerbal/container/avl_ordered/avl_ordered.decl.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/tuple_first_extractor.hpp>
#include <kerbal/container/associative_container_facility/map_data.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#include <kerbal/macro/macro_concat.hpp>
#include <kerbal/macro/ppexpand.hpp>

#if __cplusplus >= 201703L
#	include <kerbal/container/associative_container_facility/map_from_iter_pair_tad_traits.hpp>
#	include <kerbal/memory/allocator/is_allocator.hpp>
#	include <kerbal/type_traits/enable_if.hpp>
#	include <kerbal/type_traits/logical.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		template <typename K, typename M, typename KeyCompare, typename Allocator>
		class avl_map :
			protected kerbal::container::avl_ordered<
				kerbal::container::map_data<K, M>,
				kerbal::container::tuple_first_extractor<kerbal::container::map_data<K, M>, K>,
				KeyCompare,
				Allocator
			>
		{
			private:
				typedef kerbal::container::avl_ordered<
					kerbal::container::map_data<K, M>,
					kerbal::container::tuple_first_extractor<kerbal::container::map_data<K, M>, K>,
					KeyCompare,
					Allocator
				> avl_ordered;

			public:
				typedef typename avl_ordered::value_type					value_type;
				typedef typename avl_ordered::const_type					const_type;
				typedef typename avl_ordered::reference						reference;
				typedef typename avl_ordered::const_reference				const_reference;
				typedef typename avl_ordered::pointer						pointer;
				typedef typename avl_ordered::const_pointer					const_pointer;

#		if __cplusplus >= 201103L
				typedef typename avl_ordered::rvalue_reference				rvalue_reference;
				typedef typename avl_ordered::const_rvalue_reference		const_rvalue_reference;
#		endif

				typedef typename avl_ordered::size_type						size_type;
				typedef typename avl_ordered::difference_type				difference_type;

				typedef typename avl_ordered::iterator						iterator;
				typedef typename avl_ordered::const_iterator				const_iterator;
				typedef typename avl_ordered::reverse_iterator				reverse_iterator;
				typedef typename avl_ordered::const_reverse_iterator		const_reverse_iterator;
				typedef typename avl_ordered::unique_insert_r				unique_insert_r;

				typedef typename avl_ordered::key_type						key_type;
				typedef M													mapped_type;
				typedef typename avl_ordered::key_compare					key_compare;

			private:
				typedef typename avl_ordered::node_base					node_base;
				typedef typename avl_ordered::node						node;

			public:
				typedef Allocator										allocator_type;

			private:
				typedef typename avl_ordered::rebind_allocator_type			node_allocator_type;
				typedef typename avl_ordered::rebind_allocator_traits 		node_allocator_traits;

			public:

			//===================
			// construct/copy/destroy

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				avl_map() = default;

#		endif


#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define EMPTY

#			define EXPLICIT_0
#			define EXPLICIT_1 explicit
#			define EXPLICIT_2 explicit
#			define EXPLICIT_3
#			define EXPLICIT(i) KERBAL_MACRO_CONCAT(EXPLICIT_, i)

#			define ARG_DECL_1 const Allocator & alloc
#			define ARG_DECL_2 const KeyCompare & key_comp
#			define ARG_DECL_3 const KeyCompare & key_comp, const Allocator & alloc
#			define ARG_DECL(i) KERBAL_MACRO_CONCAT(ARG_DECL_, i)


#			define FBODY(i) \
				KERBAL_CONSTEXPR20 \
				EXPLICIT(i) \
				avl_map( \
					KERBAL_OPT_EXPAND_N(REMAINF, EMPTY, ARG_DECL, i) \
				); \

#		if __cplusplus < 201103L
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
#		endif
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 3)

#			undef FBODY


				KERBAL_CONSTEXPR20
				avl_map(const avl_map & src);

				KERBAL_CONSTEXPR20
				avl_map(const avl_map & src, const Allocator & alloc);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				avl_map(avl_map && src);

				KERBAL_CONSTEXPR20
				avl_map(avl_map && src, const Allocator & alloc);

#		endif


#			define FBODY(i) \
				template <typename InputIterator> \
				KERBAL_CONSTEXPR20 \
				avl_map( \
					InputIterator first, InputIterator last \
					KERBAL_OPT_EXPAND_N(LEFT_JOIN_COMMA, EMPTY, ARG_DECL, i) \
				); \

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 3)

#			undef FBODY


#		if __cplusplus >= 201103L

#			define FBODY(i) \
				KERBAL_CONSTEXPR20 \
				avl_map( \
					std::initializer_list<value_type> ilist \
					KERBAL_OPT_EXPAND_N(LEFT_JOIN_COMMA, EMPTY, ARG_DECL, i) \
				); \

#		else

#			define FBODY(i) \
				template <typename U> \
				avl_map( \
					const kerbal::assign::assign_list<U> & ilist \
					KERBAL_OPT_EXPAND_N(LEFT_JOIN_COMMA, EMPTY, ARG_DECL, i) \
				); \

#		endif

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 3)

#			undef FBODY


#			undef EXPLICIT_0
#			undef EXPLICIT_1
#			undef EXPLICIT_2
#			undef EXPLICIT_3
#			undef EXPLICIT

#			undef ARG_DECL_1
#			undef ARG_DECL_2
#			undef ARG_DECL_3
#			undef ARG_DECL

#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef EMPTY



			//===================
			// assign

				KERBAL_CONSTEXPR20
				avl_map & operator=(const avl_map & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				avl_map & operator=(avl_map && src);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				avl_map & operator=(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				avl_map & operator=(const kerbal::assign::assign_list<U> & ilist);

#		endif


				KERBAL_CONSTEXPR20
				void assign(const avl_map & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(avl_map && src);

#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				void assign(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				void assign(const kerbal::assign::assign_list<U> & ilist);

#		endif


			//===================
			// element access

				KERBAL_CONSTEXPR20
				mapped_type & at(const key_type & key);

				KERBAL_CONSTEXPR20
				const mapped_type & at(const key_type & key) const;

				KERBAL_CONSTEXPR20
				mapped_type & operator[](const key_type & key);


			//===================
			// iterator

				using avl_ordered::begin;
				using avl_ordered::cbegin;

				using avl_ordered::end;
				using avl_ordered::cend;

				using avl_ordered::rbegin;
				using avl_ordered::crbegin;

				using avl_ordered::rend;
				using avl_ordered::crend;

			//===================
			// capacity

				using avl_ordered::empty;
				using avl_ordered::size;
				using avl_ordered::max_size;

			//===================
			// lookup

			protected:

				template <typename Key, typename Result>
				struct enable_if_transparent_lookup :
					avl_ordered::template enable_if_transparent_lookup<Key, Result>
				{
				};

			public:

				KERBAL_CONSTEXPR20
				const_iterator find(const key_type & key) const;

				KERBAL_CONSTEXPR20
				iterator find(const key_type & key);

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, const_iterator>::type
				find(const Key & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, iterator>::type
				find(const Key & key);

				KERBAL_CONSTEXPR20
				const_iterator lower_bound(const key_type & key) const;

				KERBAL_CONSTEXPR20
				iterator lower_bound(const key_type & key);

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, const_iterator>::type
				lower_bound(const Key & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, iterator>::type
				lower_bound(const Key & key);

				KERBAL_CONSTEXPR20
				const_iterator upper_bound(const key_type & key) const;

				KERBAL_CONSTEXPR20
				iterator upper_bound(const key_type & key);

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, const_iterator>::type
				upper_bound(const Key & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, iterator>::type
				upper_bound(const Key & key);

				KERBAL_CONSTEXPR20
				kerbal::utility::compressed_pair<const_iterator, const_iterator>
				equal_range(const key_type & key) const;

				KERBAL_CONSTEXPR20
				kerbal::utility::compressed_pair<iterator, iterator>
				equal_range(const key_type & key);

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<
					Key,
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
				>::type
				equal_range(const Key & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<
					Key,
					kerbal::utility::compressed_pair<iterator, iterator>
				>::type
				equal_range(const Key & key);

				KERBAL_CONSTEXPR20
				bool contains(const key_type & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, bool>::type
				contains(const Key & key) const;

			//===================
			// insert

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				unique_insert_r emplace(Args && ... args);

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				unique_insert_r emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)); \

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif

				KERBAL_CONSTEXPR20
				unique_insert_r insert(const_reference src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				unique_insert_r insert(rvalue_reference src);

#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				void insert(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void insert(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				void insert(const kerbal::assign::assign_list<U> & ilist);

#		endif


			//===================
			// erase

				KERBAL_CONSTEXPR20
				iterator erase_not_end_unsafe(const_iterator pos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator pos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator first, const_iterator last) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				size_type erase(const key_type & key) KERBAL_NOEXCEPT;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, size_type>::type
				erase(const Key & pos) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void clear() KERBAL_NOEXCEPT;

			//===================
			// operation

				template <typename OtherKeyCompare>
				KERBAL_CONSTEXPR20
				void merge(avl_map<K, M, OtherKeyCompare, Allocator> & other);

#		if __cplusplus >= 201103L

				template <typename OtherKeyCompare>
				KERBAL_CONSTEXPR20
				void merge(avl_map<K, M, OtherKeyCompare, Allocator> && other);

#		endif

				KERBAL_CONSTEXPR20
				void swap(avl_map & other);

				KERBAL_CONSTEXPR20
				kerbal::container::detail::avl_normal_result_t avl_normal() const
				{
					return avl_ordered::avl_normal();
				}

				KERBAL_CONSTEXPR20
				typename node_base::height_t height() const KERBAL_NOEXCEPT
				{
					return avl_ordered::height();
				}

		};


#	if __cplusplus >= 201703L

		template <typename InputIterator>
		avl_map(
			InputIterator, InputIterator
		) ->
		avl_map<
			typename kerbal::container::map_from_iter_pair_tad_traits<InputIterator>::key_type,
			typename kerbal::container::map_from_iter_pair_tad_traits<InputIterator>::mapped_type
		>;

		template <
			typename InputIterator,
			typename KeyCompare,
			typename =
				typename kerbal::type_traits::enable_if<
					!kerbal::memory::is_allocator<KeyCompare>::value
				>::type
		>
		avl_map(
			InputIterator, InputIterator,
			const KeyCompare &
		) ->
		avl_map<
			typename kerbal::container::map_from_iter_pair_tad_traits<InputIterator>::key_type,
			typename kerbal::container::map_from_iter_pair_tad_traits<InputIterator>::mapped_type,
			KeyCompare
		>;

		template <
			typename InputIterator,
			typename Allocator,
			typename =
				typename kerbal::type_traits::enable_if<
					kerbal::memory::is_allocator<Allocator>::value
				>::type
		>
		avl_map(
			InputIterator, InputIterator,
			const Allocator &
		) ->
		avl_map<
			typename kerbal::container::map_from_iter_pair_tad_traits<InputIterator>::key_type,
			typename kerbal::container::map_from_iter_pair_tad_traits<InputIterator>::mapped_type,
			kerbal::compare::binary_type_less<void, void>,
			Allocator
		>;

		template <
			typename InputIterator,
			typename KeyCompare,
			typename Allocator,
			typename =
				typename kerbal::type_traits::enable_if<
					kerbal::type_traits::conjunction<
						kerbal::type_traits::negation<
							kerbal::memory::is_allocator<KeyCompare>
						>,
						kerbal::memory::is_allocator<Allocator>
					>::value
				>::type
		>
		avl_map(
			InputIterator, InputIterator,
			const KeyCompare &, const Allocator &
		) ->
		avl_map<
			typename kerbal::container::map_from_iter_pair_tad_traits<InputIterator>::key_type,
			typename kerbal::container::map_from_iter_pair_tad_traits<InputIterator>::mapped_type,
			KeyCompare,
			Allocator
		>;


		template <typename K, typename M>
		avl_map(
			std::initializer_list<kerbal::container::map_data<K, M> >
		) ->
		avl_map<K, M>;

		template <
			typename K, typename M, typename KeyCompare,
			typename =
				typename kerbal::type_traits::enable_if<
					!kerbal::memory::is_allocator<KeyCompare>::value
				>::type
		>
		avl_map(
			std::initializer_list<kerbal::container::map_data<K, M> >,
			const KeyCompare &
		) ->
		avl_map<K, M, KeyCompare>;

		template <
			typename K, typename M, typename Allocator,
			typename =
				typename kerbal::type_traits::enable_if<
					kerbal::memory::is_allocator<Allocator>::value
				>::type
		>
		avl_map(
			std::initializer_list<kerbal::container::map_data<K, M> >,
			const Allocator &
		) ->
		avl_map<
			K, M,
			kerbal::compare::binary_type_less<void, void>,
			Allocator
		>;

		template <
			typename K, typename M, typename KeyCompare, typename Allocator,
			typename =
				typename kerbal::type_traits::enable_if<
					kerbal::type_traits::conjunction<
						kerbal::type_traits::negation<
							kerbal::memory::is_allocator<KeyCompare>
						>,
						kerbal::memory::is_allocator<Allocator>
					>::value
				>::type
		>
		avl_map(
			std::initializer_list<kerbal::container::map_data<K, M> >,
			const KeyCompare &, const Allocator &
		) ->
		avl_map<K, M, KeyCompare, Allocator>;

#	endif // if __cplusplus >= 201703L


		template <typename K, typename M, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator==(
			const avl_map<K, M, KeyCompare, Allocator> & lhs,
			const avl_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			if (lhs.size() != rhs.size()) {
				return false;
			}
			return kerbal::compare::sequence_equal_to(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator!=(
			const avl_map<K, M, KeyCompare, Allocator> & lhs,
			const avl_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			if (lhs.size() != rhs.size()) {
				return true;
			}
			return kerbal::compare::sequence_not_equal_to(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<(
			const avl_map<K, M, KeyCompare, Allocator> & lhs,
			const avl_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return kerbal::compare::sequence_less(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<=(
			const avl_map<K, M, KeyCompare, Allocator> & lhs,
			const avl_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return kerbal::compare::sequence_less_equal(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>(
			const avl_map<K, M, KeyCompare, Allocator> & lhs,
			const avl_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return kerbal::compare::sequence_greater(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename K, typename M, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>=(
			const avl_map<K, M, KeyCompare, Allocator> & lhs,
			const avl_map<K, M, KeyCompare, Allocator2> & rhs
		)
		{
			return kerbal::compare::sequence_greater_equal(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

	} // namespace container

	namespace algorithm
	{

		template <typename K, typename M, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::container::avl_map<K, M, KeyCompare, Allocator> & a,
			kerbal::container::avl_map<K, M, KeyCompare, Allocator> & b
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
	void swap(
		kerbal::container::avl_map<K, M, KeyCompare, Allocator> & a,
		kerbal::container::avl_map<K, M, KeyCompare, Allocator> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_AVL_MAP_AVL_MAP_DECL_HPP
