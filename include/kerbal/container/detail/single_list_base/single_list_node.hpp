/**
 * @file       single_list_node.hpp
 * @brief
 * @date       2020-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_NODE_HPP

#include <kerbal/container/detail/forward_list_base/forward_list_base.fwd.hpp>
#include <kerbal/container/detail/single_list_base/single_list_base.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_constructible.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class sl_node_base : private kerbal::utility::noncopyable
			{
				private:
					friend class kerbal::container::detail::fl_type_unrelated;

					template <typename T>
					friend class kerbal::container::detail::fl_type_only;

					template <typename T>
					friend class fl_iter;

					template <typename T>
					friend class fl_kiter;

					friend class kerbal::container::detail::sl_type_unrelated;

					template <typename T>
					friend class kerbal::container::detail::sl_type_only;

					template <typename T>
					friend class sl_iter;

					template <typename T>
					friend class sl_kiter;

				public:
					sl_node_base * next;

				protected:
					KERBAL_CONSTEXPR
					explicit sl_node_base() KERBAL_NOEXCEPT :
						next(NULL)
					{
					}

			};

			template <typename T>
			class sl_node:
				public sl_node_base,
				private kerbal::utility::member_compress_helper<T>
			{
				private:
					typedef kerbal::utility::member_compress_helper<T> member_compress_helper;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit sl_node(kerbal::utility::in_place_t in_place, Args && ... args)
						KERBAL_CONDITIONAL_NOEXCEPT((
							kerbal::type_traits::try_test_is_nothrow_constructible<
								member_compress_helper, kerbal::utility::in_place_t, Args &&...
							>::IS_TRUE::value
						)) :
						member_compress_helper(in_place, kerbal::utility::forward<Args>(args)...)
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
					explicit sl_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						member_compress_helper(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
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
					sl_node *
					reinterpret_as(sl_node_base * p) KERBAL_NOEXCEPT
					{
						return static_cast<sl_node *>(p);
					}

					KERBAL_CONSTEXPR14
					static
					const sl_node *
					reinterpret_as(const sl_node_base * p) KERBAL_NOEXCEPT
					{
						return static_cast<const sl_node *>(p);
					}

					using member_compress_helper::member;

			};


			struct sl_node_base_chain
			{
					sl_node_base * start;
					sl_node_base * back;

					KERBAL_CONSTEXPR
					sl_node_base_chain(sl_node_base * start, sl_node_base * back) KERBAL_NOEXCEPT :
						start(start), back(back)
					{
					}

			};

			template <typename T>
			struct sl_node_chain
			{
					sl_node<T> * start;
					sl_node<T> * back;

					KERBAL_CONSTEXPR
					sl_node_chain(sl_node<T> * start, sl_node<T> * back) KERBAL_NOEXCEPT :
						start(start), back(back)
					{
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_SINGLE_LIST_NODE_HPP
