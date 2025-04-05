/**
 * @file       is_invocable.cxx11.part.hpp
 * @brief
 * @date       2024-04-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_INVOKE_DETAIL_IS_INVOCABLE_CXX11_PART_HPP
#define KERBAL_FUNCTION_INVOKE_DETAIL_IS_INVOCABLE_CXX11_PART_HPP

#include <kerbal/config/compiler_id.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/type_traits/yes_no_type.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/reference_wrapper.hpp>

#include <kerbal/function/invoke/invoke_overload_ver_selector.hpp>


namespace kerbal
{

	namespace function
	{

		namespace detail
		{

			template <typename Ver, typename Fun, typename ... Args>
			struct is_invocable_helper;

			/*
			 * f()
			 */
			template <typename Fun_, typename ... Args_>
			struct is_invocable_helper<
				INVOKE_OVERLOAD_VER_CALLABLE,
				Fun_, Args_...
			>
			{
				private:
					template <typename Fun, typename ... Args>
					static kerbal::type_traits::no_type test(...);

#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC // could not handle private member under msvc
			
					template <typename Fun, typename ... Args>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
						kerbal::utility::declval<Fun>()(kerbal::utility::declval<Args>()...),
						0
					)]);

#	else

					template <typename Fun, typename ... Args>
					static kerbal::type_traits::yes_type test(char *, decltype(
						kerbal::utility::declval<Fun>()(kerbal::utility::declval<Args>()...),
						0
					) = 0);

#	endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<Fun_, Args_...>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;

			};


			template <typename MemObjPtr, typename TOri, typename T, typename ... Args>
			struct is_invocable_helper_of_mem_obj;

			template <typename MemObjPtr, typename TOri, typename T, typename U, typename ... Args>
			struct is_invocable_helper_of_mem_obj<MemObjPtr, TOri, T, U, Args...>
			{
				public:
					typedef kerbal::type_traits::false_type type;
			};

			/*
			 * obj.*mem
			 */
			template <typename MemObjPtr_, typename TOri_, typename T>
			struct is_invocable_helper_of_mem_obj<
				MemObjPtr_,
				TOri_, T
			>
			{
				private:
					template <typename MemObjPtr, typename TOri>
					static kerbal::type_traits::no_type test(...);

#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC // could not handle private member under msvc
			
					template <typename MemObjPtr, typename TOri>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
						kerbal::utility::declval<TOri>().*(kerbal::utility::declval<MemObjPtr>()),
						0
					)]);

#	else

					template <typename MemObjPtr, typename TOri>
					static kerbal::type_traits::yes_type test(char *, decltype(
						kerbal::utility::declval<TOri>().*(kerbal::utility::declval<MemObjPtr>()),
						0
					) = 0);

#	endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<MemObjPtr_, TOri_>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;

			};

			/*
			 * obj->*mem
			 */
			template <typename MemObjPtr_, typename TOri_, typename T>
			struct is_invocable_helper_of_mem_obj<
				MemObjPtr_,
				TOri_, T *
			>
			{
				private:
					template <typename MemObjPtr, typename TOri>
					static kerbal::type_traits::no_type test(...);

#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC // could not handle private member under msvc
			
					template <typename MemObjPtr, typename TOri>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
						kerbal::utility::declval<TOri>()->*(kerbal::utility::declval<MemObjPtr>()),
						0
					)]);

#	else

					template <typename MemObjPtr, typename TOri>
					static kerbal::type_traits::yes_type test(char *, decltype(
						kerbal::utility::declval<TOri>()->*(kerbal::utility::declval<MemObjPtr>()),
						0
					) = 0);

#	endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<MemObjPtr_, TOri_>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;

			};

			/*
			 * obj.get().*mem
			 */
			template <typename MemObjPtr_, typename TOri_, typename T>
			struct is_invocable_helper_of_mem_obj<
				MemObjPtr_,
				TOri_, kerbal::utility::reference_wrapper<T>
			>
			{
				private:
					template <typename MemObjPtr, typename TOri>
					static kerbal::type_traits::no_type test(...);

#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC // could not handle private member under msvc
			
					template <typename MemObjPtr, typename TOri>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
						kerbal::utility::declval<TOri>().get().*(kerbal::utility::declval<MemObjPtr>()),
						0
					)]);

#	else

					template <typename MemObjPtr, typename TOri>
					static kerbal::type_traits::yes_type test(char *, decltype(
						kerbal::utility::declval<TOri>().get().*(kerbal::utility::declval<MemObjPtr>()),
						0
					) = 0);

#	endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<MemObjPtr_, TOri_>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;

			};

			template <typename MemObjPtr, typename T, typename ... Args>
			struct is_invocable_helper<
				INVOKE_OVERLOAD_VER_MEM_OBJ,
				MemObjPtr, T, Args...
			> :
				is_invocable_helper_of_mem_obj<
					MemObjPtr,
					T, typename kerbal::type_traits::remove_cvref<T>::type,
					Args...
				>
			{
			};


			/*
			 * obj.*mem()
			 */
			template <typename MemFunPtr_, typename TOri_, typename T, typename ... Args_>
			struct is_invocable_helper_of_mem_fun
			{
				private:
					template <typename MemFunPtr, typename TOri, typename ... Args>
					static kerbal::type_traits::no_type test(...);

#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC // could not handle private member under msvc
			
					template <typename MemFunPtr, typename TOri, typename ... Args>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
						(kerbal::utility::declval<TOri>().*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...),
						0
					)]);

#	else

					template <typename MemFunPtr, typename TOri, typename ... Args>
					static kerbal::type_traits::yes_type test(char *, decltype(
						(kerbal::utility::declval<TOri>().*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...),
						0
					) = 0);

#	endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<MemFunPtr_, TOri_, Args_...>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;

			};

			/*
			 * obj->*mem()
			 */
			template <typename MemFunPtr_, typename TOri_, typename T, typename ... Args_>
			struct is_invocable_helper_of_mem_fun<
				MemFunPtr_,
				TOri_, T *, Args_...
			>
			{
				private:
					template <typename MemFunPtr, typename TOri, typename ... Args>
					static kerbal::type_traits::no_type test(...);

#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC // could not handle private member under msvc
			
					template <typename MemFunPtr, typename TOri, typename ... Args>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
						(kerbal::utility::declval<TOri>()->*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...),
						0
					)]);

#	else

					template <typename MemFunPtr, typename TOri, typename ... Args>
					static kerbal::type_traits::yes_type test(char *, decltype(
						(kerbal::utility::declval<TOri>()->*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...),
						0
					) = 0);

#	endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<MemFunPtr_, TOri_, Args_...>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;

			};

			/*
			 * obj.get().*mem()
			 */
			template <typename MemFunPtr_, typename TOri_, typename T, typename ... Args_>
			struct is_invocable_helper_of_mem_fun<
				MemFunPtr_,
				TOri_, kerbal::utility::reference_wrapper<T>, Args_...
			>
			{
				private:
					template <typename MemFunPtr, typename TOri, typename ... Args>
					static kerbal::type_traits::no_type test(...);

#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_MSVC // could not handle private member under msvc
			
					template <typename MemFunPtr, typename TOri, typename ... Args>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
						(kerbal::utility::declval<TOri>().get().*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...),
						0
					)]);

#	else

					template <typename MemFunPtr, typename TOri, typename ... Args>
					static kerbal::type_traits::yes_type test(char *, decltype(
						(kerbal::utility::declval<TOri>().get().*kerbal::utility::declval<MemFunPtr>())
							(kerbal::utility::declval<Args>()...),
						0
					) = 0);

#	endif

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<MemFunPtr_, TOri_, Args_...>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;

			};

			template <typename MemFunPtr, typename T, typename ... Args>
			struct is_invocable_helper<
				INVOKE_OVERLOAD_VER_MEM_FUN,
				MemFunPtr, T, Args...
			> :
				is_invocable_helper_of_mem_fun<
					MemFunPtr,
					T, typename kerbal::type_traits::remove_cvref<T>::type,
					Args...
				>
			{
			};

		} // namespace detail


		template <typename Fun, typename ... Args>
		struct is_invocable :
			kerbal::function::detail::is_invocable_helper<
				typename kerbal::function::detail::invoke_overload_ver_selector<Fun, Args...>::type, Fun, Args...
			>::type
		{
		};

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_INVOKE_DETAIL_IS_INVOCABLE_CXX11_PART_HPP
