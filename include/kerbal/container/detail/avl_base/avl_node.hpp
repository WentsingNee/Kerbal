/**
 * @file       avl_node.hpp
 * @brief
 * @date       2020-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_NODE_HPP

#include <kerbal/container/detail/avl_base/avl_base.fwd.hpp>

#include <kerbal/compare/minmax.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class avl_head_node
			{
				protected:
					friend class kerbal::container::detail::avl_node_base;

					friend class kerbal::container::detail::avl_iter_type_unrelated;

					friend class kerbal::container::detail::avl_kiter_type_unrelated;

					template <typename T>
					friend class kerbal::container::detail::avl_iter;

					template <typename T>
					friend class kerbal::container::detail::avl_kiter;

					friend class kerbal::container::detail::avl_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				protected:
					avl_node_base * left;

				protected:
					KERBAL_CONSTEXPR
					avl_head_node() KERBAL_NOEXCEPT :
							left(get_avl_vnull_node())
					{
					}

					KERBAL_CONSTEXPR14
					avl_node_base * as_node_base() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const avl_node_base * as_node_base() const KERBAL_NOEXCEPT;


					template <typename T>
					KERBAL_CONSTEXPR14
					avl_node<T> & reinterpret_as() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<avl_node<T> &>(*this);
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					const avl_node<T> & reinterpret_as() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const avl_node<T> &>(*this);
					}

#			if __cplusplus >= 201103L

					template <typename T>
					KERBAL_CONSTEXPR14
					avl_node<T> && reinterpret_as() && KERBAL_NOEXCEPT
					{
						return static_cast<avl_node<T> &&>(*this);
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					const avl_node<T> && reinterpret_as() const && KERBAL_NOEXCEPT
					{
						return static_cast<const avl_node<T> &&>(*this);
					}

#			endif

					KERBAL_CONSTEXPR14
					const avl_node_base *
					leftest_offspring() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					avl_node_base *
					leftest_offspring() KERBAL_NOEXCEPT
					{
						return const_cast<avl_node_base*>(
							static_cast<const avl_head_node*>(this)->leftest_offspring()
						);
					}

					KERBAL_CONSTEXPR14
					inline
					const avl_head_node*
					inorder_prev() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					inline
					avl_head_node*
					inorder_prev() KERBAL_NOEXCEPT
					{
						return const_cast<avl_head_node*>(
							static_cast<const avl_head_node*>(this)->inorder_prev()
						);
					}

			};



			class avl_node_base: protected kerbal::container::detail::avl_head_node
			{
				private:
					typedef kerbal::container::detail::avl_head_node super;

					friend class kerbal::container::detail::avl_head_node;

					template <int>
					friend class kerbal::container::detail::avl_vnull_node_helper;

					friend class kerbal::container::detail::avl_iter_type_unrelated;

					friend class kerbal::container::detail::avl_kiter_type_unrelated;

					template <typename T>
					friend class kerbal::container::detail::avl_iter;

					template <typename T>
					friend class kerbal::container::detail::avl_kiter;

					friend class kerbal::container::detail::avl_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				public:
					typedef unsigned short height_t;

				private:
					avl_head_node * parent;
					avl_node_base * right;
					height_t height;

				protected:
					KERBAL_CONSTEXPR
					avl_node_base() KERBAL_NOEXCEPT :
							parent(NULL), right(get_avl_vnull_node()), height(1)
					{
					}

					KERBAL_CONSTEXPR
					avl_node_base(int) KERBAL_NOEXCEPT :
							parent(NULL), right(NULL), height(0)
					{
					}


					KERBAL_CONSTEXPR14
					avl_head_node * as_head() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const avl_head_node * as_head() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const avl_head_node *
					inorder_next() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					inline
					avl_head_node*
					inorder_next() KERBAL_NOEXCEPT
					{
						return const_cast<avl_head_node*>(
							static_cast<const avl_node_base*>(this)->inorder_next()
						);
					}

					KERBAL_CONSTEXPR14
					inline
					const avl_head_node *
					postorder_next(const avl_head_node * head) const KERBAL_NOEXCEPT
					{
						const avl_node_base * current = this;
						if (current == parent->left) {
							if (parent == head) {
								return head;
							}
							const avl_node_base * brother = parent->as_node_base()->right;
							if (brother == get_avl_vnull_node()) {
								return parent;
							}
							brother = brother->leftest_offspring();
							if (brother->right != get_avl_vnull_node()) { // correct only under avl
								return brother->right;
							}
							return brother;
						} else {
							return parent;
						}
					}

					KERBAL_CONSTEXPR14
					inline
					avl_head_node*
					postorder_next(const avl_head_node * head) KERBAL_NOEXCEPT
					{
						return const_cast<avl_head_node*>(
							static_cast<const avl_node_base*>(this)->postorder_next(head)
						);
					}

					KERBAL_CONSTEXPR14
					const avl_node_base *
					rightest_offspring() const KERBAL_NOEXCEPT
					{
						const avl_node_base * current = this;
						avl_node_base * offspring = current->right;
						while (offspring != get_avl_vnull_node()) {
							current = offspring;
							offspring = current->right;
						}
						return current;
					}

					KERBAL_CONSTEXPR14
					avl_node_base *
					rightest_offspring() KERBAL_NOEXCEPT
					{
						return const_cast<avl_node_base*>(
							static_cast<const avl_node_base*>(this)->rightest_offspring()
						);
					}

					KERBAL_CONSTEXPR14
					static height_t height_of(const avl_node_base * p) KERBAL_NOEXCEPT
					{
#	if KERBAL_AVL_ENABLE_VNULL

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							if (p == NULL) {
								return 0;
							}
						}
#		endif
						return p->height;

#	else

						if (p == get_avl_vnull_node()) {
							return 0;
						}
						return p->height;

#	endif
					}

					KERBAL_CONSTEXPR14
					void update_height(height_t hl, height_t hr) KERBAL_NOEXCEPT
					{
						this->height = 1 + kerbal::compare::max(hl, hr);
					}

					KERBAL_CONSTEXPR14
					void update_height() KERBAL_NOEXCEPT
					{
						height_t hl = height_of(this->left);
						height_t hr = height_of(this->right);
						this->update_height(hl, hr);
					}


					KERBAL_CONSTEXPR14
					friend inline
					void set_parent_ignore_null(avl_node_base * p_base, avl_head_node * p_parent)
					{
#	if KERBAL_AVL_ENABLE_VNULL

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							if (p_base == NULL) {
								return ;
							}
						}
#		endif

						p_base->parent = p_parent;
#	else
						if (p_base != get_avl_vnull_node()) {
							p_base->parent = p_parent;
						}
#	endif
					}

			};



			template <typename T>
			class avl_node:
					public avl_node_base,
					private kerbal::utility::member_compress_helper<T>
			{
				private:
					typedef avl_node_base node_base;
					typedef kerbal::utility::member_compress_helper<T> member_compress_helper;

					friend class kerbal::container::detail::avl_iter<T>;

					friend class kerbal::container::detail::avl_kiter<T>;

					friend class kerbal::container::detail::avl_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit avl_node(kerbal::utility::in_place_t in_place, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT((
								kerbal::type_traits::try_test_is_nothrow_constructible<
									member_compress_helper, kerbal::utility::in_place_t, Args&&...
								>::IS_TRUE::value
							))
							: node_base(), member_compress_helper(in_place, kerbal::utility::forward<Args>(args)...)
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
					explicit avl_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: node_base(), member_compress_helper(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
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

					using member_compress_helper::member;

			};

			inline
			KERBAL_CONSTEXPR14
			avl_node_base * avl_head_node::as_node_base() KERBAL_NOEXCEPT
			{
				return static_cast<avl_node_base *>(this);
			}

			inline
			KERBAL_CONSTEXPR
			const avl_node_base * avl_head_node::as_node_base() const KERBAL_NOEXCEPT
			{
				return static_cast<const avl_node_base *>(this);
			}

			inline
			KERBAL_CONSTEXPR14
			const avl_node_base *
			avl_head_node::leftest_offspring() const KERBAL_NOEXCEPT
			{
				const avl_head_node * current = this;
				avl_node_base * offspring = current->left;
				while (offspring != get_avl_vnull_node()) {
					current = offspring->as_head();
					offspring = current->left;
				}
				return current->as_node_base();
			}

			inline
			KERBAL_CONSTEXPR14
			avl_head_node * avl_node_base::as_head() KERBAL_NOEXCEPT
			{
				return static_cast<avl_head_node *>(this);
			}

			inline
			KERBAL_CONSTEXPR
			const avl_head_node * avl_node_base::as_head() const KERBAL_NOEXCEPT
			{
				return static_cast<const avl_head_node *>(this);
			}


			KERBAL_CONSTEXPR14
			inline
			const avl_head_node*
			avl_head_node::inorder_prev() const KERBAL_NOEXCEPT
			{
				const avl_head_node * current = this;
				if (current->left == get_avl_vnull_node()) {
					const avl_head_node * ancestor = current->as_node_base()->parent;
					while (current == ancestor->left) { // warning: head doesn't have right domain!
						// is parent's right son
						current = ancestor;
						ancestor = ancestor->as_node_base()->parent;
					}
					// is parent's left son
					current = ancestor;
				} else {
					current = current->left->rightest_offspring();
				}
				return current;
			}

			KERBAL_CONSTEXPR14
			inline
			const avl_head_node *
			avl_node_base::inorder_next() const KERBAL_NOEXCEPT
			{
				const avl_head_node * current = this;
				if (current->as_node_base()->right == get_avl_vnull_node()) {
					const avl_head_node * ancestor = current->as_node_base()->parent;
					while (current != ancestor->left) { // warning: head doesn't have right domain!
						// is parent's right son
						current = ancestor;
						ancestor = current->as_node_base()->parent;
					}
					// is parent's left son
					current = ancestor;
				} else {
					current = current->as_node_base()->right->leftest_offspring();
				}
				return current;
			}



#	if KERBAL_AVL_ENABLE_VNULL

			template <int>
			class avl_vnull_node_helper
			{
				static avl_node_base vnull_node;

				friend inline
				KERBAL_CONSTEXPR
				avl_node_base * get_avl_vnull_node() KERBAL_NOEXCEPT;

			};

			template <int I>
			avl_node_base avl_vnull_node_helper<I>::vnull_node(0);

#	endif



			inline
			KERBAL_CONSTEXPR
			avl_node_base * get_avl_vnull_node() KERBAL_NOEXCEPT
			{
#	if KERBAL_AVL_ENABLE_VNULL

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				return KERBAL_IS_CONSTANT_EVALUATED() ? NULL : &avl_vnull_node_helper<>::vnull_node;
#		else
				return &avl_vnull_node_helper<>::vnull_node;
#		endif

#	else
				return NULL;
#	endif
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_NODE_HPP
