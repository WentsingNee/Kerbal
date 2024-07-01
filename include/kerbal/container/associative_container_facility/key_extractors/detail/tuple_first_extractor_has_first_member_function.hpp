/**
 * @file       tuple_first_extractor_has_first_member_function.hpp
 * @brief
 * @date       2023-06-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_DETAIL_TUPLE_FIRST_EXTRACTOR_HAS_FIRST_MEMBER_FUNCTION_HPP
#define KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_DETAIL_TUPLE_FIRST_EXTRACTOR_HAS_FIRST_MEMBER_FUNCTION_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/yes_no_type.hpp>
#include <kerbal/utility/declval.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename ValueType>
			struct tuple_first_extractor_has_first_member_function_helper
			{
				private:
					template <typename ValueType2>
					static kerbal::type_traits::no_type test(...);

#if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC

					template <typename ValueType2>
					static kerbal::type_traits::yes_type test(char(*)[sizeof(
							kerbal::utility::declval<ValueType2>().first(),
							0
					)]);

#else

					template <typename ValueType2>
					static kerbal::type_traits::yes_type test(char *, decltype(
							kerbal::utility::declval<ValueType2>().first(),
							0
					) = 0);

#endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<ValueType>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;
			};

			template <typename ValueType>
			struct tuple_first_extractor_has_first_member_function:
					kerbal::container::detail::tuple_first_extractor_has_first_member_function_helper<ValueType>::type
			{
			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_DETAIL_TUPLE_FIRST_EXTRACTOR_HAS_FIRST_MEMBER_FUNCTION_HPP
