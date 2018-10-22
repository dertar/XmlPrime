#include "pch.h"
#include "XMLDocument.h"


XMLDocument::XMLDocument(const std::string &rootName) 
	: XMLDocument(new XMLNode(rootName))
{
	
}

XMLDocument::XMLDocument(XMLNode *root)
{
	this->_root = root;
}

XMLDocument::~XMLDocument()
{
	this->clear();
	delete this->_root;
}

unsigned int XMLDocument::clear()
{
	auto nodes = new std::stack<XMLNode*>();
	unsigned int ret = 0;
	std::string name = this->_root->getName();


	this->destroy(this->_root, nodes, ret);

	delete nodes;

	this->_root = new XMLNode(name);

	return ret;
}

void XMLDocument::destroy(XMLNode *node, std::stack<XMLNode*> *nodes, unsigned int &count)
{
	if (!node)
	{
		if (nodes->empty())
			return;
		
		while (!nodes->empty())
		{
			node = nodes->top();
			nodes->pop();
			delete node;

			count++;
		}

		return;
	}

	nodes->push(node);

	if (node->hasChild())
	{
		destroy(node->getChild(), nodes, count);
		return;
	}
	
	destroy(node->getNext(), nodes, count);
}

XMLNode * XMLDocument::root() const
{
	return this->_root;
}



