/**
 * @file       binary_search_tree_node.hpp
 * @brief
 * @date       2020-10-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_NODE_HPP

#include <kerbal/container/detail/bst_base/binary_search_tree.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class bst_head_node
			{
				protected:
					bst_node_base * left;

					friend class kerbal::container::detail::bst_iter_type_unrelated;

					template <typename Tp>
					friend class kerbal::container::detail::bst_iter;

					template <typename Tp>
					friend class kerbal::container::detail::bst_kiter;

					template <typename Entity, typename Key, typename KeyCompare, typename Extract>
					friend class kerbal::container::detail::bst;

				protected:
					KERBAL_CONSTEXPR
					bst_head_node() KERBAL_NOEXCEPT :
							left(NULL)
					{
					}
			};

			class bst_node_base: private bst_head_node
			{
				private:
					typedef bst_head_node super;

					friend class kerbal::container::detail::bst_iter_type_unrelated;

					template <typename Tp>
					friend class kerbal::container::detail::bst_iter;

					template <typename Tp>
					friend class kerbal::container::detail::bst_kiter;

					template <typename Entity, typename Key, typename KeyCompare, typename Extract>
					friend class kerbal::container::detail::bst;

				private:
					bst_node_base * parent;
					bst_node_base * right;

				protected:
					KERBAL_CONSTEXPR
					bst_node_base() KERBAL_NOEXCEPT :
							parent(NULL), right(NULL)
					{
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					bst_node<Tp> & reinterpret_as() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<bst_node<Tp> &>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const bst_node<Tp> & reinterpret_as() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const bst_node<Tp> &>(*this);
					}

#			if __cplusplus >= 201103L

					template <typename Tp>
					KERBAL_CONSTEXPR14
					bst_node<Tp> && reinterpret_as() && KERBAL_NOEXCEPT
					{
						return static_cast<bst_node<Tp> &&>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const bst_node<Tp> && reinterpret_as() const && KERBAL_NOEXCEPT
					{
						return static_cast<const bst_node<Tp> &&>(*this);
					}

#			endif

					friend
					KERBAL_CONSTEXPR14
					const bst_node_base*
					inorder_next(const bst_node_base* current) KERBAL_NOEXCEPT;

					friend
					KERBAL_CONSTEXPR14
					const bst_node_base*
					inorder_prev(const bst_node_base* current) KERBAL_NOEXCEPT;

			};

			template <typename Tp>
			class bst_node: public bst_node_base
			{
				private:
					typedef bst_node_base super;

					friend class kerbal::container::detail::bst_iter_type_unrelated;

					friend class kerbal::container::detail::bst_iter<Tp>;

					friend class kerbal::container::detail::bst_kiter<Tp>;

					template <typename Entity, typename Key, typename KeyCompare, typename Extract>
					friend class kerbal::container::detail::bst;

				private:
					Tp value;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit bst_node(kerbal::utility::in_place_t, Args&& ... args)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<Tp, Args...>::value)
										)
							: super(), value(kerbal::utility::forward<Args>(args)...)
					{
					}

#		else

					explicit bst_node(kerbal::utility::in_place_t)
							: super(), value()
					{
					}

					template <typename Arg0>
					explicit bst_node(kerbal::utility::in_place_t, const Arg0 & arg0)
							: super(), value(arg0)
					{
					}

					template <typename Arg0, typename Arg1>
					explicit bst_node(kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1)
							: super(), value(arg0, arg1)
					{
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					explicit bst_node(kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
							: super(), value(arg0, arg1, arg2)
					{
					}

#		endif

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_BST_BASE_BINARY_SEARCH_TREE_NODE_HPP
