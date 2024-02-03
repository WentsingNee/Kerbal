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

#include <kerbal/container/detail/bst_base/bst_node.hpp>
#include <kerbal/container/detail/rb_base/rb_node.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/allocator/default_allocator.hpp>
#include <kerbal/utility/forward.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class rb_type_unrelated
			{
				protected:
					typedef kerbal::container::detail::bst_head_node	bst_head_node;
					typedef kerbal::container::detail::bst_node_base	bst_node_base;
					typedef kerbal::container::detail::rb_node_base		rb_node_base;

					bst_head_node k_head;
					std::size_t k_cnt;

					KERBAL_CONSTEXPR14
					rb_type_unrelated() KERBAL_NOEXCEPT :
							k_head(get_rb_vnull_node()), k_cnt(0)
					{
					}

					KERBAL_CONSTEXPR14
					static void rb_adjust_RRb(rb_node_base * g, rb_node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static void rb_adjust_LLb(rb_node_base * g, rb_node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					void rb_adjust(rb_node_base * n, rb_node_base * p) KERBAL_NOEXCEPT;

					// replacee has two sons
					// replacer has no left son
					// replacer must be the left son of its parent
					static void k_unhook_node_replace(rb_node_base * replacee, rb_node_base * replacer) KERBAL_NOEXCEPT
					{
						bst_head_node * replacer_parent = replacee->parent;
						bst_head_node * replacee_parent = replacer->parent;

						if (replacee == replacee_parent->left) {
							replacer_parent->left = replacer;
						} else {
							replacer_parent->as_node_base()->right = replacer;
						}

						replacee_parent->left = replacee;

						replacee->left->parent = replacer;
						// replacer->left is always null
						replacee->right->parent = replacer;
						set_parent_ignore_null(replacer->right, replacee); // replacer->right may null
						kerbal::algorithm::swap(*replacee, *replacer);
					}

					KERBAL_CONSTEXPR14
					void k_unhook_node(rb_node_base * n) KERBAL_NOEXCEPT;

			};

			template <typename T>
			class rb_type_only : protected kerbal::container::detail::rb_type_unrelated
			{
				private:
					typedef kerbal::container::detail::rb_type_unrelated super;
					typedef kerbal::container::detail::rb_node<T> node;

				public:
					typedef T value_type;
					typedef kerbal::container::associative_unique_insert_r<node *> unique_insert_r;

					typedef kerbal::container::detail::rb_normal_result_t			rb_normal_result_t;

				public:
					rb_type_only() :
						super()
					{
					}

					template <typename NodeAllocator>
					static void k_destroy_using_allocator_impl(NodeAllocator & alloc, rb_node_base * p)
					{
						if (p == get_rb_vnull_node()) {
							return;
						}
						k_destroy_using_allocator_impl(alloc, static_cast<rb_node_base *>(p->left));
						k_destroy_using_allocator_impl(alloc, static_cast<rb_node_base *>(p->right));
						k_destroy_rb_node(alloc, static_cast<node *>(p));
					}

					template <typename NodeAllocator>
					void destroy_using_allocator(NodeAllocator & alloc)
					{
						k_destroy_using_allocator_impl(alloc, static_cast<rb_node_base *>(this->k_head.left));
					}


					~rb_type_only()
					{
						kerbal::memory::default_allocator<node> alloc;
						this->destroy_using_allocator(alloc);
					}

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					unique_insert_r k_hook_node_unique(Extract & e, KeyCompare & kc, node * n);

				public:
					template <typename Extract, typename KeyCompare>
					node * find_impl(Extract & e, KeyCompare & kc, const value_type & value)
					{
						node * p = static_cast<node *>(this->k_head.left);
						while (p != get_rb_vnull_node()) {
							const typename Extract::key_type & p_key = e(p->member());
							if (kc(value, p_key)) { // value < p->member()
								p = static_cast<node *>(p->left);
							} else if (kc(p_key, value)) { // p->member() < value
								p = static_cast<node *>(p->right);
							} else {
								return p;
							}
						}
						return NULL;
					}

					node * find(const value_type & value)
					{
						kerbal::container::identity_extractor<T> e;
						kerbal::compare::binary_type_less<void, void> kc;
						return find_impl(e, kc, value);
					}

				public:

					template <typename NodeAllocator, typename Extract, typename KeyCompare, typename ... Args>
					KERBAL_CONSTEXPR14
					unique_insert_r emplace_using_allocator(NodeAllocator & alloc, Extract & e, KeyCompare & kc, Args && ... args)
					{
						node * p = k_build_rb_node(alloc, kerbal::utility::forward<Args>(args)...);
						unique_insert_r uir = k_hook_node_unique(e, kc, p);
						if (!uir.insert_happen()) {
							k_destroy_rb_node(alloc, p);
						}
						return uir;
					}

					template <typename ... Args>
					unique_insert_r emplace(Args && ... args)
					{
						kerbal::container::identity_extractor<T> e;
						kerbal::compare::binary_type_less<void, void> kc;
						kerbal::memory::default_allocator<node> alloc;
						return this->emplace_using_allocator(alloc, e, kc, kerbal::utility::forward<Args>(args)...);
					}

					unique_insert_r insert(const value_type & src)
					{
						return this->emplace(src);
					}

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR14
					void erase_using_allocator(NodeAllocator & alloc, node * p)
					{
						k_unhook_node(p);
						k_destroy_rb_node(alloc, p);
					}

					void erase(node * p)
					{
						kerbal::memory::default_allocator<node> alloc;
						return erase_using_allocator(alloc, p);
					}

					template <typename F>
					static void preorder_helper(const rb_node_base * p, F f)
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
					static void inorder_helper(const rb_node_base * p, F f)
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
					static node * k_build_rb_node(NodeAllocator & alloc, Args && ... args)
					{
						typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
						node * p = node_allocator_traits::allocate_one(alloc);
						try {
							node_allocator_traits::construct(alloc, p, kerbal::utility::in_place_t(), RED::value, kerbal::utility::forward<Args>(args)...);
						} catch (...) {
							node_allocator_traits::deallocate_one(alloc, p);
							throw;
						}
						return p;
					}

					template <typename NodeAllocator>
					static void k_destroy_rb_node(NodeAllocator & alloc, node * p)
					{
						typedef kerbal::memory::allocator_traits<NodeAllocator> node_allocator_traits;
						node_allocator_traits::destroy(alloc, p);
						node_allocator_traits::deallocate_one(alloc, p);
					}




					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					static rb_normal_result_t rb_normal_impl(Extract & e, KeyCompare & kc, const rb_node_base * pbase, const value_type * & mini, const value_type * & maxi, std::size_t & nodes_cnt, std::size_t & black_cnt);

					KERBAL_CONSTEXPR14
					rb_normal_result_t rb_normal() const;

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_DECL_HPP
