/**
 * @file       list_node.impl.hpp
 * @brief
 * @date       2020-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_LIST_NODE_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_LIST_NODE_IMPL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/noncopyable.hpp>

#include <cstddef>

#if __cplusplus >= 201103L
#	include <utility> // forward
#endif

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		class list;

		namespace detail
		{

			template <typename Tp, typename Allocator, bool>
			class list_base;

			template <typename Tp>
			class list_node;

			template <typename Tp>
			class list_iter;

			template <typename Tp>
			class list_kiter;

			struct init_list_node_ptr_to_self_tag
			{
			};

			class list_node_base: kerbal::utility::noncopyable
			{
				private:
					template <typename Up, typename Allocator>
					friend class kerbal::container::list;

					template <typename Up, typename Allocator, bool B>
					friend class kerbal::container::detail::list_base;

					template <typename Up>
					friend class list_iter;

					template <typename Up>
					friend class list_kiter;

				private:
					list_node_base* prev;
					list_node_base* next;

				protected:
					KERBAL_CONSTEXPR
					list_node_base() KERBAL_NOEXCEPT :
							prev(NULL), next(NULL)
					{
					}

					KERBAL_CONSTEXPR
					explicit list_node_base(init_list_node_ptr_to_self_tag) KERBAL_NOEXCEPT :
							prev(this), next(this)
					{
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					list_node<Tp> & reinterpret_as() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<list_node<Tp> &>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const list_node<Tp> & reinterpret_as() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const list_node<Tp> &>(*this);
					}

#			if __cplusplus >= 201103L

					template <typename Tp>
					KERBAL_CONSTEXPR14
					list_node<Tp> && reinterpret_as() && KERBAL_NOEXCEPT
					{
						return static_cast<list_node<Tp> &&>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const list_node<Tp> && reinterpret_as() const && KERBAL_NOEXCEPT
					{
						return static_cast<const list_node<Tp> &&>(*this);
					}

#			endif

			};

			template <typename Tp>
			class list_node: public list_node_base
			{
				private:
					template <typename Up, typename Allocator>
					friend class kerbal::container::list;

					template <typename Up>
					friend class list_iter;

					template <typename Up>
					friend class list_kiter;

				private:
					Tp value;

				private:
					typedef list_node_base super;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit list_node(kerbal::utility::in_place_t, Args&& ... args)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<Tp, Args...>::value)
										)
							: super(), value(std::forward<Args>(args)...)
					{
					}

#		else

					explicit list_node(kerbal::utility::in_place_t)
							: super(), value()
					{
					}

					template <typename Arg0>
					explicit list_node(kerbal::utility::in_place_t, const Arg0 & arg0)
							: super(), value(arg0)
					{
					}

					template <typename Arg0, typename Arg1>
					explicit list_node(kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1)
							: super(), value(arg0, arg1)
					{
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					explicit list_node(kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
							: super(), value(arg0, arg1, arg2)
					{
					}

#		endif

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_LIST_NODE_IMPL_HPP
