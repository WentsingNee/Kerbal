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
#include <kerbal/container/detail/bst_base/bst_node.hpp>

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

			class avl_node_base : protected kerbal::container::detail::bst_node_base<avl_vnull_node_helper<> >
			{
				private:
					typedef avl_vnull_node_helper<> VNULL_HELPER;
					typedef kerbal::container::detail::bst_node_base<VNULL_HELPER> super;

					friend class kerbal::container::detail::bst_node_base<VNULL_HELPER>;

					template <int>
					friend class kerbal::container::detail::avl_vnull_node_helper;

					friend class kerbal::container::detail::bst_iter_type_unrelated<VNULL_HELPER>;

					friend class kerbal::container::detail::bst_kiter_type_unrelated<VNULL_HELPER>;

					template <typename T>
					friend class kerbal::container::detail::avl_iter;

					template <typename T>
					friend class kerbal::container::detail::avl_kiter;

					friend class kerbal::container::detail::avl_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::avl_type_only;

				protected:
					typedef kerbal::container::detail::bst_head_node<avl_vnull_node_helper<> > bst_head_node;

					KERBAL_CONSTEXPR
					static
					avl_node_base *
					as(bst_head_node * self) KERBAL_NOEXCEPT
					{
						return static_cast<avl_node_base *>(self);
					}

					KERBAL_CONSTEXPR
					static
					const avl_node_base *
					as(const bst_head_node * self) KERBAL_NOEXCEPT
					{
						return static_cast<const avl_node_base *>(self);
					}

				public:
					typedef unsigned short height_t;

				private:
					height_t height;

				protected:
					KERBAL_CONSTEXPR
					avl_node_base() KERBAL_NOEXCEPT :
						super(get_avl_vnull_node()), height(1)
					{
					}

					KERBAL_CONSTEXPR
					avl_node_base(int) KERBAL_NOEXCEPT :
						super(NULL), height(0)
					{
					}


					KERBAL_CONSTEXPR
					avl_node_base *
					get_left() const KERBAL_NOEXCEPT
					{
						return avl_node_base::as(this->left);
					}

					KERBAL_CONSTEXPR
					avl_node_base *
					get_right() const KERBAL_NOEXCEPT
					{
						return avl_node_base::as(this->right);
					}

					KERBAL_CONSTEXPR14
					static
					height_t
					height_of(const avl_node_base * p) KERBAL_NOEXCEPT
					{
#	if KERBAL_AVL_ENABLE_VNULL

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							if (p == get_avl_vnull_node()) {
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
						height_t hl = height_of(this->get_left());
						height_t hr = height_of(this->get_right());
						this->update_height(hl, hr);
					}

			};



			template <typename T>
			class avl_node :
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
					explicit
					avl_node(kerbal::utility::in_place_t in_place, Args && ... args)
						KERBAL_CONDITIONAL_NOEXCEPT((
							kerbal::type_traits::try_test_is_nothrow_constructible<
								member_compress_helper, kerbal::utility::in_place_t, Args && ...
							>::IS_TRUE::value
						)) :
						node_base(), member_compress_helper(in_place, kerbal::utility::forward<Args>(args)...)
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
					explicit \
					avl_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						node_base(), member_compress_helper(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
					{ \
					} \

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

					KERBAL_CONSTEXPR14
					static
					avl_node *
					reinterpret_as(avl_node_base * p) KERBAL_NOEXCEPT
					{
						return static_cast<avl_node *>(p);
					}

					KERBAL_CONSTEXPR14
					static
					const avl_node *
					reinterpret_as(const avl_node_base * p) KERBAL_NOEXCEPT
					{
						return static_cast<const avl_node *>(p);
					}

					KERBAL_CONSTEXPR14
					static
					avl_node *
					reinterpret_as(bst_head_node * p) KERBAL_NOEXCEPT
					{
						return static_cast<avl_node *>(p);
					}

					KERBAL_CONSTEXPR14
					static
					const avl_node *
					reinterpret_as(const bst_head_node * p) KERBAL_NOEXCEPT
					{
						return static_cast<const avl_node *>(p);
					}

					using member_compress_helper::member;

			};


			template <int>
			class avl_vnull_node_helper
			{

#	if KERBAL_AVL_ENABLE_VNULL
					static avl_node_base vnull_node;
#	endif

					friend inline
					KERBAL_CONSTEXPR
					avl_node_base * get_avl_vnull_node() KERBAL_NOEXCEPT;

				public:
					KERBAL_CONSTEXPR
					static
					avl_node_base::bst_head_node *
					get_vnull() KERBAL_NOEXCEPT
					{
						return static_cast<avl_node_base::bst_head_node *>(get_avl_vnull_node());
					}

			};


#	if KERBAL_AVL_ENABLE_VNULL

			template <int I>
			avl_node_base avl_vnull_node_helper<I>::vnull_node(0);

#	endif


			inline
			KERBAL_CONSTEXPR
			avl_node_base *
			get_avl_vnull_node() KERBAL_NOEXCEPT
			{
#	if KERBAL_AVL_ENABLE_VNULL
				return &avl_vnull_node_helper<>::vnull_node;
#	else
				return NULL;
#	endif
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_BASE_AVL_NODE_HPP
