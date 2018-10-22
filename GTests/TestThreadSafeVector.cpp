#include "pch.h"

#include "../XmlPrime/ThreadSafeVector.h"
#include <thread>

TEST(TestThreadSafeVector, TestThreadSaveVectorAdd) {
	ThreadSafeVector<int> v1;

	std::thread t1([&v1]()
	{
		for (int i = 0; i < 1000; i++)
			v1.add(i);
	});

	std::thread t2([&v1]()
	{
		for (int i = 0; i < 1000; i++)
			v1.add(i);
	});


	t1.join();
	t2.join();

	ASSERT_EQ(v1.size(), 2000);

}
