/**
 * @file       destroy_on.part.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DETAIL_DESTROY_ON_DESTROY_ON_PART_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DETAIL_DESTROY_ON_DESTROY_ON_PART_HPP

#include <kerbal/memory/uninitialized/reverse_destroy/reverse_destroy.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_destructible.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0>		DESTROY_ON_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		DESTROY_ON_VER_TRIVIALLY;

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void destroy_on_impl(Tp & plc, DESTROY_ON_VER_DEFAULT)
					KERBAL_CONDITIONAL_NOEXCEPT(
						kerbal::type_traits::try_test_is_nothrow_destructible<Tp>::IS_TRUE::value
					)
			{
				plc.~Tp();
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR20
			void destroy_on_impl(Tp (& plc) [N], DESTROY_ON_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				kerbal::memory::reverse_destroy(plc + 0, plc + N);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void destroy_on_impl(Tp & /*plc*/, DESTROY_ON_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
			}

			template <typename Tp>
			struct destroy_on_overload_version :
					kerbal::type_traits::conditional<
						kerbal::type_traits::try_test_is_trivially_destructible<Tp>::IS_TRUE::value,
						DESTROY_ON_VER_TRIVIALLY,
						DESTROY_ON_VER_DEFAULT
					>::type
			{
			};

		} // namespace detail

		template <typename Tp>
		KERBAL_CONSTEXPR14
		void destroy_on(Tp & plc)
		{
			typedef kerbal::memory::detail::destroy_on_overload_version<Tp> VER;
			kerbal::memory::detail::destroy_on_impl(plc, VER());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DETAIL_DESTROY_ON_DESTROY_ON_PART_HPP
