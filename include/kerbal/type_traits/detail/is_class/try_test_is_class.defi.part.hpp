/**
 * @file       try_test_is_class.defi.part.hpp
 * @brief
 * @date       2023-04-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DETAIL_IS_CLASS_TRY_TEST_IS_CLASS_DEFI_PART_HPP
#define KERBAL_TYPE_TRAITS_DETAIL_IS_CLASS_TRY_TEST_IS_CLASS_DEFI_PART_HPP

#include <kerbal/type_traits/detail/is_class/is_class.part.hpp>

#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct try_test_is_class :
			kerbal::type_traits::tribool_constant<
				!!kerbal::type_traits::is_class<T>::value
			>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_DETAIL_IS_CLASS_TRY_TEST_IS_CLASS_DEFI_PART_HPP
