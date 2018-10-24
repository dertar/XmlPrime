#include "pch.h"
#include <algorithm>
#include <future>
#include "../XmlPrime/ThreadPool.h"
#include "../XmlPrime/XMLPrime.h"



TEST(TestThreadPool, TestThreadPool1) {
	ThreadPool pool(4);
	std::vector< std::future<int>> results;

	std::shared_ptr<ThreadSafeVector<unsigned int, std::recursive_mutex> > vec
		= std::make_shared<ThreadSafeVector<unsigned int, std::recursive_mutex> >();

	pool.start();

	auto f1 = pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, 0, 10, vec);
	auto f2 = pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, 10, 20, vec);

	f1.get();f2.get();

	vec->removeDuplicates();

	std::vector<unsigned int> answers{ 2, 3, 5, 7, 11, 13, 17, 19 };

	ASSERT_EQ(vec->size(), answers.size());
	
	for (unsigned int i = 0; i < answers.size(); i++)
		ASSERT_EQ(vec->at(i), answers.at(i));
}

TEST(TestThreadPool, TestThreadPoolZeroThread) {
	ThreadPool pool(0);
	std::vector< std::future<int>> results;

	std::shared_ptr<ThreadSafeVector<unsigned int, std::recursive_mutex> > vec
		= std::make_shared<ThreadSafeVector<unsigned int, std::recursive_mutex> >();

	pool.start();

	auto f1 = pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, 0, 2, vec);
	f1.get();

	std::vector<unsigned int> answers{ 2 };

	ASSERT_EQ(vec->size(), answers.size());

	for (unsigned int i = 0; i < answers.size(); i++)
		ASSERT_EQ(vec->at(i), answers.at(i));
}

TEST(TestThreadPool, TestThreadPoolBiggerThenMaxThread) {
	ThreadPool pool(1000);
	std::vector< std::future<int>> results;

	std::shared_ptr<ThreadSafeVector<unsigned int, std::recursive_mutex> > vec
		= std::make_shared<ThreadSafeVector<unsigned int, std::recursive_mutex> >();

	pool.start();

	auto f1 = pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, 0, 2, vec);
	f1.get();

	std::vector<unsigned int> answers{ 2 };

	ASSERT_EQ(vec->size(), answers.size());

	for (unsigned int i = 0; i < answers.size(); i++)
		ASSERT_EQ(vec->at(i), answers.at(i));
}

TEST(TestThreadPool, TestThreadPool2) {
	ThreadPool pool(0);
	std::vector< std::future<int>> results;

	std::shared_ptr<ThreadSafeVector<unsigned int, std::recursive_mutex> > vec
		= std::make_shared<ThreadSafeVector<unsigned int, std::recursive_mutex> >();

	pool.start();

	auto c1 = pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, 0, 200, vec);
	auto c2 = pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, 201, 400, vec);
	auto c3 = pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, 401, 600, vec);
	auto c4 = pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, 601, 800, vec);
	auto c5 = pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, 801, 1000, vec);
	
	c1.get();c2.get();c3.get();c4.get();c5.get();

	vec->removeDuplicates();

	std::vector<unsigned int> answers{ 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};

	ASSERT_EQ(vec->size(), answers.size());

	for (unsigned int i = 0; i < answers.size(); i++)
		ASSERT_EQ(vec->at(i), answers.at(i));

}
