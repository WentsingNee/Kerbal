/**
 * @file       rb_set.decl.hpp
 * @brief
 * @date       2024-09-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_RB_SET_RB_SET_DECL_HPP
#define KERBAL_CONTAINER_RB_SET_RB_SET_DECL_HPP

#include <kerbal/container/rb_set/rb_set.fwd.hpp>
#include <kerbal/container/rb_ordered/rb_ordered.decl.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

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

		template <typename T, typename KeyCompare, typename Allocator>
		class rb_set :
			protected kerbal::container::rb_ordered<
				T,
				kerbal::container::identity_extractor<T>,
				KeyCompare,
				Allocator
			>
		{
			private:
				typedef kerbal::container::rb_ordered<
					T,
					kerbal::container::identity_extractor<T>,
					KeyCompare,
					Allocator
				> rb_ordered;

			public:
				typedef typename rb_ordered::value_type					value_type;
				typedef typename rb_ordered::const_type					const_type;
				typedef typename rb_ordered::reference					reference;
				typedef typename rb_ordered::const_reference			const_reference;
				typedef typename rb_ordered::pointer					pointer;
				typedef typename rb_ordered::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename rb_ordered::rvalue_reference			rvalue_reference;
				typedef typename rb_ordered::const_rvalue_reference		const_rvalue_reference;
#		endif

				typedef typename rb_ordered::size_type					size_type;
				typedef typename rb_ordered::difference_type			difference_type;

				typedef typename rb_ordered::const_iterator				iterator;
				typedef typename rb_ordered::const_iterator				const_iterator;
				typedef typename rb_ordered::const_reverse_iterator		reverse_iterator;
				typedef typename rb_ordered::const_reverse_iterator		const_reverse_iterator;
				typedef kerbal::container::associative_unique_insert_r<const_iterator>
																		unique_insert_r;

				typedef typename rb_ordered::key_type					key_type;
				typedef typename rb_ordered::key_compare				key_compare;

			private:
				typedef typename rb_ordered::node						node;
				typedef typename rb_ordered::height_t					height_t;

			public:
				typedef Allocator										allocator_type;

			private:
				typedef typename rb_ordered::rebind_allocator_type		node_allocator_type;
				typedef typename rb_ordered::rebind_allocator_traits	node_allocator_traits;

			public:

			//===================
			// construct/copy/destroy

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				rb_set() = default;

#		else

				rb_set();

#		endif

				KERBAL_CONSTEXPR20
				explicit
				rb_set(const Allocator & alloc);

				KERBAL_CONSTEXPR20
				explicit
				rb_set(const KeyCompare & kc);

				KERBAL_CONSTEXPR20
				rb_set(const KeyCompare & kc, const Allocator & alloc);


				KERBAL_CONSTEXPR20
				rb_set(const rb_set & src);

				KERBAL_CONSTEXPR20
				rb_set(const rb_set & src, const Allocator & alloc);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				rb_set(rb_set && src);

				KERBAL_CONSTEXPR20
				rb_set(rb_set && src, const Allocator & alloc);

#		endif


				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				rb_set(
					InputIterator first, InputIterator last
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				rb_set(
					InputIterator first, InputIterator last,
					const Allocator & alloc
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				rb_set(
					InputIterator first, InputIterator last,
					const KeyCompare & kc
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				rb_set(
					InputIterator first, InputIterator last,
					const KeyCompare & kc, const Allocator & alloc
				);


#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				rb_set(
					std::initializer_list<value_type> ilist
				);

				KERBAL_CONSTEXPR20
				rb_set(
					std::initializer_list<value_type> ilist,
					const Allocator & alloc
				);

				KERBAL_CONSTEXPR20
				rb_set(
					std::initializer_list<value_type> ilist,
					const KeyCompare & kc
				);

				KERBAL_CONSTEXPR20
				rb_set(
					std::initializer_list<value_type> ilist,
					const KeyCompare & kc, const Allocator & alloc
				);

#		else

				template <typename U>
				rb_set(
					const kerbal::assign::assign_list<U> & ilist
				);

				template <typename U>
				rb_set(
					const kerbal::assign::assign_list<U> & ilist,
					const Allocator & alloc
				);

				template <typename U>
				rb_set(
					const kerbal::assign::assign_list<U> & ilist,
					const KeyCompare & kc
				);

				template <typename U>
				rb_set(
					const kerbal::assign::assign_list<U> & ilist,
					const KeyCompare & kc, const Allocator & alloc
				);

#		endif


			//===================
			// assign

				KERBAL_CONSTEXPR20
				rb_set & operator=(const rb_set & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				rb_set & operator=(rb_set && src);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				rb_set & operator=(std::initializer_list<value_type> ilist);

#		else

				template <typename U>
				rb_set & operator=(const kerbal::assign::assign_list<U> & ilist);

#		endif


				KERBAL_CONSTEXPR20
				void assign(const rb_set & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(rb_set && src);

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
			// iterator

				KERBAL_CONSTEXPR20
				const_iterator begin() const
				{
					return this->rb_ordered::cbegin();
				}

				KERBAL_CONSTEXPR20
				const_iterator end() const
				{
					return this->rb_ordered::cend();
				}

				KERBAL_CONSTEXPR20
				const_reverse_iterator rbegin() const
				{
					return this->rb_ordered::crbegin();
				}

				KERBAL_CONSTEXPR20
				const_reverse_iterator rend() const
				{
					return this->rb_ordered::crend();
				}

				using rb_ordered::cbegin;
				using rb_ordered::cend;
				using rb_ordered::crbegin;
				using rb_ordered::crend;

			//===================
			// capacity

				using rb_ordered::empty;
				using rb_ordered::size;
				using rb_ordered::max_size;

			//===================
			// lookup

			protected:

				template <typename Key, typename Result>
				struct enable_if_transparent_lookup :
					rb_ordered::template enable_if_transparent_lookup<Key, Result>
				{
				};

			public:

				KERBAL_CONSTEXPR20
				const_iterator find(const key_type & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, const_iterator>::type
				find(const Key & key) const;

				KERBAL_CONSTEXPR20
				const_iterator lower_bound(const key_type & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, const_iterator>::type
				lower_bound(const Key & key) const;

				KERBAL_CONSTEXPR20
				const_iterator upper_bound(const key_type & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<Key, const_iterator>::type
				upper_bound(const Key & key) const;

				KERBAL_CONSTEXPR20
				kerbal::utility::compressed_pair<const_iterator, const_iterator>
				equal_range(const key_type & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				typename enable_if_transparent_lookup<
					Key,
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
				>::type
				equal_range(const Key & key) const;

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
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				unique_insert_r replace_emplace(const_iterator replace KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \

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

				template <typename OtherKeyCompare>
				KERBAL_CONSTEXPR20
				void merge(rb_set<T, OtherKeyCompare, Allocator> & other);

				KERBAL_CONSTEXPR20
				void swap(rb_set & other);

				using rb_ordered::preorder;
				using rb_ordered::inorder;

				KERBAL_CONSTEXPR20
				kerbal::container::detail::rb_normal_result_t rb_normal() const
				{
					return rb_ordered::rb_normal();
				}

				KERBAL_CONSTEXPR20
				height_t height() const KERBAL_NOEXCEPT
				{
					return rb_ordered::height();
				}

		};


#	if __cplusplus >= 201703L

		template <typename InputIterator>
		rb_set(
			InputIterator, InputIterator
		) ->
		rb_set<
			typename kerbal::iterator::iterator_traits<InputIterator>::value_type
		>;

		template <
			typename InputIterator,
			typename KeyCompare,
			typename =
				typename kerbal::type_traits::enable_if<
					!kerbal::memory::is_allocator<KeyCompare>::value
				>::type
		>
		rb_set(
			InputIterator, InputIterator,
			const KeyCompare &
		) ->
		rb_set<
			typename kerbal::iterator::iterator_traits<InputIterator>::value_type,
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
		rb_set(
			InputIterator, InputIterator,
			const Allocator &
		) ->
		rb_set<
			typename kerbal::iterator::iterator_traits<InputIterator>::value_type,
			kerbal::compare::binary_type_less<void, void>,
			Allocator
		>;

		template <
			typename InputIterator,
			typename KeyCompare,
			typename Allocator,
			typename =
				typename kerbal::type_traits::enable_if<
					kerbal::memory::is_allocator<Allocator>::value
				>::type
		>
		rb_set(
			InputIterator, InputIterator,
			const KeyCompare &, const Allocator &
		) ->
		rb_set<
			typename kerbal::iterator::iterator_traits<InputIterator>::value_type,
			KeyCompare,
			Allocator
		>;


		template <typename T>
		rb_set(
			std::initializer_list<T>
		) ->
		rb_set<T>;

		template <
			typename T, typename KeyCompare,
			typename =
				typename kerbal::type_traits::enable_if<
					!kerbal::memory::is_allocator<KeyCompare>::value
				>::type
		>
		rb_set(
			std::initializer_list<T>,
			const KeyCompare &
		) ->
		rb_set<T, KeyCompare>;

		template <
			typename T, typename Allocator,
			typename =
				typename kerbal::type_traits::enable_if<
					kerbal::memory::is_allocator<Allocator>::value
				>::type
		>
		rb_set(
			std::initializer_list<T>,
			const Allocator &
		) ->
		rb_set<
			T,
			kerbal::compare::binary_type_less<void, void>,
			Allocator
		>;

		template <
			typename T, typename KeyCompare, typename Allocator,
			typename =
				typename kerbal::type_traits::enable_if<
					!kerbal::memory::is_allocator<KeyCompare>::value
				>::type
		>
		rb_set(
			std::initializer_list<T>,
			KeyCompare, const Allocator &
		) ->
		rb_set<T, KeyCompare, Allocator>;

#	endif // if __cplusplus >= 201703L


		template <typename T, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator==(
			const rb_set<T, KeyCompare, Allocator> & lhs,
			const rb_set<T, KeyCompare, Allocator2> & rhs
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

		template <typename T, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator!=(
			const rb_set<T, KeyCompare, Allocator> & lhs,
			const rb_set<T, KeyCompare, Allocator2> & rhs
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

		template <typename T, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<(
			const rb_set<T, KeyCompare, Allocator> & lhs,
			const rb_set<T, KeyCompare, Allocator2> & rhs
		)
		{
			return kerbal::compare::sequence_less(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<=(
			const rb_set<T, KeyCompare, Allocator> & lhs,
			const rb_set<T, KeyCompare, Allocator2> & rhs
		)
		{
			return kerbal::compare::sequence_less_equal(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>(
			const rb_set<T, KeyCompare, Allocator> & lhs,
			const rb_set<T, KeyCompare, Allocator2> & rhs
		)
		{
			return kerbal::compare::sequence_greater(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, typename KeyCompare, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>=(
			const rb_set<T, KeyCompare, Allocator> & lhs,
			const rb_set<T, KeyCompare, Allocator2> & rhs
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

		template <typename T, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::container::rb_set<T, KeyCompare, Allocator> & a,
			kerbal::container::rb_set<T, KeyCompare, Allocator> & b
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
	void swap(
		kerbal::container::rb_set<T, KeyCompare, Allocator> & a,
		kerbal::container::rb_set<T, KeyCompare, Allocator> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_RB_SET_RB_SET_DECL_HPP
