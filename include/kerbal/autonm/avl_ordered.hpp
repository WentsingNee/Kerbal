/**
 * @file       avl_ordered.hpp
 * @brief
 * @date       2021-01-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_AVL_ORDERED_HPP
#define KERBAL_AUTONM_AVL_ORDERED_HPP

#include <kerbal/autonm/detail/is_discard_deallocate_semi_allocator.hpp>
#include <kerbal/container/detail/container_rebind_allocator_overload.hpp>
#include <kerbal/container/detail/avl_base/avl_node.hpp>
#include <kerbal/container/detail/avl_base/avl_iterator.hpp>
#include <kerbal/container/detail/avl_base.hpp>

#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/compressed_pair.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace autonm
	{

		namespace detail
		{

			template <typename T>
			class autonm_avl_ordered_node :
					public kerbal::container::detail::avl_node<T>
			{
				private:
					typedef kerbal::container::detail::avl_node<T> super;

				public:
					KERBAL_CONSTEXPR
					autonm_avl_ordered_node() :
							super(kerbal::utility::in_place_t())
					{
					}


#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit autonm_avl_ordered_node(kerbal::utility::in_place_t in_place, Args&& ... args)
							: super(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

#		else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit autonm_avl_ordered_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

			};


			template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator,
					bool IsDiscardDeallocate = kerbal::autonm::is_discard_deallocate_semi_allocator<SemiAllocator>::value
			>
			class avl_ordered_destroy_overload;


			template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator>
			struct avl_ordered_typedef_helper
			{
					typedef kerbal::container::detail::avl_type_unrelated			avl_type_unrelated;
					typedef kerbal::container::detail::avl_type_only<Entity>		avl_type_only;
					typedef kerbal::autonm::detail::autonm_avl_ordered_node<Entity>	auto_node;
					typedef SemiAllocator											semi_allocator_type;
					typedef kerbal::container::detail::container_rebind_allocator_overload<
						semi_allocator_type, auto_node
					>																avl_ordered_semi_allocator_overload;
					typedef kerbal::autonm::detail::avl_ordered_destroy_overload<
						Entity, Extract, KeyCompare, SemiAllocator
					>																avl_ordered_destroy_overload;
			};


			template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator>
			class avl_ordered_destroy_overload<Entity, Extract, KeyCompare, SemiAllocator, false> :
					protected kerbal::autonm::detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, SemiAllocator>::avl_ordered_semi_allocator_overload,
					protected kerbal::autonm::detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, SemiAllocator>::avl_type_only
			{
				private:
					typedef kerbal::autonm::detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, SemiAllocator>
																										avl_ordered_typedef_helper;
					typedef typename avl_ordered_typedef_helper::avl_type_only							avl_type_only;
					typedef typename avl_ordered_typedef_helper::avl_ordered_semi_allocator_overload	avl_ordered_semi_allocator_overload;

				protected:
					typedef typename avl_ordered_semi_allocator_overload::rebind_allocator_type 		node_semi_allocator_type;

				protected:
					KERBAL_CONSTEXPR14
					node_semi_allocator_type & semi_alloc() KERBAL_NOEXCEPT
					{
						return this->avl_ordered_semi_allocator_overload::alloc();
					}

					KERBAL_CONSTEXPR
					const node_semi_allocator_type & semi_alloc() const KERBAL_NOEXCEPT
					{
						return this->avl_ordered_semi_allocator_overload::alloc();
					}

					KERBAL_CONSTEXPR20
					~avl_ordered_destroy_overload()
					{
						this->avl_type_only::destroy_using_allocator(this->semi_alloc());
					}

					KERBAL_CONSTEXPR14
					void clear()
					{
						this->avl_type_only::clear_using_allocator(this->semi_alloc());
					}

			};

			template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator>
			class avl_ordered_destroy_overload<Entity, Extract, KeyCompare, SemiAllocator, true> :
					protected kerbal::autonm::detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, SemiAllocator>::avl_ordered_semi_allocator_overload,
					protected kerbal::autonm::detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, SemiAllocator>::avl_type_only
			{
				private:
					typedef kerbal::autonm::detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, SemiAllocator>
																										avl_ordered_typedef_helper;
					typedef typename avl_ordered_typedef_helper::avl_type_only							avl_type_only;
					typedef typename avl_ordered_typedef_helper::avl_ordered_semi_allocator_overload	avl_ordered_semi_allocator_overload;

				protected:
					typedef typename avl_ordered_semi_allocator_overload::rebind_allocator_type 		node_semi_allocator_type;

				protected:
					KERBAL_CONSTEXPR14
					node_semi_allocator_type & semi_alloc() KERBAL_NOEXCEPT
					{
						return this->avl_ordered_semi_allocator_overload::alloc();
					}

					KERBAL_CONSTEXPR
					const node_semi_allocator_type & semi_alloc() const KERBAL_NOEXCEPT
					{
						return this->avl_ordered_semi_allocator_overload::alloc();
					}

					KERBAL_CONSTEXPR14
					void clear()
					{
					}

			};

		} // namespace detail


		template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator>
		class avl_ordered :
				protected kerbal::utility::member_compress_helper<Extract>,
				protected kerbal::utility::member_compress_helper<KeyCompare>,
				protected kerbal::autonm::detail::avl_ordered_destroy_overload<Entity, Extract, KeyCompare, SemiAllocator>,
				private kerbal::utility::noncopyable
		{
			private:
				typedef kerbal::autonm::detail::avl_ordered_typedef_helper<Entity, Extract, KeyCompare, SemiAllocator>
																									avl_ordered_typedef_helper;
				typedef typename avl_ordered_typedef_helper::avl_type_only							avl_type_only;
				typedef typename avl_ordered_typedef_helper::avl_type_unrelated						avl_type_unrelated;
				typedef typename avl_ordered_typedef_helper::avl_ordered_semi_allocator_overload	avl_ordered_semi_allocator_overload;
				typedef typename avl_ordered_typedef_helper::avl_ordered_destroy_overload			avl_ordered_destroy_overload;

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
				typedef typename avl_type_only::const_iterator 				const_iterator;
				typedef typename avl_type_only::reverse_iterator			reverse_iterator;
				typedef typename avl_type_only::const_reverse_iterator 		const_reverse_iterator;
				typedef typename avl_type_only::unique_insert_r				unique_insert_r;

				typedef typename Extract::key_type							key_type;

			protected:
				typedef typename avl_type_only::node_base					node_base;
				typedef typename avl_type_only::node						node;

			public:
				typedef typename avl_ordered_typedef_helper::auto_node		auto_node;

			public:
				typedef SemiAllocator										semi_allocator_type;

			private:
				typedef typename avl_ordered_semi_allocator_overload::rebind_allocator_type 		node_semi_allocator_type;
				typedef typename avl_ordered_semi_allocator_overload::rebind_allocator_traits		node_semi_allocator_traits;

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
				KeyCompare & kc() KERBAL_NOEXCEPT
				{
					return key_compare_compress_helper::member();
				}

				KERBAL_CONSTEXPR
				const KeyCompare & kc() const KERBAL_NOEXCEPT
				{
					return key_compare_compress_helper::member();
				}


			public:

			//===================
			// construct/copy/destroy

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				avl_ordered() = default;

#		else

				avl_ordered() :
						avl_ordered_destroy_overload()
				{
				}

#		endif

				KERBAL_CONSTEXPR14
				explicit
				avl_ordered(const SemiAllocator & semi_alloc) /*KERBAL_CONDITIONAL_NOEXCEPT(
						avl_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						avl_type_only::is_nothrow_init_to_self_constrctible::value
				)*/;

				KERBAL_CONSTEXPR14
				explicit
				avl_ordered(const KeyCompare & kc);

				KERBAL_CONSTEXPR14
				avl_ordered(const KeyCompare & kc, const SemiAllocator & semi_alloc);


	#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				avl_ordered(avl_ordered && src)
						/*KERBAL_CONDITIONAL_NOEXCEPT(
								avl_type_only::is_nothrow_move_constructible::value
						)*/ :
						avl_ordered_destroy_overload(kerbal::compatibility::move(src))
				{
				}

#		endif

			//===================
			// iterator

			public:

				using avl_type_only::begin;
				using avl_type_only::end;

				using avl_type_only::cbegin;
				using avl_type_only::cend;

				using avl_type_only::rbegin;
				using avl_type_only::rend;

				using avl_type_only::crbegin;
				using avl_type_only::crend;

				//using avl_type_only::nth;
				//using avl_type_only::index_of;

			//===================
			// capacity

			public:

				using avl_type_only::empty;
				using avl_type_only::size;

			//===================
			// lookup

			public:

				KERBAL_CONSTEXPR20
				const_iterator find(const key_type & key) const;

				KERBAL_CONSTEXPR20
				iterator find(const key_type & key);

				template <typename Key>
				KERBAL_CONSTEXPR20
				const_iterator find(const Key & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				iterator find(const Key & key);

				KERBAL_CONSTEXPR20
				const_iterator lower_bound(const key_type & key) const;

				KERBAL_CONSTEXPR20
				iterator lower_bound(const key_type & key);

				template <typename Key>
				KERBAL_CONSTEXPR20
				const_iterator lower_bound(const Key & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				iterator lower_bound(const Key & key);

				KERBAL_CONSTEXPR20
				const_iterator upper_bound(const key_type & key) const;

				KERBAL_CONSTEXPR20
				iterator upper_bound(const key_type & key);

				template <typename Key>
				KERBAL_CONSTEXPR20
				const_iterator upper_bound(const Key & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				iterator upper_bound(const Key & key);

				KERBAL_CONSTEXPR20
				kerbal::utility::compressed_pair<const_iterator, const_iterator>
				equal_range(const key_type & key) const;

				KERBAL_CONSTEXPR20
				kerbal::utility::compressed_pair<iterator, iterator>
				equal_range(const key_type & key);

				template <typename Key>
				KERBAL_CONSTEXPR20
				kerbal::utility::compressed_pair<const_iterator, const_iterator>
				equal_range(const Key & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				kerbal::utility::compressed_pair<iterator, iterator>
				equal_range(const Key & key);

				KERBAL_CONSTEXPR20
				bool contains(const key_type & key) const;

				template <typename Key>
				KERBAL_CONSTEXPR20
				bool contains(const Key & key) const;

			//===================
			// insert

			public:

				KERBAL_CONSTEXPR20
				iterator insert(auto_node & auto_node)
				{
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
					try {
#			endif
						return this->avl_type_only::k_emplace_hook_node(this->extract(), this->kc(), static_cast<node*>(&auto_node));
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
					} catch (...) {
						avl_type_only::k_destroy_node(this->semi_alloc(), static_cast<node_base *>(&auto_node));
						throw;
					}
#			endif
				}

				KERBAL_CONSTEXPR20
				unique_insert_r insert_unique(auto_node & auto_node)
				{
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
					try {
#			endif
						unique_insert_r insert_r(this->avl_type_only::k_emplace_hook_node_unique(this->extract(), this->kc(), static_cast<node*>(&auto_node)));
						if (!insert_r.insert_happen()) {
							avl_type_only::k_destroy_node(this->semi_alloc(), static_cast<node_base *>(&auto_node));
						}
						return insert_r;
#			if KERBAL_HAS_EXCEPTIONS_SUPPORT
					} catch (...) {
						avl_type_only::k_destroy_node(this->semi_alloc(), static_cast<node_base *>(&auto_node));
						throw;
					}
#			endif
				}

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_forward_compatible_iterator<ForwardIterator>::value
				>::type
				insert(ForwardIterator first, ForwardIterator last)
				{
					while (first != last) {
						this->insert(*first);
						++first;
					}
				}

			//===================
			// erase

				KERBAL_CONSTEXPR14
				iterator erase(const_iterator pos)
				{
					return avl_type_only::erase_using_allocator(this->semi_alloc(), pos);
				}

				KERBAL_CONSTEXPR14
				iterator erase(const_iterator first, const_iterator last)
				{
					return avl_type_only::erase_using_allocator(this->semi_alloc(), first, last);
				}

				using avl_ordered_destroy_overload::clear;

			//===================
			// operation

				KERBAL_CONSTEXPR14
				void swap(avl_ordered & with) KERBAL_NOEXCEPT
				{
					avl_ordered_semi_allocator_overload::k_swap_allocator_if_propagate(
						static_cast<avl_ordered_semi_allocator_overload&>(*this),
						static_cast<avl_ordered_semi_allocator_overload&>(with)
					);
					this->avl_type_only::swap(
						static_cast<avl_type_only &>(with)
					);
				}

		};

		template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator, typename SemiAllocator2>
		KERBAL_CONSTEXPR14
		bool operator==(const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator2> & rhs)
		{
			if (lhs.size() != rhs.size()) {
				return false;
			}
			return kerbal::compare::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator, typename SemiAllocator2>
		KERBAL_CONSTEXPR14
		bool operator!=(const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator2> & rhs)
		{
			if (lhs.size() != rhs.size()) {
				return true;
			}
			return kerbal::compare::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator, typename SemiAllocator2>
		KERBAL_CONSTEXPR14
		bool operator<(const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator2> & rhs)
		{
			return kerbal::compare::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator, typename SemiAllocator2>
		KERBAL_CONSTEXPR14
		bool operator<=(const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator2> & rhs)
		{
			return kerbal::compare::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator, typename SemiAllocator2>
		KERBAL_CONSTEXPR14
		bool operator>(const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator2> & rhs)
		{
			return kerbal::compare::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator, typename SemiAllocator2>
		KERBAL_CONSTEXPR14
		bool operator>=(const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & lhs, const avl_ordered<Entity, Extract, KeyCompare, SemiAllocator2> & rhs)
		{
			return kerbal::compare::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace autonm

	namespace algorithm
	{

		template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator>
		KERBAL_CONSTEXPR14
		void swap(kerbal::autonm::avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & a, kerbal::autonm::avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Entity, typename Extract, typename KeyCompare, typename SemiAllocator>
	KERBAL_CONSTEXPR14
	void swap(kerbal::autonm::avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & a, kerbal::autonm::avl_ordered<Entity, Extract, KeyCompare, SemiAllocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_AUTONM_AVL_ORDERED_HPP
