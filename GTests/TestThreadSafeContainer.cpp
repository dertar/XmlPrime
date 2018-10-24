#include "pch.h"

#include "../XmlPrime/ThreadSafeVector.h"
#include "../XmlPrime/ThreadSafeSet.h"

#include <thread>

TEST(TestThreadSafeContainer, TestThreadSaveVectorAdd) {
	ThreadSafeVector<int, std::recursive_mutex> v1;
	int count = 1000;
	std::thread t1([&v1, &count]()
	{
		for (int i = 0; i < count; i++)
			v1.add(i);
	});

	std::thread t2([&v1, &count]()
	{
		for (int i = 0; i < count; i++)
			v1.add(i);
	});


	t1.join();
	t2.join();

	ASSERT_EQ(v1.size(), count * 2);

}

TEST(TestThreadSafeContainer, TestThreadSaveSet) {
	ThreadSafeSet<int, std::recursive_mutex> v1;

	int count = 1000;

	std::thread t1([&v1, &count]()
	{
		for (int i = 0; i < count; i++)
			v1.insert(i);
	});

	std::thread t2([&v1, &count]()
	{
		for (int i = 0; i < count; i++)
			v1.insert(i);
	});


	t1.join();
	t2.join();

	ASSERT_EQ(v1.size(), count);

}
