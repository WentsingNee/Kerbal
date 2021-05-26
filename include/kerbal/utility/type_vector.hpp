/**
 * @file       type_vector.hpp
 * @brief
 * @date       2021-05-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_TYPE_VECTOR_HPP
#define KERBAL_UTILITY_TYPE_VECTOR_HPP

#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace utility
	{

		template <typename ... Args>
		struct type_vector
		{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof...(Args)> SIZE;
		};



		template <typename TypeVector, std::size_t I>
		struct type_vector_at;

		template <std::size_t I, typename T, typename ... Args>
		struct type_vector_at<type_vector<T, Args...>, I> : type_vector_at<type_vector<Args...>, I - 1>
		{
		};

		template <typename T, typename ... Args>
		struct type_vector_at<type_vector<T, Args...>, 0>
		{
				typedef T result;
		};



		template <typename TypeVector1, typename TypeVector2>
		struct type_vector_cat;

		template <typename ... Args1, typename ... Args2>
		struct type_vector_cat<type_vector<Args1...>, type_vector<Args2...> >
		{
				typedef type_vector<Args1..., Args2...> result;
		};



		template <typename TypeVector, typename T>
		struct type_vector_push_back;

		template <typename ... Args, typename T>
		struct type_vector_push_back<type_vector<Args...>, T>
		{
				typedef type_vector<Args..., T> result;
		};



		template <typename TypeVector, typename T>
		struct type_vector_push_front;

		template <typename ... Args, typename T>
		struct type_vector_push_front<type_vector<Args...>, T>
		{
				typedef type_vector<T, Args...> result;
		};



		template <typename TypeVector>
		struct type_vector_pop_front;

		template <typename T, typename ... Args>
		struct type_vector_pop_front<type_vector<T, Args...> >
		{
				typedef T result;
				typedef type_vector<Args...> remain;
		};



		template <typename TypeVector, std::size_t N>
		struct type_vector_spilit;

		template <typename ... Args, std::size_t N>
		struct type_vector_spilit<type_vector<Args...>, N>
		{
			private:
				typedef type_vector<Args...> typevec;
				typedef typename type_vector_pop_front<typevec>::result front;
				typedef typename type_vector_pop_front<typevec>::remain remain;

			public:
				typedef typename type_vector_push_front<
						typename type_vector_spilit<remain, N - 1>::head,
						front
				>::result				head;

				typedef typename type_vector_spilit<remain, N - 1>::tail		tail;
		};

		template <typename ... Args>
		struct type_vector_spilit<type_vector<Args...>, 0>
		{
			public:
				typedef type_vector<>				head;
				typedef type_vector<Args...>		tail;
		};

//		template <typename ... Args>
//		struct type_vector_spilit<type_vector<Args...>, sizeof...(Args)>
//		{
//			public:
//				typedef type_vector<Args...>		head;
//				typedef type_vector<>				tail;
//		};



		template <typename TypeVector>
		struct type_vector_reverse;

		template <typename ... Args>
		struct type_vector_reverse<type_vector<Args...> >
		{
			private:
				typedef type_vector<Args...> typevec;
				typedef typename type_vector_pop_front<typevec>::result front;
				typedef typename type_vector_pop_front<typevec>::remain remain;

			public:
				typedef typename type_vector_push_back<
						typename type_vector_reverse<remain>::result,
						front
				>::result				result;

		};

		template <>
		struct type_vector_reverse<type_vector<> >
		{
				typedef type_vector<> result;
		};



		template <typename TypeVector, typename T>
		struct type_vector_find;

		template <typename T, typename ... Args>
		struct type_vector_find<type_vector<T, Args...>, T> : kerbal::type_traits::integral_constant<std::size_t, 0>
		{
		};

		template <typename T, typename U, typename ... Args>
		struct type_vector_find<type_vector<U, Args...>, T> :
				kerbal::type_traits::integral_constant<std::size_t, type_vector_find<type_vector<Args...>, T>::value + 1>
		{
		};

		template <typename T>
		struct type_vector_find<type_vector<>, T> : kerbal::type_traits::integral_constant<std::size_t, 0>
		{
		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_TYPE_VECTOR_HPP
