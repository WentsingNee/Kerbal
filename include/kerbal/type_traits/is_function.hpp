/**
 * @file       is_function.hpp
 * @brief
 * @date       2019-6-25
 * @author     Peter
 * @remark     renamed from function_deduction.hpp
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_IS_FUNCTION_HPP
#define KERBAL_TYPE_TRAITS_IS_FUNCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus < 201103L
#	include <kerbal/type_traits/is_const.hpp>
#endif


namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename >
		struct is_function : kerbal::type_traits::false_type {};

#	define EMPTY
#	define VAR_LIST ,...

#	define IS_FUNCTION_VAR_LIST_DEF(VAR_L, CV_QUALIFIER, REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		KERBAL_MODULE_EXPORT \
		template <typename Ret, typename ... Args> \
		struct is_function<Ret(Args... VAR_L) CV_QUALIFIER REF_QUALIFIER NOEXCEPT_QUALIFIER> : kerbal::type_traits::true_type {}; \

#	define IS_FUNCTION_CV_DEF(CV_QUALIFIER, REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_VAR_LIST_DEF(EMPTY,    CV_QUALIFIER, REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_VAR_LIST_DEF(VAR_LIST, CV_QUALIFIER, REF_QUALIFIER, NOEXCEPT_QUALIFIER)

#	define IS_FUNCTION_REF_DEF(REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_CV_DEF(EMPTY,          REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_CV_DEF(const,          REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_CV_DEF(volatile,       REF_QUALIFIER, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_CV_DEF(const volatile, REF_QUALIFIER, NOEXCEPT_QUALIFIER)

#	define IS_FUNCTION_NOEXCEPT_DEF(NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_REF_DEF(EMPTY, NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_REF_DEF(&,     NOEXCEPT_QUALIFIER) \
		IS_FUNCTION_REF_DEF(&&,    NOEXCEPT_QUALIFIER)


		IS_FUNCTION_NOEXCEPT_DEF(EMPTY)
#	if __cpp_noexcept_function_type >= 201510L
		IS_FUNCTION_NOEXCEPT_DEF(noexcept)
#	endif

#	undef EMPTY
#	undef VAR_LIST
#	undef IS_FUNCTION_VAR_LIST_DEF
#	undef IS_FUNCTION_CV_DEF
#	undef IS_FUNCTION_REF_DEF
#	undef IS_FUNCTION_NOEXCEPT_DEF

#	else

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_function :
				kerbal::type_traits::bool_constant<
					!kerbal::type_traits::is_const<const T>::value
				>
		{
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_function<T &> :
				kerbal::type_traits::false_type
		{
		};

#	endif

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_IS_FUNCTION_HPP
