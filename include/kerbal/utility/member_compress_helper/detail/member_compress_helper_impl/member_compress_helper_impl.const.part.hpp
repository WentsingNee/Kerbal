/**
 * @file       member_compress_helper_impl.const.part.hpp
 * @brief
 * @date       2020-09-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_IMPL_MEMBER_COMPRESS_HELPER_IMPL_CONST_PART_HPP
#define KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_IMPL_MEMBER_COMPRESS_HELPER_IMPL_CONST_PART_HPP

#include <kerbal/utility/member_compress_helper/detail/member_compress_helper_impl.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/add_lvalue_reference.hpp>
#include <kerbal/type_traits/add_const_lvalue_reference.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_volatile.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/add_rvalue_reference.hpp>
#	include <kerbal/type_traits/add_const_rvalue_reference.hpp>
#	include <kerbal/type_traits/is_nothrow_constructible.hpp>
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename T>
			class member_compress_helper_impl<const T, true>:
				private kerbal::type_traits::remove_volatile<T>::type
			{
				private:
					typedef typename kerbal::type_traits::remove_volatile<T>::type super;

				public:
					typedef kerbal::type_traits::true_type IS_COMPRESSED;

					typedef const T																		value_type;
					typedef typename kerbal::type_traits::add_lvalue_reference<const T>::type			reference;
					typedef typename kerbal::type_traits::add_const_lvalue_reference<const T>::type		const_reference;

#			if __cplusplus >= 201103L
					typedef typename kerbal::type_traits::add_rvalue_reference<const T>::type			rvalue_reference;
					typedef typename kerbal::type_traits::add_const_rvalue_reference<const T>::type		const_rvalue_reference;
#			endif

				public:

#			if __cplusplus >= 201103L

					member_compress_helper_impl() = default;

#			else

					member_compress_helper_impl()
					{
					}

#			endif

#			if __cplusplus >= 201103L

					template <typename ... Args>
					struct try_test_is_nothrow_in_place_constructible :
						kerbal::type_traits::try_test_is_nothrow_constructible<super, Args...>
					{
					};

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(kerbal::utility::in_place_t, Args && ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
							try_test_is_nothrow_in_place_constructible<Args && ...>::IS_TRUE::value
						) :
						super(kerbal::utility::forward<Args>(args)...)
					{
					}

#			else

#				define EMPTY
#				define REMAINF(exp) exp
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit member_compress_helper_impl( \
						kerbal::utility::in_place_t \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					): \
						super(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)) \
					{ \
					} \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef REMAINF
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#			endif


				// note: `member_compress_helper_impl` couldn't inherit from `noncopyassignable` in pursuit of more effective compression effect

#			if __cplusplus < 201103L

				private:
					member_compress_helper_impl & operator=(const member_compress_helper_impl &);

#			else

				public:
					member_compress_helper_impl & operator=(const member_compress_helper_impl &) = delete;
					member_compress_helper_impl & operator=(member_compress_helper_impl &&) = delete;

#			endif

				public:

					KERBAL_CONSTEXPR14
					reference member() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<reference>(*this);
					}

					KERBAL_CONSTEXPR
					const_reference member() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const_reference>(*this);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference member() && KERBAL_NOEXCEPT
					{
						return static_cast<rvalue_reference>(*this);
					}

					KERBAL_CONSTEXPR
					const_rvalue_reference member() const && KERBAL_NOEXCEPT
					{
						return static_cast<const_rvalue_reference>(*this);
					}

#			endif

			};

		} // namespace detail

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_IMPL_MEMBER_COMPRESS_HELPER_IMPL_CONST_PART_HPP
