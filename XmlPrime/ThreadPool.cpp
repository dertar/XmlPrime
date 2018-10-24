#include "pch.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(const unsigned int threads, const bool start)
{
	if (threads > MAX_THREADS)
		this->threads = MAX_THREADS;
	else
		this->threads = threads != 0 ? threads : 1;

	if (start)
		this->start();
}

ThreadPool::~ThreadPool()
{
	this->join();
}

unsigned int ThreadPool::getCountThreads()
{
	return this->threads;
}

void ThreadPool::start()
{
	for (unsigned int i = 0; i < this->threads; i++)
	{
		this->pool.push_back(
			std::thread(Thread(this, i))
		);
	}
}

void ThreadPool::join()
{
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		this->shutdown = true;
	}

	// time's up, let's do this!
	this->condition.notify_all();

	for (std::thread &t : this->pool)
		if (t.joinable())
			t.join();

	this->rethrowExceptions();
}


void ThreadPool::rethrowExceptions()
{
	for (auto &e : this->exceptions)
	{
		if (e != nullptr)
			std::rethrow_exception(e);
	}
}
