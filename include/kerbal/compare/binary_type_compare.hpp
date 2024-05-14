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

#include <kerbal/compare/sequence_compare/sequence_compare.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/macro/macro_concat.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_array.hpp>
#include <kerbal/type_traits/remove_reference.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/declval.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace compare
	{

#define DEF_FWD(NAME) \
		template <typename T, typename U> \
		struct KERBAL_MACRO_CONCAT(binary_type_, NAME);


#define DEF_PLAIN(NAME, OP) \
		template <typename T, typename U> \
		struct KERBAL_MACRO_CONCAT(binary_type_, NAME) \
		{ \
				KERBAL_CONSTEXPR \
				bool operator()(const T & lhs, const U & rhs) const \
						KERBAL_CONDITIONAL_NOEXCEPT( \
								noexcept(static_cast<bool>(lhs OP rhs)) \
						) \
				{ \
					KERBAL_STATIC_ASSERT( \
						!( \
							kerbal::type_traits::is_array<T>::value && \
							kerbal::type_traits::is_array<U>::value \
						), \
						"comparison between two arrays" \
					); \
					return static_cast<bool>(lhs OP rhs); \
				} \
		};


#	if __cplusplus < 201103L

#define DEF_VOID_1(NAME, OP) \
		template <typename U> \
		struct KERBAL_MACRO_CONCAT(binary_type_, NAME)<void, U> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename T> \
				bool operator()(const T & lhs, const U & rhs) const \
				{ \
					return static_cast<bool>(KERBAL_MACRO_CONCAT(binary_type_, NAME)<T, U>()(lhs, rhs)); \
				} \
		};

#	else

#define DEF_VOID_1(NAME, OP) \
		template <typename U> \
		struct KERBAL_MACRO_CONCAT(binary_type_, NAME)<void, U> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
			private: \
				template <typename T> \
				struct is_nothrow_invokable_helper \
				{ \
						typedef typename kerbal::type_traits::remove_reference<T>::type TRRef; \
						typedef kerbal::type_traits::bool_constant<noexcept(static_cast<bool>( \
							KERBAL_MACRO_CONCAT(binary_type_, NAME)<TRRef, U>()( \
								kerbal::utility::declval<T &&>(), kerbal::utility::declval<const U &>() \
							) \
						))> type; \
				}; \
 \
			public: \
				template <typename T> \
				struct is_nothrow_invokable : is_nothrow_invokable_helper<T>::type \
				{ \
				}; \
 \
				template <typename T> \
				KERBAL_CONSTEXPR \
				bool operator()(T && lhs, const U & rhs) const \
						KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_invokable<T>::value) \
				{ \
					typedef typename kerbal::type_traits::remove_reference<T>::type TRRef; \
					return static_cast<bool>(KERBAL_MACRO_CONCAT(binary_type_, NAME)<TRRef, U>()(kerbal::utility::forward<T>(lhs), rhs)); \
				} \
		};

#	endif


#	if __cplusplus < 201103L

#define DEF_VOID_2(NAME, OP) \
		template <typename T> \
		struct KERBAL_MACRO_CONCAT(binary_type_, NAME)<T, void> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename U> \
				bool operator()(const T & lhs, const U & rhs) const \
				{ \
					return static_cast<bool>(KERBAL_MACRO_CONCAT(binary_type_, NAME)<T, U>()(lhs, rhs)); \
				} \
		};

#	else

#define DEF_VOID_2(NAME, OP) \
		template <typename T> \
		struct KERBAL_MACRO_CONCAT(binary_type_, NAME)<T, void> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
			private: \
				template <typename U> \
				struct is_nothrow_invokable_helper \
				{ \
						typedef typename kerbal::type_traits::remove_reference<U>::type URRef; \
						typedef kerbal::type_traits::bool_constant<noexcept(static_cast<bool>( \
							KERBAL_MACRO_CONCAT(binary_type_, NAME)<T, URRef>()( \
								kerbal::utility::declval<const T &>(), kerbal::utility::declval<U &&>() \
							) \
						))> type; \
				}; \
 \
			public: \
				template <typename U> \
				struct is_nothrow_invokable : is_nothrow_invokable_helper<U>::type \
				{ \
				}; \
 \
				template <typename U> \
				KERBAL_CONSTEXPR \
				bool operator()(const T & lhs, U && rhs) const \
						KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_invokable<U>::value) \
				{ \
					typedef typename kerbal::type_traits::remove_reference<U>::type URRef; \
					return static_cast<bool>(KERBAL_MACRO_CONCAT(binary_type_, NAME)<T, URRef>()(lhs, kerbal::utility::forward<U>(rhs))); \
				} \
		};

#	endif


#	if __cplusplus < 201103L

#define DEF_VOID_3(NAME, OP) \
		template <> \
		struct KERBAL_MACRO_CONCAT(binary_type_, NAME)<void, void> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename T, typename U> \
				bool operator()(const T & lhs, const U & rhs) const \
				{ \
					return static_cast<bool>(KERBAL_MACRO_CONCAT(binary_type_, NAME)<T, U>()(lhs, rhs)); \
				} \
		};

#	else

#define DEF_VOID_3(NAME, OP) \
		template <> \
		struct KERBAL_MACRO_CONCAT(binary_type_, NAME)<void, void> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
			private: \
				template <typename T, typename U> \
				struct is_nothrow_invokable_helper \
				{ \
						typedef typename kerbal::type_traits::remove_reference<T>::type TRRef; \
						typedef typename kerbal::type_traits::remove_reference<U>::type URRef; \
						typedef kerbal::type_traits::bool_constant<noexcept(static_cast<bool>( \
							KERBAL_MACRO_CONCAT(binary_type_, NAME)<TRRef, URRef>()( \
								kerbal::utility::declval<T &&>(), kerbal::utility::declval<U &&>() \
							) \
						))> type; \
				}; \
 \
			public: \
				template <typename T, typename U> \
				struct is_nothrow_invokable : is_nothrow_invokable_helper<T, U>::type \
				{ \
				}; \
 \
				template <typename T, typename U> \
				KERBAL_CONSTEXPR \
				bool operator()(T && lhs, U && rhs) const \
						KERBAL_CONDITIONAL_NOEXCEPT((is_nothrow_invokable<T, U>::value)) \
				{ \
					typedef typename kerbal::type_traits::remove_reference<T>::type TRRef; \
					typedef typename kerbal::type_traits::remove_reference<U>::type URRef; \
					return static_cast<bool>(KERBAL_MACRO_CONCAT(binary_type_, NAME)<TRRef, URRef>()(kerbal::utility::forward<T>(lhs), kerbal::utility::forward<U>(rhs))); \
				} \
		};

#	endif


#	define DEF_ARRAY_SPEC(NAME) \
		template <typename T, typename U, std::size_t N> \
		struct KERBAL_MACRO_CONCAT(binary_type_, NAME)<T[N], U[N]> \
		{ \
				KERBAL_CONSTEXPR14 \
				bool operator()(const T (&lhs)[N], const U (&rhs)[N]) const \
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept( \
							static_cast<bool>(kerbal::compare::KERBAL_MACRO_CONCAT(sequence_, NAME)(lhs, rhs, KERBAL_MACRO_CONCAT(binary_type_, NAME)<T, U>())) \
						)) \
				{ \
					return static_cast<bool>(kerbal::compare::KERBAL_MACRO_CONCAT(sequence_, NAME)(lhs, rhs, KERBAL_MACRO_CONCAT(binary_type_, NAME)<T, U>())); \
				} \
		};


#	define DEF(NAME, OP) \
		DEF_FWD(NAME) \
		DEF_PLAIN(NAME, OP) \
		DEF_VOID_1(NAME, OP) \
		DEF_VOID_2(NAME, OP) \
		DEF_VOID_3(NAME, OP) \
		DEF_ARRAY_SPEC(NAME)

		DEF(equal_to, ==)
		DEF(not_equal_to, !=)
		DEF(less, <)
		DEF(less_equal, <=)
		DEF(greater, >)
		DEF(greater_equal, >=)


#	undef DEF_FWD
#	undef DEF_PLAIN
#	undef DEF_VOID_1
#	undef DEF_VOID_2
#	undef DEF_VOID_3
#	undef DEF_ARRAY_SPEC
#	undef DEF


	} // namespace compare

} // namespace kerbal

#endif // KERBAL_COMPARE_BINARY_TYPE_COMPARE_HPP
