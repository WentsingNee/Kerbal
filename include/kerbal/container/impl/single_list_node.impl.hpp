/**
 * @file       single_list_node.impl.hpp
 * @brief
 * @date       2020-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_SINGLE_LIST_NODE_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_SINGLE_LIST_NODE_IMPL_HPP

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
		class single_list;

		namespace detail
		{
			template <typename Tp>
			class sl_node;

			template <typename Tp>
			class sl_iter;

			template <typename Tp>
			class sl_kiter;

			class sl_node_base: kerbal::utility::noncopyable
			{
				private:
					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

					template <typename Up>
					friend class sl_iter;

					template <typename Up>
					friend class sl_kiter;

				private:
					sl_node_base * next;

				protected:
					KERBAL_CONSTEXPR
					sl_node_base() KERBAL_NOEXCEPT :
							next(NULL)
					{
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					sl_node<Tp> & reinterpret_as() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<sl_node<Tp> &>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const sl_node<Tp> & reinterpret_as() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const sl_node<Tp> &>(*this);
					}

#			if __cplusplus >= 201103L

					template <typename Tp>
					KERBAL_CONSTEXPR14
					sl_node<Tp> && reinterpret_as() && KERBAL_NOEXCEPT
					{
						return static_cast<sl_node<Tp> &&>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const sl_node<Tp> && reinterpret_as() const && KERBAL_NOEXCEPT
					{
						return static_cast<const sl_node<Tp> &&>(*this);
					}

#			endif

			};

			template <typename Tp>
			class sl_node: public sl_node_base
			{
				private:
					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

					template <typename Up>
					friend class sl_iter;

					template <typename Up>
					friend class sl_kiter;

				private:
					Tp value;

				private:
					typedef sl_node_base super;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit sl_node(kerbal::utility::in_place_t, Args&& ... args)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<Tp, Args...>::value)
										)
							: super(), value(std::forward<Args>(args)...)
					{
					}

#		else

					sl_node(kerbal::utility::in_place_t)
							: super(), value()
					{
					}

					template <typename Arg0>
					explicit sl_node(kerbal::utility::in_place_t, const Arg0 & arg0)
							: super(), value(arg0)
					{
					}

					template <typename Arg0, typename Arg1>
					sl_node(kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1)
							: super(), value(arg0, arg1)
					{
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					sl_node(kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
							: super(), value(arg0, arg1, arg2)
					{
					}

#		endif

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_SINGLE_LIST_NODE_IMPL_HPP
