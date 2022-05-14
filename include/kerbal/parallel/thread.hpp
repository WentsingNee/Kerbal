/**
 * @file       thread.hpp
 * @brief
 * @date       2019-8-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_HPP
#define KERBAL_PARALLEL_THREAD_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/decay.hpp>
#include <kerbal/utility/noncopyable.hpp>
#include <kerbal/utility/throw_this_exception.hpp>
#include <kerbal/utility/tuple.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/function/invoke.hpp>
#	include <kerbal/utility/forward.hpp>
#	include <kerbal/utility/integer_sequence.hpp>
#endif

#include <pthread.h>
#include <exception> // std::terminate

#include <kerbal/parallel/thread_create_failed.hpp>


namespace kerbal
{

	namespace parallel
	{

		template <typename Allocator>
		class basic_thread: private kerbal::utility::noncopyable
		{
			public:
				typedef pthread_t native_handle_type;

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
				id _K_th_id;

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
						_K_th_id()
				{
				}

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
				basic_thread(Callable&& fun, Args&& ... args) :
						_K_th_id()
				{
					typedef kerbal::utility::tuple<
							typename kerbal::type_traits::decay<Callable>::type,
							typename kerbal::type_traits::decay<Args>::type ...
					> fun_args_pack_t;

					typedef typename allocator_traits::template rebind_alloc<fun_args_pack_t>::other rebind_allocator;
					typedef typename allocator_traits::template rebind_traits<fun_args_pack_t>::other rebind_allocator_traits;

					struct dealloc_helper
					{
						fun_args_pack_t * p;

						KERBAL_CONSTEXPR
						dealloc_helper(fun_args_pack_t * p) KERBAL_NOEXCEPT :
								p(p)
						{
						}

						~dealloc_helper()
						{
							if (this->p) {
								rebind_allocator alloc(rebind_alloc<fun_args_pack_t>());
								rebind_allocator_traits::deallocate(alloc, this->p, 1);
							}
						}
					};

					struct destroy_helper
					{
						fun_args_pack_t * p;

						KERBAL_CONSTEXPR
						destroy_helper(fun_args_pack_t * p) KERBAL_NOEXCEPT :
								p(p)
						{
						}

						~destroy_helper()
						{
							if (this->p) {
								rebind_allocator alloc(rebind_alloc<fun_args_pack_t>());
								rebind_allocator_traits::destroy(alloc, this->p);
							}
						}
					};

					struct helper
					{
							static void* start_rtn(void * fun_args_pack_v)
							{
								fun_args_pack_t * fun_args_pack_p = static_cast<fun_args_pack_t*>(fun_args_pack_v);
								dealloc_helper dealloc_h(fun_args_pack_p);
								destroy_helper destroy_h(fun_args_pack_p);
								basic_thread::apply(*fun_args_pack_p,
												kerbal::utility::make_index_sequence<sizeof...(Args)>());
								return NULL;
							}
					};

					rebind_allocator alloc(rebind_alloc<fun_args_pack_t>());
					fun_args_pack_t * fun_args_pack_p = rebind_allocator_traits::allocate(alloc, 1);
					dealloc_helper dealloc_h(fun_args_pack_p);

					rebind_allocator_traits::construct(
							alloc, fun_args_pack_p,
							kerbal::utility::forward<Callable>(fun),
							kerbal::utility::forward<Args>(args)...
					);
					destroy_helper destroy_h(fun_args_pack_p);

					void * fun_args_pack_v = reinterpret_cast<void*>(fun_args_pack_p);
					int err = ::pthread_create(&this->_K_th_id.native_handle, NULL, helper::start_rtn, fun_args_pack_v);
					if (err != 0) {
						kerbal::utility::throw_this_exception_helper<
								kerbal::parallel::thread_create_failed
						>::throw_this_exception();
					} else {
						destroy_h.p = NULL;
						dealloc_h.p = NULL;
					}
				}

#	else

			public:

#		define EMPTY
#		define REMAINF(exp) exp
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define TARGS_USE(i) typename kerbal::type_traits::decay<KERBAL_MACRO_CONCAT(Arg, i)>::type
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#		define FUN_ARGS_PACK_EXPAND_ARG(i) (fun_args_pack_p->template get<(i)>())
#		define FBODY(i) \
				template <typename Callable KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				explicit \
				basic_thread(Callable fun KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						_K_th_id() \
				{ \
					typedef kerbal::utility::tuple< \
							typename kerbal::type_traits::decay<Callable>::type \
							KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_USE, i) \
					> fun_args_pack_t; \
					typedef typename allocator_traits::template rebind_alloc<fun_args_pack_t>::other rebind_allocator; \
					typedef typename allocator_traits::template rebind_traits<fun_args_pack_t>::other rebind_allocator_traits; \
 \
					struct dealloc_helper \
					{ \
						fun_args_pack_t * p; \
 \
						KERBAL_CONSTEXPR \
						dealloc_helper(fun_args_pack_t * p) KERBAL_NOEXCEPT : \
								p(p) \
						{ \
						} \
 \
						~dealloc_helper() \
						{ \
							if (this->p) { \
								rebind_allocator alloc(rebind_alloc<fun_args_pack_t>()); \
								rebind_allocator_traits::deallocate(alloc, this->p, 1); \
							} \
						} \
					}; \
 \
					struct destroy_helper \
					{ \
						fun_args_pack_t * p; \
 \
						KERBAL_CONSTEXPR \
						destroy_helper(fun_args_pack_t * p) KERBAL_NOEXCEPT : \
								p(p) \
						{ \
						} \
 \
						~destroy_helper() \
						{ \
							if (this->p) { \
								rebind_allocator alloc(rebind_alloc<fun_args_pack_t>()); \
								rebind_allocator_traits::destroy(alloc, this->p); \
							} \
						} \
					}; \
 \
					struct helper \
					{ \
							static void* start_rtn(void * fun_args_pack_v) \
							{ \
								fun_args_pack_t * fun_args_pack_p = static_cast<fun_args_pack_t*>(fun_args_pack_v); \
								dealloc_helper dealloc_h(fun_args_pack_p); \
								destroy_helper destroy_h(fun_args_pack_p); \
								fun_args_pack_p->template get<0>()(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, FUN_ARGS_PACK_EXPAND_ARG, i)); \
								return NULL; \
							} \
					}; \
 \
					rebind_allocator alloc(rebind_alloc<fun_args_pack_t>()); \
					fun_args_pack_t * fun_args_pack_p = rebind_allocator_traits::allocate(alloc, 1); \
					dealloc_helper dealloc_h(fun_args_pack_p); \
 \
					rebind_allocator_traits::construct( \
							alloc, fun_args_pack_p, \
							fun \
							KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
					); \
					destroy_helper destroy_h(fun_args_pack_p); \
 \
					void * fun_args_pack_v = reinterpret_cast<void*>(fun_args_pack_p); \
					int err = ::pthread_create(&this->_K_th_id.native_handle, NULL, helper::start_rtn, fun_args_pack_v); \
					if (err != 0) { \
						kerbal::utility::throw_this_exception_helper< \
								kerbal::parallel::thread_create_failed \
						>::throw_this_exception(); \
					} else { \
						destroy_h.p = NULL; \
						dealloc_h.p = NULL; \
					} \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#		undef EMPTY
#		undef REMAINF
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef TARGS_USE
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FUN_ARGS_PACK_EXPAND_ARG
#		undef FBODY

#	endif

#	if __cplusplus >= 201103L

			public:

				KERBAL_CONSTEXPR14
				basic_thread(basic_thread&& ano) KERBAL_NOEXCEPT :
						_K_th_id(ano._K_th_id)
				{
					ano._K_th_id = id();
				}

#	endif

			public:

				~basic_thread()
				{
					if (this->joinable()) {
						std::terminate();
					}
				}

				KERBAL_CONSTEXPR
				bool joinable() const KERBAL_NOEXCEPT
				{
					return this->_K_th_id != id();
				}

				void join()
				{
					::pthread_join(this->native_handle(), NULL);
					this->_K_th_id = id();
				}

				void detach()
				{
					::pthread_detach(this->native_handle());
					this->_K_th_id = id();
				}

				KERBAL_CONSTEXPR14
				void swap(basic_thread & ano)
				{
					kerbal::algorithm::swap(this->_K_th_id, ano._K_th_id);
				}

				KERBAL_CONSTEXPR
				id get_id() const KERBAL_NOEXCEPT
				{
					return this->_K_th_id;
				}

				KERBAL_CONSTEXPR
				native_handle_type native_handle() const KERBAL_NOEXCEPT
				{
					return this->get_id().native_handle;
				}

				KERBAL_CONSTEXPR
				bool operator==(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->_K_th_id == with._K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->_K_th_id != with._K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator<(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->_K_th_id < with._K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator<=(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->_K_th_id <= with._K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator>(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->_K_th_id > with._K_th_id;
				}

				KERBAL_CONSTEXPR
				bool operator>=(const basic_thread & with) const KERBAL_NOEXCEPT
				{
					return this->_K_th_id >= with._K_th_id;
				}

		};

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_HPP
