/**
 * @file       construct.hpp
 * @brief
 * @date       2023-04-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_TRAITS_CONSTRUCT_HPP
#define KERBAL_MEMORY_ALLOCATOR_TRAITS_CONSTRUCT_HPP

#if __cplusplus >= 201703L
#	include <kerbal/memory/allocator/std_allocator/std_allocator.fwd.hpp>
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/declval.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#	include <kerbal/type_traits/yes_no_type.hpp>
#else
#	include <kerbal/tmp/type_vector.hpp>
#	include <kerbal/type_traits/enable_if.hpp>
#	include <kerbal/type_traits/is_same.hpp>
#	include <kerbal/type_traits/void_type.hpp>
#endif

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

#	if __cplusplus >= 201103L

		namespace detail
		{

			template <typename Alloc, typename T, typename ... Args>
			struct allocator_has_construct_helper
			{
				private:
					template <typename Alloc2>
					static kerbal::type_traits::no_type test(...);

					template <typename Alloc2>
					static kerbal::type_traits::yes_type test(char (*)[sizeof(
							kerbal::utility::declval<Alloc2&>().construct(
								kerbal::utility::declval<T*>(),
								kerbal::utility::declval<Args>()...
							),
							0
					)]);

				public:
					typedef kerbal::type_traits::bool_constant<
						sizeof(test<Alloc>(NULL)) == sizeof(kerbal::type_traits::yes_type)
					> type;
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
			kerbal::memory::detail::allocator_has_construct_helper<Alloc, T, kerbal::tmp::type_vector<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> >::type \
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

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_TRAITS_CONSTRUCT_HPP
