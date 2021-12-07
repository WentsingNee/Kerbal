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
#include <kerbal/parallel/thread.hpp>

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

				fkerbal::container::vector<fkerbal::parallel::thread> _K_threads_pool;
				std::queue<Task> _K_tasks_queue;
				std::mutex _K_mutex;
				std::condition_variable _K_cv;
				std::atomic<bool> _K_stopped;
				std::atomic<unsigned int> _K_idle_threads_num;

			public:
				explicit
				thread_pool(unsigned int init_size = 4) :
						_K_stopped(false), _K_idle_threads_num(init_size)
				{
					_K_threads_pool.reserve(init_size);
					for (size_t i = 0; i < this->_K_idle_threads_num; ++i) {   //初始化线程数量
						_K_threads_pool.emplace_back([this] {
							while (!this->_K_stopped.load()) {
								std::unique_lock<std::mutex> lock(this->_K_mutex);
								this->_K_cv.wait(lock, [this] {
									return this->_K_stopped.load() || !this->_K_tasks_queue.empty();
								});
								if (this->_K_stopped.load() && this->_K_tasks_queue.empty()) {
									return;
								}
								std::function<void()> task(kerbal::compatibility::move(this->_K_tasks_queue.front()));
								this->_K_tasks_queue.pop();
								lock.unlock();
								--this->_K_idle_threads_num;
								task();
								++this->_K_idle_threads_num;
							}
						});
					}
				}

				~thread_pool()
				{
					this->_K_stopped.store(true);
					this->_K_cv.notify_all(); // 唤醒所有线程执行
					for (fkerbal::parallel::thread & thread : this->_K_threads_pool) {
						//thread.detach(); // 让线程“自生自灭”
						if (thread.joinable()) {
							thread.join(); // 等待任务结束， 前提：线程一定会执行完
						}
					}
				}

			public:

//				void stop()
//				{
//				}

				// 提交一个任务
				// 调用.get()获取返回值会等待任务执行完,获取返回值
				// 有两种方法可以实现调用类成员，
				// 一种是使用   bind： .commit(std::bind(&Dog::sayHello, &dog));
				// 一种是用 mem_fn： .commit(std::mem_fn(&Dog::sayHello), &dog)
				template <class F, class... Args>
				std::future<typename std::result_of<F(Args...)>::type>
				commit(F&& f, Args&& ... args)
				{
					if (this->_K_stopped.load()) {
						throw std::runtime_error("commit on ThreadPool is stopped.");
					}

					using result_type = typename std::result_of<F(Args...)>::type; // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
					auto task = std::make_shared<std::packaged_task<result_type()> >(
							std::bind(kerbal::utility::forward<F>(f), kerbal::utility::forward<Args>(args)...)
					);
					std::future<result_type> future = task->get_future();
					{// 添加任务到队列
						std::lock_guard<std::mutex> lock(_K_mutex);
						_K_tasks_queue.emplace([task]() {
							// push(Task{...})
							(*task)();
						});
					}
					_K_cv.notify_one();
					return future;
				}

				//空闲线程数量
				unsigned int idle_count() const KERBAL_NOEXCEPT
				{
					return this->_K_idle_threads_num.load();
				}

		};

	} // namespace parallel

} // namespace kerbal

#endif // KERBAL_PARALLEL_THREAD_POOL_HPP
