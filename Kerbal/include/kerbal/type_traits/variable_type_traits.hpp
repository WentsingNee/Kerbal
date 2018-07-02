/*
 * variable_type_traits.hpp
 *
 *  Created on: 2018年6月30日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_TYPE_TRAITS_VARIABLE_TYPE_TRAITS_HPP_
#define INCLUDE_KERBAL_TYPE_TRAITS_VARIABLE_TYPE_TRAITS_HPP_

#include <kerbal/compatibility/compatibility_macro.hpp>
#include <cstddef>

#include <type_traits>

namespace kerbal
{
	namespace type_traits
	{
		namespace variable_type_traits
		{

			template <typename Tp>
			KERBAL_CONSTEXPR bool is_same(const Tp &, const Tp &)
			{
				return true;
			}

			template <typename Tp, typename Up>
			KERBAL_CONSTEXPR bool is_same(const Tp &, const Up &)
			{
				return false;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR bool is_const(Tp &)
			{
				return false;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR bool is_const(const Tp &)
			{
				return true;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR bool is_volatile(const Tp &)
			{
				return false;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR bool is_volatile(const volatile Tp &)
			{
				return true;
			}

#		if __cplusplus >= 201103L
			template <typename Tp>
			KERBAL_CONSTEXPR bool is_rvalue_reference(Tp &)
			{
				return false;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR bool is_rvalue_reference(Tp &&)
			{
				return true;
			}
#		endif

			template <typename Type>
			KERBAL_CONSTEXPR bool is_array(const Type &)
			{
				return false;
			}

			template <typename Type, size_t N>
			KERBAL_CONSTEXPR bool is_array(const Type (&)[N])
			{
				return true;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR bool is_pointer_helper(const Tp &)
			{
				return false;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR bool is_pointer_helper(Tp *)
			{
				return true;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR bool is_pointer(const Tp & src)
			{
				return is_pointer_helper(src) && !is_array(src);
			}

		}
	}
}

#endif /* INCLUDE_KERBAL_TYPE_TRAITS_VARIABLE_TYPE_TRAITS_HPP_ */
