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
#include <kerbal/memory/guard.hpp>
#include <kerbal/utility/noncopyable.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <pthread.h>
#include <exception> // std::terminate

#if __cplusplus >= 201103L
#	include <kerbal/utility/integer_sequence.hpp>
#	include <tuple>
#endif

#include <kerbal/parallel/thread_create_failed.hpp>


namespace kerbal
{

	namespace parallel
	{

		class thread: private kerbal::utility::noncopyable
		{
			public:
				typedef pthread_t native_handle_type;

				class id
				{
					public:
						friend class thread;

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
				id th_id;

			public:

				KERBAL_CONSTEXPR
				thread() KERBAL_NOEXCEPT
						: th_id()
				{
				}

			private:
				void create(void* (*start_rtn)(void*), void * fun_args_pack)
				{
					int err = ::pthread_create(&this->th_id.native_handle, NULL, start_rtn, fun_args_pack);
					if (err != 0) {
						kerbal::parallel::thread_create_failed::throw_this_exception();
					}

				}

#		if __cplusplus >= 201103L

			private:

				template <typename Callable, typename ... Args, size_t ... I>
				static void apply(std::tuple<Callable, Args...> & pack,
									kerbal::utility::integer_sequence<size_t, I...>)
				{
					std::get<0>(pack)(std::get<I + 1>(pack)...);
				}

			public:

				template <typename Callable, typename ... Args>
				explicit
				thread(Callable&& fun, Args&& ... args)
						: th_id()
				{
					typedef std::tuple<Callable, Args...> fun_args_pack_t;
					struct helper
					{
							static void* start_rtn(void * fun_args_pack)
							{
								fun_args_pack_t * fun_args_pack_p = static_cast<fun_args_pack_t*>(fun_args_pack);
								kerbal::memory::guard<fun_args_pack_t> guard(fun_args_pack_p);
								thread::apply(*fun_args_pack_p,
												kerbal::utility::make_index_sequence<sizeof...(Args)>());
								return NULL;
							}
					};
					void * fun_args_pack = reinterpret_cast<void*>(
							new fun_args_pack_t(
								std::forward<Callable>(fun),
								std::forward<Args>(args)...
							)
					);
					this->create(helper::start_rtn, fun_args_pack);
				}

#		else

			public:

				template <typename Callable>
				explicit
				thread(Callable fun)
						: th_id()
				{
					typedef Callable fun_args_pack_t;
					struct helper
					{
							static void* start_rtn(void * fun_args_pack)
							{
								fun_args_pack_t * fun_args_pack_p = static_cast<fun_args_pack_t*>(fun_args_pack);
								kerbal::memory::guard<fun_args_pack_t> guard(fun_args_pack_p);
								(*fun_args_pack_p)();
								return NULL;
							}
					};
					void * fun_args_pack = reinterpret_cast<void*>(
							new fun_args_pack_t(
								fun
							)
					);
					this->create(helper::start_rtn, fun_args_pack);
				}

				template <typename Callable, typename Arg0>
				explicit
				thread(Callable fun, Arg0& arg0)
						: th_id()
				{
					typedef std::pair<Callable, Arg0> fun_args_pack_t;
					struct helper
					{
							static void* start_rtn(void * fun_args_pack)
							{
								fun_args_pack_t * fun_args_pack_p = static_cast<fun_args_pack_t*>(fun_args_pack);
								kerbal::memory::guard<fun_args_pack_t> guard(fun_args_pack_p);
								fun_args_pack_p->first(fun_args_pack_p->second);
								return NULL;
							}
					};
					void * fun_args_pack = reinterpret_cast<void*>(
							new fun_args_pack_t(fun, arg0)
					);
					this->create(helper::start_rtn, fun_args_pack);
				}

#		endif

#		if __cplusplus >= 201103L

			public:

				KERBAL_CONSTEXPR14
				thread(kerbal::parallel::thread&& ano) KERBAL_NOEXCEPT
						: th_id(ano.th_id)
				{
					ano.th_id = id();
				}

#		endif

			public:

				~thread()
				{
					if (this->joinable()) {
						std::terminate();
					}
				}

				KERBAL_CONSTEXPR
				bool joinable() const KERBAL_NOEXCEPT
				{
					return this->th_id != id();
				}

				void join()
				{
					::pthread_join(this->native_handle(), NULL);
					this->th_id = id();
				}

				void detach()
				{
					::pthread_detach(this->native_handle());
					this->th_id = id();
				}

				KERBAL_CONSTEXPR14
				void swap(thread & ano)
				{
					kerbal::algorithm::swap(this->th_id, ano.th_id);
				}

				KERBAL_CONSTEXPR
				id get_id() const KERBAL_NOEXCEPT
				{
					return this->th_id;
				}

				KERBAL_CONSTEXPR
				native_handle_type native_handle() const KERBAL_NOEXCEPT
				{
					return this->get_id().native_handle;
				}

				KERBAL_CONSTEXPR
				bool operator==(const thread & with) const KERBAL_NOEXCEPT
				{
					return this->th_id == with.th_id;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const thread & with) const KERBAL_NOEXCEPT
				{
					return this->th_id != with.th_id;
				}

				KERBAL_CONSTEXPR
				bool operator<(const thread & with) const KERBAL_NOEXCEPT
				{
					return this->th_id < with.th_id;
				}

				KERBAL_CONSTEXPR
				bool operator<=(const thread & with) const KERBAL_NOEXCEPT
				{
					return this->th_id <= with.th_id;
				}

				KERBAL_CONSTEXPR
				bool operator>(const thread & with) const KERBAL_NOEXCEPT
				{
					return this->th_id > with.th_id;
				}

				KERBAL_CONSTEXPR
				bool operator>=(const thread & with) const KERBAL_NOEXCEPT
				{
					return this->th_id >= with.th_id;
				}

		};

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_HPP
