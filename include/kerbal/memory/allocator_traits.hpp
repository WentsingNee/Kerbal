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

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/pointer_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>
#include <kerbal/type_traits/void_type.hpp>
#include <kerbal/utility/declval.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <memory>


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
					template <typename Alloc2>
					static kerbal::type_traits::false_type test(...);

					template <typename Alloc2, typename = decltype(kerbal::utility::declval<Alloc2*>()->construct(
							kerbal::utility::declval<T*>(),
							kerbal::utility::declval<Args>()...
					))>
					static kerbal::type_traits::true_type test(int);

					typedef decltype(test<Alloc>(0)) type;
			};

		} // namespace detail

		template <typename Alloc, typename T, typename ... Args>
		struct allocator_has_construct: kerbal::memory::detail::allocator_has_construct_helper<Alloc, T, Args...>::type
		{
		};

		template <typename Alloc, typename T, typename ... Args>
		struct allocator_could_use_construct : kerbal::memory::allocator_has_construct<Alloc, T, Args...>
		{
		};

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
				private:
					template <typename T, typename ... Args>
					KERBAL_CONSTEXPR20
					static void __construct(kerbal::type_traits::false_type, Alloc&, T* p, Args&& ... args)
					{
#			if KERBAL_ENABLE_CONSTEXPR20
						std::construct_at(p, kerbal::utility::forward<Args>(args)...);
#			else
						::new(static_cast<void*>(p)) T(kerbal::utility::forward<Args>(args)...);
#			endif
					}

					template <typename T, typename ... Args>
					KERBAL_CONSTEXPR14
					static void __construct(kerbal::type_traits::true_type, Alloc& alloc, T* p, Args&& ... args)
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
					{
						__construct(allocator_could_use_construct<Alloc, T, Args...>(), alloc, p,
									kerbal::utility::forward<Args>(args)...);
					}

			};

		} // namespace detail

#	endif // __cplusplus >= 201103L



#	if __cplusplus >= 201103L

		template <typename Alloc, typename T, typename = kerbal::type_traits::void_type<>::type >
		struct allocator_has_destroy: kerbal::type_traits::false_type
		{
		};

		template <typename Alloc, typename T>
		struct allocator_has_destroy<Alloc, T, typename kerbal::type_traits::void_type<
				decltype(
					kerbal::utility::declval<Alloc>().destroy(
							kerbal::utility::declval<T*>()
					)
				)
		>::type >: kerbal::type_traits::true_type
		{
		};

		template <typename Alloc, typename T>
		struct allocator_could_use_destroy : kerbal::memory::allocator_has_destroy<Alloc, T>
		{
		};

#	if __cplusplus >= 201703L

		template <typename T>
		struct allocator_could_use_destroy<std::allocator<T>, T>: kerbal::type_traits::false_type
		{
		};

#	endif

#	endif // __cplusplus >= 201103L

		namespace detail
		{

			template <typename Alloc>
			struct allocator_traits_destroy_helper
			{

#		if __cplusplus >= 201103L

				private:
					template <typename T>
					KERBAL_CONSTEXPR20
					static void __destroy(kerbal::type_traits::false_type, Alloc &, T * p)
											KERBAL_CONDITIONAL_NOEXCEPT(
													std::is_nothrow_destructible<T>::value
											)
					{
						p->~T();
					}

					template <typename T>
					KERBAL_CONSTEXPR14
					static void __destroy(kerbal::type_traits::true_type, Alloc & alloc, T * p)
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
													noexcept(__destroy(allocator_could_use_destroy<Alloc, T>(), alloc, p))
											)
					{
						__destroy(allocator_could_use_destroy<Alloc, T>(), alloc, p);
					}

#		else


				public:
					template <typename T>
					KERBAL_CONSTEXPR14
					static void destroy(Alloc & alloc, T * p)
					{
						alloc.destroy(p);
					}

#		endif // __cplusplus >= 201103L

			};

		} // namespace detail



#	if __cplusplus >= 201103L

		namespace detail
		{

			template <typename Alloc, typename = kerbal::type_traits::void_type<>::type>
			struct allocator_has_max_size_helper : kerbal::type_traits::false_type
			{
			};

			template <typename Alloc>
			struct allocator_has_max_size_helper<Alloc, typename kerbal::type_traits::void_type<
																	decltype(kerbal::utility::declval<const Alloc>().max_size())
														>::type>
					: kerbal::type_traits::true_type
			{
			};

		}; // namespace detail

		template <typename Alloc>
		struct allocator_has_max_size : detail::allocator_has_max_size_helper<Alloc>
		{
		};

#	endif

#	if __cplusplus < 201103L

		template <typename Alloc>
		struct allocator_could_use_max_size : kerbal::type_traits::false_type
		{
		};

#	else

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

#	endif // __cplusplus < 201103L

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
									noexcept(kerbal::utility::declval<const Alloc>().max_size())
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
				{
					kerbal::memory::detail::allocator_traits_construct_helper<Alloc>::construct(alloc, p, kerbal::utility::forward<Args>(args)...);
				}

#		else

				template <typename T>
				static void construct(Alloc & alloc, T * p, const value_type & val)
				{
					alloc.construct(p, val);
				}

				template <typename T>
				static void construct(Alloc &, T * p)
				{
					::new(static_cast<void*>(p)) T();
				}

				template <typename T, typename Arg0>
				static void construct(Alloc &, T * p, const Arg0& arg0)
				{
					::new(static_cast<void*>(p)) T(arg0);
				}

				template <typename T, typename Arg0, typename Arg1>
				static void construct(Alloc &, T * p, const Arg0& arg0, const Arg1& arg1)
				{
					::new(static_cast<void*>(p)) T(arg0, arg1);
				}

				template <typename T, typename Arg0, typename Arg1, typename Arg2>
				static void construct(Alloc &, T * p, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
				{
					::new(static_cast<void*>(p)) T(arg0, arg1, arg2);
				}

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
