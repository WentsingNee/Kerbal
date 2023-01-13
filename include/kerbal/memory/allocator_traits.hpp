/**
 * @file       allocator_traits.hpp
 * @brief
 * @date       2020-03-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_HPP

#include <kerbal/memory/allocator/std_allocator.fwd.hpp>
#include <kerbal/memory/allocator/std_pmr_allocator.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/pointer_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/type_traits/add_lvalue_reference.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_empty.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>
#include <kerbal/type_traits/void_type.hpp>
#include <kerbal/utility/declval.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#	include <kerbal/tmp/tppter.hpp>
#	include <kerbal/tmp/type_vector.hpp>
#	include <kerbal/type_traits/enable_if.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_destructible.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_pointer: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_pointer<Alloc, typename kerbal::type_traits::void_type<typename Alloc::pointer>::type>
				: kerbal::type_traits::true_type
		{
		};

		template <typename Alloc>
		struct allocator_could_use_pointer_def : kerbal::memory::allocator_has_def_pointer<Alloc>
		{
		};

#	if __cplusplus >= 201703L

		template <typename T>
		struct allocator_could_use_pointer_def<std::allocator<T> >: kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_could_use_pointer_def<Alloc>::value>
			struct allocator_pointer_traits_helper
			{
					typedef typename Alloc::value_type* type;
			};

			template <typename Alloc>
			struct allocator_pointer_traits_helper<Alloc, true>
			{
					typedef typename Alloc::pointer type;
			};

		} // namespace detail



		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_const_pointer: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_const_pointer<Alloc, typename kerbal::type_traits::void_type<typename Alloc::const_pointer>::type>
				: kerbal::type_traits::true_type
		{
		};

		template <typename Alloc>
		struct allocator_could_use_const_pointer_def : kerbal::memory::allocator_has_def_const_pointer<Alloc>
		{
		};

#	if __cplusplus >= 201703L

		template <typename T>
		struct allocator_could_use_const_pointer_def<std::allocator<T> >: kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_could_use_const_pointer_def<Alloc>::value>
			struct allocator_const_pointer_traits_helper
			{
				private:
					typedef typename Alloc::value_type value_type;
					typedef typename allocator_pointer_traits_helper<Alloc>::type pointer;

				public:
					typedef typename kerbal::memory::pointer_traits<pointer>::template rebind<const value_type>::other type;
			};

			template <typename Alloc>
			struct allocator_const_pointer_traits_helper<Alloc, true>
			{
					typedef typename Alloc::const_pointer type;
			};

		} // namespace detail



		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_void_pointer: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_void_pointer<Alloc, typename kerbal::type_traits::void_type<typename Alloc::void_pointer>::type>
				: kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_def_void_pointer<Alloc>::value>
			struct allocator_void_pointer_traits_helper
			{
				private:
					typedef typename allocator_pointer_traits_helper<Alloc>::type pointer;

				public:
					typedef typename kerbal::memory::pointer_traits<pointer>::template rebind<void>::other type;
			};

			template <typename Alloc>
			struct allocator_void_pointer_traits_helper<Alloc, true>
			{
					typedef typename Alloc::void_pointer type;
			};

		} // namespace detail



		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_const_void_pointer: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_const_void_pointer<Alloc, typename kerbal::type_traits::void_type<typename Alloc::const_void_pointer>::type>
				: kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_def_const_void_pointer<Alloc>::value>
			struct allocator_const_void_pointer_traits_helper
			{
				private:
					typedef typename allocator_pointer_traits_helper<Alloc>::type pointer;

				public:
					typedef typename kerbal::memory::pointer_traits<pointer>::template rebind<const void>::other type;
			};

			template <typename Alloc>
			struct allocator_const_void_pointer_traits_helper<Alloc, true>
			{
					typedef typename Alloc::const_void_pointer type;
			};

		} // namespace detail



		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_difference_type: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_difference_type<Alloc, typename kerbal::type_traits::void_type<typename Alloc::difference_type>::type>
				: kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_def_difference_type<Alloc>::value>
			struct allocator_difference_type_traits_helper
			{
				private:
					typedef typename allocator_pointer_traits_helper<Alloc>::type pointer;

				public:
					typedef typename kerbal::memory::pointer_traits<pointer>::difference_type type;
			};

			template <typename Alloc>
			struct allocator_difference_type_traits_helper<Alloc, true>
			{
					typedef typename Alloc::difference_type type;
			};

		} // namespace detail



		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_size_type: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_size_type<Alloc, typename kerbal::type_traits::void_type<typename Alloc::size_type>::type>
				: kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_def_size_type<Alloc>::value>
			struct allocator_size_type_traits_helper
			{
				private:
					typedef typename allocator_pointer_traits_helper<Alloc>::type pointer;
					typedef typename kerbal::memory::pointer_traits<pointer>::difference_type difference_type;

				public:
					typedef typename kerbal::type_traits::make_unsigned<difference_type>::type type;
			};

			template <typename Alloc>
			struct allocator_size_type_traits_helper<Alloc, true>
			{
					typedef typename Alloc::size_type type;
			};

		} // namespace detail



		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_propagate_on_container_copy_assignment: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_propagate_on_container_copy_assignment
				<Alloc, typename kerbal::type_traits::void_type<typename Alloc::propagate_on_container_copy_assignment>::type>
				: kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_def_propagate_on_container_copy_assignment<Alloc>::value>
			struct allocator_propagate_on_container_copy_assignment_traits_helper : kerbal::type_traits::false_type
			{
			};

			template <typename Alloc>
			struct allocator_propagate_on_container_copy_assignment_traits_helper<Alloc, true>
					: kerbal::type_traits::bool_constant<
							Alloc::propagate_on_container_copy_assignment::value
					>
			{
			};

		} // namespace detail



		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_propagate_on_container_move_assignment: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_propagate_on_container_move_assignment
				<Alloc, typename kerbal::type_traits::void_type<typename Alloc::propagate_on_container_move_assignment>::type>
				: kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_def_propagate_on_container_move_assignment<Alloc>::value>
			struct allocator_propagate_on_container_move_assignment_traits_helper : kerbal::type_traits::false_type
			{
			};

			template <typename Alloc>
			struct allocator_propagate_on_container_move_assignment_traits_helper<Alloc, true>
					: kerbal::type_traits::bool_constant<
							Alloc::propagate_on_container_move_assignment::value
					>
			{
			};

		} // namespace detail



		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_propagate_on_container_swap: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_propagate_on_container_swap
				<Alloc, typename kerbal::type_traits::void_type<typename Alloc::propagate_on_container_swap>::type>
				: kerbal::type_traits::true_type
		{
		};

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_has_def_propagate_on_container_swap<Alloc>::value>
			struct allocator_propagate_on_container_swap_traits_helper: kerbal::type_traits::false_type
			{
			};

			template <typename Alloc>
			struct allocator_propagate_on_container_swap_traits_helper<Alloc, true>
					: kerbal::type_traits::bool_constant<
							Alloc::propagate_on_container_swap::value
					>
			{
			};

		} // namespace detail



		template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_is_always_equal: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc>
		struct allocator_has_def_is_always_equal
				<Alloc, typename kerbal::type_traits::void_type<typename Alloc::is_always_equal>::type>
				: kerbal::type_traits::true_type
		{
		};

		template <typename Alloc>
		struct allocator_could_use_is_always_equal : kerbal::memory::allocator_has_def_is_always_equal<Alloc>
		{
		};

#	if __cplusplus > 201703L

		template <typename Tp>
		struct allocator_could_use_is_always_equal<std::allocator<Tp> >: kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_could_use_is_always_equal<Alloc>::value>
			struct allocator_is_always_equal_traits_helper:
					kerbal::type_traits::tribool_is_true<
						kerbal::type_traits::try_test_is_empty<Alloc>
					>
			{
			};

			template <typename Alloc>
			struct allocator_is_always_equal_traits_helper<Alloc, true>
					: kerbal::type_traits::bool_constant<
							Alloc::is_always_equal::value
					>
			{
			};

#		if __cplusplus < 201103L

			template <typename T>
			struct allocator_is_always_equal_traits_helper<std::allocator<T>, false>
					: kerbal::type_traits::true_type
			{
			};

#		endif

		} // namespace detail



		template <typename Alloc, typename , typename = kerbal::type_traits::void_type<>::type>
		struct allocator_has_def_rebind_alloc: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc, typename Up>
		struct allocator_has_def_rebind_alloc<Alloc, Up, typename kerbal::type_traits::void_type<typename Alloc::template rebind<Up>::other>::type>
				: kerbal::type_traits::true_type
		{
		};

		template <typename Alloc, typename Up>
		struct allocator_could_use_rebind_alloc : kerbal::memory::allocator_has_def_rebind_alloc<Alloc, Up>
		{
		};

#	if __cplusplus >= 201703L

		template <typename Tp, typename Up>
		struct allocator_could_use_rebind_alloc<std::allocator<Tp>, Up>: kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc, typename Up>
			struct pointer_traits_rebind_impl;

#		if __cplusplus >= 201103L

			template <typename Tp, typename ... Args, typename Up, template <typename, typename ...> class AllocTem>
			struct pointer_traits_rebind_impl<AllocTem<Tp, Args...>, Up>
			{
					typedef AllocTem<Up, Args...> type;
			};

#		else

			template <typename Tp, typename Up, template <typename> class AllocTem>
			struct pointer_traits_rebind_impl<AllocTem<Tp>, Up>
			{
					typedef AllocTem<Up> type;
			};

#		endif // __cplusplus >= 201103L

			template <typename Alloc, typename Up, bool = kerbal::memory::allocator_could_use_rebind_alloc<Alloc, Up>::value>
			struct allocator_traits_rebind_alloc_helper: pointer_traits_rebind_impl<Alloc, Up>
			{
			};

			template <typename Alloc, typename Up>
			struct allocator_traits_rebind_alloc_helper<Alloc, Up, true>
			{
					typedef typename Alloc::template rebind<Up>::other type;
			};

		} // namespace detail



#	if __cplusplus >= 201103L

		namespace detail
		{

			template <typename Alloc, typename T, typename ... Args>
			struct allocator_has_construct_helper
			{
				private:
					typedef char NO [1];
					typedef char YES [2];

					template <typename Alloc2>
					static NO* test(...);

					template <typename Alloc2, typename =
							kerbal::type_traits::integral_constant<
								std::size_t,
								sizeof(
									kerbal::utility::declval<Alloc2&>().construct(
										kerbal::utility::declval<T*>(),
										kerbal::utility::declval<Args>()...
									),
									0
								)
							>
					>
					static YES* test(int);

				public:
					typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::is_same<decltype(test<Alloc>(0)), YES*>::value,
						kerbal::type_traits::true_type,
						kerbal::type_traits::false_type
					>::type type;
			};

		} // namespace detail

		template <typename Alloc, typename T, typename ... Args>
		struct allocator_has_construct: kerbal::memory::detail::allocator_has_construct_helper<Alloc, T, Args...>::type
		{
		};

#	else // __cplusplus >= 201103L

		namespace detail
		{

			template <typename Alloc, typename T, typename TVec, typename = kerbal::type_traits::void_type<>::type>
			struct allocator_has_construct_helper
			{
					typedef kerbal::type_traits::false_type type;
			};

#		define EMPTY
#		define REMAINF(exp) exp
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE2(i) kerbal::utility::declval<TARGS_USE(i)>()
#		define TARGS_USE3(i) typename kerbal::type_traits::enable_if<!kerbal::type_traits::is_same<TARGS_USE(i), kerbal::tmp::tppter>::value>::type
#		define DBODY(i) \
			template <typename Alloc, typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			struct allocator_has_construct_helper<Alloc, T, kerbal::tmp::type_vector<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)>, \
										typename kerbal::type_traits::void_type< \
											kerbal::type_traits::integral_constant< \
												std::size_t, \
												sizeof( \
													kerbal::utility::declval<Alloc &>().construct( \
														kerbal::utility::declval<T*>() \
														KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE2, i) \
													), \
													0 \
												) \
											> \
											KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE3, i) \
										>::type \
			> \
			{ \
					typedef kerbal::type_traits::true_type type; \
			};

			KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef REMAINF
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef TARGS_USE
#		undef TARGS_USE2
#		undef TARGS_USE3
#		undef DBODY

		} // namespace detail


#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i) = kerbal::tmp::tppter

		template <typename Alloc, typename T, KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_DECL, 20)>
		struct allocator_has_construct;

#	undef TARGS_DECL


#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#	define DBODY(i) \
		template <typename Alloc, typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		struct allocator_has_construct<Alloc, T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i) > : \
			detail::allocator_has_construct_helper<Alloc, T, kerbal::tmp::type_vector<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> >::type \
		{ \
		};

		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef DBODY

#	endif // __cplusplus >= 201103L


#	if __cplusplus >= 201103L

		template <typename Alloc, typename T, typename ... Args>
		struct allocator_could_use_construct : kerbal::memory::allocator_has_construct<Alloc, T, Args...>
		{
		};

#	else // __cplusplus >= 201103L

#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i) = kerbal::tmp::tppter
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)

		template <typename Alloc, typename T, KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_DECL, 19)>
		struct allocator_could_use_construct : kerbal::memory::allocator_has_construct<Alloc, T, KERBAL_PPEXPAND_WITH_COMMA_N(TARGS_USE, 19)>
		{
		};

#	undef TARGS_DECL

#	endif // __cplusplus >= 201103L


#	if __cplusplus >= 201703L

		template <typename T, typename ... Args>
		struct allocator_could_use_construct<std::allocator<T>, T, Args...>: kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc>
			struct allocator_traits_construct_helper
			{

#	if __cplusplus >= 201103L

				private:
					template <typename T, typename ... Args>
					KERBAL_CONSTEXPR20
					static void k_construct(kerbal::type_traits::false_type, Alloc&, T* p, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::memory::construct_at(p, kerbal::utility::forward<Args>(args)...))
							)
					{
						kerbal::memory::construct_at(p, kerbal::utility::forward<Args>(args)...);
					}

					template <typename T, typename ... Args>
					KERBAL_CONSTEXPR14
					static void k_construct(kerbal::type_traits::true_type, Alloc& alloc, T* p, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(alloc.construct(p, kerbal::utility::forward<Args>(args)...))
							)
					{
						alloc.construct(p, kerbal::utility::forward<Args>(args)...);
					}

				public:
					template <typename T, typename ... Args>
					KERBAL_CONSTEXPR14
					static void construct(Alloc& alloc, T* p, Args&& ... args)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept
									(k_construct(allocator_could_use_construct<Alloc, T, Args...>(), alloc, p,
												  kerbal::utility::forward<Args>(args)...)
								)
							)
					{
						k_construct(allocator_could_use_construct<Alloc, T, Args...>(), alloc, p,
									kerbal::utility::forward<Args>(args)...);
					}

#	else // __cplusplus >= 201103L

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define DBODY(i) \
				private: \
					template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static void k_construct(kerbal::type_traits::false_type, Alloc&, T* p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
					{ \
						kerbal::memory::construct_at(p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					} \
 \
					template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static void k_construct(kerbal::type_traits::true_type, Alloc& alloc, T* p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
					{ \
						alloc.construct(p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					} \
 \
				public: \
					template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					static void construct(Alloc& alloc, T* p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
					{ \
						k_construct(allocator_could_use_construct<Alloc, T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)>(), alloc, p \
									KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					}

				KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef TARGS_USE
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef DBODY

#	endif // __cplusplus >= 201103L

			};

		} // namespace detail



		template <typename Alloc, typename T, typename = kerbal::type_traits::void_type<>::type >
		struct allocator_has_destroy: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc, typename T>
		struct allocator_has_destroy<Alloc, T, typename kerbal::type_traits::void_type<
#	if __cplusplus >= 201103L // compatible with msvc
				decltype(
					kerbal::utility::declval<Alloc&>().destroy(
							kerbal::utility::declval<T*>()
					)
				)
#	else
				kerbal::type_traits::integral_constant<
					std::size_t,
					sizeof(
						kerbal::utility::declval<Alloc&>().destroy(
							kerbal::utility::declval<T*>()
						),
						0
					)
				>
#	endif
		>::type >: kerbal::type_traits::true_type
		{
		};

		template <typename Alloc, typename T>
		struct allocator_could_use_destroy : kerbal::memory::allocator_has_destroy<Alloc, T>
		{
		};

#	if __cplusplus >= 201703L

		template <typename T, typename U>
		struct allocator_could_use_destroy<std::allocator<T>, U>: kerbal::type_traits::false_type
		{
		};

#	endif

#	if __cplusplus > 201703L

		template <typename T, typename U>
		struct allocator_could_use_destroy<std::pmr::polymorphic_allocator<T>, U>: kerbal::type_traits::false_type
		{
		};

#	endif

		namespace detail
		{

			template <typename Alloc>
			struct allocator_traits_destroy_helper
			{

				private:
					template <typename T>
					KERBAL_CONSTEXPR20
					static void k_destroy(kerbal::type_traits::false_type, Alloc &, T * p)
											KERBAL_CONDITIONAL_NOEXCEPT(
													kerbal::type_traits::tribool_is_true<
														kerbal::type_traits::try_test_is_nothrow_destructible<T>
													>::value
											)
					{
						kerbal::memory::destroy_at(p);
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					static void k_destroy(kerbal::type_traits::true_type, Alloc & alloc, T * p)
											KERBAL_CONDITIONAL_NOEXCEPT(
													noexcept(alloc.destroy(p))
											)
					{
						alloc.destroy(p);
					}

				public:
					template <typename T>
					KERBAL_CONSTEXPR14
					static void destroy(Alloc & alloc, T * p)
											KERBAL_CONDITIONAL_NOEXCEPT(
													noexcept(k_destroy(allocator_could_use_destroy<Alloc, T>(), alloc, p))
											)
					{
						k_destroy(allocator_could_use_destroy<Alloc, T>(), alloc, p);
					}

			};

		} // namespace detail



		namespace detail
		{

			template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
			struct allocator_has_max_size_helper : kerbal::type_traits::false_type
			{
			};

			template <typename Alloc>
			struct allocator_has_max_size_helper<Alloc, typename kerbal::type_traits::void_type<
#	if __cplusplus >= 201103L // compatible with msvc
					decltype(static_cast<std::size_t>(kerbal::utility::declval<const Alloc&>().max_size()))
#	else
					kerbal::type_traits::integral_constant<
						std::size_t,
						sizeof(
							static_cast<std::size_t>(kerbal::utility::declval<const Alloc&>().max_size()),
							0
						)
					>
#	endif
			>::type>: kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		template <typename Alloc>
		struct allocator_has_max_size : detail::allocator_has_max_size_helper<Alloc>
		{
		};


		template <typename Alloc>
		struct allocator_could_use_max_size : kerbal::memory::allocator_has_max_size<Alloc>
		{
		};

#	if __cplusplus >= 201703L

		template <typename T>
		struct allocator_could_use_max_size<std::allocator<T> >: kerbal::type_traits::false_type
		{
		};

#	endif


		namespace detail
		{

			template <typename Alloc, bool = kerbal::memory::allocator_could_use_max_size<Alloc>::value>
			struct allocator_traits_max_size_helper
			{
				private:
					typedef typename Alloc::value_type value_type;
					typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type size_type;

				public:
					KERBAL_CONSTEXPR
					static size_type max_size(const Alloc & /*alloc*/)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(value_type))
							)
					{
						return kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(value_type);
					}
			};

			template <typename Alloc>
			struct allocator_traits_max_size_helper<Alloc, true>
			{
				private:
					typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<Alloc>::type size_type;

				public:
					KERBAL_CONSTEXPR
					static size_type max_size(const Alloc & alloc)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(kerbal::utility::declval<const Alloc&>().max_size())
							)
					{
						return alloc.max_size();
					}
			};

		} // namespace detail



		template <typename Alloc>
		struct allocator_traits
		{
				typedef Alloc allocator_type;

				typedef typename allocator_type::value_type value_type;

				typedef typename kerbal::memory::detail::allocator_pointer_traits_helper<allocator_type>::type pointer;

				typedef typename kerbal::memory::detail::allocator_const_pointer_traits_helper<allocator_type>::type const_pointer;

				typedef typename kerbal::memory::detail::allocator_void_pointer_traits_helper<allocator_type>::type void_pointer;

				typedef typename kerbal::memory::detail::allocator_const_void_pointer_traits_helper<allocator_type>::type const_void_pointer;

				typedef typename kerbal::memory::detail::allocator_difference_type_traits_helper<allocator_type>::type difference_type;

				typedef typename kerbal::memory::detail::allocator_size_type_traits_helper<allocator_type>::type size_type;

				typedef kerbal::memory::detail::allocator_propagate_on_container_copy_assignment_traits_helper<allocator_type> propagate_on_container_copy_assignment;

				typedef kerbal::memory::detail::allocator_propagate_on_container_move_assignment_traits_helper<allocator_type> propagate_on_container_move_assignment;

				typedef kerbal::memory::detail::allocator_propagate_on_container_swap_traits_helper<allocator_type> propagate_on_container_swap;

				typedef kerbal::memory::detail::allocator_is_always_equal_traits_helper<allocator_type> is_always_equal;

				template <typename Up>
				struct rebind_alloc
				{
						typedef typename kerbal::memory::detail::allocator_traits_rebind_alloc_helper<Alloc, Up>::type other;
				};

				template <typename Up>
				struct rebind_traits
				{
						typedef kerbal::memory::allocator_traits<typename rebind_alloc<Up>::other> other;
				};

				KERBAL_CONSTEXPR14
				static pointer allocate(allocator_type & alloc, size_type n)
													KERBAL_CONDITIONAL_NOEXCEPT(
															noexcept(alloc.allocate(n))
													)
				{
					return alloc.allocate(n);
				}

				KERBAL_CONSTEXPR14
				static void deallocate(allocator_type & alloc, pointer p, size_type n)
													KERBAL_CONDITIONAL_NOEXCEPT(
															noexcept(alloc.deallocate(p, n))
													)
				{
					alloc.deallocate(p, n);
				}

#		if __cplusplus >= 201103L

				template <typename T, typename ... Args>
				KERBAL_CONSTEXPR14
				static void construct(Alloc & alloc, T * p, Args&& ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::detail::allocator_traits_construct_helper<Alloc>::construct(alloc, p, kerbal::utility::forward<Args>(args)...)
							)
						)
				{
					kerbal::memory::detail::allocator_traits_construct_helper<Alloc>::construct(alloc, p, kerbal::utility::forward<Args>(args)...);
				}

#		else

			private:
				typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::is_same<value_type, void>::value,
						void*,
						typename kerbal::type_traits::add_lvalue_reference<const value_type>::type
				>::type cxx98_construct_cref;

			public:

				template <typename T>
				static void construct(Alloc & alloc, T * p, cxx98_construct_cref val)
				{
					alloc.construct(p, val);
				}

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				static void construct(Alloc & alloc, T * p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					kerbal::memory::detail::allocator_traits_construct_helper<Alloc>::construct(alloc, p KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		endif // __cplusplus >= 201103L

				template <typename T>
				KERBAL_CONSTEXPR14
				static void destroy(Alloc & alloc, T * p)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(kerbal::memory::detail::allocator_traits_destroy_helper<Alloc>::destroy(alloc, p))
								)
				{
					kerbal::memory::detail::allocator_traits_destroy_helper<Alloc>::destroy(alloc, p);
				}

				KERBAL_CONSTEXPR
				static size_type max_size(const Alloc & alloc)
								KERBAL_CONDITIONAL_NOEXCEPT(
										noexcept(kerbal::memory::detail::allocator_traits_max_size_helper<Alloc>::max_size(alloc))
								)
				{
					return kerbal::memory::detail::allocator_traits_max_size_helper<Alloc>::max_size(alloc);
				}

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_HPP
