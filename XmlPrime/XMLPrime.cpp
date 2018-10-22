#include "pch.h"
#include "XMLPrime.h"


std::string XMLPrime::get(std::string &rawXml, const bool sorts, const bool removeDuplicates)
{
	auto xmlIntervals = converter->toXML(rawXml);

	auto root = xmlIntervals->root();

	if (root->getName() != "root")
		throw std::exception("incorrect root node");

	auto intervals = root->get("intervals");

	if (intervals == nullptr || intervals->getName() != "intervals")
		throw std::exception("incorrect intervals node");

	auto intervalsChild = intervals->getChild();

	if (intervalsChild == nullptr || intervalsChild->getName() != "interval")
		throw std::exception("incorrect interval node");

	auto inters = this->getIntervals(intervalsChild);

	this->pushTasks(inters);

	delete inters;
	this->vec->clear();

	pool->join();

	if (sorts || removeDuplicates)
	{
		std::sort(vec->begin(), vec->end());
		if (removeDuplicates)
			vec->removeDuplicates();
	}

	auto data = this->getStringData();

	XMLDocument out("root");
	out.root()->addChild("primes")->setData(*data);
	auto outXml = converter->toPlain(&out);

	delete data;
	delete xmlIntervals;
	std::string copy(*outXml);
	delete outXml;
	return copy;
}

XMLPrime::XMLPrime(const unsigned int threads)
{
	this->converter = XMLConvertor::getIntance();
	
	this->vec = new ThreadSafeVector<unsigned int>();
	this->pool = new ThreadPrimeFinder(this->vec, threads);
}


XMLPrime::~XMLPrime()
{
}

std::vector<std::pair<unsigned int, unsigned int>>* XMLPrime::getIntervals(XMLNode *intervals)
{
	auto ret = new std::vector<std::pair<unsigned int, unsigned int>>();

	while (intervals != nullptr)
	{
		auto low = intervals->getChild();
		auto high = low->getNext()->getData();
		try
		{
			unsigned int  uLow = std::stoul(*low->getData(), nullptr, 0);
			unsigned int uHigh = std::stoul(*high, nullptr, 0);

			if (uLow >= uHigh)
				throw std::exception("error data low bound is bigger then high bound");
			
			ret->push_back(
				std::pair<unsigned int, unsigned int>(uLow, uHigh)
			);
		}
		catch (...)
		{
			delete ret;
			throw std::current_exception();
		}

		intervals = intervals->getNext();
	}

	return ret;
}

void XMLPrime::pushTasks(std::vector< std::pair<unsigned int, unsigned int> >* intervals)
{
	for (auto &x : *intervals)
	{
		pool->push(x.first, x.second);
	}
}

std::string * XMLPrime::getStringData()
{
	auto ret = new std::string();

	for (auto it = vec->begin(); it != vec->end(); ++it)
	{
		*ret += (std::to_string(*it) + " ");
	}

	return ret;
}


