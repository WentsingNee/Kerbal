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

#ifndef KERBAL_ANY_ANY_ANY_FWD_HPP
#define KERBAL_ANY_ANY_ANY_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <memory>

#include <cstddef>


namespace kerbal
{

	namespace any
	{

		KERBAL_MODULE_EXPORT
		template <
			std::size_t Size = sizeof(void *),
			std::size_t Align = Size,
			typename Allocator = std::allocator<char>
		>
		class basic_any;

		KERBAL_MODULE_EXPORT
		typedef basic_any<sizeof(void *), KERBAL_ALIGNOF(void *), std::allocator<char> > any;

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T * any_cast(basic_any<Size, Align, Allocator> * operand) KERBAL_NOEXCEPT;

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		const T * any_cast(const basic_any<Size, Align, Allocator> * operand) KERBAL_NOEXCEPT;

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T any_cast(basic_any<Size, Align, Allocator> & operand);

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		const T any_cast(const basic_any<Size, Align, Allocator> & operand);

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T any_cast(basic_any<Size, Align, Allocator> && operand);

#	endif

	} // namespace any

} // namespace kerbal


#endif // KERBAL_ANY_ANY_ANY_FWD_HPP
