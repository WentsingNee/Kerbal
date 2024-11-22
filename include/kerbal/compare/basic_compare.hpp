/**
 * @file       basic_compare.hpp
 * @brief
 * @date       2021-11-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPARE_BASIC_COMPARE_HPP
#define KERBAL_COMPARE_BASIC_COMPARE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_array.hpp>

#if __cplusplus >= 201103L

#	include <kerbal/compatibility/static_assert.hpp>
#	include <kerbal/type_traits/is_same.hpp>
#	include <kerbal/type_traits/remove_cvref.hpp>
#	include <kerbal/utility/forward.hpp>

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
#		include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#		include <kerbal/utility/declval.hpp>
#	endif

#endif

#include <cstddef>


namespace kerbal
{

	namespace compare
	{

#define DEF_FWD(NAME) \
		KERBAL_MODULE_EXPORT \
		template <typename T = void> \
		struct NAME; \


#define DEF_PLAIN(NAME, OP) \
		KERBAL_MODULE_EXPORT \
		template <typename T> \
		struct NAME \
		{ \
				KERBAL_CONSTEXPR \
				bool operator()(const T & lhs, const T & rhs) const \
					KERBAL_CONDITIONAL_NOEXCEPT( \
						noexcept(static_cast<bool>(lhs OP rhs)) \
					) \
				{ \
					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_array<T>::value, "comparison between two arrays"); \
					return static_cast<bool>(lhs OP rhs); \
				} \
		}; \


#	if __cplusplus < 201103L

#define DEF_VOID(NAME, OP) \
		/*KERBAL_MODULE_EXPORT*/ \
		template <> \
		struct NAME<void> \
		{ \
 \
				typedef kerbal::type_traits::true_type is_transparent; \
 \
				template <typename T> \
				bool operator()(const T & lhs, const T & rhs) const \
				{ \
					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_array<T>::value, "comparison between two arrays"); \
					return static_cast<bool>(lhs OP rhs); \
				} \
		}; \

#	else

#define DEF_VOID(NAME, OP) \
		/*KERBAL_MODULE_EXPORT*/ \
		template <> \
		struct NAME<void> \
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
					typedef typename kerbal::type_traits::remove_cvref<T>::type T0; \
					typedef typename kerbal::type_traits::remove_cvref<U>::type U0; \
					KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<T0, U0>::value), "lhs and rhs must be same type"); \
					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_array<T0>::value, "comparison between two arrays"); \
					return static_cast<bool>(kerbal::utility::forward<T>(lhs) OP kerbal::utility::forward<U>(rhs)); \
				} \
		}; \

#	endif


#	define DEF(NAME, OP) \
		DEF_FWD(NAME) \
		DEF_PLAIN(NAME, OP) \
		DEF_VOID(NAME, OP)

		DEF(equal_to, ==)
		DEF(not_equal_to, !=)
		DEF(less, <)
		DEF(less_equal, <=)
		DEF(greater, >)
		DEF(greater_equal, >=)

#	undef DEF_FWD
#	undef DEF_PLAIN
#	undef DEF_ARR
#	undef DEF_VOID
#	undef DEF


		/*KERBAL_MODULE_EXPORT*/
		template <typename T, std::size_t N>
		struct equal_to<T[N]>
		{

			private:
				typedef kerbal::compare::equal_to<T> ValuePredict;

#	if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				typedef kerbal::type_traits::bool_constant<
					kerbal::type_traits::try_test_is_nothrow_default_constructible<ValuePredict>::IS_TRUE::value &&
					noexcept(
						kerbal::utility::declval<ValuePredict>()(
							kerbal::utility::declval<T>(), kerbal::utility::declval<T>()
						)
					)
				> IS_NOTHROW_COMPARABLE;

#	endif

			public:
				KERBAL_CONSTEXPR14
				bool operator()(const T (& lhs)[N], const T (& rhs)[N]) const
					KERBAL_CONDITIONAL_NOEXCEPT(IS_NOTHROW_COMPARABLE::value)
				{
					ValuePredict pred;
					for (std::size_t i = 0; i < N; ++i) {
						if (pred(lhs[i], rhs[i])) { // namely lhs[i] == rhs[i]
							continue;
						} else {
							return false;
						}
					}
					return true;
				}
		};


		/*KERBAL_MODULE_EXPORT*/
		template <typename T, std::size_t N>
		struct not_equal_to<T[N]>
		{

			private:
				typedef kerbal::compare::not_equal_to<T> ValuePredict;

#	if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				typedef kerbal::type_traits::bool_constant<
					kerbal::type_traits::try_test_is_nothrow_default_constructible<ValuePredict>::IS_TRUE::value &&
					noexcept(
						kerbal::utility::declval<ValuePredict>()(
							kerbal::utility::declval<T>(), kerbal::utility::declval<T>()
						)
					)
				> IS_NOTHROW_COMPARABLE;

#	endif

			public:
				KERBAL_CONSTEXPR14
				bool operator()(const T (& lhs)[N], const T (& rhs)[N]) const
					KERBAL_CONDITIONAL_NOEXCEPT(IS_NOTHROW_COMPARABLE::value)
				{
					ValuePredict pred;
					for (std::size_t i = 0; i < N; ++i) {
						if (pred(lhs[i], rhs[i])) { // namely lhs[i] != rhs[i]
							return true;
						} else {
							continue;
						}
					}
					return false;
				}
		};


		/*KERBAL_MODULE_EXPORT*/
		template <typename T, std::size_t N>
		struct less<T[N]>
		{

			private:
				typedef kerbal::compare::less<T> ValuePredict;

#	if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				typedef kerbal::type_traits::bool_constant<
					kerbal::type_traits::try_test_is_nothrow_default_constructible<ValuePredict>::IS_TRUE::value &&
					noexcept(
						kerbal::utility::declval<ValuePredict>()(
							kerbal::utility::declval<T>(), kerbal::utility::declval<T>()
						)
					)
				> IS_NOTHROW_COMPARABLE;

#	endif

			public:
				KERBAL_CONSTEXPR14
				bool operator()(const T (& lhs)[N], const T (& rhs) [N]) const
					KERBAL_CONDITIONAL_NOEXCEPT(IS_NOTHROW_COMPARABLE::value)
				{
					ValuePredict pred;
					for (std::size_t i = 0; i < N; ++i) {
						if (pred(lhs[i], rhs[i])) { // namely lhs[i] < rhs[i]
							return true;
						} else if (pred(rhs[i], lhs[i])) { // namely rhs[i] < lhs[i]
							return false;
						} else {
							continue;
						}
					}
					return false;
				}
		};


		/*KERBAL_MODULE_EXPORT*/
		template <typename T, std::size_t N>
		struct greater<T[N]>
		{

			private:
				typedef kerbal::compare::greater<T> ValuePredict;

#	if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				typedef kerbal::type_traits::bool_constant<
					kerbal::type_traits::try_test_is_nothrow_default_constructible<ValuePredict>::IS_TRUE::value &&
					noexcept(
						kerbal::utility::declval<ValuePredict>()(
							kerbal::utility::declval<T>(), kerbal::utility::declval<T>()
						)
					)
				> IS_NOTHROW_COMPARABLE;

#	endif

			public:
				KERBAL_CONSTEXPR14
				bool operator()(const T (& lhs)[N], const T (& rhs)[N]) const
					KERBAL_CONDITIONAL_NOEXCEPT(IS_NOTHROW_COMPARABLE::value)
				{
					ValuePredict pred;
					for (std::size_t i = 0; i < N; ++i) {
						if (pred(lhs[i], rhs[i])) { // namely lhs[i] > rhs[i]
							return true;
						} else if (pred(rhs[i], lhs[i])) { // namely rhs[i] > lhs[i]
							return false;
						} else {
							continue;
						}
					}
					return false;
				}
		};


		/*KERBAL_MODULE_EXPORT*/
		template <typename T, std::size_t N>
		struct less_equal<T[N]>
		{

			private:
				typedef kerbal::compare::less_equal<T> ValuePredict;

#	if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				typedef kerbal::type_traits::bool_constant<
					kerbal::type_traits::try_test_is_nothrow_default_constructible<ValuePredict>::IS_TRUE::value &&
					noexcept(
						kerbal::utility::declval<ValuePredict>()(
							kerbal::utility::declval<T>(), kerbal::utility::declval<T>()
						)
					)
				> IS_NOTHROW_COMPARABLE;

#	endif

			public:
				KERBAL_CONSTEXPR14
				bool operator()(const T (& lhs)[N], const T (& rhs)[N]) const
					KERBAL_CONDITIONAL_NOEXCEPT(IS_NOTHROW_COMPARABLE::value)
				{
					ValuePredict pred;
					for (std::size_t i = 0; i < N; ++i) {
						if (pred(lhs[i], rhs[i])) { // namely lhs[i] <= rhs[i]
							if (pred(rhs[i], lhs[i])) { // namely lhs[i] >= rhs[i]
								// namely lhs[i] == rhs[i]
								continue;
							} else { // namely lhs[i] < rhs[i]
								return true;
							}
						} else { // namely lhs[i] > rhs[i]
							return false;
						}
					}
					return true;
				}
		};


		/*KERBAL_MODULE_EXPORT*/
		template <typename T, std::size_t N>
		struct greater_equal<T[N]>
		{

			private:
				typedef kerbal::compare::greater_equal<T> ValuePredict;

#	if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				typedef kerbal::type_traits::bool_constant<
					kerbal::type_traits::try_test_is_nothrow_default_constructible<ValuePredict>::IS_TRUE::value &&
					noexcept(
						kerbal::utility::declval<ValuePredict>()(
							kerbal::utility::declval<T>(), kerbal::utility::declval<T>()
						)
					)
				> IS_NOTHROW_COMPARABLE;

#	endif

			public:
				KERBAL_CONSTEXPR14
				bool operator()(const T (& lhs)[N], const T (& rhs)[N]) const
					KERBAL_CONDITIONAL_NOEXCEPT(IS_NOTHROW_COMPARABLE::value)
				{
					ValuePredict pred;
					for (std::size_t i = 0; i < N; ++i) {
						if (pred(lhs[i], rhs[i])) { // namely lhs[i] >= rhs[i]
							if (pred(rhs[i], lhs[i])) { // namely lhs[i] <= rhs[i]
								// namely lhs[i] == rhs[i]
								continue;
							} else { // namely lhs[i] > rhs[i]
								return true;
							}
						} else { // namely lhs[i] < rhs[i]
							return false;
						}
					}
					return true;
				}
		};

	} // namespace compare

} // namespace kerbal

#endif // KERBAL_COMPARE_BASIC_COMPARE_HPP
