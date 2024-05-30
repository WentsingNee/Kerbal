/**
 * @file       avl_ordered.decl.hpp
 * @brief
 * @date       2022-09-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_AVL_ORDERED_AVL_ORDERED_DECL_HPP
#define KERBAL_CONTAINER_AVL_ORDERED_AVL_ORDERED_DECL_HPP

#include <kerbal/container/avl_ordered/avl_ordered.fwd.hpp>
#include <kerbal/container/detail/avl_base/avl_base.decl.hpp>

#include <kerbal/container/detail/container_rebind_allocator_overload.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>
#include <kerbal/utility/compressed_pair.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201703L
#	include <kerbal/memory/allocator/is_allocator.hpp>
#	include <kerbal/type_traits/enable_if.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
			struct avl_ordered_typedef_helper
			{
					typedef kerbal::container::detail::avl_type_unrelated			avl_type_unrelated;
					typedef kerbal::container::detail::avl_type_only<Entity>		avl_type_only;
					typedef typename avl_type_only::node	 						node;
					typedef Allocator												allocator_type;

					typedef kerbal::container::detail::container_rebind_allocator_overload<
							allocator_type, node
					>																avl_allocator_overload;
			};

		} // namespace detail


		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		class avl_ordered :
				protected kerbal::utility::member_compress_helper<Extract>,
				protected kerbal::utility::member_compress_helper<KeyCompare>,
				protected detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, Allocator>::avl_allocator_overload,
				protected detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, Allocator>::avl_type_only
		{
			protected:
				typedef detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, Allocator>		avl_ordered_typedef_helper;
				typedef typename avl_ordered_typedef_helper::avl_type_unrelated				avl_type_unrelated;
				typedef typename avl_ordered_typedef_helper::avl_type_only					avl_type_only;
				typedef typename avl_ordered_typedef_helper::avl_allocator_overload			avl_allocator_overload;

				typedef kerbal::utility::member_compress_helper<Extract>		extract_compress_helper;
				typedef kerbal::utility::member_compress_helper<KeyCompare>		key_compare_compress_helper;

			public:
				typedef typename avl_type_only::value_type					value_type;
				typedef typename avl_type_only::const_type					const_type;
				typedef typename avl_type_only::reference					reference;
				typedef typename avl_type_only::const_reference				const_reference;
				typedef typename avl_type_only::pointer						pointer;
				typedef typename avl_type_only::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename avl_type_only::rvalue_reference			rvalue_reference;
				typedef typename avl_type_only::const_rvalue_reference		const_rvalue_reference;
#		endif

				typedef typename avl_type_only::size_type					size_type;
				typedef typename avl_type_only::difference_type				difference_type;

				typedef typename avl_type_only::iterator					iterator;
				typedef typename avl_type_only::const_iterator				const_iterator;
				typedef typename avl_type_only::reverse_iterator			reverse_iterator;
				typedef typename avl_type_only::const_reverse_iterator		const_reverse_iterator;
				typedef typename avl_type_only::unique_insert_r				unique_insert_r;

				typedef typename Extract::key_type							key_type;
				typedef KeyCompare											key_compare;

			protected:
				typedef typename avl_type_only::node_base					node_base;
				typedef typename avl_type_only::node						node;

			public:
				typedef Allocator														allocator_type;

			protected:
				typedef typename avl_allocator_overload::rebind_allocator_type			node_allocator_type;
				typedef typename avl_allocator_overload::rebind_allocator_traits 		node_allocator_traits;

			protected:

				using avl_allocator_overload::alloc;

			//===================
			// Observers

			public:
				KERBAL_CONSTEXPR14
				Extract & extract() KERBAL_NOEXCEPT
				{
					return extract_compress_helper::member();
				}

				KERBAL_CONSTEXPR
				const Extract & extract() const KERBAL_NOEXCEPT
				{
					return extract_compress_helper::member();
				}

				KERBAL_CONSTEXPR14
				key_compare & key_comp() KERBAL_NOEXCEPT
				{
					return key_compare_compress_helper::member();
				}

				KERBAL_CONSTEXPR
				const key_compare & key_comp() const KERBAL_NOEXCEPT
				{
					return key_compare_compress_helper::member();
				}


			public:

			//===================
			// construct/copy/destroy

			//===================
			// construct with empty

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				avl_ordered() = default;

#		else

				avl_ordered();

#		endif

				KERBAL_CONSTEXPR20
				explicit
				avl_ordered(const Allocator & alloc) /*KERBAL_CONDITIONAL_NOEXCEPT(
						avl_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						avl_type_only::is_nothrow_init_to_self_constrctible::value
				)*/;

				KERBAL_CONSTEXPR20
				explicit
				avl_ordered(const KeyCompare & key_comp);

				KERBAL_CONSTEXPR20
				avl_ordered(const KeyCompare & key_comp, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				explicit
				avl_ordered(const Extract & e);

				KERBAL_CONSTEXPR20
				avl_ordered(const Extract & e, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				avl_ordered(const Extract & e, const KeyCompare & key_comp);

				KERBAL_CONSTEXPR20
				avl_ordered(const Extract & e, const KeyCompare & key_comp, const Allocator & alloc);


			//===================
			// construct with iterators range

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(InputIterator first, InputIterator last);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(InputIterator first, InputIterator last, const Allocator & alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(InputIterator first, InputIterator last, const KeyCompare & key_comp);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(InputIterator first, InputIterator last, const KeyCompare & key_comp, const Allocator & alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(InputIterator first, InputIterator last, const Extract & e);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(InputIterator first, InputIterator last, const Extract & e, const Allocator & alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(InputIterator first, InputIterator last, const Extract & e, const KeyCompare & key_comp);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(InputIterator first, InputIterator last, const Extract & e, const KeyCompare & key_comp, const Allocator & alloc);


			//===================
			// construct with iterators range (unique)

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, InputIterator first, InputIterator last);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, InputIterator first, InputIterator last, const Allocator & alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, InputIterator first, InputIterator last, const KeyCompare & key_comp);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, InputIterator first, InputIterator last, const KeyCompare & key_comp, const Allocator & alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, InputIterator first, InputIterator last, const Extract & e);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, InputIterator first, InputIterator last, const Extract & e, const Allocator & alloc);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, InputIterator first, InputIterator last, const Extract & e, const KeyCompare & key_comp);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, InputIterator first, InputIterator last, const Extract & e, const KeyCompare & key_comp, const Allocator & alloc);


#		if __cplusplus >= 201103L

			//===================
			// construct with initializer_list

				KERBAL_CONSTEXPR20
				avl_ordered(std::initializer_list<value_type> ilist);

				KERBAL_CONSTEXPR20
				avl_ordered(std::initializer_list<value_type> ilist, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				avl_ordered(std::initializer_list<value_type> ilist, const KeyCompare & key_comp);

				KERBAL_CONSTEXPR20
				avl_ordered(std::initializer_list<value_type> ilist, const KeyCompare & key_comp, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				avl_ordered(std::initializer_list<value_type> ilist, const Extract & e);

				KERBAL_CONSTEXPR20
				avl_ordered(std::initializer_list<value_type> ilist, const Extract & e, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				avl_ordered(std::initializer_list<value_type> ilist, const Extract & e, const KeyCompare & key_comp);

				KERBAL_CONSTEXPR20
				avl_ordered(std::initializer_list<value_type> ilist, const Extract & e, const KeyCompare & key_comp, const Allocator & alloc);


			//===================
			// construct with initializer_list (unique)

				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, std::initializer_list<value_type> ilist);

				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, std::initializer_list<value_type> ilist, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, std::initializer_list<value_type> ilist, const KeyCompare & key_comp);

				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, std::initializer_list<value_type> ilist, const KeyCompare & key_comp, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, std::initializer_list<value_type> ilist, const Extract & e);

				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, std::initializer_list<value_type> ilist, const Extract & e, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, std::initializer_list<value_type> ilist, const Extract & e, const KeyCompare & key_comp);

				KERBAL_CONSTEXPR20
				avl_ordered(kerbal::container::unique_tag_t unique_tag, std::initializer_list<value_type> ilist, const Extract & e, const KeyCompare & key_comp, const Allocator & alloc);

#		else

			//===================
			// construct with assign_list

				template <typename U>
				avl_ordered(const kerbal::assign::assign_list<U> & ilist);

				template <typename U>
				avl_ordered(const kerbal::assign::assign_list<U> & ilist, const Allocator & alloc);

				template <typename U>
				avl_ordered(const kerbal::assign::assign_list<U> & ilist, const KeyCompare & key_comp);

				template <typename U>
				avl_ordered(const kerbal::assign::assign_list<U> & ilist, const KeyCompare & key_comp, const Allocator & alloc);

				template <typename U>
				avl_ordered(const kerbal::assign::assign_list<U> & ilist, const Extract & e);

				template <typename U>
				avl_ordered(const kerbal::assign::assign_list<U> & ilist, const Extract & e, const Allocator & alloc);

				template <typename U>
				avl_ordered(const kerbal::assign::assign_list<U> & ilist, const Extract & e, const KeyCompare & key_comp);

				template <typename U>
				avl_ordered(const kerbal::assign::assign_list<U> & ilist, const Extract & e, const KeyCompare & key_comp, const Allocator & alloc);


			//===================
			// construct with assign_list (unique)

				template <typename U>
				avl_ordered(kerbal::container::unique_tag_t unique_tag, const kerbal::assign::assign_list<U> & ilist);

				template <typename U>
				avl_ordered(kerbal::container::unique_tag_t unique_tag, const kerbal::assign::assign_list<U> & ilist, const Allocator & alloc);

				template <typename U>
				avl_ordered(kerbal::container::unique_tag_t unique_tag, const kerbal::assign::assign_list<U> & ilist, const KeyCompare & key_comp);

				template <typename U>
				avl_ordered(kerbal::container::unique_tag_t unique_tag, const kerbal::assign::assign_list<U> & ilist, const KeyCompare & key_comp, const Allocator & alloc);

				template <typename U>
				avl_ordered(kerbal::container::unique_tag_t unique_tag, const kerbal::assign::assign_list<U> & ilist, const Extract & e);

				template <typename U>
				avl_ordered(kerbal::container::unique_tag_t unique_tag, const kerbal::assign::assign_list<U> & ilist, const Extract & e, const Allocator & alloc);

				template <typename U>
				avl_ordered(kerbal::container::unique_tag_t unique_tag, const kerbal::assign::assign_list<U> & ilist, const Extract & e, const KeyCompare & key_comp);

				template <typename U>
				avl_ordered(kerbal::container::unique_tag_t unique_tag, const kerbal::assign::assign_list<U> & ilist, const Extract & e, const KeyCompare & key_comp, const Allocator & alloc);

#		endif

			//===================
			// copy constructor

				KERBAL_CONSTEXPR20
				avl_ordered(const avl_ordered & src);

				KERBAL_CONSTEXPR20
				avl_ordered(const avl_ordered & src, const Allocator & alloc);

#		if __cplusplus >= 201103L

			//===================
			// move constructor

				KERBAL_CONSTEXPR20
				avl_ordered(avl_ordered && src);

				KERBAL_CONSTEXPR20
				avl_ordered(avl_ordered && src, const Allocator & alloc);

/*
				KERBAL_CONSTEXPR20
				avl_ordered(avl_ordered && src, const KeyCompare & key_comp);

				KERBAL_CONSTEXPR20
				avl_ordered(avl_ordered && src, const KeyCompare & key_comp, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				avl_ordered(avl_ordered && src, const Extract & e);

				KERBAL_CONSTEXPR20
				avl_ordered(avl_ordered && src, const Extract & e, const Allocator & alloc);

				KERBAL_CONSTEXPR20
				avl_ordered(avl_ordered && src, const Extract & e, const KeyCompare & key_comp);

				KERBAL_CONSTEXPR20
				avl_ordered(avl_ordered && src, const Extract & e, const KeyCompare & key_comp, const Allocator & alloc);
*/

#		endif

				KERBAL_CONSTEXPR20
				~avl_ordered();

			//===================
			// assign

				KERBAL_CONSTEXPR20
				avl_ordered & operator=(const avl_ordered & src);

				KERBAL_CONSTEXPR20
				void assign(const avl_ordered & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				avl_ordered & operator=(avl_ordered && src);

				KERBAL_CONSTEXPR20
				void assign(avl_ordered && src);

#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				void assign(InputIterator first, InputIterator last);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				void assign_unique(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				avl_ordered & operator=(std::initializer_list<value_type> ilist);

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> ilist);

				KERBAL_CONSTEXPR20
				void assign_unique(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				avl_ordered & operator=(const kerbal::assign::assign_list<U> & ilist);

				template <typename U>
				void assign(const kerbal::assign::assign_list<U> & ilist);

				template <typename U>
				void assign_unique(const kerbal::assign::assign_list<U> & ilist);

#		endif

			//===================
			// iterator

			public:

				using avl_type_only::begin;
				using avl_type_only::cbegin;

				using avl_type_only::end;
				using avl_type_only::cend;

				using avl_type_only::rbegin;
				using avl_type_only::crbegin;

				using avl_type_only::rend;
				using avl_type_only::crend;

				//using avl_type_only::nth;
				//using avl_type_only::index_of;

			//===================
			// capacity

			public:

				using avl_type_only::empty;
				using avl_type_only::size;

				KERBAL_CONSTEXPR
				size_type max_size() const KERBAL_NOEXCEPT
				{
					return node_allocator_traits::max_size(this->alloc());
				}

			//===================
			// lookup

			protected:

				template <typename Key, typename Result>
				struct enable_if_transparent_lookup :
						avl_type_only::template enable_if_transparent_lookup<Key, Extract, KeyCompare, Result>
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

			public:

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				iterator emplace(Args&& ... args);

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				unique_insert_r emplace_unique(Args&& ... args);

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)); \
 \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				unique_insert_r emplace_unique(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i));

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
				iterator insert(const_reference src);

				KERBAL_CONSTEXPR20
				unique_insert_r insert_unique(const_reference src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert(rvalue_reference src);

				KERBAL_CONSTEXPR20
				unique_insert_r insert_unique(rvalue_reference src);

#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				void insert(InputIterator first, InputIterator last);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				void insert_unique(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void insert(std::initializer_list<value_type> ilist);

				KERBAL_CONSTEXPR20
				void insert_unique(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				void insert(const kerbal::assign::assign_list<U> & ilist);

				template <typename U>
				void insert_unique(const kerbal::assign::assign_list<U> & ilist);

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
				erase(const Key & key) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void clear() KERBAL_NOEXCEPT;


			//===================
			// replace

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				iterator replace_emplace(const_iterator replace, Args&& ... args);

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				unique_insert_r replace_emplace_unique(const_iterator replace, Args&& ... args);

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator replace_emplace(const_iterator replace KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \
 \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				unique_insert_r replace_emplace_unique(const_iterator replace KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif


			//===================
			// operation

				template <typename OtherExtract, typename OtherKeyCompare>
				KERBAL_CONSTEXPR20
				void merge(avl_ordered<Entity, OtherExtract, OtherKeyCompare, Allocator> & other);

				template <typename OtherExtract, typename OtherKeyCompare>
				KERBAL_CONSTEXPR20
				void merge_unique(avl_ordered<Entity, OtherExtract, OtherKeyCompare, Allocator> & other);

				KERBAL_CONSTEXPR20
				void swap(avl_ordered & other);

				KERBAL_CONSTEXPR20
				kerbal::container::detail::avl_normal_result_t avl_normal() const
				{
					return avl_type_only::avl_normal(this->extract(), this->key_comp());
				}

				KERBAL_CONSTEXPR20
				typename node_base::height_t height() const KERBAL_NOEXCEPT
				{
					return avl_type_only::height();
				}

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Extract>
		avl_ordered(InputIterator, InputIterator, const Extract &)
		-> avl_ordered<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Extract>;

		template <typename InputIterator, typename Extract, typename KeyCompare,
				typename = typename kerbal::type_traits::enable_if<!kerbal::memory::is_allocator<KeyCompare>::value>::type
		>
		avl_ordered(InputIterator, InputIterator, const Extract &, const KeyCompare &)
		-> avl_ordered<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Extract, KeyCompare>;

		template <typename InputIterator, typename Extract, typename Allocator,
				typename = typename kerbal::type_traits::enable_if<kerbal::memory::is_allocator<Allocator>::value>::type
		>
		avl_ordered(InputIterator, InputIterator, const Extract &, const Allocator &)
		-> avl_ordered<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Extract, kerbal::compare::binary_type_less<void, void>, Allocator>;

		template <typename InputIterator, typename Extract, typename KeyCompare, typename Allocator,
				typename = typename kerbal::type_traits::enable_if<kerbal::memory::is_allocator<Allocator>::value>::type
		>
		avl_ordered(InputIterator, InputIterator, const Extract &, const KeyCompare &, const Allocator &)
		-> avl_ordered<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Extract, KeyCompare, Allocator>;


		template <typename InputIterator, typename Extract>
		avl_ordered(kerbal::container::unique_tag_t, InputIterator, InputIterator, const Extract &)
		-> avl_ordered<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Extract>;

		template <typename InputIterator, typename Extract, typename KeyCompare,
				typename = typename kerbal::type_traits::enable_if<!kerbal::memory::is_allocator<KeyCompare>::value>::type
		>
		avl_ordered(kerbal::container::unique_tag_t, InputIterator, InputIterator, const Extract &, const KeyCompare &)
		-> avl_ordered<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Extract, KeyCompare>;

		template <typename InputIterator, typename Extract, typename Allocator,
				typename = typename kerbal::type_traits::enable_if<kerbal::memory::is_allocator<Allocator>::value>::type
		>
		avl_ordered(kerbal::container::unique_tag_t, InputIterator, InputIterator, const Extract &, const Allocator &)
		-> avl_ordered<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Extract, kerbal::compare::binary_type_less<void, void>, Allocator>;

		template <typename InputIterator, typename Extract, typename KeyCompare, typename Allocator,
				typename = typename kerbal::type_traits::enable_if<kerbal::memory::is_allocator<Allocator>::value>::type
		>
		avl_ordered(kerbal::container::unique_tag_t, InputIterator, InputIterator, const Extract &, const KeyCompare &, const Allocator &)
		-> avl_ordered<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Extract, KeyCompare, Allocator>;


		template <typename Entity, typename Extract>
		avl_ordered(std::initializer_list<Entity>, const Extract &)
		-> avl_ordered<Entity, Extract>;

		template <typename Entity, typename Extract, typename KeyCompare,
				typename = typename kerbal::type_traits::enable_if<!kerbal::memory::is_allocator<KeyCompare>::value>::type
		>
		avl_ordered(std::initializer_list<Entity>, const Extract &, const KeyCompare &)
		-> avl_ordered<Entity, Extract, KeyCompare>;

		template <typename Entity, typename Extract, typename Allocator,
				typename = typename kerbal::type_traits::enable_if<kerbal::memory::is_allocator<Allocator>::value>::type>
		avl_ordered(std::initializer_list<Entity>, const Extract &, const Allocator &)
		-> avl_ordered<Entity, Extract, kerbal::compare::binary_type_less<void, void>, Allocator>;

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator,
				typename = typename kerbal::type_traits::enable_if<kerbal::memory::is_allocator<Allocator>::value>::type
		>
		avl_ordered(std::initializer_list<Entity>, const Extract &, const KeyCompare &, const Allocator &)
		-> avl_ordered<Entity, Extract, KeyCompare, Allocator>;

#	endif // if __cplusplus >= 201703L


		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator==(const avl_ordered<Entity, Extract, KeyCompare, Allocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs)
		{
			if (lhs.size() != rhs.size()) {
				return false;
			}
			return kerbal::compare::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator!=(const avl_ordered<Entity, Extract, KeyCompare, Allocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs)
		{
			if (lhs.size() != rhs.size()) {
				return true;
			}
			return kerbal::compare::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<(const avl_ordered<Entity, Extract, KeyCompare, Allocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<=(const avl_ordered<Entity, Extract, KeyCompare, Allocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>(const avl_ordered<Entity, Extract, KeyCompare, Allocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>=(const avl_ordered<Entity, Extract, KeyCompare, Allocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

	namespace algorithm
	{

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(kerbal::container::avl_ordered<Entity, Extract, KeyCompare, Allocator> & a, kerbal::container::avl_ordered<Entity, Extract, KeyCompare, Allocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
	KERBAL_CONSTEXPR20
	void swap(kerbal::container::avl_ordered<Entity, Extract, KeyCompare, Allocator> & a, kerbal::container::avl_ordered<Entity, Extract, KeyCompare, Allocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_AVL_ORDERED_AVL_ORDERED_DECL_HPP
