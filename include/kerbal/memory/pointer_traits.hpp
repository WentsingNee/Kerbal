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

#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>

#include <cstddef>

namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename Tp>
			struct pointer_element_type_traits_impl;

#		if __cplusplus >= 201103L

			template <typename Tp, typename ... Args, template <typename, typename ...> typename PtrTem>
			struct pointer_element_type_traits_impl<PtrTem<Tp, Args...> >
			{
					typedef Tp type;
			};

#		else

			template <typename Tp, template <typename> class PtrTem>
			struct pointer_element_type_traits_impl<PtrTem<Tp> >
			{
					typedef Tp type;
			};

#		endif

			template <typename Tp>
			struct pointer_element_type_traits_impl<Tp*>
			{
					typedef Tp type;
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

			template <typename Tp, typename Up>
			struct pointer_traits_rebind_helper;

#		if __cplusplus >= 201103L

			template <typename Tp, typename ... Args, typename Up, template <typename, typename ...> typename PtrTem>
			struct pointer_traits_rebind_helper<PtrTem<Tp, Args...>, Up>
			{
					typedef PtrTem<Up, Args...> type;
			};

#		else

			template <typename Tp, typename Up, template <typename> class PtrTem>
			struct pointer_traits_rebind_helper<PtrTem<Tp>, Up>
			{
					typedef PtrTem<Up> type;
			};

#		endif

			template <typename Tp, typename Up>
			struct pointer_traits_rebind_helper<Tp*, Up>
			{
					typedef Up* type;
			};

		} // namespace detail

		template <typename Ptr>
		struct pointer_traits
		{
				typedef Ptr pointer;

				typedef typename detail::pointer_element_type_traits_helper<Ptr>::type element_type;

				typedef typename detail::pointer_difference_type_traits_helper<Ptr>::type difference_type;

				template <typename Up>
				struct rebind
				{
						typedef typename kerbal::memory::detail::pointer_traits_rebind_helper<Ptr, Up>::type other;
				};
		};

		template <typename T>
		struct pointer_traits<T*>
		{
				typedef T* pointer;

				typedef T element_type;

				typedef std::ptrdiff_t difference_type;

				template <typename Up>
				struct rebind
				{
						typedef typename kerbal::memory::detail::pointer_traits_rebind_helper<T*, Up>::type other;
				};

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_POINTER_TRAITS_HPP
