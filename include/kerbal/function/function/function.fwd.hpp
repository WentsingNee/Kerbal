/**
 * @file       function.fwd.hpp
 * @brief
 * @date       2021-10-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_FUNCTION_FUNCTION_FWD_HPP
#define KERBAL_FUNCTION_FUNCTION_FUNCTION_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <memory>

#include <cstddef>


namespace kerbal
{

	namespace function
	{

		KERBAL_MODULE_EXPORT
		template <
			typename Fun,
			std::size_t Size = sizeof(void *),
			std::size_t Align = Size,
			typename Allocator = std::allocator<char>
		>
		class basic_function;

#	if __cplusplus >= 201103L
		KERBAL_MODULE_EXPORT
		template <typename Fun>
		using function = basic_function<Fun, sizeof(void *), KERBAL_ALIGNOF(void *), std::allocator<char> >;
#	endif

		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T * function_cast(basic_function<Fun, Size, Align, Allocator> * operand) KERBAL_NOEXCEPT;

		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		const T * function_cast(const basic_function<Fun, Size, Align, Allocator> * operand) KERBAL_NOEXCEPT;

		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T function_cast(basic_function<Fun, Size, Align, Allocator> & operand);

		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		const T function_cast(const basic_function<Fun, Size, Align, Allocator> & operand);

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T function_cast(basic_function<Fun, Size, Align, Allocator> && operand);

#	endif

	} // namespace function

} // namespace kerbal


#endif // KERBAL_FUNCTION_FUNCTION_FUNCTION_FWD_HPP
