#pragma once
#include <set>
#include <mutex>

template <typename T, typename M = std::recursive_mutex>
class ThreadSafeSet
{
public:
	ThreadSafeSet() {}
	~ThreadSafeSet() {}

	void insert(T t) 
	{
		std::lock_guard<M> locker(this->mutex);
		set.insert(t);
	}

	size_t size() const
	{
		return this->set.size();
	}

	void lock() const
	{
		this->mutex.lock();
	}

	void unlock() const
	{
		this->mutex.unlock();
	}

	typename std::set<T>::iterator begin()
	{
		return this->set.begin();
	}

	typename std::set<T>::iterator end()
	{
		return this->set.end();
	}
private:
	std::set<T> set;
	mutable M mutex;
};

