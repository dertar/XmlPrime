#pragma once

#include <mutex>
#include <vector>
#include <algorithm>


template <typename T>
class ThreadSafeVector
{
private:
	mutable std::recursive_mutex mutex;
	std::vector<T> vec;
public:

	void add(T el)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex);
		this->vec.push_back(el);
	}

	T at(unsigned int i) const
	{
		std::lock_guard<std::recursive_mutex> lock(mutex);
		return this->vec.at(i);
	}

	size_t size() const
	{
		return vec.size();
	}

	void lock()
	{
		this->mutex.lock();
	}

	void unlock()
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
		std::lock_guard<std::recursive_mutex> lock(mutex);
		this->vec.clear();
	}

	typename std::vector<T>::iterator erase()
	{
		return this->vec.erase();
	}

	//must be sorted
	void removeDuplicates()
	{
		this->vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
	}

	ThreadSafeVector() {};
	~ThreadSafeVector() {};
};

