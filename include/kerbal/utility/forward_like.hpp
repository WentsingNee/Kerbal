/**
 * @file       forward_like.hpp
 * @brief
 * @date       2024-05-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_FORWARD_LIKE_HPP
#define KERBAL_UTILITY_FORWARD_LIKE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/add_const.hpp>
#include <kerbal/type_traits/add_lvalue_reference.hpp>
#include <kerbal/type_traits/add_rvalue_reference.hpp>
#include <kerbal/type_traits/is_const.hpp>
#include <kerbal/type_traits/is_lvalue_reference.hpp>
#include <kerbal/type_traits/remove_reference.hpp>


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename T>
			struct as_const_result_t;

			template <typename T>
			struct as_const_result_t<T &>
			{
					typedef T const & type;
			};

			template <typename T>
			struct as_const_result_t<T &&>
			{
					typedef T const & type;
			};


			template <typename T>
			struct move_result_t;

			template <typename T>
			struct move_result_t<T &>
			{
					typedef T && type;
			};

			template <typename T>
			struct move_result_t<T &&>
			{
					typedef T && type;
			};


			template <
				typename TRR, typename URR,
				bool TIsConst = kerbal::type_traits::is_const<typename kerbal::type_traits::remove_reference<TRR>::type>::value,
				bool TIsLvalueReference = kerbal::type_traits::is_lvalue_reference<TRR>::value
			>
			struct forward_like_result_impl;

			template <typename TRR, typename URR>
			struct forward_like_result_impl<TRR, URR, true, true>
			{
					typedef
						typename as_const_result_t<
							URR
						>::type
					type;
			};

			template <typename TRR, typename URR>
			struct forward_like_result_impl<TRR, URR, true, false>
			{
					typedef
						typename move_result_t<
							typename as_const_result_t<
								URR
							>::type
						>::type
					type;
			};

			template <typename TRR, typename URR>
			struct forward_like_result_impl<TRR, URR, false, true>
			{
				private:
					typedef typename kerbal::type_traits::remove_reference<URR>::type U;

				public:
					typedef
						typename kerbal::type_traits::add_lvalue_reference<
							U
						>::type
					type;
			};

			template <typename TRR, typename URR>
			struct forward_like_result_impl<TRR, URR, false, false>
			{
					typedef
						typename move_result_t<
							URR
						>::type
					type;
			};


			template <typename T, typename U>
			struct forward_like_result_helper :
				forward_like_result_impl<T &&, U &&>
			{
			};

		} // namespace detail


		template <typename T, typename U>
		struct forward_like_result :
			kerbal::utility::detail::forward_like_result_helper<T, U>
		{
		};

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		typename forward_like_result<T, U>::type
		forward_like(U && x) KERBAL_NOEXCEPT
		{
			return static_cast<typename forward_like_result<T, U>::type>(x);
		}

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_FORWARD_LIKE_HPP
