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

#ifndef KERBAL_CONTAINER_DETAIL_SINGLE_LIST_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_SINGLE_LIST_NODE_HPP

#include <kerbal/container/fwd/single_list.fwd.hpp>

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/utility/forward.hpp>
#	include <kerbal/utility/integer_sequence.hpp>
#endif

#include <cstddef>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class sl_node_base: private kerbal::utility::noncopyable
			{
				public:
					sl_node_base * next;

				public:
					KERBAL_CONSTEXPR
					explicit sl_node_base() KERBAL_NOEXCEPT :
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
					typedef sl_node_base super;

				public:
					Tp value;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit sl_node(kerbal::utility::in_place_t, Args&& ... args)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<Tp, Args...>::value)
										)
							: super(), value(kerbal::utility::forward<Args>(args)...)
					{
					}

#		else

					explicit sl_node(kerbal::utility::in_place_t)
							: super(), value()
					{
					}

					template <typename Arg0>
					explicit sl_node(kerbal::utility::in_place_t, const Arg0 & arg0)
							: super(), value(arg0)
					{
					}

					template <typename Arg0, typename Arg1>
					explicit sl_node(kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1)
							: super(), value(arg0, arg1)
					{
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					explicit sl_node(kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
							: super(), value(arg0, arg1, arg2)
					{
					}

#		endif

			};

			template <typename Tp, size_t N>
			class sl_node<Tp[N]>: public sl_node_base
			{
				private:
					typedef sl_node_base super;

				public:
					Tp value[N];

#		if __cplusplus >= 201103L

				private:

					typedef kerbal::type_traits::integral_constant<size_t, 32> BRACE_INIT_LIMIT;

					template <typename Up, size_t ... I>
					KERBAL_CONSTEXPR
					explicit sl_node(const Up (&arg)[N], kerbal::utility::integer_sequence<size_t, I...>)
							: super(), value{arg[I]...}
					{
					}

					template <typename Up>
					KERBAL_CONSTEXPR
					explicit sl_node(const Up (&arg) [N], kerbal::type_traits::true_type) // for N < BRACE_INIT_LIMIT
							: sl_node(arg, kerbal::utility::make_index_sequence<N>())
					{
					}

					template <typename Up>
					KERBAL_CONSTEXPR14
					explicit sl_node(const Up (&arg) [N], kerbal::type_traits::false_type) // for N >= BRACE_INIT_LIMIT
							: sl_node(arg, kerbal::utility::make_index_sequence<BRACE_INIT_LIMIT::value>())
					{
						kerbal::algorithm::copy(arg + BRACE_INIT_LIMIT::value, arg + N, this->value + BRACE_INIT_LIMIT::value);
					}

				public:

					KERBAL_CONSTEXPR
					explicit sl_node(kerbal::utility::in_place_t)
							: super(), value{}
					{
					}

					template <typename Up>
					KERBAL_CONSTEXPR
					explicit sl_node(kerbal::utility::in_place_t, const Up (&arg) [N])
							: sl_node(arg, kerbal::type_traits::bool_constant<N < BRACE_INIT_LIMIT::value>())
					{
					}

#		else

				public:

					explicit sl_node(kerbal::utility::in_place_t)
							: super()
					{
					}

					template <typename Up>
					explicit sl_node(kerbal::utility::in_place_t, const Up (&arg) [N])
							: super()
					{
						kerbal::algorithm::copy(arg, arg + N, this->value);
					}

#		endif

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_SINGLE_LIST_NODE_HPP
