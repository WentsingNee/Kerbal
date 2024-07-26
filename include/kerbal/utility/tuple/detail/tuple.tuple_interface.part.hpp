/**
 * @file       tuple.tuple_interface.part.hpp
 * @brief
 * @date       2024-07-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_TUPLE_DETAIL_TUPLE_TUPLE_INTERFACE_PART_HPP
#define KERBAL_UTILITY_TUPLE_DETAIL_TUPLE_TUPLE_INTERFACE_PART_HPP

#if __cplusplus >= 201103L

#include <kerbal/utility/std_tuple/std_tuple.fwd.hpp>
#include <kerbal/utility/tuple/tuple.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <type_traits> // std::integral_constant

#include <cstddef>


KERBAL_NAMESPACE_STD_BEGIN

	template <typename ... Args>
	struct tuple_size<kerbal::utility::tuple<Args...> > :
		std::integral_constant<std::size_t, kerbal::utility::tuple<Args...>::TUPLE_SIZE::value>
	{
	};

	template <std::size_t I, typename ... Args>
	struct tuple_element<I, kerbal::utility::tuple<Args...> > :
		kerbal::utility::tuple<Args...>::template value_type<I>
	{
	};

	template <std::size_t I, typename ... Args>
	KERBAL_CONSTEXPR14
	typename kerbal::utility::tuple<Args...>::template reference<I>::type
	get(kerbal::utility::tuple<Args...> & t) KERBAL_NOEXCEPT
	{
		return t.template get<I>();
	}

	template <std::size_t I, typename ... Args>
	KERBAL_CONSTEXPR
	typename kerbal::utility::tuple<Args...>::template const_reference<I>::type
	get(const kerbal::utility::tuple<Args...> & t) KERBAL_NOEXCEPT
	{
		return t.template get<I>();
	}

	template <std::size_t I, typename ... Args>
	KERBAL_CONSTEXPR14
	typename kerbal::utility::tuple<Args...>::template rvalue_reference<I>::type
	get(kerbal::utility::tuple<Args...> && t) KERBAL_NOEXCEPT
	{
		return kerbal::compatibility::move(t).template get<I>();
	}

	template <std::size_t I, typename ... Args>
	KERBAL_CONSTEXPR
	typename kerbal::utility::tuple<Args...>::template const_rvalue_reference<I>::type
	get(const kerbal::utility::tuple<Args...> && t) KERBAL_NOEXCEPT
	{
		return kerbal::compatibility::move(t).template get<I>();
	}

KERBAL_NAMESPACE_STD_END

#endif

#endif // KERBAL_UTILITY_TUPLE_DETAIL_TUPLE_TUPLE_INTERFACE_PART_HPP
