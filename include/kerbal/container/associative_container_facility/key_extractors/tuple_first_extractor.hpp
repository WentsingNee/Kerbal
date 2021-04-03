/**
 * @file       tuple_first_extractor.hpp
 * @brief
 * @date       2020-10-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_TUPLE_FIRST_EXTRACTOR_HPP
#define KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_TUPLE_FIRST_EXTRACTOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/detail/tuple_first_extractor_has_first_data_member.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/detail/tuple_first_extractor_has_first_member_function.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus >= 201103L
#	include <tuple>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> TFE_VER_USE_FIRST_DATA_MEMBER;
			typedef kerbal::type_traits::integral_constant<int, 1> TFE_VER_USE_FIRST_MEMBER_FUNCTION;
			typedef kerbal::type_traits::integral_constant<int, 2> TFE_VER_USE_STD_GET_0;


			template <typename ValueType>
			struct tuple_first_extractor_policy
			{
					typedef typename kerbal::type_traits::conditional<
						kerbal::container::detail::tuple_first_extractor_has_first_data_member<ValueType>::value,
						TFE_VER_USE_FIRST_DATA_MEMBER,
						typename kerbal::type_traits::conditional<
							kerbal::container::detail::tuple_first_extractor_has_first_member_function<ValueType>::value,
							TFE_VER_USE_FIRST_MEMBER_FUNCTION,
							TFE_VER_USE_STD_GET_0
						>::type
					>::type result;
			};


			struct tuple_first_extractor_helper
			{
				private:
					template <typename KeyType, typename ValueType>
					KERBAL_CONSTEXPR
					static KeyType & k_extract(ValueType & t, TFE_VER_USE_FIRST_DATA_MEMBER) KERBAL_NOEXCEPT
					{
						return t.first;
					}

					template <typename KeyType, typename ValueType>
					KERBAL_CONSTEXPR
					static KeyType & k_extract(ValueType & t, TFE_VER_USE_FIRST_MEMBER_FUNCTION) KERBAL_NOEXCEPT
					{
						return t.first();
					}

#		if __cplusplus >= 201103L

					template <typename KeyType, typename ValueType>
					KERBAL_CONSTEXPR
					static KeyType & k_extract(ValueType & t, TFE_VER_USE_STD_GET_0) KERBAL_NOEXCEPT
					{
						return std::get<0>(t);
					}

#		endif

				public:
					template <typename KeyType, typename ValueType>
					KERBAL_CONSTEXPR
					static KeyType & k_extract(ValueType & t) KERBAL_NOEXCEPT
					{
						typedef typename tuple_first_extractor_policy<ValueType>::result VER;
						return k_extract<KeyType>(t, VER());
					}
			};

		} // namespace detail


		template <typename Tuple, typename Key>
		struct tuple_first_extractor;

		template <typename Tuple, typename Key>
		struct tuple_first_extractor
		{
				typedef Tuple value_type;
				typedef Key key_type;

				KERBAL_CONSTEXPR
				key_type & operator()(value_type & p) const KERBAL_NOEXCEPT
				{
					return kerbal::container::detail::tuple_first_extractor_helper::k_extract<key_type>(p);
				}

				KERBAL_CONSTEXPR
				const key_type & operator()(const value_type & p) const KERBAL_NOEXCEPT
				{
					return kerbal::container::detail::tuple_first_extractor_helper::k_extract<const key_type>(p);
				}
		};

		template <typename Tuple, typename Key>
		struct tuple_first_extractor<const Tuple, Key>
		{
				typedef const Tuple value_type;
				typedef Key key_type;

				KERBAL_CONSTEXPR
				const key_type & operator()(value_type & p) const KERBAL_NOEXCEPT
				{
					return kerbal::container::detail::tuple_first_extractor_helper::k_extract<const key_type>(p);
				}
		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_KEY_EXTRACTORS_TUPLE_FIRST_EXTRACTOR_HPP
