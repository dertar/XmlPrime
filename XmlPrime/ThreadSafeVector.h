#pragma once

#include <mutex>
#include <vector>
#include <algorithm>

template <typename T, typename M = std::recursive_mutex>
class ThreadSafeVector
{
private:
	mutable M mutex;
	std::vector<T> vec;
public:

	void add(T el)
	{
		std::lock_guard<M> lock(this->mutex);
		this->vec.push_back(el);
	}

	T at(unsigned int i) const
	{
		std::lock_guard<M> lock(mutex);
		return this->vec.at(i);
	}

	size_t size() const
	{
		return vec.size();
	}

	void lock() const
	{
		this->mutex.lock();
	}

	void unlock() const
	{
		this->mutex.unlock();
	}

	typename std::vector<T>::iterator begin()
	{
		return this->vec.begin();
	}

	typename std::vector<T>::iterator end() 
	{
		return this->vec.end();
	}

	void clear()
	{
		std::lock_guard<M> lock(mutex);
		this->vec.clear();
	}

	typename std::vector<T>::iterator erase()
	{
		return this->vec.erase();
	}
	

	void removeDuplicates()
	{
		std::sort(this->vec.begin(), this->vec.end());
		this->vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
	}

	ThreadSafeVector() {};
	~ThreadSafeVector() {};
};

