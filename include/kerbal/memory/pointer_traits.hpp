/**
 * @file       pointer_traits.hpp
 * @brief
 * @date       2020-03-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_POINTER_TRAITS_HPP
#define KERBAL_MEMORY_POINTER_TRAITS_HPP

#include <kerbal/type_traits/void_type.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename T>
			struct pointer_element_type_traits_impl;

#		if __cplusplus >= 201103L

			template <typename T, typename ... Args, template <typename, typename ...> class PtrTem>
			struct pointer_element_type_traits_impl<PtrTem<T, Args...> >
			{
					typedef T type;
			};

#		else

			template <typename T, template <typename> class PtrTem>
			struct pointer_element_type_traits_impl<PtrTem<T> >
			{
					typedef T type;
			};

#		endif

			template <typename T>
			struct pointer_element_type_traits_impl<T *>
			{
					typedef T type;
			};


			template <typename Ptr, typename = kerbal::type_traits::void_type<> >
			struct pointer_element_type_traits_helper: pointer_element_type_traits_impl<Ptr>
			{
			};

			template <typename Ptr>
			struct pointer_element_type_traits_helper<Ptr, kerbal::type_traits::void_type<typename Ptr::element_type> >
			{
					typedef typename Ptr::element_type type;
			};

			template <typename Ptr, typename = kerbal::type_traits::void_type<> >
			struct pointer_difference_type_traits_helper
			{
					typedef std::ptrdiff_t type;
			};

			template <typename Ptr>
			struct pointer_difference_type_traits_helper<Ptr, kerbal::type_traits::void_type<typename Ptr::difference_type> >
			{
					typedef typename Ptr::difference_type type;
			};

			template <typename T, typename U>
			struct pointer_traits_rebind_helper;

#		if __cplusplus >= 201103L

			template <typename T, typename ... Args, typename U, template <typename, typename ...> class PtrTem>
			struct pointer_traits_rebind_helper<PtrTem<T, Args...>, U>
			{
					typedef PtrTem<U, Args...> type;
			};

#		else

			template <typename T, typename U, template <typename> class PtrTem>
			struct pointer_traits_rebind_helper<PtrTem<T>, U>
			{
					typedef PtrTem<U> type;
			};

#		endif

			template <typename T, typename U>
			struct pointer_traits_rebind_helper<T *, U>
			{
					typedef U * type;
			};

		} // namespace detail

		template <typename Ptr>
		struct pointer_traits
		{
				typedef Ptr pointer;

				typedef typename detail::pointer_element_type_traits_helper<Ptr>::type element_type;

				typedef typename detail::pointer_difference_type_traits_helper<Ptr>::type difference_type;

				template <typename U>
				struct rebind
				{
						typedef typename kerbal::memory::detail::pointer_traits_rebind_helper<Ptr, U>::type other;
				};
		};

		template <typename T>
		struct pointer_traits<T *>
		{
				typedef T * pointer;

				typedef T element_type;

				typedef std::ptrdiff_t difference_type;

				template <typename U>
				struct rebind
				{
						typedef typename kerbal::memory::detail::pointer_traits_rebind_helper<T *, U>::type other;
				};

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_POINTER_TRAITS_HPP
