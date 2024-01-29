/**
 * @file       member_compress_helper.array.part.hpp
 * @brief
 * @date       2020-09-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_ARRAY_PART_HPP
#define KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_ARRAY_PART_HPP

#include <kerbal/utility/member_compress_helper/member_compress_helper.fwd.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/add_lvalue_reference.hpp>
#include <kerbal/type_traits/add_const_lvalue_reference.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/add_rvalue_reference.hpp>
#	include <kerbal/type_traits/add_const_rvalue_reference.hpp>
#	include <kerbal/type_traits/is_nothrow_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#	include <kerbal/type_traits/tribool_constant.hpp>
#	include <kerbal/utility/integer_sequence.hpp>
#else
#	include <kerbal/algorithm/modifier/copy.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

#		if __cplusplus >= 201103L

		namespace detail
		{

			template <typename T, typename ... Args>
			struct member_compress_helper_array_try_test_is_nothrow_in_place_constructible_helper :
				kerbal::type_traits::tribool_unspecified
			{
			};

			template <typename T>
			struct member_compress_helper_array_try_test_is_nothrow_in_place_constructible_helper<T> :
				kerbal::type_traits::try_test_is_nothrow_default_constructible<T>
			{
			};

			template <typename T, typename U, std::size_t N>
			struct member_compress_helper_array_try_test_is_nothrow_in_place_constructible_helper<T, const U (&)[N]> :
				kerbal::type_traits::try_test_is_nothrow_constructible<T, const U &>
			{
			};

			template <typename T, typename U, std::size_t N>
			struct member_compress_helper_array_try_test_is_nothrow_in_place_constructible_helper<T, U (&&)[N]> :
				kerbal::type_traits::try_test_is_nothrow_constructible<T, U &&>
			{
			};

			template <typename T, typename U>
			struct member_compress_helper_array_try_test_is_nothrow_in_place_constructible_helper<T, std::initializer_list<U> > :
				kerbal::type_traits::try_test_is_nothrow_constructible<T, const U &>
			{
			};

		};

#		endif


		template <typename T, std::size_t I, std::size_t N>
		class member_compress_helper<T[N], I>
		{
			public:
				T k_member[N];

			public:
				typedef kerbal::type_traits::false_type IS_COMPRESSED;

				typedef T value_type[N];
				typedef typename kerbal::type_traits::add_lvalue_reference<value_type>::type			reference;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<value_type>::type		const_reference;

#		if __cplusplus >= 201103L
				typedef typename kerbal::type_traits::add_rvalue_reference<value_type>::type			rvalue_reference;
				typedef typename kerbal::type_traits::add_const_rvalue_reference<value_type>::type		const_rvalue_reference;
#		endif

			public:

#		if __cplusplus >= 201103L

				member_compress_helper() = default;

#		else

				member_compress_helper()
				{
				}

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				struct try_test_is_nothrow_in_place_constructible_helper :
					detail::member_compress_helper_array_try_test_is_nothrow_in_place_constructible_helper<T, Args...>
				{
				};

#		endif

				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t in_place)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_in_place_constructible_helper<>::IS_TRUE::value
					)
				{
				}


#		if __cplusplus >= 201103L

			private:

				template <std::size_t ... I2, typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(
					kerbal::utility::in_place_t,
					kerbal::utility::index_sequence<I2...>,
					const U (&src)[N]
				)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_in_place_constructible_helper<const U (&)[N]>::IS_TRUE::value
					) :
					k_member{src[I2]...}
				{
				}

			public:

				template <typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t in_place, const U (&src)[N])
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_in_place_constructible_helper<const U (&)[N]>::IS_TRUE::value
					) :
					member_compress_helper(in_place, kerbal::utility::make_index_sequence<N>(), src)
				{
				}

#		else

				template <typename U>
				explicit member_compress_helper(kerbal::utility::in_place_t in_place, const U (&src)[N])
				{
					kerbal::algorithm::copy(src + 0, src + N, this->k_member + 0);
				}

#		endif


#		if __cplusplus >= 201103L

			private:

				template <std::size_t ... I2, typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(
					kerbal::utility::in_place_t,
					kerbal::utility::index_sequence<I2...>,
					U (&& src)[N]
				)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_in_place_constructible_helper<U (&&)[N]>::IS_TRUE::value
					) :
					k_member{kerbal::compatibility::move(src[I2])...}
				{
				}

			public:

				template <typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t in_place, U (&&src)[N])
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_in_place_constructible_helper<U (&&)[N]>::IS_TRUE::value
					) :
					member_compress_helper(
						in_place,
						kerbal::utility::make_index_sequence<N>(),
						kerbal::compatibility::move(src)
					)
				{
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t, std::initializer_list<U> ilist)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_in_place_constructible_helper<std::initializer_list<U> >::IS_TRUE::value
					) :
					k_member{ilist}
				{
				}

#		else

				explicit
				member_compress_helper(kerbal::utility::in_place_t, const kerbal::assign::assign_list<void> & ilist)
				{
				}

				template <typename U>
				explicit
				member_compress_helper(kerbal::utility::in_place_t, const kerbal::assign::assign_list<U> & ilist)
				{
					kerbal::algorithm::copy(ilist.cbegin(), ilist.cend(), this->k_member + 0);
				}

#		endif


#		if __cplusplus >= 201103L

			private:

				template <std::size_t ... I2, typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit
				member_compress_helper(
					kerbal::utility::in_place_t,
					kerbal::utility::index_sequence<I2...>,
					const kerbal::utility::member_compress_helper<U, J> & src
				) :
					k_member{src.member()[I2]...}
				{
				}

			public:

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(const kerbal::utility::member_compress_helper<U, J> & src) :
					member_compress_helper(
						kerbal::utility::in_place_t(),
						kerbal::utility::make_index_sequence<N>(),
						src
					)
				{
				}

#		else

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(const kerbal::utility::member_compress_helper<U, J> & src)
				{
					kerbal::algorithm::copy(src.member() + 0, src.member() + N, this->k_member + 0);
				}

#		endif


#		if __cplusplus >= 201103L

			private:

				template <std::size_t ... I2, typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit
				member_compress_helper(
					kerbal::utility::in_place_t,
					kerbal::utility::index_sequence<I2...>,
					kerbal::utility::member_compress_helper<U, J> && src
				) :
					k_member{kerbal::compatibility::move(src).member()[I2]...}
				{
				}

			public:

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit
				member_compress_helper(kerbal::utility::member_compress_helper<U, J> && src) :
					member_compress_helper(
						kerbal::utility::in_place_t(),
						kerbal::utility::make_index_sequence<N>(),
						kerbal::compatibility::move(src)
					)
				{
				}

#		endif

				KERBAL_CONSTEXPR14
				reference member() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->k_member;
				}

				KERBAL_CONSTEXPR
				const_reference member() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->k_member;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				rvalue_reference member() && KERBAL_NOEXCEPT
				{
//					return kerbal::compatibility::move(*this).k_member; // compile failed in msvc2017
					return static_cast<rvalue_reference>(kerbal::compatibility::move(*this).k_member);
				}

				KERBAL_CONSTEXPR
				const_rvalue_reference member() const && KERBAL_NOEXCEPT
				{
					return static_cast<const_rvalue_reference>(kerbal::compatibility::move(*this).k_member);
				}

#		endif

		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_ARRAY_PART_HPP
