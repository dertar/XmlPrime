#include "pch.h"
#include "XMLPrime.h"


std::string XMLPrime::get(std::string &rawXml, const bool sorts, const bool removeDuplicates)
{
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toStr;

	auto root = toXML.convert(rawXml);

	if (root->getKey() != "root")
		throw Exception("incorrect root node", __LINE__, __FILE__, __FUNCTION__);

	auto intervals = root->findFirstChild("intervals");

	if (intervals == nullptr || intervals->getKey() != "intervals")
		throw Exception("incorrect intervals node", __LINE__, __FILE__, __FUNCTION__);
	
	auto intervalsChild = intervals->getChild();

	if (intervalsChild == nullptr || intervalsChild->getKey() != "interval")
		throw Exception("incorrect interval node", __LINE__, __FILE__, __FUNCTION__);

	ConverterIntervals c;
	
	auto inters = c.convert(intervalsChild);

	this->pushTasks(&inters);

	inters.clear();

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
	
	auto primes = out.root()->addChild(
		this->factory->createNode<std::string>("primes", data)
	);
	
	auto outXml = toStr.convert(out.root(), "\n", "\t");

	return outXml;
}

XMLPrime::XMLPrime(const unsigned int threads)
{
	this->factory = XMLNodeFactory::getInstance();

	this->vec = new ThreadSafeVector<unsigned int>();
	this->pool = new ThreadPrimeFinder(this->vec, threads);
}


XMLPrime::~XMLPrime()
{
}


void XMLPrime::pushTasks(std::vector< std::pair<unsigned int, unsigned int> >* intervals)
{
	for (auto &x : *intervals)
	{
		pool->push(x.first, x.second);
	}
}

std::string XMLPrime::getStringData()
{
	std::string ret;

	for (auto it = vec->begin(); it != vec->end(); ++it)
	{
		ret += (std::to_string(*it) + " ");
	}

	return ret;
}


