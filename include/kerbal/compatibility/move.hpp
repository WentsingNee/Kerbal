/**
 * @file       move.hpp
 * @brief      
 * @date       2019年6月2日
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */
#ifndef INCLUDE_KERBAL_COMPATIBILITY_MOVE_HPP_
#define INCLUDE_KERBAL_COMPATIBILITY_MOVE_HPP_

#include <kerbal/type_traits/type_traits_details/reference_deduction.hpp>

namespace kerbal
{
	namespace compatibility
	{

#	if __cplusplus < 201103L

		template <typename _Tp>
		typename kerbal::type_traits::remove_reference<_Tp>::type&
		to_xvalue(_Tp& __t)
		{
			return static_cast<typename kerbal::type_traits::remove_reference<_Tp>::type&>(__t);
		}

#	else

		template <typename _Tp>
		constexpr	typename kerbal::type_traits::remove_reference<_Tp>::type&&
		to_xvalue(_Tp&& __t) noexcept
		{
			return static_cast<typename kerbal::type_traits::remove_reference<_Tp>::type&&>(__t);
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename _Tp>
		constexpr	typename kerbal::type_traits::remove_reference<_Tp>::type&&
		move(_Tp&& __t) noexcept
		{
			return static_cast<typename kerbal::type_traits::remove_reference<_Tp>::type&&>(__t);
		}

#	endif

	}
}

#endif /* INCLUDE_KERBAL_COMPATIBILITY_MOVE_HPP_ */
