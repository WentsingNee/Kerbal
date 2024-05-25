/**
 * @file       default_delete.hpp
 * @brief      
 * @date       2019-7-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_DEFAULT_DELETE_HPP
#define KERBAL_MEMORY_DEFAULT_DELETE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_destructible.hpp>
#endif


namespace kerbal
{

	namespace memory
	{

		template <typename T>
		struct default_delete
		{

#	if __cplusplus >= 201103L

				default_delete() = default;

#	else

				default_delete() KERBAL_NOEXCEPT
				{
				}

#	endif

				template <typename U>
				KERBAL_CONSTEXPR
				default_delete(const default_delete<U> &) KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR20
				void operator()(T * ptr) const
					KERBAL_CONDITIONAL_NOEXCEPT(
						kerbal::type_traits::try_test_is_nothrow_destructible<T>::IS_TRUE::value
					)
				{
					delete ptr;
				}

		};

		template <typename T>
		struct default_delete<T[]>
		{

#	if __cplusplus >= 201103L

				default_delete() = default;

#	else

				default_delete() KERBAL_NOEXCEPT
				{
				}

#	endif

				template <typename U>
				KERBAL_CONSTEXPR
				default_delete(const default_delete<U[]> &) KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR20
				void operator()(T * ptr) const
					KERBAL_CONDITIONAL_NOEXCEPT(
						kerbal::type_traits::try_test_is_nothrow_destructible<T>::IS_TRUE::value
					)
				{
					delete[] ptr;
				}

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_DEFAULT_DELETE_HPP
