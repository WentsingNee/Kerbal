/**
 * @file       try_test_is_base_of.defi.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_TRY_TEST_IS_BASE_OF_DEFI_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_TRY_TEST_IS_BASE_OF_DEFI_PART_HPP

#include <kerbal/type_traits/detail/is_base_of/is_base_of.part.hpp>

#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename Base, typename Derived>
		struct try_test_is_base_of :
				kerbal::type_traits::tribool_constant<
					!!kerbal::type_traits::is_base_of<Base, Derived>::value
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_BASE_OF_TRY_TEST_IS_BASE_OF_DEFI_PART_HPP
