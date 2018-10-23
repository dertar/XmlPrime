#pragma once
#include "ThreadSafeVector.h"

#include <thread>
#include <mutex>
#include <vector>
#include <queue>

// similitude class of thread pool
// creates a pool of threads and a queue of tasks that it computes by rotation
class ThreadPrimeFinder
{
public:
	static const unsigned int MAX_THREADS = 8;

	// vector of primes numbers
	// count of threads is count of hardware threads by defalut, [1, MAX_THREADS]
	ThreadPrimeFinder(ThreadSafeVector<unsigned int> *vec, const unsigned int threads = std::thread::hardware_concurrency());
	~ThreadPrimeFinder();
	
	// add task to threads
	void push(const unsigned int lower, const unsigned int upper);

	// joins all threads and stops threads
	void join();
	
	// checks if number is prime by division algorithm
	static bool isPrime(unsigned int num);

	unsigned int getThreads() const;

private:
	ThreadSafeVector<unsigned int> *primes;
	ThreadSafeVector<std::exception_ptr> exceptions;
	std::vector<std::thread> pool;
	std::queue<std::pair<unsigned int, unsigned int> > tasks;
	
	std::mutex mutex;

	// for waiting procees
	std::condition_variable condition;

	// flag for stopping threads
	bool isDone = false;

	// count of threads
	unsigned int threads;

	// thread that waiting for task
	// if task available, thread would compute it
	void thread();
	
	// thread function that finds all primes between range and push they into thread safe vector
	bool find(const unsigned int lower, const unsigned int upper);
	
	// if has errors, they would be rethrown
	void rethrowException();

	
};

