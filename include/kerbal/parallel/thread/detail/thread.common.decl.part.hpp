/**
 * @file       thread.common.decl.part.hpp
 * @brief
 * @date       2023-07-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_DETAIL_THREAD_COMMON_DECL_PART_HPP
#define KERBAL_PARALLEL_THREAD_DETAIL_THREAD_COMMON_DECL_PART_HPP

#include <kerbal/parallel/thread/thread.fwd.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/function/invoke_r.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/decay.hpp>
#include <kerbal/utility/noncopyable.hpp>
#include <kerbal/utility/tuple.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/utility/integer_sequence.hpp>
#endif

#include <exception> // std::terminate


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


			class basic_thread_allocator_unrelated : private kerbal::utility::noncopyable
			{
				public:
					typedef kerbal::parallel::detail::thread_native_handle_type native_handle_type;

					class id
					{
						public:
							friend class basic_thread_allocator_unrelated;

							template <typename Allocator>
							friend class kerbal::parallel::basic_thread;

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

				protected:
					id k_th_id;

				public:

					KERBAL_CONSTEXPR
					basic_thread_allocator_unrelated() KERBAL_NOEXCEPT :
						k_th_id()
					{
					}

#	if __cplusplus >= 201103L

				public:

					KERBAL_CONSTEXPR14
					basic_thread_allocator_unrelated(basic_thread_allocator_unrelated && ano) KERBAL_NOEXCEPT :
						k_th_id(ano.k_th_id)
					{
						ano.k_th_id = id();
					}

#	endif

				public:

					~basic_thread_allocator_unrelated()
					{
						if (this->joinable()) {
							std::terminate();
						}
					}

#	if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					basic_thread_allocator_unrelated & operator=(basic_thread_allocator_unrelated && ano) KERBAL_NOEXCEPT
					{
						this->swap(ano);
						return *this;
					}

#	endif

					KERBAL_CONSTEXPR
					bool joinable() const KERBAL_NOEXCEPT
					{
						return this->k_th_id != id();
					}

					void join();

					void detach();

					KERBAL_CONSTEXPR14
					void swap(basic_thread_allocator_unrelated & ano) KERBAL_NOEXCEPT
					{
						kerbal::algorithm::swap(this->k_th_id, ano.k_th_id);
					}

					KERBAL_CONSTEXPR
					id get_id() const KERBAL_NOEXCEPT
					{
						return this->k_th_id;
					}

					KERBAL_CONSTEXPR
					native_handle_type native_handle() const KERBAL_NOEXCEPT
					{
						return this->get_id().native_handle;
					}

			};

		} // namespace detail



		template <typename Allocator>
		class basic_thread : private kerbal::parallel::detail::basic_thread_allocator_unrelated
		{
			private:
				typedef kerbal::parallel::detail::basic_thread_allocator_unrelated super;

			public:
				typedef super::native_handle_type native_handle_type;
				typedef super::id id;

			private:
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

#	if __cplusplus >= 201103L

				basic_thread() = default;

#	else

				basic_thread() KERBAL_NOEXCEPT :
					super()
				{
				}

#	endif

			private:

#	if __cplusplus >= 201103L

				template <typename PackAllocator, typename Callable, typename ... Args>
				static typename detail::fun_args_pack_type<Callable, Args...>::type *
				k_build_fun_args_pack(PackAllocator & alloc, Callable && fun, Args && ... args);

#	else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
				template <typename PackAllocator, typename Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				static typename detail::fun_args_pack_type<Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i)>::type * \
				k_build_fun_args_pack(PackAllocator & alloc, Callable fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \

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
				static void k_destroy_fun_args_pack(PackAllocator & alloc, FunArgsPack * fun_args_pack_p) KERBAL_NOEXCEPT;


#	if __cplusplus >= 201103L

			private:

				template <typename Callable, typename ... Args, std::size_t ... I>
				static void apply(
					kerbal::utility::tuple<Callable, Args...> & pack,
					kerbal::utility::integer_sequence<std::size_t, I...>
				)
				{
					kerbal::function::invoke_r<void>(
						pack.template get<0>(),
						kerbal::compatibility::move(pack.template get<I + 1>())...
					);
				}

			public:

				template <typename Callable, typename ... Args>
				explicit
				basic_thread(Callable && fun, Args && ... args);

#	else

			public:

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define FBODY(i) \
				template <typename Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				explicit \
				basic_thread(Callable fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \

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
					super(static_cast<super &&>(ano))
				{
				}

#	endif

			public:

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				basic_thread & operator=(basic_thread && ano) KERBAL_NOEXCEPT
				{
					this->swap(ano);
					return *this;
				}

#	endif

				using super::joinable;
				using super::join;
				using super::detach;

				KERBAL_CONSTEXPR14
				void swap(basic_thread & ano) KERBAL_NOEXCEPT
				{
					this->super::swap(static_cast<super &>(ano));
				}

				using super::get_id;
				using super::native_handle;

				KERBAL_CONSTEXPR
				bool operator==(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->k_th_id == with.k_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->k_th_id != with.k_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator<(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->k_th_id < with.k_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator<=(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->k_th_id <= with.k_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator>(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->k_th_id > with.k_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator>=(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->k_th_id >= with.k_th_id;
				}

		};

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_DETAIL_THREAD_COMMON_DECL_PART_HPP
