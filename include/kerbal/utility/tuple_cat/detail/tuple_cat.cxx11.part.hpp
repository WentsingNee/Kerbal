/**
 * @file       tuple_cat.cxx11.part.hpp
 * @brief
 * @date       2024-07-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_TUPLE_CAT_DETAIL_TUPLE_CAT_CXX11_PART_HPP
#define KERBAL_UTILITY_TUPLE_CAT_DETAIL_TUPLE_CAT_CXX11_PART_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/tmp/type_vector.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_const.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/integer_sequence.hpp>
#include <kerbal/utility/tuple.hpp>

#include <tuple>

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename T, typename>
			struct k_elements_type_vector_helper;

			template <typename T, std::size_t ... I>
			struct k_elements_type_vector_helper<T, kerbal::utility::index_sequence<I...> >
			{
					typedef kerbal::tmp::type_vector<typename std::tuple_element<I, T>::type ...> type;
			};

			template <typename T>
			struct elements_type_vector :
				k_elements_type_vector_helper<T, kerbal::utility::make_index_sequence<std::tuple_size<T>::value> >
			{
			};


			template <typename ... Ts>
			struct elements_type_vector_cat;

			template <>
			struct elements_type_vector_cat<>
			{
					typedef kerbal::tmp::type_vector<> type;
			};

			template <typename T, typename ... Ts>
			struct elements_type_vector_cat<T, Ts...>
			{
					typedef typename kerbal::tmp::type_vector_cat<
						typename elements_type_vector<T>::type,
						typename elements_type_vector_cat<Ts...>::type
					>::result type;
			};


			template <typename TypeVector>
			struct replace_type_vector_to_tuple;

			template <typename ... Args>
			struct replace_type_vector_to_tuple<kerbal::tmp::type_vector<Args...> >
			{
					typedef kerbal::utility::tuple<Args...> result;
			};


			template <std::size_t I, typename ... Ts>
			struct element_index_in_tuples;

			template <std::size_t I, typename T>
			struct element_index_in_tuples<I, T>
			{
				private:
					KERBAL_STATIC_ASSERT(I < std::tuple_size<T>::value, "Index out of range");

				public:
					typedef kerbal::type_traits::integral_constant<std::size_t, 0> tuple_index;
					typedef kerbal::type_traits::integral_constant<std::size_t, I> tuple_inner_index;
			};

			template <bool in_the_first, std::size_t I, typename T, typename ... Ts>
			struct k_element_index_in_tuples_helper;

			template <std::size_t I, typename T, typename ... Ts>
			struct k_element_index_in_tuples_helper<true, I, T, Ts...>
			{
					typedef kerbal::type_traits::integral_constant<std::size_t, 0> tuple_index;
					typedef kerbal::type_traits::integral_constant<std::size_t, I> tuple_inner_index;
			};

			template <std::size_t I, typename T, typename ... Ts>
			struct k_element_index_in_tuples_helper<false, I, T, Ts...>
			{
				private:
					typedef element_index_in_tuples<I - std::tuple_size<T>::value, Ts...> next;

				public:
					typedef kerbal::type_traits::integral_constant<std::size_t, next::tuple_index::value + 1> tuple_index;
					typedef typename next::tuple_inner_index tuple_inner_index;
			};

			template <std::size_t I, typename T, typename ... Ts>
			struct element_index_in_tuples<I, T, Ts...> :
				k_element_index_in_tuples_helper<I < std::tuple_size<T>::value, I, T, Ts...>
			{
			};


			template <std::size_t I, typename T>
			struct std_get_result_type
			{
					typedef decltype(std::get<I>(kerbal::utility::declval<T>())) type;
			};


			template <std::size_t I, typename ... Ts>
			struct get_in_tuples_result_type
			{
					typedef element_index_in_tuples<I, typename kerbal::type_traits::remove_reference<Ts>::type ...> ele_index;
					typedef typename ele_index::tuple_index tuple_index;
					typedef typename ele_index::tuple_inner_index tuple_inner_index;
					typedef kerbal::tmp::type_vector<Ts...> tuples_type_vector;
					typedef typename kerbal::tmp::type_vector_at<tuples_type_vector, tuple_index::value>::result tuple_with_ref;

					typedef typename std_get_result_type<tuple_inner_index::value, tuple_with_ref>::type type;
			};


			template <std::size_t I>
			struct forward_packs_at;

			template <>
			struct forward_packs_at<0>
			{
					template <typename T, typename ... Args>
					KERBAL_CONSTEXPR
					static T && f(T && t, Args && ...) KERBAL_NOEXCEPT
					{
						return kerbal::utility::forward<T>(t);
					}
			};

			template <std::size_t I>
			struct forward_packs_at
			{
					template <typename T, typename ... Args>
					KERBAL_CONSTEXPR
					static auto f(T &&, Args && ... args) KERBAL_NOEXCEPT ->
						decltype(forward_packs_at<I - 1>::f(kerbal::utility::forward<Args>(args)...))
					{
						return forward_packs_at<I - 1>::f(kerbal::utility::forward<Args>(args)...);
					}
			};


			template <std::size_t I, typename ... Args>
			KERBAL_CONSTEXPR
			auto get_in_tuples(Args && ... args) KERBAL_NOEXCEPT ->
				typename get_in_tuples_result_type<I, Args && ...>::type
			{
				typedef element_index_in_tuples<I, typename kerbal::type_traits::remove_reference<Args>::type ...> ele_index;
				typedef typename ele_index::tuple_index tuple_index;
				typedef typename ele_index::tuple_inner_index tuple_inner_index;

				return std::get<tuple_inner_index::value>(forward_packs_at<tuple_index::value>::f(kerbal::utility::forward<Args>(args)...));
			}


			template <typename ... Tuples>
			struct tuple_cat_helper
			{

					typedef typename elements_type_vector_cat<
						typename kerbal::type_traits::remove_const<
							typename kerbal::type_traits::remove_reference<Tuples>::type
						>::type ...
					>::type elements_type_vector_cat_result;

					typedef typename replace_type_vector_to_tuple<elements_type_vector_cat_result>::result tuple_cat_result_type;
					typedef typename elements_type_vector_cat_result::SIZE SIZE_TOTAL;

					template <std::size_t ... Index>
					KERBAL_CONSTEXPR
					static tuple_cat_result_type k_cat_impl(kerbal::utility::index_sequence<Index...>, Tuples && ... tuples)
					{
						return tuple_cat_result_type(get_in_tuples<Index>(kerbal::utility::forward<Tuples>(tuples)...)...);
					}

					KERBAL_CONSTEXPR
					static tuple_cat_result_type cat(Tuples && ... tuples)
					{
						return k_cat_impl(
							kerbal::utility::make_index_sequence<SIZE_TOTAL::value>(),
							kerbal::utility::forward<Tuples>(tuples)...
						);
					}
			};

		} // namespace detail

		template <typename ... Tuples>
		KERBAL_CONSTEXPR
		typename detail::tuple_cat_helper<Tuples...>::tuple_cat_result_type
		tuple_cat(Tuples && ... tuples)
		{
			return detail::tuple_cat_helper<Tuples...>::cat(kerbal::utility::forward<Tuples>(tuples)...);
		}

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_TUPLE_CAT_DETAIL_TUPLE_CAT_CXX11_PART_HPP
