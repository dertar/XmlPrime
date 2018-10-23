#include "pch.h"
#include "XMLDocument.h"


XMLDocument::XMLDocument(const std::string &rootName) 
	: XMLDocument(new Node(rootName))
{
	
}

XMLDocument::XMLDocument(Node *root)
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
	auto nodes = new std::stack<Node*>();
	unsigned int ret = 0;
	std::string name = this->_root->getKey();


	this->destroy(this->_root, nodes, ret);

	delete nodes;

	this->_root = new Node(name);

	return ret;
}

void XMLDocument::destroy(Node *node, std::stack<Node*> *nodes, unsigned int &count)
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

Node* XMLDocument::root() const
{
	return this->_root;
}