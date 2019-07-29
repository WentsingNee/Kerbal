/**
 * @file       default_delete.hpp
 * @brief      
 * @date       2019-7-26
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_DEFALUT_DELETE_HPP_
#define KERBAL_MEMORY_DEFALUT_DELETE_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/noncopyable.hpp>

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

#	if __cplusplus < 201103L

			default_delete() KERBAL_NOEXCEPT
			{
			}

#	else
			constexpr default_delete() noexcept = default;

#	endif

			template <typename Up>
			KERBAL_CONSTEXPR default_delete(const default_delete<Up> &) KERBAL_NOEXCEPT
			{
			}

			void operator()(Tp* ptr) const KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_destructible<Tp>::value)
			{
				delete ptr;
			}
		};

		template <typename Tp>
		struct default_delete<Tp[]>
		{

#	if __cplusplus < 201103L

			default_delete() KERBAL_NOEXCEPT
			{
			}

#	else

			constexpr default_delete() noexcept = default;

#	endif

			template <typename Up>
			KERBAL_CONSTEXPR default_delete(const default_delete<Up[]> &) KERBAL_NOEXCEPT
			{
			}

			void operator()(Tp* ptr) const KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_destructible<Tp>::value)
			{
				delete[] ptr;
			}
		};

	} // namespace memory

} // namespace kerbal

#endif /* KERBAL_MEMORY_DEFALUT_DELETER_HPP_ */
