#pragma once
#include <mutex>
#include <thread>
#include <queue>

template <typename T, typename M = std::mutex>
class ThreadSafeQueue {
public:
	ThreadSafeQueue() {}
	~ThreadSafeQueue() {}

	void push(T& t)
	{
		std::lock_guard<M> lock(this->mutex);
		this->queue.push(std::move(t));
	}

	T pop()
	{
		std::lock_guard<M> lock(this->mutex);
		// for shared ptr
		auto ret = std::move(this->queue.front());
		this->queue.pop();
		return ret;
	}

	bool empty() const
	{
		return this->queue.empty();
	}

private:
	std::queue<T> queue;
	mutable M mutex;
};