/**
 * @file       hash_set.decl.hpp
 * @brief
 * @date       2024-05-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_HASH_SET_HASH_SET_DECL_HPP
#define KERBAL_CONTAINER_HASH_SET_HASH_SET_DECL_HPP

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


#include <kerbal/container/hash_table/hash_table.decl.hpp>


namespace kerbal
{

	namespace container
	{

		template <
			typename T,
			typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		class hash_set :
			protected kerbal::container::hash_table<
				T, kerbal::container::identity_extractor<T>, Hash, KeyEqual,
				NodeAllocator, BucketAllocator
			>
		{
			private:
				typedef kerbal::container::hash_table<
					T,
					kerbal::container::identity_extractor<T>, Hash, KeyEqual,
					NodeAllocator, BucketAllocator
				>															hash_table;

			public:
				typedef typename hash_table::value_type						value_type;
				typedef typename hash_table::const_type						const_type;
				typedef typename hash_table::reference						reference;
				typedef typename hash_table::const_reference				const_reference;
				typedef typename hash_table::pointer						pointer;
				typedef typename hash_table::const_pointer					const_pointer;

#		if __cplusplus >= 201103L
				typedef typename hash_table::rvalue_reference				rvalue_reference;
				typedef typename hash_table::const_rvalue_reference			const_rvalue_reference;
#		endif

				typedef typename hash_table::size_type						size_type;
				typedef typename hash_table::difference_type				difference_type;

				typedef typename hash_table::const_iterator					iterator;
				typedef typename hash_table::const_iterator					const_iterator;
				typedef kerbal::container::associative_unique_insert_r<const_iterator>
																			unique_insert_r;

				typedef typename hash_table::key_type						key_type;
				typedef typename hash_table::key_equal						key_equal;

				typedef NodeAllocator										node_allocator_type;
				typedef BucketAllocator										bucket_allocator_type;

//			private:
//				typedef typename hash_table::rebind_allocator_type			node_allocator_type;
//				typedef typename hash_table::rebind_allocator_traits 		node_allocator_traits;


			public:

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				hash_set() = default;

#		else

				hash_set();

#		endif

				KERBAL_CONSTEXPR20
				explicit
				hash_set(
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc
				);

				KERBAL_CONSTEXPR20
				explicit
				hash_set(
					KeyEqual const & ke
				);

				KERBAL_CONSTEXPR20
				hash_set(
					KeyEqual const & ke,
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc
				);


				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_set(
					InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_set(
					InputIterator first, InputIterator last,
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_set(
					InputIterator first, InputIterator last,
					KeyEqual const & ke,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				hash_set(
					InputIterator first, InputIterator last,
					KeyEqual const & ke,
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);


#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				hash_set(
					std::initializer_list<value_type> ilist
				);

				KERBAL_CONSTEXPR20
				hash_set(
					std::initializer_list<value_type> ilist,
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc
				);

				KERBAL_CONSTEXPR20
				hash_set(
					std::initializer_list<value_type> ilist,
					KeyEqual const & ke
				);

				KERBAL_CONSTEXPR20
				hash_set(
					std::initializer_list<value_type> ilist,
					KeyEqual const & ke,
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc
				);

#		else

				template <typename U>
				hash_set(
					kerbal::assign::assign_list<U> const & ilist
				);

				template <typename U>
				hash_set(
					kerbal::assign::assign_list<U> const & ilist,
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc
				);

				template <typename U>
				hash_set(
					kerbal::assign::assign_list<U> const & ilist,
					KeyEqual const & ke
				);

				template <typename U>
				hash_set(
					kerbal::assign::assign_list<U> const & ilist,
					KeyEqual const & ke,
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc
				);

#		endif

				KERBAL_CONSTEXPR20
				hash_set(
					hash_set const & src
				);

				KERBAL_CONSTEXPR20
				hash_set(
					hash_set const & src,
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc
				);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				hash_set(
					hash_set && src
				);

				KERBAL_CONSTEXPR20
				hash_set(
					hash_set && src,
					NodeAllocator const & node_alloc, BucketAllocator const & bucket_alloc
				);

#		endif


			//===================
			// assign

				KERBAL_CONSTEXPR20
				hash_set & operator=(hash_set const & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				hash_set & operator=(hash_set && src);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				hash_set & operator=(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				hash_set & operator=(kerbal::assign::assign_list<U> const & ilist);

#		endif

				KERBAL_CONSTEXPR20
				void assign(hash_set const & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(hash_set && src);

#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				assign(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				void assign(kerbal::assign::assign_list<U> const & ilist);

#		endif


			//===================
			// iterator

				KERBAL_CONSTEXPR20
				const_iterator begin() const
				{
					return this->hash_table::cbegin();
				}

				KERBAL_CONSTEXPR20
				const_iterator end() const
				{
					return this->hash_table::cend();
				}

				using hash_table::cbegin;
				using hash_table::cend;

			//===================
			// capacity

				using hash_table::empty;
				using hash_table::size;
				using hash_table::max_size;

			//===================
			// lookup

/*
			protected:

				template <typename Key, typename Result>
				struct enable_if_transparent_lookup :
					hash_table::template enable_if_transparent_lookup<Key, Result>
				{
				};
*/

			public:

				using hash_table::contains;

				KERBAL_CONSTEXPR20
				const_iterator find(const_reference key) const;

/*
				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, const_iterator>::type
				find(const Key & key) const;
*/

				KERBAL_CONSTEXPR20
				kerbal::utility::compressed_pair<const_iterator, const_iterator>
				equal_range(const_reference key) const;

/*
				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<
					Key,
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
				>::type
				equal_range(const Key & key) const;
*/

				using hash_table::count;

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
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				insert(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void insert(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				void insert(kerbal::assign::assign_list<U> const & ilist);

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
				size_type erase(key_type const & key) KERBAL_NOEXCEPT;

/*
				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, size_type>::type
				erase(Key const & pos) KERBAL_NOEXCEPT;
*/

				KERBAL_CONSTEXPR20
				void clear() KERBAL_NOEXCEPT;


			//===================
			// replace

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				unique_insert_r replace_emplace(const_iterator replace, Args && ... args);

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(Arg, i) const & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				unique_insert_r \
				replace_emplace( \
					const_iterator replace \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
				); \

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

				KERBAL_CONSTEXPR20
				void merge(hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator> & other);

				KERBAL_CONSTEXPR20
				void swap(hash_set & other);

			//===================
			// Hash policy

			public:

				using hash_table::load_factor;
				using hash_table::max_load_factor;
				using hash_table::reserve;
				using hash_table::rehash;

		};

	} // namespace container


	namespace algorithm
	{

		template <
			typename T,
			typename Hash, typename KeyEqual,
			typename NodeAllocator, typename BucketAllocator
		>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::container::hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator> & a,
			kerbal::container::hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <
		typename T,
		typename Hash, typename KeyEqual,
		typename NodeAllocator, typename BucketAllocator
	>
	KERBAL_CONSTEXPR20
	void swap(
		kerbal::container::hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator> & a,
		kerbal::container::hash_set<T, Hash, KeyEqual, NodeAllocator, BucketAllocator>& b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_HASH_SET_HASH_SET_DECL_HPP
