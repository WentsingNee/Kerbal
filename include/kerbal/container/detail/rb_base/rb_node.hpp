/**
 * @file       rb_node.hpp
 * @brief
 * @date       2023-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_RB_BASE_RB_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_RB_BASE_RB_NODE_HPP

#include <kerbal/container/detail/rb_base/rb_base.fwd.hpp>

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

			class rb_node_base : protected kerbal::container::detail::bst_node_base
			{
				private:
					typedef kerbal::container::detail::bst_node_base super;

					friend class kerbal::container::detail::bst_node_base;

					template <int>
					friend class kerbal::container::detail::rb_vnull_node_helper;

					friend class kerbal::container::detail::rb_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::rb_type_only;

					KERBAL_CONSTEXPR14
					friend inline
					rb_node_base * as_rb_node_base(bst_head_node * self) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					friend inline
					const rb_node_base * as_rb_node_base(const bst_head_node * self) KERBAL_NOEXCEPT;

				protected:
					typedef kerbal::container::detail::rb_color_t		rb_color_t;
					rb_color_t color;

				protected:
					KERBAL_CONSTEXPR
					rb_node_base(rb_color_t color) KERBAL_NOEXCEPT :
							super(get_rb_vnull_node()), color(color)
					{
					}

					KERBAL_CONSTEXPR
					rb_node_base(int) KERBAL_NOEXCEPT :
							super(NULL), color(BLACK::value)
					{
					}


					template <typename T>
					KERBAL_CONSTEXPR14
					rb_node<T> & reinterpret_as() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<rb_node<T> &>(*this);
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					const rb_node<T> & reinterpret_as() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const rb_node<T> &>(*this);
					}

					KERBAL_CONSTEXPR14
					void set_red() KERBAL_NOEXCEPT
					{
						this->color = RED::value;
					}

					KERBAL_CONSTEXPR14
					void set_black() KERBAL_NOEXCEPT
					{
						this->color = BLACK::value;
					}

					KERBAL_CONSTEXPR14
					static bool is_black(const rb_node_base * p) KERBAL_NOEXCEPT
					{
#	if KERBAL_AVL_ENABLE_VNULL

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							if (p == NULL) {
								return true;
							}
						}
#		endif
						return p->color == BLACK::value;

#	else

						if (p == get_rb_vnull_node()) {
							return true;
						}
						return p->color == BLACK::value;

#	endif
					}

			};



			KERBAL_CONSTEXPR14
			inline
			rb_node_base * as_rb_node_base(bst_head_node * self) KERBAL_NOEXCEPT
			{
				return static_cast<rb_node_base *>(self);
			}

			KERBAL_CONSTEXPR
			inline
			const rb_node_base * as_rb_node_base(const bst_head_node * self) KERBAL_NOEXCEPT
			{
				return static_cast<const rb_node_base *>(self);
			}



			template <typename T>
			class rb_node:
					public rb_node_base,
					private kerbal::utility::member_compress_helper<T>
			{
				protected:
					typedef rb_node_base node_base;
					typedef typename rb_node_base::rb_color_t rb_color_t;

					typedef kerbal::utility::member_compress_helper<T> member_compress_helper;

					friend class kerbal::container::detail::rb_node_base;

					friend class kerbal::container::detail::rb_iter<T>;

					friend class kerbal::container::detail::rb_kiter<T>;

					friend class kerbal::container::detail::rb_type_unrelated;

					template <typename Entity>
					friend class kerbal::container::detail::rb_type_only;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit rb_node(kerbal::utility::in_place_t in_place, rb_color_t color, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT((
								kerbal::type_traits::tribool_is_true<
									kerbal::type_traits::try_test_is_nothrow_constructible<member_compress_helper, kerbal::utility::in_place_t, Args&&...>
								>::value
							))
							: node_base(color), member_compress_helper(in_place, kerbal::utility::forward<Args>(args)...)
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
					explicit rb_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
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


#	if KERBAL_AVL_ENABLE_VNULL

			template <int>
			class rb_vnull_node_helper
			{
				static rb_node_base vnull_node;

				friend inline
				KERBAL_CONSTEXPR
				rb_node_base * get_rb_vnull_node() KERBAL_NOEXCEPT;

			};

			template <int I>
			rb_node_base rb_vnull_node_helper<I>::vnull_node(0);

#	endif



			inline
			KERBAL_CONSTEXPR
			rb_node_base * get_rb_vnull_node() KERBAL_NOEXCEPT
			{
#	if KERBAL_AVL_ENABLE_VNULL

#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				return KERBAL_IS_CONSTANT_EVALUATED() ? NULL : &rb_vnull_node_helper<>::vnull_node;
#		else
				return &rb_vnull_node_helper<>::vnull_node;
#		endif

#	else
				return NULL;
#	endif
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_RB_BASE_RB_NODE_HPP
