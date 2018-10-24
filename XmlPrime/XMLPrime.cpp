#include "pch.h"
#include "XMLPrime.h"


std::string XMLPrime::start(std::string &rawXml)
{
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toStr;
	ConverterIntervals toIntervals;
	
	auto root = toXML.convert(rawXml);

	if (root->getKey() != "root")
		throw Exception("incorrect root node", __LINE__, __FILE__, __FUNCTION__);

	auto rootChild = root->findFirstChild("intervals");

	if (rootChild == nullptr || rootChild->getKey() != "intervals")
		throw Exception("incorrect intervals node", __LINE__, __FILE__, __FUNCTION__);
	
	auto intervalsChild = rootChild->getChild();

	if (intervalsChild == nullptr || intervalsChild->getKey() != "interval")
		throw Exception("incorrect interval node", __LINE__, __FILE__, __FUNCTION__);

	auto intervals = toIntervals.convert(intervalsChild);
	
	this->pool.start();

	this->addTasks(intervals);
	// getting answers
	this->getAnswers();

	this->primes->removeDuplicates();
	this->count = primes->size();

	XMLDocument out("root");
	
	auto primes = out.root()->addChild(
		this->factory->createNode<std::string>("primes", this->getPrimes())
	);
	
	auto outXml = toStr.convert(out.root(), "\n", "\t");

	return outXml;
}

XMLPrime::XMLPrime(const unsigned int threads) :
	primes(std::make_shared<set_of_primes>()),
	pool(threads)
{
	this->factory = XMLNodeFactory::getInstance(); 
}


XMLPrime::~XMLPrime()
{
}

void XMLPrime::addTasks(std::vector<std::pair<unsigned int, unsigned int>> &intervals)
{
	this->answers.clear();
	for (auto &p : intervals)
	{
		this->answers.push_back(
			this->pool.addTask(XMLPrime::THREAD_PRIME_VECTOR, p.first, p.second, this->primes)
		);
	}
}

void XMLPrime::getAnswers()
{
	for (auto &p : this->answers)
	{
		p.get();
	}
}

std::string XMLPrime::getPrimes(const char delim)
{
	std::string ret;
	this->primes->lock();
	for (auto it = this->primes->begin(); it != this->primes->end(); ++it)
	{
		ret += (std::to_string(*it) + delim);
	}
	this->primes->unlock();
	return ret;
}

bool XMLPrime::THREAD_PRIME_SET(
	const unsigned int lower,
	const unsigned int upper,
	std::shared_ptr<ThreadSafeSet<unsigned int, std::recursive_mutex> > &primes)
{
	for (unsigned int i = lower; i <= upper; i++)
	{
		if (XMLPrime::IS_PRIME(i))
			primes->insert(i);
	}

	return true;
}

bool XMLPrime::THREAD_PRIME_VECTOR(
	const unsigned int lower,
	const unsigned int upper,
	std::shared_ptr<ThreadSafeVector<unsigned int, std::recursive_mutex> > &primes)
{
	for (unsigned int i = lower; i <= upper; i++)
	{
		if (XMLPrime::IS_PRIME(i))
			primes->add(i);
	}

	return true;
}

//checks if number is prime by division algorithm
bool XMLPrime::IS_PRIME(unsigned int num)
{
	if (num == 0 || num == 1)
		return false;

	for (unsigned int i = 2; i * i <= num; i++)
		if (num % i == 0)
			return false;

	return true;
}

unsigned int XMLPrime::getPrimeCount()
{
	return this->count;
}

unsigned int XMLPrime::getCountThreads()
{
	return this->pool.getCountThreads();
}
