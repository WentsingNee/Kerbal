/**
 * @file       member_compress_helper.ref.part.hpp
 * @brief
 * @date       2020-09-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_REF_PART_HPP
#define KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_REF_PART_HPP

#include <kerbal/utility/member_compress_helper/member_compress_helper.fwd.hpp>

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/add_lvalue_reference.hpp>
#include <kerbal/type_traits/add_const_lvalue_reference.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/add_rvalue_reference.hpp>
#	include <kerbal/type_traits/add_const_rvalue_reference.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

		template <typename T, std::size_t I>
		class member_compress_helper<T &, I>
		{
			public:
				typedef kerbal::type_traits::false_type IS_COMPRESSED;

				typedef T &																	value_type;
				typedef typename kerbal::type_traits::add_lvalue_reference<T &>::type		reference;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<T &>::type	const_reference;

#		if __cplusplus >= 201103L
				typedef typename kerbal::type_traits::add_rvalue_reference<T &>::type		rvalue_reference;
				typedef typename kerbal::type_traits::add_const_rvalue_reference<T &>::type	const_rvalue_reference;
#		endif

			private:
				T & k_member;

			public:

				KERBAL_CONSTEXPR14
				explicit member_compress_helper(kerbal::utility::in_place_t, reference arg0) KERBAL_NOEXCEPT:
					k_member(arg0)
				{
				}

#		if __cplusplus >= 201103L

				explicit member_compress_helper(const member_compress_helper & arg) = default;

#		endif

				template <std::size_t J>
				KERBAL_CONSTEXPR14
				explicit member_compress_helper(const member_compress_helper<T, J> & arg) KERBAL_NOEXCEPT:
					k_member(arg.member())
				{
				}

				template <std::size_t J>
				KERBAL_CONSTEXPR14
				explicit member_compress_helper(const member_compress_helper<T &, J> & arg) KERBAL_NOEXCEPT:
					k_member(arg.member())
				{
				}

				KERBAL_CONSTEXPR14
				void assign(T & arg)
				{
					kerbal::assign::generic_assign(this->member(), arg);
				}

				KERBAL_CONSTEXPR14
				member_compress_helper & operator=(const member_compress_helper & arg)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::assign::generic_assign(
								kerbal::utility::declthis<member_compress_helper>()->member(),
								arg.member()
							)
						)
					)
				{
					kerbal::assign::generic_assign(this->member(), arg.member());
					return *this;
				}

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR14
				member_compress_helper & operator=(const member_compress_helper<U, J> & arg)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::assign::generic_assign(
								kerbal::utility::declthis<member_compress_helper>()->member(),
								arg.member()
							)
						)
					)
				{
					kerbal::assign::generic_assign(this->member(), arg.member());
					return *this;
				}

				KERBAL_CONSTEXPR14
				reference member() const KERBAL_NOEXCEPT
				{
					return this->k_member;
				}

		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_REF_PART_HPP
