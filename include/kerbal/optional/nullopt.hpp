/**
 * @file       nullopt.hpp
 * @brief
 * @date       2018-10-28
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_NULLOPT_HPP_
#define KERBAL_OPTIONAL_NULLOPT_HPP_

#include <kerbal/compatibility/compatibility_macro.hpp>
#include <kerbal/optional/optional_settings.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/less_than_comparable.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

namespace kerbal
{
	namespace optional
	{

		struct nullopt_t:
				kerbal::operators::equality_comparable<nullopt_t>,
				kerbal::operators::less_than_comparable<nullopt_t>
		{
					KERBAL_CONSTEXPR bool operator==(const nullopt_t &) const KERBAL_NOEXCEPT
					{
						return true;
					}

					KERBAL_CONSTEXPR bool operator<(const nullopt_t &) const KERBAL_NOEXCEPT
					{
						return false;
					}
		};

#	if __cplusplus < 201103L
		extern const nullopt_t nullopt;
#	else
		constexpr const nullopt_t nullopt;
#	endif

		///@private
		template <typename Type>
		struct __is_nullopt_helper: kerbal::type_traits::false_type
		{
		};

		///@private
		template <>
		struct __is_nullopt_helper<kerbal::optional::nullopt_t > : kerbal::type_traits::true_type
		{
		};

#	if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_STD_OPTIONAL==1
		///@private
		template <>
		struct __is_nullopt_helper<std::nullopt_t > : kerbal::type_traits::true_type
		{
		};
#	endif

#	if KERBAL_OPTIONAL_ENABLE_SUPPORT_TO_BOOST_OPTIONAL==1
		///@private
		template <>
		struct __is_nullopt_helper<boost::none_t > : kerbal::type_traits::true_type
		{
		};
#	endif

		template <typename Type>
		struct is_nullopt: __is_nullopt_helper<typename kerbal::type_traits::remove_cv<Type>::type>
		{
		};

		///@private
		template <typename NulloptType, typename Ret>
		struct enable_if_is_nullopt:
				kerbal::type_traits::enable_if<kerbal::optional::is_nullopt<NulloptType>::value, Ret>
		{
		};

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator==(const kerbal::optional::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator!=(const kerbal::optional::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator<(const kerbal::optional::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator>(const kerbal::optional::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator<=(const kerbal::optional::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator>=(const kerbal::optional::nullopt_t &, const NulloptType &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator==(const NulloptType &, const kerbal::optional::nullopt_t &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator!=(const NulloptType &, const kerbal::optional::nullopt_t &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator<(const NulloptType &, const kerbal::optional::nullopt_t &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator>(const NulloptType &, const kerbal::optional::nullopt_t &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator<=(const NulloptType &, const kerbal::optional::nullopt_t &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename NulloptType>
		KERBAL_CONSTEXPR
		typename enable_if_is_nullopt<NulloptType, bool>::type
		operator>=(const NulloptType &, const kerbal::optional::nullopt_t &) KERBAL_NOEXCEPT
		{
			return true;
		}


	} /* namespace optional */

} /* namespace kerbal */


#endif /* KERBAL_OPTIONAL_NULLOPT_HPP_ */
