#include "pch.h"
#include <iostream>
#include "XMLPrime.h"
#include "IOFile.h"
#include "StopWatch.h"

int main(int argc, char *argv[])
{
	if (argc != 3 && argc != 4) 
	{
		std::cout << "Usage: XmlPrime [name file to read intervals in XML] [name file to write primes in XML] {count of threads, can be omitted}" << std::endl;
		std::cout << "Example: XmlPrime.exe intervals.xml primes.xml 4" << std::endl;
		return -1;
	}

	int threads = std::thread::hardware_concurrency();
	
	if (argc == 4)
	{ 
		Converter<std::string, unsigned int> toInt;
		threads = toInt.convert(argv[3]);
	}
	
	XMLPrime prime(threads);
	auto timer = StopWatch();

	try {
		auto inXml = IOFile::read(argv[1]);
		timer.start();
		auto outXml = prime.start(inXml);
		timer.stop();

		std::cout << "Time passed: " << timer.get() << "ms" << std::endl;
		std::cout << "Found primes: " << prime.getPrimeCount() << std::endl;
		std::cout << "Threads: " << prime.getCountThreads() << std::endl;

		IOFile::write(argv[2], outXml);
		
	}
	catch(Exception &e){
		std::cout << "Catched the exception: " << e.what() << std::endl;
		std::cout << "Line:" << e.getLine() << std::endl;
		std::cout << "File:" << e.getFileName() << std::endl;
		std::cout << "Function:" << e.getFuncName() << std::endl;
	
		return EXIT_FAILURE;
	}
	catch (std::exception &e)
	{
		std::cout << "Catched the exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	

	return EXIT_SUCCESS;
}

