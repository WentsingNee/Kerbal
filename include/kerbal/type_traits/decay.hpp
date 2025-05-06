/**
 * @file       decay.hpp
 * @brief
 * @date       2019-7-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DECAY_HPP
#define KERBAL_TYPE_TRAITS_DECAY_HPP


#include <kerbal/type_traits/add_pointer.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_array.hpp>
#include <kerbal/type_traits/is_function.hpp>
#include <kerbal/type_traits/remove_cv.hpp>
#include <kerbal/type_traits/remove_extent.hpp>
#include <kerbal/type_traits/remove_reference.hpp>


namespace kerbal
{

	namespace type_traits
	{

		namespace detail
		{

			template <
				typename T,
				bool IsArray = kerbal::type_traits::is_array<T>::value,
				bool IsFunction = kerbal::type_traits::is_function<T>::value
			>
			struct decay_selector;

			template <typename T>
			struct decay_selector<T, false, false>
			{
				typedef typename kerbal::type_traits::remove_cv<T>::type type;
			};

			template <typename T>
			struct decay_selector<T, true, false>
			{
				typedef typename kerbal::type_traits::remove_extent<T>::type *type;
			};

			template <typename T>
			struct decay_selector<T, false, true>
			{
				typedef typename kerbal::type_traits::add_pointer<T>::type type;
			};

		} // namespace detail


		template <typename T>
		struct decay
		{
			private:
				typedef typename kerbal::type_traits::remove_reference<T>::type U;

			public:
				typedef typename kerbal::type_traits::detail::decay_selector<U>::type type;
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_DECAY_HPP
