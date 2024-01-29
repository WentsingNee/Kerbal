/**
 * @file       member_compress_helper.default.part.hpp
 * @brief
 * @date       2020-09-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_DEFAULT_PART_HPP
#define KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_DEFAULT_PART_HPP

#include <kerbal/utility/member_compress_helper/member_compress_helper.fwd.hpp>

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_constructible.hpp>
#	include <kerbal/type_traits/remove_cvref.hpp>
#	include <kerbal/utility/forward.hpp>
#	include <kerbal/utility/integer_sequence.hpp>
#	include <kerbal/utility/piecewise_construct.hpp>
#endif

#include <cstddef>

#include <kerbal/utility/member_compress_helper/detail/member_compress_helper_impl.hpp>


namespace kerbal
{

	namespace utility
	{

		template <typename T, std::size_t I>
		class member_compress_helper :
			public kerbal::utility::detail::member_compress_helper_impl<T>
		{
			private:
				typedef kerbal::utility::detail::member_compress_helper_impl<T> super;

			public:
				typedef typename super::value_type					value_type;
				typedef typename super::reference					reference;
				typedef typename super::const_reference				const_reference;

#		if __cplusplus >= 201103L
				typedef typename super::rvalue_reference			rvalue_reference;
				typedef typename super::const_rvalue_reference		const_rvalue_reference;
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
				struct try_test_is_nothrow_in_place_constructible :
					super::template try_test_is_nothrow_in_place_constructible<Args...>
				{
				};

				template <typename ... Args>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t in_place, Args && ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_in_place_constructible<Args && ...>::IS_TRUE::value
					) :
					super(in_place, kerbal::utility::forward<Args>(args)...)
				{
				}

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				explicit member_compress_helper( \
					kerbal::utility::in_place_t in_place \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
				): \
					super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
				{ \
				} \

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		endif


#			if __cplusplus >= 201103L

				template <typename U, std::size_t J>
				struct try_test_is_nothrow_covariant_copy_constructible :
					super::template try_test_is_nothrow_in_place_constructible<
						typename kerbal::utility::member_compress_helper<U, J>::const_reference
					>
				{
				};

#			endif

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(const kerbal::utility::member_compress_helper<U, J> & src)
					KERBAL_CONDITIONAL_NOEXCEPT((
						try_test_is_nothrow_covariant_copy_constructible<U, J>::IS_TRUE::value
					)) :
					super(kerbal::utility::in_place_t(), src.member())
				{
				}


#		if __cplusplus >= 201103L

				template <typename U, std::size_t J>
				struct try_test_is_nothrow_covariant_move_constructible :
					super::template try_test_is_nothrow_in_place_constructible<
						typename kerbal::utility::member_compress_helper<U, J>::rvalue_reference
					>
				{
				};

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::member_compress_helper<U, J> && src)
					KERBAL_CONDITIONAL_NOEXCEPT((
						try_test_is_nothrow_covariant_move_constructible<U, J>::IS_TRUE::value
					)) :
					super(kerbal::utility::in_place_t(), kerbal::compatibility::move(src).member())
				{
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename Tuple, std::size_t ... J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::index_sequence<J...>, Tuple && args) :
					super(kerbal::utility::in_place_t(), kerbal::utility::forward<Tuple>(args).template get<J>()...)
				{
				}

				template <typename Tuple>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::piecewise_construct_t, Tuple && args) :
					member_compress_helper(
						kerbal::utility::make_index_sequence<
							kerbal::type_traits::remove_cvref<Tuple>::type::TUPLE_SIZE::value
						>(),
						kerbal::utility::forward<Tuple>(args)
					)
				{
				}

#		endif


#		if __cplusplus < 201103L

				template <typename U>
				void assign(const U & arg)
				{
					kerbal::assign::generic_assign(this->member(), arg);
				}

#		else

				template <typename U>
				KERBAL_CONSTEXPR14
				void assign(U && arg)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::assign::generic_assign(
								kerbal::utility::declthis<member_compress_helper>()->member(),
								kerbal::utility::forward<U>(arg)
							)
						)
					)
				{
					kerbal::assign::generic_assign(this->member(), kerbal::utility::forward<U>(arg));
				}

#		endif


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

#		if __cplusplus >= 201103L

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR14
				member_compress_helper & operator=(member_compress_helper<U, J> && arg)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::assign::generic_assign(
								kerbal::utility::declthis<member_compress_helper>()->member(),
								kerbal::compatibility::move(arg).member()
							)
						)
					)
				{
					kerbal::assign::generic_assign(
						this->member(),
						kerbal::compatibility::move(arg).member()
					);
					return *this;
				}

#		endif

		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_DETAIL_MEMBER_COMPRESS_HELPER_MEMBER_COMPRESS_HELPER_DEFAULT_PART_HPP
