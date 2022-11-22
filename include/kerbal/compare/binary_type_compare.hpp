/**
 * @file       binary_type_compare.hpp
 * @brief
 * @date       2018-9-7
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPARE_BINARY_TYPE_COMPARE_HPP
#define KERBAL_COMPARE_BINARY_TYPE_COMPARE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

namespace kerbal
{

	namespace compare
	{

#define DEF_FWD(NAME) \
		template <typename T, typename U> \
		struct NAME;


#define DEF_PLAIN(NAME, OP) \
		template <typename T, typename U> \
		struct NAME \
		{ \
				KERBAL_CONSTEXPR \
				bool operator()(const T & lhs, const U & rhs) const \
						KERBAL_CONDITIONAL_NOEXCEPT( \
								noexcept(static_cast<bool>(lhs OP rhs)) \
						) \
				{ \
					return static_cast<bool>(lhs OP rhs); \
				} \
		};


#	if __cplusplus < 201103L

#define DEF_VOID_1(NAME, OP) \
		template <typename U> \
		struct NAME<void, U> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename T> \
				bool operator()(const T & lhs, const U & rhs) const \
				{ \
					return static_cast<bool>(lhs OP rhs); \
				} \
		};

#	else

#define DEF_VOID_1(NAME, OP) \
		template <typename U> \
		struct NAME<void, U> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename T> \
				KERBAL_CONSTEXPR \
				bool operator()(T && lhs, const U & rhs) const \
						KERBAL_CONDITIONAL_NOEXCEPT( \
							noexcept(static_cast<bool>(kerbal::utility::forward<T>(lhs) OP rhs)) \
						) \
				{ \
					return static_cast<bool>(kerbal::utility::forward<T>(lhs) OP rhs); \
				} \
		};

#	endif


#	if __cplusplus < 201103L

#define DEF_VOID_2(NAME, OP) \
		template <typename T> \
		struct NAME<T, void> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename U> \
				bool operator()(const T & lhs, const U & rhs) const \
				{ \
					return static_cast<bool>(lhs OP rhs); \
				} \
		};

#	else

#define DEF_VOID_2(NAME, OP) \
		template <typename T> \
		struct NAME<T, void> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename U> \
				KERBAL_CONSTEXPR \
				bool operator()(const T & lhs, U && rhs) const \
						KERBAL_CONDITIONAL_NOEXCEPT( \
							noexcept(static_cast<bool>(lhs OP kerbal::utility::forward<U>(rhs))) \
						) \
				{ \
					return static_cast<bool>(lhs OP kerbal::utility::forward<U>(rhs)); \
				} \
		};

#	endif


#	if __cplusplus < 201103L

#define DEF_VOID_3(NAME, OP) \
		template <> \
		struct NAME<void, void> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename T, typename U> \
				bool operator()(const T & lhs, const U & rhs) const \
				{ \
					return static_cast<bool>(lhs OP rhs); \
				} \
		};

#	else

#define DEF_VOID_3(NAME, OP) \
		template <> \
		struct NAME<void, void> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename T, typename U> \
				KERBAL_CONSTEXPR \
				bool operator()(T && lhs, U && rhs) const \
						KERBAL_CONDITIONAL_NOEXCEPT( \
							noexcept(static_cast<bool>(kerbal::utility::forward<T>(lhs) OP kerbal::utility::forward<U>(rhs))) \
						) \
				{ \
					return static_cast<bool>(kerbal::utility::forward<T>(lhs) OP kerbal::utility::forward<U>(rhs)); \
				} \
		};

#	endif


#	define DEF(NAME, OP) \
		DEF_FWD(NAME) \
		DEF_PLAIN(NAME, OP) \
		DEF_VOID_1(NAME, OP) \
		DEF_VOID_2(NAME, OP) \
		DEF_VOID_3(NAME, OP)

		DEF(binary_type_equal_to, ==)
		DEF(binary_type_not_equal_to, !=)
		DEF(binary_type_less, <)
		DEF(binary_type_less_equal, <=)
		DEF(binary_type_greater, >)
		DEF(binary_type_greater_equal, >=)

#	undef DEF_FWD
#	undef DEF_PLAIN
#	undef DEF_VOID_1
#	undef DEF_VOID_2
#	undef DEF_VOID_3
#	undef DEF


	} // namespace compare

} // namespace kerbal

#endif // KERBAL_COMPARE_BINARY_TYPE_COMPARE_HPP
