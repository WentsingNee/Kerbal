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

#include "kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp"
#include "kerbal/compare/binary_type_compare.hpp"


#include <kerbal/container/detail/rb_base/rb_base.fwd.hpp>

#include <kerbal/container/detail/bst_base/bst_node.hpp>
#include <kerbal/container/detail/rb_base/rb_node.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>


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

					template <typename Extract, typename KeyCompare>
					KERBAL_CONSTEXPR14
					unique_insert_r k_hook_node_unique(Extract & e, KeyCompare & kc, node * n);

				public:

					template <typename Extract, typename KeyCompare, typename ... Args>
					KERBAL_CONSTEXPR14
					unique_insert_r emplace_using(Extract & e, KeyCompare & kc, Args && ... args)
					{
						node * p = new node(kerbal::utility::in_place_t(), RED::value, kerbal::utility::forward<Args>(args)...);
						return k_hook_node_unique(e, kc, p);
					}

					template <typename ... Args>
					unique_insert_r emplace(Args && ... args)
					{
						kerbal::container::identity_extractor<T> e;
						kerbal::compare::binary_type_less<void, void> kc;
						return emplace_using(e, kc, kerbal::utility::forward<Args>(args)...);
					}

					unique_insert_r insert(const T & src)
					{
						return this->emplace(src);
					}

					template <typename F>
					static void inorder_helper(const node * p, F f)
					{
						if (p == get_rb_vnull_node()) {
							return;
						}
						inorder_helper(static_cast<const node *>(p->left), f);
						f(p->member());
						inorder_helper(static_cast<const node *>(p->right), f);
					}

					template <typename F>
					void inorder(F f) const
					{
						inorder_helper(static_cast<const node *>(this->k_head.left), f);
					}



					KERBAL_CONSTEXPR14
					static rb_normal_result_t rb_normal_impl(const bst_node_base * pbase, const value_type * & mini, const value_type * & maxi, std::size_t & nodes_cnt, std::size_t & black_cnt);

					KERBAL_CONSTEXPR14
					rb_normal_result_t rb_normal() const;

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RB_BASE_RB_BASE_DECL_HPP
