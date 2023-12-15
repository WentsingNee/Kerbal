/**
 * @file       thread_pool.hpp
 * @brief
 * @date       2020-03-02
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PARALLEL_THREAD_POOL_HPP
#define KERBAL_PARALLEL_THREAD_POOL_HPP

#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/function/invoke.hpp>
#include <kerbal/function/move_only_function.hpp>
#include <kerbal/memory/unique_ptr.hpp>
#include <kerbal/parallel/thread.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/integer_sequence.hpp>
#include <kerbal/utility/tuple.hpp>
#include <kerbal/type_traits/remove_reference.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <queue>
#include <atomic>
#include <condition_variable>
#include <future>
#include <stdexcept>

#include <cstddef>


namespace kerbal
{

	namespace parallel
	{

		class thread_pool;

		namespace detail
		{

			template <typename R>
			class task_base;


			template <typename Pack, typename IndexSeq>
			struct task_result_type_helper;

			template <typename Pack, std::size_t ... I>
			struct task_result_type_helper<Pack, kerbal::utility::index_sequence<I...> > :
					kerbal::function::invoke_result<
						typename Pack::template reference<I>::type ...
					>
			{
			};

			template <typename F, typename ... Args>
			struct task_typedef_helper
			{
					typedef kerbal::utility::tuple<F, Args...> pack_t;
					typedef typename task_result_type_helper<
						pack_t,
						kerbal::utility::make_index_sequence<1 + sizeof...(Args)>
					>::type result_t;
					typedef task_base<result_t> task_super_t;
			};


			template <>
			class task_base<void>
			{
					friend class kerbal::parallel::thread_pool;

				protected:
					typedef void result_type;
					std::promise<result_type> promise;

					template <typename Pack, std::size_t ... I>
					void apply(Pack & pack, kerbal::utility::integer_sequence<std::size_t, I...>)
					{
						try {
							kerbal::function::invoke(pack.template get<0>(), pack.template get<I + 1>()...);
							promise.set_value();
						} catch (...) {
							promise.set_exception(std::current_exception());
						}
					}
			};

			template <typename R>
			class task_base
			{
					friend class kerbal::parallel::thread_pool;

				protected:
					typedef R result_type;
					std::promise<result_type> promise;

					template <typename Pack, std::size_t ... I>
					void apply(Pack & pack, kerbal::utility::integer_sequence<std::size_t, I...>)
					{
						try {
							promise.set_value(kerbal::function::invoke(pack.template get<0>(), pack.template get<I + 1>()...));
						} catch (...) {
							promise.set_exception(std::current_exception());
						}
					}
			};


			template <typename F, typename ... Args>
			class task : private task_typedef_helper<F, Args...>::task_super_t
			{
				private:
					typedef task_typedef_helper<F, Args...> typedef_helper;
					typedef typename typedef_helper::pack_t pack_t;
					typedef typename typedef_helper::task_super_t super;

					friend class kerbal::parallel::thread_pool;

				private:
					typedef typename typedef_helper::result_t result_type;

					pack_t pack;

					template <typename FU, typename ... UArgs>
					explicit task(FU && f, UArgs && ... args) :
							pack(kerbal::utility::forward<FU>(f), kerbal::utility::forward<UArgs>(args)...)
					{
					}

					void operator()()
					{
						super::apply(pack, kerbal::utility::make_index_sequence<sizeof...(Args)>());
					}
			};

		} // namespace detail


		class thread_pool
		{
				typedef kerbal::function::move_only_function<void()> job_type;

				kerbal::container::vector<kerbal::parallel::thread> k_workers;
				std::queue<job_type> k_jobs_queue;
				std::mutex k_mutex;
				std::condition_variable k_cv;
				std::atomic<bool> k_stopped;
				std::atomic<unsigned int> k_idle_threads_num;

			private:
				struct worker
				{
						thread_pool * self;

						worker(thread_pool * self) :
								self(self)
						{
						}

						void operator()() const
						{
							while (!self->k_stopped.load()) {
								std::unique_lock<std::mutex> lock(self->k_mutex);
								self->k_cv.wait(lock, [self = this->self] {
									return self->k_stopped.load() || !self->k_jobs_queue.empty();
								});
								if (self->k_stopped.load() && self->k_jobs_queue.empty()) {
									return;
								}
								job_type job(kerbal::compatibility::move(self->k_jobs_queue.front()));
								self->k_jobs_queue.pop();
								lock.unlock();
								--self->k_idle_threads_num;
								job();
								++self->k_idle_threads_num;
							}
						}
				};

			public:
				explicit
				thread_pool(unsigned int init_size = 4) :
						k_stopped(false), k_idle_threads_num(init_size)
				{
					k_workers.reserve(init_size);
					for (size_t i = 0; i < init_size; ++i) {
						k_workers.emplace_back(worker(this));
					}
				}

				~thread_pool()
				{
					this->k_stopped.store(true);
					this->k_cv.notify_all();
					for (auto & thread: this->k_workers) {
						if (thread.joinable()) {
							thread.join();
						}
					}
				}

			private:

				template <typename F, typename ... Args>
				struct commit_typedef_helper
				{
						typedef kerbal::parallel::detail::task<
							typename kerbal::type_traits::remove_reference<F>::type,
							typename kerbal::type_traits::remove_reference<Args>::type ...
						> task_type;

						typedef typename task_type::result_type result_type;
				};

			public:

				template <typename F, typename ... Args>
				std::future<typename commit_typedef_helper<F&&, Args&&...>::result_type>
				commit(F && f, Args && ... args)
				{
					if (this->k_stopped.load()) {
						throw std::runtime_error("commit on thread pool is stopped.");
					}

					typedef commit_typedef_helper<F&&, Args&&...> commit_typedef_helper;
					typedef typename commit_typedef_helper::task_type task_type;
					typedef typename commit_typedef_helper::result_type result_type;

					kerbal::memory::unique_ptr<task_type> p_task(new task_type(
							kerbal::utility::forward<F>(f),
							kerbal::utility::forward<Args>(args)...
					));
					std::future<result_type> future = p_task->promise.get_future();
					{
						std::lock_guard<std::mutex> lock(k_mutex);
						k_jobs_queue.emplace([p_task = kerbal::compatibility::move(p_task)] {
							(*p_task)();
						});
					}
					k_cv.notify_one();
					return future;
				}

				const std::atomic<unsigned int> &
				idle_count() const KERBAL_NOEXCEPT
				{
					return this->k_idle_threads_num;
				}

		};

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_POOL_HPP
