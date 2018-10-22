#include "pch.h"
#include "ThreadPrimeFinder.h"

void ThreadPrimeFinder::thread()
{
	try {

		while (true)
		{
			std::pair<unsigned int, unsigned int> pair;

			{
				std::unique_lock<std::mutex> lock(this->mutex);

				this->condition.wait(lock,
					[this]() {
					return this->isDone || !this->tasks.empty();
				});

				if (this->isDone && this->tasks.empty())
					return;

				pair = std::move(this->tasks.front());
				this->tasks.pop();
			}

			this->find(pair.first, pair.second);
		}
	}
	catch (...)
	{
		this->exceptions.add(std::current_exception());
	}
}

bool ThreadPrimeFinder::find(const unsigned int lower, const unsigned int upper)
{
	for (unsigned int i = lower; i <= upper; i++)
	{
		if (ThreadPrimeFinder::isPrime(i))
			primes->add(i);
	}

	return true;
}

void ThreadPrimeFinder::rethrowException()
{
	for (auto &e : this->exceptions)
	{
		if (e != nullptr)
			std::rethrow_exception(e);
	}
}

void ThreadPrimeFinder::push(const unsigned int lower, const unsigned int upper)
{
	tasks.push(std::pair<unsigned int, unsigned int>(lower, upper));
}

ThreadPrimeFinder::ThreadPrimeFinder (ThreadSafeVector<unsigned int> *vec, const unsigned int threads)
{
	this->primes = vec;

	if (threads > MAX_THREADS)
		this->threads = MAX_THREADS;
	else
		this->threads = threads != 0 ? threads : 1;

	for (unsigned int i = 0; i < this->threads; i++)
	{
		pool.push_back(
			std::thread(&ThreadPrimeFinder::thread, this)
		);
	}

}

void ThreadPrimeFinder::join()
{
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		isDone = true;
	}

	// time's up, let's do this!
	this->condition.notify_all();

	for (std::thread &t : this->pool)
		t.join();

	this->rethrowException();

}

bool ThreadPrimeFinder::isPrime(unsigned int num)
{
	if (num == 0 || num == 1)
		return false;

	for (unsigned int i = 2; i * i <= num; i++)
		if (num % i == 0)
			return false;

	return true;
}

ThreadPrimeFinder::~ThreadPrimeFinder()
{
}

unsigned int ThreadPrimeFinder::getThreads() const
{
	return this->threads;
}