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
#include <kerbal/type_traits/enable_if.hpp>


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

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
							typedef typename type_vector_at<type_vector<Args...>, I>::result type;
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
					struct converting_cnstrct_tag {};

					template <std::size_t ... HeadIndex, std::size_t ... TailIndex, typename ... UArgs>
					KERBAL_CONSTEXPR
					tuple_impl(
							converting_cnstrct_tag,
							kerbal::utility::index_sequence<HeadIndex...>,
							kerbal::utility::index_sequence<TailIndex...>,
							UArgs && ... args) :
							super<HeadIndex>::type(kerbal::utility::in_place_t(), std::forward<UArgs>(args))...,
							super<TailIndex + sizeof...(HeadIndex)>::type(kerbal::utility::in_place_t())...
					{
					}

				public:

					template <typename ... UArgs>
					KERBAL_CONSTEXPR
					explicit tuple_impl(UArgs && ... args) :
							tuple_impl(
									converting_cnstrct_tag(),
									kerbal::utility::make_index_sequence<sizeof...(UArgs)>(),
									kerbal::utility::make_index_sequence<TUPLE_SIZE::value - sizeof...(UArgs)>(),
									std::forward<UArgs>(args)...)
					{
						static_assert(sizeof...(UArgs) <= sizeof...(Args), "too many arguments");
					}

				public:

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
					KERBAL_CONSTEXPR
					typename const_reference<I>::type
					cget() const & KERBAL_NOEXCEPT
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

					template <std::size_t I>
					KERBAL_CONSTEXPR
					typename const_rvalue_reference<I>::type
					cget() const && KERBAL_NOEXCEPT
					{
						return super<I>::type::member();
					}

			};

		} // namespace detail

		template <typename ... Args>
		struct tuple : detail::tuple_impl<kerbal::utility::make_index_sequence<sizeof...(Args)>, Args...>
		{
			private:
				typedef detail::tuple_impl<kerbal::utility::make_index_sequence<sizeof...(Args)>, Args...> super;

			public:
				typedef typename super::TUPLE_SIZE			TUPLE_SIZE;
				using super::super;

			protected:

				template <std::size_t ... Index1, typename ... UArgs, std::size_t ... Index2>
				KERBAL_CONSTEXPR
				static tuple<Args..., UArgs...> _K_tuple_cat_impl(
						const tuple<Args...> & tuple1, kerbal::utility::index_sequence<Index1...>,
						const tuple<UArgs...> & tuple2, kerbal::utility::index_sequence<Index2...>)
				{
					return tuple<Args..., UArgs...>(tuple1.template get<Index1>()..., tuple2.template get<Index2>()...);
				}

			public:

				template <typename ... UArgs>
				KERBAL_CONSTEXPR
				friend
				tuple<Args..., UArgs...> operator+(const tuple<Args...> & tuple1, const tuple<UArgs...> & tuple2)
				{
					return _K_tuple_cat_impl(
							tuple1, kerbal::utility::make_index_sequence<sizeof...(Args)>(),
							tuple2, kerbal::utility::make_index_sequence<sizeof...(UArgs)>());
				}


			protected:

				template <std::size_t ... Index>
				KERBAL_CONSTEXPR14
				tuple<typename kerbal::type_traits::add_lvalue_reference<Args>::type...>
				_K_ref_impl(kerbal::utility::index_sequence<Index...>) KERBAL_NOEXCEPT
				{
					return tuple<typename kerbal::type_traits::add_lvalue_reference<Args>::type...>(this->template get<Index>()...);
				}

			public:

				KERBAL_CONSTEXPR14
				tuple<typename kerbal::type_traits::add_lvalue_reference<Args>::type...>
				ref() KERBAL_NOEXCEPT
				{
					return _K_ref_impl(kerbal::utility::make_index_sequence<TUPLE_SIZE::value>());
				}


			protected:

				template <std::size_t ... Index>
				KERBAL_CONSTEXPR14
				tuple<typename kerbal::type_traits::add_const_lvalue_reference<Args>::type...>
				_K_cref_impl(kerbal::utility::index_sequence<Index...>) const KERBAL_NOEXCEPT
				{
					return tuple<typename kerbal::type_traits::add_const_lvalue_reference<Args>::type...>(this->template get<Index>()...);
				}

			public:

				KERBAL_CONSTEXPR14
				tuple<typename kerbal::type_traits::add_const_lvalue_reference<Args>::type...>
				cref() const KERBAL_NOEXCEPT
				{
					return _K_cref_impl(kerbal::utility::make_index_sequence<TUPLE_SIZE::value>());
				}


			protected:

				template <typename F, std::size_t ... Index>
				KERBAL_CONSTEXPR14
				void _K_for_each_impl(F f, kerbal::utility::index_sequence<Index...>)
				{
					int a[[maybe_unused]][]{(f(
							this->template get<Index>(),
							kerbal::type_traits::integral_constant<std::size_t, Index>()
					), 0)...};
				}

				template <typename F, std::size_t ... Index>
				KERBAL_CONSTEXPR14
				void _K_for_each_impl(F f, kerbal::utility::index_sequence<Index...>) const
				{
					int a[[maybe_unused]][]{(f(
							this->template get<Index>(),
							kerbal::type_traits::integral_constant<std::size_t, Index>()
					), 0)...};
				}

			public:

				template <typename F>
				KERBAL_CONSTEXPR14
				void for_each(F f)
				{
					_K_for_each_impl(f, kerbal::utility::make_index_sequence<TUPLE_SIZE::value>());
				}

				template <typename F>
				KERBAL_CONSTEXPR14
				void for_each(F f) const
				{
					_K_for_each_impl(f, kerbal::utility::make_index_sequence<TUPLE_SIZE::value>());
				}


			protected:

				template <std::size_t ... Index>
				KERBAL_CONSTEXPR14
				void _K_swap_impl(tuple & ano, kerbal::utility::index_sequence<Index...>)
				{
					int a[[maybe_unused]][]{(kerbal::algorithm::swap(
							this->template get<Index>(), ano.template get<Index>()
					), 0)...};
				}

			public:

				KERBAL_CONSTEXPR14
				void swap(tuple & ano)
				{
					_K_swap_impl(ano, kerbal::utility::make_index_sequence<TUPLE_SIZE::value>());
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
		kerbal::utility::tuple<Args&...>
		tie(Args& ... args) KERBAL_NOEXCEPT
		{
			return kerbal::utility::tuple<Args&...>(args...);
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
