#include "pch.h"
#include <iostream>
#include "XMLPrime.h"
#include "IOFile.h"
#include "StopWatch.h"

const static bool TIMER = true;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "Usage: XmlPrime [name file to read intervals in XML] [name file to write primes in XML ]" << std::endl;
		std::cout << "Example: XmlPrime.exe intervals.xml primes.xml" << std::endl;
		return -1;
	}

	XMLPrime prime;
	auto timer = StopWatch();
	
	try {
		auto rawXml = IOFile::read(argv[1]);
		timer.start();
		auto outXml = prime.get(rawXml);
		timer.stop();
		IOFile::write(argv[2], outXml);
	}
	catch (std::exception &e)
	{
		std::cout << "Catched the exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	if (TIMER)
		std::cout << "Time passed: " << timer.get() << "ms" << std::endl;

	return EXIT_SUCCESS;
}

