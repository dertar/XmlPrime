#pragma once

#include<algorithm>

#include "XMLNode.h"
#include "XMLConvertor.h"
#include "ThreadPrimeFinder.h"
#include "ThreadSafeVector.h"

class XMLPrime
{
public:
	// takes a raw XML text with intervals, returns primes in XML
	// if sort is true, it will sort primes array
	// if removeDuplicate is true, the sort flag also will be true, it will remove duplicates form primes array
	std::string get(std::string &rawXml, const bool sorts = true, const bool removeDuplicates = true);

	XMLPrime(const unsigned int threads = std::thread::hardware_concurrency());
	~XMLPrime();

private:
	// scrap the intervals from XMLNode to comfortable container
	std::vector<std::pair<unsigned int, unsigned int>> *getIntervals(XMLNode *intervals);
	
	// pushes intervals in thread tasks
	void pushTasks(std::vector< std::pair<unsigned int, unsigned int> >* intervals);

	// generate string data to XMLNode
	std::string *getStringData();

	ThreadSafeVector<unsigned int> *vec;
	ThreadPrimeFinder *pool;
	XMLConvertor *converter;

};

