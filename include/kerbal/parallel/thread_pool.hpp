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
#include <kerbal/function/function.hpp>
#include <kerbal/function/invoke.hpp>
#include <kerbal/parallel/thread.hpp>
#include <kerbal/utility/forward.hpp>
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


namespace kerbal
{

	namespace parallel
	{

		class thread_pool;

		namespace detail
		{

			template <typename R>
			struct task_base;


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
			struct task : task_base<typename kerbal::function::invoke_result<F, Args...>::type>
			{
				private:
					typedef task_base<typename kerbal::function::invoke_result<F, Args...>::type> super;

				public:
					typedef typename super::result_type result_type;

					kerbal::utility::tuple<F, Args...> pack;

					template <typename ... UArgs>
					explicit task(F && f, UArgs && ... args) :
							pack(kerbal::utility::forward<F>(f), kerbal::utility::forward<UArgs>(args)...)
					{
					}

				public:

					void operator()()
					{
						super::apply(pack, kerbal::utility::make_index_sequence<sizeof...(Args)>());
					}
			};

		} // namespace detail


		class thread_pool
		{
				typedef kerbal::function::function<void()> job_type;

				kerbal::container::vector<kerbal::parallel::thread> k_threads_pool;
				std::queue<job_type> k_jobs_queue;
				std::mutex k_mutex;
				std::condition_variable k_cv;
				std::atomic<bool> k_stopped;
				std::atomic<unsigned int> k_idle_threads_num;

			public:
				explicit
				thread_pool(unsigned int init_size = 4) :
						k_stopped(false), k_idle_threads_num(init_size)
				{
					k_threads_pool.reserve(init_size);
					for (size_t i = 0; i < this->k_idle_threads_num; ++i) {
						k_threads_pool.emplace_back([this] {
							while (!this->k_stopped.load()) {
								std::unique_lock<std::mutex> lock(this->k_mutex);
								this->k_cv.wait(lock, [this] {
									return this->k_stopped.load() || !this->k_jobs_queue.empty();
								});
								if (this->k_stopped.load() && this->k_jobs_queue.empty()) {
									return;
								}
								job_type job(kerbal::compatibility::move(this->k_jobs_queue.front()));
								this->k_jobs_queue.pop();
								lock.unlock();
								--this->k_idle_threads_num;
								job();
								++this->k_idle_threads_num;
							}
						});
					}
				}

				~thread_pool()
				{
					this->k_stopped.store(true);
					this->k_cv.notify_all();
					for (auto & thread: this->k_threads_pool) {
						if (thread.joinable()) {
							thread.join();
						}
					}
				}

			public:

				template <class F, class... Args>
				std::future<typename kerbal::function::invoke_result<F, Args...>::type>
				commit(F && f, Args && ... args)
				{
					if (this->k_stopped.load()) {
						throw std::runtime_error("commit on thread pool is stopped.");
					}

					using task_type = kerbal::parallel::detail::task<F, typename kerbal::type_traits::remove_reference<Args>::type ...>;
					using result_type = typename task_type::result_type;
					auto p_task = std::make_shared<task_type>(kerbal::utility::forward<F>(f), kerbal::utility::forward<Args>(args)...);
					std::future<result_type> future = p_task->promise.get_future();
					{
						std::lock_guard<std::mutex> lock(k_mutex);
						k_jobs_queue.emplace([p_task] {
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
