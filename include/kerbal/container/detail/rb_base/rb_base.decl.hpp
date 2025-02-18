/**
 * @file       rb_base.decl.hpp
 * @brief
 * @date       2023-12-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_DECL_HPP

#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/compare/binary_type_compare.hpp>


#include <kerbal/container/detail/rb_base/rb_base.fwd.hpp>
#include <kerbal/container/rb_ordered/rb_ordered.fwd.hpp>

#include <kerbal/container/detail/bst_base/bst_node.hpp>
#include <kerbal/container/detail/rb_base/rb_node.hpp>
#include <kerbal/container/detail/rb_base/rb_iterator.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/container/associative_container_facility/key_compare_is_transparent.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/forward.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class rb_type_unrelated
			{
				public:
					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

				protected:
					typedef kerbal::container::detail::rb_node_base		rb_node_base;
					typedef rb_node_base::bst_head_node					bst_head_node;
					typedef rb_node_base::bst_node_base					bst_node_base;

					bst_head_node k_head;
					size_type k_cnt;

					KERBAL_CONSTEXPR14
					rb_type_unrelated() KERBAL_NOEXCEPT :
						k_head(get_rb_vnull_node()), k_cnt(0)
					{
					}

				public:
					KERBAL_CONSTEXPR14
					bool empty() const KERBAL_NOEXCEPT
					{
						return this->k_cnt == 0u;
					}

					KERBAL_CONSTEXPR14
					size_type size() const KERBAL_NOEXCEPT
					{
						return this->k_cnt;
					}

				private:

					KERBAL_CONSTEXPR14
					static
					void rb_adjust_RRb(rb_node_base * g, rb_node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static
					void rb_adjust_LLb(rb_node_base * g, rb_node_base * p) KERBAL_NOEXCEPT;

				protected:

					KERBAL_CONSTEXPR14
					void rb_adjust(rb_node_base * n, rb_node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					// replacee has two sons
					// replacer has no left son
					// replacer must be the left son of its parent
					static
					void k_unhook_node_replace(rb_node_base * replacee, rb_node_base * replacer) KERBAL_NOEXCEPT
					{
						bst_head_node * replacee_parent = replacee->parent;
						bst_head_node * replacer_parent = replacer->parent;

						replacee_parent->replace_son(replacee, replacer);

						replacee->left->parent = replacer;
						replacee->right->parent = replacer;

						replacer_parent->replace_son(replacer, replacee);

						// replacer->left is always null
						set_parent_ignore_null(replacer->right, replacee); // replacer->right may null
						kerbal::algorithm::swap(*replacee, *replacer);
					}

					KERBAL_CONSTEXPR14
					bst_head_node * k_unhook_node_and_get_successor(rb_node_base * n) KERBAL_NOEXCEPT;

			};


			template <typename Entity>
			class rb_type_only :
				protected kerbal::container::detail::rb_type_unrelated
			{
				private:
					typedef kerbal::container::detail::rb_type_unrelated super;

					template <typename Entity2, typename Extract, typename KeyCompare, typename Allocator>
					friend struct rb_ordered_typedef_helper;

				public:
					typedef Entity						value_type;
					typedef const value_type			const_type;
					typedef value_type &				reference;
					typedef const value_type &			const_reference;
					typedef value_type *				pointer;
					typedef const value_type *			const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type &&				rvalue_reference;
					typedef const value_type &&			const_rvalue_reference;
#			endif

					typedef super::size_type					size_type;
					typedef super::difference_type				difference_type;

					typedef kerbal::container::detail::rb_iter<value_type>				iterator;
					typedef kerbal::container::detail::rb_kiter<value_type>				const_iterator;
					typedef kerbal::iterator::reverse_iterator<iterator>				reverse_iterator;
					typedef kerbal::iterator::reverse_iterator<const_iterator>			const_reverse_iterator;
					typedef kerbal::container::associative_unique_insert_r<iterator>	unique_insert_r;

					typedef kerbal::container::detail::rb_normal_result_t				rb_normal_result_t;


				protected:
//					typedef super::head_node									head_node;
					typedef super::rb_node_base 								avl_node_base;
					typedef kerbal::container::detail::rb_node<value_type>		node;
					typedef std::size_t height_t;

				public:

				//===================
				// construct/copy/destroy

#			if __cplusplus >= 201103L
					rb_type_only() = default;
#			else
					rb_type_only() :
						super()
					{
					}
#			endif

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					rb_type_only(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						rb_type_only const & src
					);

					template <typename NodeAllocator, typename Extract, typename KeyCompare>
					rb_type_only(
						NodeAllocator & this_alloc, Extract & this_e, KeyCompare & this_kc,
						NodeAllocator && src_alloc, rb_type_only && src
					);

					template <typename NodeAllocator>
					static
					void k_destroy_using_allocator_impl(NodeAllocator & alloc, rb_node_base * p)
					{
						while (p != get_rb_vnull_node()) {
							k_destroy_using_allocator_impl(alloc, static_cast<rb_node_base *>(p->left));
							rb_node_base * right = static_cast<rb_node_base *>(p->right);
							k_destroy_rb_node(alloc, static_cast<node *>(p));
							p = right;
						}
					}

					template <typename NodeAllocator>
					void k_destroy_using_allocator(NodeAllocator & alloc)
					{
						k_destroy_using_allocator_impl(alloc, static_cast<rb_node_base *>(this->k_head.left));
					}

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					iterator k_hook_node(Extract & e, KeyCompare & kc, node * n);

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					unique_insert_r k_hook_node_unique(Extract & e, KeyCompare & kc, node * n);

				//===================
				// iterator

				public:

					KERBAL_CONSTEXPR14
					iterator begin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator cbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					iterator end() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator end() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_iterator cend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					reverse_iterator rbegin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					reverse_iterator rend() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator rend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator crend() const KERBAL_NOEXCEPT;


				//===================
				// capacity

				public:
					using super::empty;
					using super::size;


				//===================
				// lookup

				protected:

					template <
						typename Extract, typename KeyCompare, typename Key,
						typename Result
					>
					struct enable_if_transparent_lookup :
						kerbal::type_traits::enable_if<
							(
								kerbal::container::key_compare_is_transparent<KeyCompare>::value &&
								!kerbal::type_traits::is_same<const Key &, const typename Extract::key_type &>::value &&
								!kerbal::type_traits::is_same<Key, const_iterator>::value &&
								!kerbal::type_traits::is_same<Key, iterator>::value
							),
							Result
						>
					{
					};

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					const_iterator
					k_find_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					const_iterator
					k_find(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					iterator
					k_find(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						const_iterator
					>::type
					k_find(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						iterator
					>::type
					k_find(
						Extract & e, KeyCompare & kc,
						const Key & key
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					static
					const avl_node_base *
					k_lower_bound_helper(
						Extract & e, KeyCompare & kc,
						const Key & key,
						const avl_node_base * p_base, const avl_node_base * lbound
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					static
					const avl_node_base *
					k_upper_bound_helper(
						Extract & e, KeyCompare & kc, const Key & key,
						const avl_node_base * p_base, const avl_node_base * ubound
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					const_iterator
					k_lower_bound_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					const_iterator
					k_lower_bound(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					iterator
					k_lower_bound(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						const_iterator
					>::type
					k_lower_bound(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						iterator
					>::type
					k_lower_bound(
						Extract & e, KeyCompare & kc,
						const Key & key
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					const_iterator
					k_upper_bound_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					const_iterator
					k_upper_bound(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					iterator
					k_upper_bound(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						const_iterator
					>::type
					k_upper_bound(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						iterator
					>::type
					k_upper_bound(
						Extract & e, KeyCompare & kc,
						const Key & key
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<
						const_iterator,
						const_iterator
					>
					k_equal_range_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<
						const_iterator,
						const_iterator
					>
					k_equal_range(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<
						iterator,
						iterator
					>
					k_equal_range(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					);

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						kerbal::utility::compressed_pair<
							const_iterator,
							const_iterator
						>
					>::type
					k_equal_range(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						kerbal::utility::compressed_pair<
							iterator,
							iterator
						>
					>::type
					k_equal_range(
						Extract & e, KeyCompare & kc,
						const Key & key
					);

				private:
					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					bool k_contains_impl(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;

				public:
					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					bool
					k_contains(
						Extract & e, KeyCompare & kc,
						const typename Extract::key_type & key
					) const;

					template <typename Extract, typename KeyCompare, typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Extract, KeyCompare, Key,
						bool
					>::type
					k_contains(
						Extract & e, KeyCompare & kc,
						const Key & key
					) const;


				public:

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare,
						typename ... Args
					>
					KERBAL_CONSTEXPR14
					iterator
					k_emplace_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						Args && ... args
					)
					{
						node * p = k_build_rb_node(alloc, kerbal::utility::forward<Args>(args)...);
						return k_hook_node(e, kc, p);
					}

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare,
						typename ... Args
					>
					KERBAL_CONSTEXPR14
					unique_insert_r
					k_emplace_unique_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						Args && ... args
					)
					{
						node * p = k_build_rb_node(alloc, kerbal::utility::forward<Args>(args)...);
						unique_insert_r uir = k_hook_node_unique(e, kc, p);
						if (!uir.insert_happen()) {
							k_destroy_rb_node(alloc, p);
						}
						return uir;
					}

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					iterator
					k_erase_not_end_using_allocator_unsafe(NodeAllocator & alloc, const_iterator pos)
					{
						rb_node_base * cur_base = rb_node_base::as(pos.cast_to_mutable().current);
						iterator ret(this->rb_type_unrelated::k_unhook_node_and_get_successor(cur_base));
						k_destroy_rb_node(alloc, node::reinterpret_as(cur_base));
						return ret;
					}

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					iterator
					k_erase_using_allocator(NodeAllocator & alloc, const_iterator pos)
					{
						if (pos == this->cend()) {
							return this->end();
						}

						return this->k_erase_not_end_using_allocator_unsafe(alloc, pos);
					}

					template <
						typename NodeAllocator, typename Extract, typename KeyCompare,
						typename Key
					>
					KERBAL_CONSTEXPR14
					size_type
					k_erase_using_allocator(
						NodeAllocator & alloc, Extract & e, KeyCompare & kc,
						const Key & key
					);
					// {
					// 	kerbal::utility::compressed_pair<const_iterator, const_iterator> eqr(
					// 		this->k_e(e, kc, key)
					// 	;
					// 	return this->k_erase_using_allocator(alloc, pos);
					// }

					template <typename NodeAllocator>
					void k_clear_using_allocator(NodeAllocator & alloc)
					{
						this->k_destroy_using_allocator(alloc);
						this->k_head.left = get_rb_vnull_node();
						this->k_cnt = 0;
					}

					template <typename F>
					static
					void preorder_helper(const rb_node_base * p, F f)
					{
						if (p == get_rb_vnull_node()) {
							return;
						}
						const node * pnode = static_cast<const node *>(p);
						f(pnode->member(), pnode->color);
						preorder_helper(static_cast<const rb_node_base *>(p->left), f);
						preorder_helper(static_cast<const rb_node_base *>(p->right), f);
					}

					template <typename F>
					void preorder(F f) const
					{
						preorder_helper(static_cast<const rb_node_base *>(this->k_head.left), f);
					}

					template <typename F>
					static
					void inorder_helper(const rb_node_base * p, F f)
					{
						if (p == get_rb_vnull_node()) {
							return;
						}
						const node * pnode = static_cast<const node *>(p);
						inorder_helper(static_cast<const rb_node_base *>(p->left), f);
						f(pnode->member(), pnode->color);
						inorder_helper(static_cast<const rb_node_base *>(p->right), f);
					}

					template <typename F>
					void inorder(F f) const
					{
						inorder_helper(static_cast<const rb_node_base *>(this->k_head.left), f);
					}



					template <typename NodeAllocator, typename ... Args>
					static
					node * k_build_rb_node(NodeAllocator & alloc, Args && ... args)
					{
						typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
						node * p = node_allocator_traits::allocate_one(alloc);
						try {
							node_allocator_traits::construct(
								alloc, p,
								kerbal::utility::in_place_t(),
								rb_node_base::RED::value,
								kerbal::utility::forward<Args>(args)...
							);
						} catch (...) {
							node_allocator_traits::deallocate_one(alloc, p);
							throw;
						}
						return p;
					}

					template <typename NodeAllocator>
					static
					void k_destroy_rb_node(NodeAllocator & alloc, node * p)
					{
						typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
						node_allocator_traits::destroy(alloc, p);
						node_allocator_traits::deallocate_one(alloc, p);
					}




					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					static
					rb_normal_result_t
					rb_normal_impl(
						Extract & e, KeyCompare & kc,
						const rb_node_base * pbase,
						const value_type * & mini, const value_type * & maxi,
						std::size_t & nodes_cnt, std::size_t & black_cnt
					);

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					rb_normal_result_t rb_normal(Extract & e, KeyCompare & kc) const;

			};


		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_DECL_HPP
