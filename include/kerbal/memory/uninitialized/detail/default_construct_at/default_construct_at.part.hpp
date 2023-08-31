/**
 * @file       default_construct_at.part.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DETAIL_DEFAULT_CONSTRUCT_AT_DEFAULT_CONSTRUCT_AT_PART_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DETAIL_DEFAULT_CONSTRUCT_AT_DEFAULT_CONSTRUCT_AT_PART_HPP

#include <kerbal/memory/uninitialized/uninitialized_default_construct/uninitialized_default_construct.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_default_constructible.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>

#include <cstddef>

#if __cplusplus > 201703L
#	include <memory>
#endif


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0>		DFT_CNSTRCT_AT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		DFT_CNSTRCT_AT_VER_TRIVIALLY;

#	if __cplusplus <= 201703L

			template <typename T>
			T * default_construct_at_impl(T * p, DFT_CNSTRCT_AT_VER_DEFAULT)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(::new (const_cast<void*>(static_cast<const volatile void*>(p))) T)
					)
			{
				::new (const_cast<void*>(static_cast<const volatile void*>(p))) T;
				return p;
			}

#	else

			template <typename T>
			KERBAL_CONSTEXPR20
			T * default_construct_at_impl(T * p, DFT_CNSTRCT_AT_VER_DEFAULT)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(std::construct_at(p))
					)
			{
				std::construct_at(p);
				return p;
			}

#	endif

			template <typename T, std::size_t N>
			KERBAL_CONSTEXPR20
			T (* default_construct_at_impl(T (*p) [N], DFT_CNSTRCT_AT_VER_DEFAULT)) [N]
			{
				kerbal::memory::uninitialized_default_construct(*p + 0, *p + N);
				return p;
			}

			template <typename T>
			KERBAL_CONSTEXPR14
			T * default_construct_at_impl(T * p, DFT_CNSTRCT_AT_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
				return p;
			}

			template <typename T>
			struct default_construct_at_overload_version :
					kerbal::type_traits::conditional<
						kerbal::type_traits::try_test_is_trivially_default_constructible<T>::IS_TRUE::value,
						DFT_CNSTRCT_AT_VER_TRIVIALLY,
						DFT_CNSTRCT_AT_VER_DEFAULT
					>::type
			{
			};

		} // namespace detail

		template <typename T>
		KERBAL_CONSTEXPR14
		T * default_construct_at(T * p)
//				KERBAL_CONDITIONAL_NOEXCEPT(
//					noexcept(kerbal::memory::detail::default_construct_at_impl(p, kerbal::memory::detail::default_construct_at_overload_version<T>()))
//				)
		{
			typedef kerbal::memory::detail::default_construct_at_overload_version<T> VER;
			return kerbal::memory::detail::default_construct_at_impl(p, VER());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DETAIL_DEFAULT_CONSTRUCT_AT_DEFAULT_CONSTRUCT_AT_PART_HPP
