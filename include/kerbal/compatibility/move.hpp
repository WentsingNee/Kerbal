/**
 * @file       move.hpp
 * @brief      
 * @date       2019-6-2
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_MOVE_HPP
#define KERBAL_COMPATIBILITY_MOVE_HPP

#include <kerbal/type_traits/reference_deduction.hpp>


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

	} // namespace compatibility

} // namespace kerbal

#endif // KERBAL_COMPATIBILITY_MOVE_HPP
