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

#include <vector>
#include <queue>
#include <thread>
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

				std::vector<std::thread> pool;
				std::queue<Task> tasks;
				std::mutex m_lock;
				std::condition_variable cv_task;
				std::atomic<bool> stoped;
				std::atomic<int> idle_thread_num;

			public:
				explicit thread_pool(size_t init_size = 4) : stoped(false), idle_thread_num(init_size)
				{
					for (size_t i = 0; i < this->idle_thread_num; ++i) {   //初始化线程数量
						pool.emplace_back([this] {
							while (!this->stoped) {
								std::unique_lock<std::mutex> lock(this->m_lock);
								this->cv_task.wait(lock, [this] {
									return this->stoped.load() || !this->tasks.empty();
								});
								if (this->stoped && this->tasks.empty()) {
									return;
								}
								std::function<void()> task = kerbal::compatibility::move(this->tasks.front());
								this->tasks.pop();
								lock.unlock();
								--(this->idle_thread_num);
								task();
								++(this->idle_thread_num);
							}
						});
					}
				}

				~thread_pool()
				{
					stoped.store(true);
					cv_task.notify_all(); // 唤醒所有线程执行
					for (std::thread& thread : pool) {
						//thread.detach(); // 让线程“自生自灭”
						if (thread.joinable())
							thread.join(); // 等待任务结束， 前提：线程一定会执行完
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
				auto commit(F&& f, Args&& ... args) -> std::future<typename std::result_of<F(Args...)>::type>
				{
					if (stoped.load())
						throw std::runtime_error("commit on ThreadPool is stopped.");

					using RetType = typename std::result_of<F(Args...)>::type; // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
					auto task = std::make_shared<std::packaged_task<RetType()> >(
							std::bind(std::forward<F>(f), std::forward<Args>(args)...)
					);    // wtf !
					std::future<RetType> future = task->get_future();
					{// 添加任务到队列
						std::lock_guard<std::mutex> lock(m_lock);
						tasks.emplace([task]() {
							// push(Task{...})
							(*task)();
						});
					}
					cv_task.notify_one();
					return future;
				}

				//空闲线程数量
				int idle_count()
				{
					return this->idle_thread_num;
				}

		};
	}

}

#endif //KERBAL_PARALLEL_THREAD_POOL_HPP
