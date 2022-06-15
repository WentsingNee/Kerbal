/**
 * @file       any.fwd.hpp
 * @brief
 * @date       2021-10-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ANY_FWD_ANY_FWD_HPP
#define KERBAL_ANY_FWD_ANY_FWD_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <memory>

#include <cstddef>


namespace kerbal
{

	namespace any
	{

		template <std::size_t Size = sizeof(void*), std::size_t Align = Size, typename Allocator = std::allocator<char> >
		class basic_any;

		typedef basic_any<sizeof(void*), KERBAL_ALIGNOF(void*), std::allocator<char> > any;

		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T* any_cast(basic_any<Size, Align, Allocator> * operand) KERBAL_NOEXCEPT;

		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		const T* any_cast(const basic_any<Size, Align, Allocator> * operand) KERBAL_NOEXCEPT;

	} // namespace any

} // namespace kerbal


#endif // KERBAL_ANY_FWD_ANY_FWD_HPP
