#include "pch.h"
#include "ConverterIntervals.h"
#include "Exception.h"

ConverterIntervals::ConverterIntervals()
{
	this->factory = XMLNodeFactory::getInstance();
}


ConverterIntervals::~ConverterIntervals()
{
	this->factory = nullptr;
}

std::vector<std::pair<unsigned int, unsigned>> ConverterIntervals::convert(Node *node)
{
	auto ret = std::vector<std::pair<unsigned int, unsigned int>>();
	Node *intervals = node;

	while (intervals != nullptr)
	{
		auto low = intervals->getChild();
		auto high = low->getNext();

		unsigned int  uLow = this->factory->getData<unsigned int>(low);
		unsigned int uHigh = this->factory->getData<unsigned int>(high);

		if (uLow >= uHigh)
			throw Exception("error data low bound is bigger then high bound", __LINE__, __FILE__, __FUNCTION__);

		ret.push_back(
			std::pair<unsigned int, unsigned int>(uLow, uHigh)
		);

		intervals = intervals->getNext();
	}

	return ret;
}