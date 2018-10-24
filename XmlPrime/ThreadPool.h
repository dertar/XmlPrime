#pragma once

#include "ThreadSafeVector.h"
#include "ThreadSafeQueue.h"
#include <thread>
#include <future>

// similitude class of thread pool
// creates a pool of threads and a queue of tasks that it computes by rotation
class ThreadPool
{
public:
	static const unsigned int MAX_THREADS = 8;

	// count of threads by default is count of hardware threads, [1, MAX_THREADS]
	// start if true then threads will be started
	ThreadPool(const unsigned int threads = std::thread::hardware_concurrency(), const bool start = false);
	~ThreadPool();

	unsigned int getCountThreads();

	// starts threads
	void start();

	// joins all threads and stops their
	void join();

	template<typename F, typename...Args>
	auto addTask(F&& f, Args&&... args) 
		-> std::future<decltype(f(args...))>
	{
		std::function<decltype(f(args...))()> bind = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		
		auto func = std::make_shared<std::packaged_task<decltype(f(args...))()>>(bind);

		std::function<void()> task = [func]() {
			(*func)();
		};

		this->tasks.push(task);

		this->condition.notify_one();
		
		return func->get_future();
	}

private:
	std::vector<std::thread> pool;

	// conition for waiting process
	std::condition_variable condition;
	std::mutex mutex;

	ThreadSafeVector<std::exception_ptr, std::mutex> exceptions;
	ThreadSafeQueue<std::function<void()>, std::mutex> tasks;

	// flag for stopping threads
	bool shutdown = false;
	unsigned int threads;

	// if has errors, they would be rethrown
	// calls at end of join method
	void rethrowExceptions();

	ThreadPool(const ThreadPool &) = delete;
	ThreadPool& operator=(const ThreadPool &) = delete;

	// thread that waiting for a task
	// if task available, thread would compute it
	class Thread
	{
	public:
		Thread(ThreadPool *pool, unsigned int id) :
			pool(pool), id(id) {}

		~Thread() {};

		void operator()()
		{
			try {

				while (true)
				{
					std::function<void()> task;

					{
						std::unique_lock<std::mutex> lock(this->pool->mutex);

						this->pool->condition.wait(lock, [this]() {
							return this->pool->shutdown || !this->pool->tasks.empty();
						});

						if (this->pool->shutdown && this->pool->tasks.empty())
							return;

						task = std::move(this->pool->tasks.pop());
					}
					task();
				}
			}
			catch (...)
			{
				this->pool->exceptions.add(std::current_exception());
			}

		}

	private:
		ThreadPool *pool;
		unsigned int id;
	};
};

