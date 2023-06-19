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
#include <functional>
#include <stdexcept>


namespace kerbal
{

	namespace parallel
	{

		class thread_pool
		{
				using Task = std::function<void()>;

//				kerbal::container::vector<std::thread> K_threads_pool;
				kerbal::container::vector<kerbal::parallel::thread> k_threads_pool;
				std::queue<Task> k_tasks_queue;
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
					for (size_t i = 0; i < this->k_idle_threads_num; ++i) {   //初始化线程数量
						k_threads_pool.emplace_back([this] {
							while (!this->k_stopped.load()) {
								std::unique_lock<std::mutex> lock(this->k_mutex);
								this->k_cv.wait(lock, [this] {
									return this->k_stopped.load() || !this->k_tasks_queue.empty();
								});
								if (this->k_stopped.load() && this->k_tasks_queue.empty()) {
									return;
								}
								std::function<void()> task(kerbal::compatibility::move(this->k_tasks_queue.front()));
								this->k_tasks_queue.pop();
								lock.unlock();
								--this->k_idle_threads_num;
								task();
								++this->k_idle_threads_num;
							}
						});
					}
				}

				~thread_pool()
				{
					this->k_stopped.store(true);
					this->k_cv.notify_all(); // 唤醒所有线程执行
					for (auto & thread : this->k_threads_pool) {
						//thread.detach(); // 让线程“自生自灭”
						if (thread.joinable()) {
							thread.join(); // 等待任务结束， 前提：线程一定会执行完
						}
					}
				}

			public:

				template <typename F, typename ... Args>
				struct task
				{
						using result_type = typename kerbal::function::invoke_result<F, Args...>::type;

						kerbal::utility::tuple<F, Args...> pack;
						std::promise<result_type> promise;

						template <typename ... UArgs>
						task(F && f, UArgs && ... args) :
								pack(kerbal::utility::forward<F>(f), kerbal::utility::forward<UArgs>(args)...)
						{
						}

					private:

						template <std::size_t ... I>
						void apply(kerbal::utility::integer_sequence<std::size_t, I...>)
						{
							try {
								result_type result = kerbal::function::invoke(pack.template get<0>(), pack.template get<I + 1>()...);
								promise.set_value(kerbal::compatibility::move(result));
							} catch (...) {
								promise.set_exception(std::current_exception());
							}
						}

					public:

						void operator()()
						{
							apply(kerbal::utility::make_index_sequence<sizeof...(Args)>());
						}
				};

				// 提交一个任务
				// 调用.get()获取返回值会等待任务执行完,获取返回值
				// 有两种方法可以实现调用类成员，
				// 一种是使用   bind： .commit(std::bind(&Dog::sayHello, &dog));
				// 一种是用 mem_fn： .commit(std::mem_fn(&Dog::sayHello), &dog)
				template <class F, class... Args>
				std::future<typename kerbal::function::invoke_result<F, Args...>::type>
				commit(F&& f, Args&& ... args)
				{
					if (this->k_stopped.load()) {
						throw std::runtime_error("commit on ThreadPool is stopped.");
					}

					using task_type = task<F, typename kerbal::type_traits::remove_reference<Args>::type ...>;
					using result_type = typename task_type::result_type;
					auto p_task = std::make_shared<task_type>(kerbal::utility::forward<F>(f), kerbal::utility::forward<Args>(args)...);
					std::future<result_type> future = p_task->promise.get_future();
					{// 添加任务到队列
						std::lock_guard<std::mutex> lock(k_mutex);
						k_tasks_queue.emplace([p_task] {
							(*p_task)();
						});
					}
					k_cv.notify_one();
					return future;
				}

				//空闲线程数量
				const std::atomic<unsigned int> &
				idle_count() const KERBAL_NOEXCEPT
				{
					return this->k_idle_threads_num;
				}

		};

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_POOL_HPP
