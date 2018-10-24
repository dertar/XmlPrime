#pragma once

#include <algorithm>

#include "XMLNode.h"
#include "ThreadSafeVector.h"
#include "XMLDocument.h"
#include "XMLNodeFactory.h"
#include "ConverterIntervals.h"
#include "ConverterPlainToXML.h"
#include "ConverterXMLToPlain.h"
#include "Exception.h"
#include "ThreadSafeSet.h"
#include "ThreadPool.h"


class XMLPrime
{
public:
	// takes a raw XML text with intervals, returns primes in XML
	std::string start(std::string &rawXml);

	XMLPrime(const unsigned int threads = std::thread::hardware_concurrency());
	~XMLPrime();

	//thread function that finds all primes between range and push they into thread safe container
	static bool THREAD_PRIME_SET(
		const unsigned int lower,
		const unsigned int upper,
		std::shared_ptr<ThreadSafeSet<unsigned int, std::recursive_mutex> > &primes);

	static bool THREAD_PRIME_VECTOR(
		const unsigned int lower,
		const unsigned int upper,
		std::shared_ptr<ThreadSafeVector<unsigned int, std::recursive_mutex> > &primes);
	
	static bool IS_PRIME(unsigned int num);

	unsigned int getPrimeCount();
	unsigned int getCountThreads();
private:

	// pushes intervals in thread tasks
	void addTasks(std::vector< std::pair<unsigned int, unsigned int> > &intervals);

	// generate string data to XMLNode
	// delim is symbol between numbers
	std::string getPrimes(const char delim = ' ');
	
	// get answers from futures
	void getAnswers();

	using set_of_primes = ThreadSafeVector<unsigned int, std::recursive_mutex>;

	std::shared_ptr<set_of_primes> primes;
	std::vector<std::future<bool>> answers;

	unsigned int count;

	ThreadPool pool;
	XMLNodeFactory *factory;
};

