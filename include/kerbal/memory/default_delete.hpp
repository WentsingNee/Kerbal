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
# include <type_traits>
#endif


namespace kerbal
{

	namespace memory
	{

		template <typename Tp>
		struct default_delete
		{

#	if __cplusplus >= 201103L

				default_delete() = default;

#	else

				default_delete() KERBAL_NOEXCEPT
				{
				}

#	endif

				template <typename Up>
				KERBAL_CONSTEXPR
				default_delete(const default_delete<Up> &) KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR20
				void operator()(Tp* ptr) const
						KERBAL_CONDITIONAL_NOEXCEPT(std::is_nothrow_destructible<Tp>::value)
				{
					delete ptr;
				}

		};

		template <typename Tp>
		struct default_delete<Tp[]>
		{

#	if __cplusplus >= 201103L

				default_delete() = default;

#	else

				default_delete() KERBAL_NOEXCEPT
				{
				}

#	endif

				template <typename Up>
				KERBAL_CONSTEXPR
				default_delete(const default_delete<Up[]> &) KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR20
				void operator()(Tp* ptr) const
						KERBAL_CONDITIONAL_NOEXCEPT(std::is_nothrow_destructible<Tp>::value)
				{
					delete[] ptr;
				}

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_DEFAULT_DELETE_HPP
