#pragma once
#include "Converter.h"
#include "Node.h"
#include "XMLNodeFactory.h"

// scraps the intervals from XMLNode to comfortable container (vector of pair)
class ConverterIntervals
	: Converter<Node* ,std::vector<std::pair<unsigned int, unsigned int>> >
{
public:
	std::vector<std::pair<unsigned int, unsigned>> convert(Node *node);

	ConverterIntervals();
	~ConverterIntervals();

private:
	XMLNodeFactory *factory;
};

