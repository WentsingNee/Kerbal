/**
 * @file       thread.decl.hpp
 * @brief
 * @date       2022-05-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_THREAD_DECL_HPP
#define KERBAL_PARALLEL_THREAD_THREAD_DECL_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/decay.hpp>
#include <kerbal/utility/noncopyable.hpp>
#include <kerbal/utility/tuple.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/function/invoke.hpp>
#	include <kerbal/utility/integer_sequence.hpp>
#endif

#include <exception> // std::terminate


#include <kerbal/parallel/thread/thread.fwd.hpp>

#if KERBAL_PARALLEL_THREAD_MODE == KERBAL_PARALLEL_THREAD_MODE_POSIX
#	include <kerbal/parallel/thread/detail/thread.posix.decl.hpp>
#elif KERBAL_PARALLEL_THREAD_MODE == KERBAL_PARALLEL_THREAD_MODE_WIN
#	include <kerbal/parallel/thread/detail/thread.win.decl.hpp>
#else
#	error "Not implemented yet"
#endif


namespace kerbal
{

	namespace parallel
	{

		namespace detail
		{

#	if __cplusplus >= 201103L

				template <typename Callable, typename ... Args>
				struct fun_args_pack_type
				{
						typedef kerbal::utility::tuple<
								typename kerbal::type_traits::decay<Callable>::type,
								typename kerbal::type_traits::decay<Args>::type ...
						> type;
				};

#	else


#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i) = void

				template <typename Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, 20)>
				struct fun_args_pack_type;

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE1(i) KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE2(i) typename kerbal::type_traits::decay<KERBAL_MACRO_CONCAT(Arg, i)>::type
#		define TBODY(i) \
				template <typename Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				struct fun_args_pack_type<Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE1, i)> \
				{ \
						typedef kerbal::utility::tuple< \
								typename kerbal::type_traits::decay<Callable>::type \
								KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE2, i) \
						> type; \
				};

				KERBAL_PPEXPAND_N(TBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(TBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef TARGS_USE1
#		undef TARGS_USE2
#		undef TBODY

#	endif

		} // namespace detail



		template <typename Allocator>
		class basic_thread: private kerbal::utility::noncopyable
		{
			public:
				typedef detail::thread_native_handle_type native_handle_type;

				class id
				{
					public:
						friend class basic_thread;

					private:
						native_handle_type native_handle;

					public:

						KERBAL_CONSTEXPR
						id() KERBAL_NOEXCEPT:
								native_handle(0)
						{
						}

						KERBAL_CONSTEXPR
						explicit id(native_handle_type th_id) KERBAL_NOEXCEPT:
								native_handle(th_id)
						{
						}

						KERBAL_CONSTEXPR
						bool operator==(const id & with) const KERBAL_NOEXCEPT
						{
							return this->native_handle == with.native_handle;
						}

						KERBAL_CONSTEXPR
						bool operator!=(const id & with) const KERBAL_NOEXCEPT
						{
							return this->native_handle != with.native_handle;
						}

						KERBAL_CONSTEXPR
						bool operator<(const id & with) const KERBAL_NOEXCEPT
						{
							return this->native_handle < with.native_handle;
						}

						KERBAL_CONSTEXPR
						bool operator<=(const id & with) const KERBAL_NOEXCEPT
						{
							return this->native_handle <= with.native_handle;
						}

						KERBAL_CONSTEXPR
						bool operator>(const id & with) const KERBAL_NOEXCEPT
						{
							return this->native_handle > with.native_handle;
						}

						KERBAL_CONSTEXPR
						bool operator>=(const id & with) const KERBAL_NOEXCEPT
						{
							return this->native_handle >= with.native_handle;
						}
				};

			private:
				id K_th_id;

				typedef Allocator allocator_type;
				typedef kerbal::memory::allocator_traits<allocator_type> allocator_traits;

				template <typename T>
				static
				typename allocator_traits::template rebind_alloc<T>::other
				rebind_alloc() KERBAL_NOEXCEPT
				{
					return typename allocator_traits::template rebind_alloc<T>::other(allocator_type());
				}

			public:

				KERBAL_CONSTEXPR
				basic_thread() KERBAL_NOEXCEPT :
						K_th_id()
				{
				}

			private:

#	if __cplusplus >= 201103L

				template <typename PackAllocator, typename Callable, typename ... Args>
				static typename detail::fun_args_pack_type<Callable, Args...>::type *
				K_build_fun_args_pack(PackAllocator & alloc, Callable && fun, Args && ... args);

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
				template <typename PackAllocator, typename Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				static typename detail::fun_args_pack_type<Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)>::type * \
				K_build_fun_args_pack(PackAllocator & alloc, Callable fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef TARGS_USE
#		undef ARGS_DECL
#		undef FBODY

#	endif

				template <typename PackAllocator, typename FunArgsPack>
				static void K_destroy_fun_args_pack(PackAllocator & alloc, FunArgsPack * fun_args_pack_p) KERBAL_NOEXCEPT;


#	if __cplusplus >= 201103L

			private:

				template <typename Callable, typename ... Args, std::size_t ... I>
				static void apply(kerbal::utility::tuple<Callable, Args...> & pack,
									kerbal::utility::integer_sequence<std::size_t, I...>)
				{
					kerbal::function::invoke(pack.template get<0>(), pack.template get<I + 1>()...);
				}

			public:

				template <typename Callable, typename ... Args>
				explicit
				basic_thread(Callable&& fun, Args&& ... args);

#	else

			public:

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
				template <typename Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				explicit \
				basic_thread(Callable fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef FBODY

#	endif

#	if __cplusplus >= 201103L

			public:

				KERBAL_CONSTEXPR14
				basic_thread(basic_thread && ano) KERBAL_NOEXCEPT :
						K_th_id(ano.K_th_id)
				{
					ano.K_th_id = id();
				}

#	endif

			public:

				~basic_thread()
				{
					if (this->joinable()) {
						std::terminate();
					}
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				basic_thread & operator=(basic_thread && ano) KERBAL_NOEXCEPT
				{
					this->swap(ano);
					return *this;
				}

#	endif

				KERBAL_CONSTEXPR
				bool joinable() const KERBAL_NOEXCEPT
				{
					return this->K_th_id != id();
				}

				void join();

				void detach();

				KERBAL_CONSTEXPR14
				void swap(basic_thread & ano)
				{
					kerbal::algorithm::swap(this->K_th_id, ano.K_th_id);
				}

				KERBAL_CONSTEXPR
				id get_id() const KERBAL_NOEXCEPT
				{
					return this->K_th_id;
				}

				KERBAL_CONSTEXPR
				native_handle_type native_handle() const KERBAL_NOEXCEPT
				{
					return this->get_id().native_handle;
				}

				KERBAL_CONSTEXPR
				bool operator==(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->K_th_id == with.K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->K_th_id != with.K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator<(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->K_th_id < with.K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator<=(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->K_th_id <= with.K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator>(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->K_th_id > with.K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator>=(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->K_th_id >= with.K_th_id;
				}

		};

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_THREAD_DECL_HPP
