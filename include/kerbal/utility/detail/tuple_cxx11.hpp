/**
 * @file       tuple_cxx11.hpp
 * @brief
 * @date       2020-07-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_DETAIL_TUPLE_CXX11_HPP
#define KERBAL_UTILITY_DETAIL_TUPLE_CXX11_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/reference_deduction.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			struct tuple_construct_t
			{
			};

			template <typename Tuple, size_t I>
			struct tuple_value_type_helper
			{
				typedef typename tuple_value_type_helper<typename Tuple::LEFT, I -1>::type type;
			};

			template <typename Tuple>
			struct tuple_value_type_helper<Tuple, 0>
			{
				typedef typename Tuple::current_value_type type;
			};

		} // namespace detail

		template <typename ... Args>
		class tuple;

		template <>
		class tuple<>
		{

			public:
				typedef kerbal::type_traits::integral_constant<size_t, 0> TUPLE_SIZE;

			public:
				tuple() KERBAL_NOEXCEPT = default;

				KERBAL_CONSTEXPR14
				void swap(tuple<> & /*ano*/) KERBAL_NOEXCEPT
				{
				}
		};

		template <typename T, typename ... Args>
		class tuple<T, Args...>:
				private kerbal::utility::member_compress_helper<T, sizeof...(Args)>,
				private tuple<Args...>
		{
			private:
				typedef kerbal::utility::member_compress_helper<T, sizeof...(Args)> CURRENT;
				typedef tuple<Args...> LEFT;

				typedef T										current_value_type;
				typedef const current_value_type				current_const_type;
				typedef current_value_type&						current_reference;
				typedef const current_value_type&				current_const_reference;

				template <typename Tuple, size_t I>
				friend struct detail::tuple_value_type_helper;

			public:
				typedef kerbal::type_traits::integral_constant<size_t, 1 + sizeof...(Args)> TUPLE_SIZE;

				template <size_t I>
				struct value_type
				{
					typedef typename detail::tuple_value_type_helper<tuple, I>::type type;
				};

				template <size_t I>
				struct const_type
				{
					typedef const typename detail::tuple_value_type_helper<tuple, I>::type type;
				};

				template <size_t I>
				struct reference
				{
					typedef typename kerbal::type_traits::add_lvalue_reference<
						typename detail::tuple_value_type_helper<tuple, I>::type
					>::type type;
				};

				template <size_t I>
				struct const_reference
				{
					typedef typename kerbal::type_traits::add_const_lvalue_reference<
						typename detail::tuple_value_type_helper<tuple, I>::type
					>::type type;
				};

				template <size_t I>
				struct rvalue_reference
				{
					typedef typename kerbal::type_traits::add_rvalue_reference<
						typename detail::tuple_value_type_helper<tuple, I>::type
					>::type type;
				};

				template <size_t I>
				struct const_rvalue_reference
				{
					typedef typename kerbal::type_traits::add_const_rvalue_reference<
						typename detail::tuple_value_type_helper<tuple, I>::type
					>::type type;
				};

			public:
				KERBAL_CONSTEXPR
				tuple():
						CURRENT(kerbal::utility::in_place_t()),
						LEFT()
				{
				}

				tuple(tuple &) noexcept = default;
				tuple(const tuple &) noexcept = default;
				tuple(tuple &&) noexcept = default;

				template <typename U, typename ... UArgs>
				KERBAL_CONSTEXPR
				tuple(U&& arg, UArgs&& ... args):
						CURRENT(kerbal::utility::in_place_t(), kerbal::utility::forward<U>(arg)),
						LEFT(kerbal::utility::forward<UArgs>(args)...)
				{
					static_assert(sizeof...(UArgs) <= sizeof...(Args), "too many arguments");
				}

				KERBAL_CONSTEXPR14
				void swap(tuple & ano)
				{
					kerbal::algorithm::swap(this->CURRENT::member(), ano.CURRENT::member());
					this->LEFT::swap(ano);
				}

			private:
				current_reference get_impl(kerbal::type_traits::integral_constant<size_t, 0>) KERBAL_NOEXCEPT
				{
					return this->CURRENT::member();
				}

				current_const_reference get_const_impl(kerbal::type_traits::integral_constant<size_t, 0>) const KERBAL_NOEXCEPT
				{
					return this->CURRENT::member();
				}

				template <size_t I>
				typename reference<I>::type
				get_impl(kerbal::type_traits::integral_constant<size_t, I>) KERBAL_NOEXCEPT
				{
					return this->LEFT::template get<I - 1>();
				}

				template <size_t I>
				typename const_reference<I>::type
				get_const_impl(kerbal::type_traits::integral_constant<size_t, I>) const KERBAL_NOEXCEPT
				{
					return this->LEFT::template get<I - 1>();
				}

			public:
				template <size_t I>
				auto get() KERBAL_NOEXCEPT
						-> decltype(kerbal::utility::declthis<tuple>()->get_impl(kerbal::type_traits::integral_constant<size_t, I>())) &
				{
					return this->get_impl(kerbal::type_traits::integral_constant<size_t, I>());
				}

				template <size_t I>
				auto get() const KERBAL_NOEXCEPT
						-> decltype(kerbal::utility::declthis<tuple>()->get_const_impl(kerbal::type_traits::integral_constant<size_t, I>())) &
				{
					return this->get_const_impl(kerbal::type_traits::integral_constant<size_t, I>());
				}

		};


		template <typename ... Args>
		KERBAL_CONSTEXPR
		kerbal::utility::tuple<Args...>
		make_tuple(Args&& ... args)
		{
			return kerbal::utility::tuple<Args...>(kerbal::utility::forward<Args>(args)...);
		}

		template <typename ... Args>
		KERBAL_CONSTEXPR
		kerbal::utility::tuple<Args&&...>
		forward_as_tuple(Args&& ... args)
		{
			return kerbal::utility::tuple<Args&&...>(kerbal::utility::forward<Args>(args)...);
		}

	} // namespace utility

} // namespace kerbal


#endif // KERBAL_UTILITY_DETAIL_TUPLE_CXX11_HPP
