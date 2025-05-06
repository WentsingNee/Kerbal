/**
 * @file       pointer_rank.hpp
 * @brief
 * @date       2022-10-30
 * @author     Peter
 * @remark     split up from kerbal/type_traits/pointer_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_POINTER_RANK_HPP
#define KERBAL_TYPE_TRAITS_POINTER_RANK_HPP


#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_pointer.hpp>
#include <kerbal/type_traits/remove_pointer.hpp>

#include <cstddef>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct pointer_rank;

		namespace detail
		{

			template <typename T, bool IsPointer>
			struct pointer_rank_helper;

			template <typename T>
			struct pointer_rank_helper<T, true>:
				kerbal::type_traits::integral_constant<
					std::size_t,
					1 + kerbal::type_traits::pointer_rank<
						typename kerbal::type_traits::remove_pointer<T>::type
					>::value
				>
			{
			};

			template <typename T>
			struct pointer_rank_helper<T, false>:
				kerbal::type_traits::integral_constant<
					std::size_t,
					0
				>
			{
			};

		} // namespace detail

		template <typename T>
		struct pointer_rank :
			kerbal::type_traits::detail::pointer_rank_helper<
				T, kerbal::type_traits::is_pointer<T>::value
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_POINTER_RANK_HPP
