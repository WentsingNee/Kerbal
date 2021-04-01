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
#include <kerbal/utility/integer_sequence.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/type_vector.hpp>


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <std::size_t Index, typename ... Args>
			struct tuple_type_index;

			template <std::size_t Index, typename T, typename ... Args>
			struct tuple_type_index<Index, T, Args...>
			{
					typedef typename tuple_type_index<Index - 1, Args...>::type type;
			};

			template <std::size_t Index>
			struct tuple_type_index<Index>
			{
			};

			template <typename T, typename ... Args>
			struct tuple_type_index<0, T, Args...>
			{
					typedef T type;
			};



			template <typename T, typename ... Args>
			struct tuple_impl;

			template <std::size_t ... Index, typename ... Args>
			struct tuple_impl<kerbal::utility::index_sequence<Index...>, Args...> :
					private kerbal::utility::member_compress_helper<Args, Index>...
			{
				public:
					typedef kerbal::type_traits::integral_constant<size_t, sizeof...(Args)> TUPLE_SIZE;

					template <std::size_t I>
					struct value_type
					{
							typedef typename tuple_type_index<I, Args...>::type type;
					};

				private:
					template <std::size_t I>
					struct super
					{
							typedef kerbal::utility::member_compress_helper<typename value_type<I>::type, I> type;
					};

				public:

					template <size_t I>
					struct const_type
					{
							typedef const typename value_type<I>::type type;
					};

					template <size_t I>
					struct reference
					{
							typedef typename kerbal::type_traits::add_lvalue_reference<
									typename value_type<I>::type
							>::type type;
					};

					template <size_t I>
					struct const_reference
					{
							typedef typename kerbal::type_traits::add_const_lvalue_reference<
									typename value_type<I>::type
							>::type type;
					};

					template <size_t I>
					struct rvalue_reference
					{
							typedef typename kerbal::type_traits::add_rvalue_reference<
									typename value_type<I>::type
							>::type type;
					};

					template <size_t I>
					struct const_rvalue_reference
					{
							typedef typename kerbal::type_traits::add_const_rvalue_reference<
									typename value_type<I>::type
							>::type type;
					};


				public:

					KERBAL_CONSTEXPR
					tuple_impl() :
							kerbal::utility::member_compress_helper<Args, Index>(kerbal::utility::in_place_t())...
					{
					}

				private:
					struct helper {};

					template <typename ... Head, std::size_t ... HeadIndex, typename ... Tail, std::size_t ... TailIndex, typename ... UArgs>
					KERBAL_CONSTEXPR
					tuple_impl(
							kerbal::utility::type_vector<Head...>, kerbal::utility::index_sequence<HeadIndex...>,
							kerbal::utility::type_vector<Tail...>, kerbal::utility::index_sequence<TailIndex...>,
							UArgs && ... args) :
							kerbal::utility::member_compress_helper<Head, HeadIndex>(kerbal::utility::in_place_t(), std::forward<UArgs>(args))...,
							kerbal::utility::member_compress_helper<Tail, TailIndex + sizeof...(Head)>(kerbal::utility::in_place_t())...
					{
					}

				public:

					template <typename ... UArgs>
					KERBAL_CONSTEXPR
					tuple_impl(UArgs && ... args) :
							tuple_impl(
									typename kerbal::utility::type_vector_spilit<kerbal::utility::type_vector<Args...>, sizeof...(UArgs)>::head(),
									kerbal::utility::make_index_sequence<sizeof...(UArgs)>(),
									typename kerbal::utility::type_vector_spilit<kerbal::utility::type_vector<Args...>, sizeof...(UArgs)>::tail(),
									kerbal::utility::make_index_sequence<TUPLE_SIZE::value - sizeof...(UArgs)>(),
									std::forward<UArgs>(args)...)
					{
						static_assert(sizeof...(UArgs) <= sizeof...(Args), "too many arguments");
					}

					template <std::size_t I>
					KERBAL_CONSTEXPR14
					typename reference<I>::type
					get() & KERBAL_NOEXCEPT
					{
						return super<I>::type::member();
					}

					template <std::size_t I>
					KERBAL_CONSTEXPR
					typename const_reference<I>::type
					get() const & KERBAL_NOEXCEPT
					{
						return super<I>::type::member();
					}

					template <std::size_t I>
					KERBAL_CONSTEXPR14
					typename rvalue_reference<I>::type
					get() && KERBAL_NOEXCEPT
					{
						return super<I>::type::member();
					}

					template <std::size_t I>
					KERBAL_CONSTEXPR
					typename const_rvalue_reference<I>::type
					get() const && KERBAL_NOEXCEPT
					{
						return super<I>::type::member();
					}

					KERBAL_CONSTEXPR14
					void swap(tuple_impl & ano)
					{
						int a[[maybe_unused]][]{(kerbal::algorithm::swap(
								static_cast<kerbal::utility::member_compress_helper<Args, Index> &>(*this),
								static_cast<kerbal::utility::member_compress_helper<Args, Index> &>(ano)
						), 0)...};
					}
			};

		} // namespace detail

		template <typename ... Args>
		struct tuple : detail::tuple_impl<kerbal::utility::make_index_sequence<sizeof...(Args)>, Args...>
		{
			private:
				typedef detail::tuple_impl<kerbal::utility::make_index_sequence<sizeof...(Args)>, Args...> super;

			public:

				using super::super;
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
