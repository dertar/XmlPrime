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
	auto vec = new std::vector<Node*>();
	std::string name = this->_root->getKey();


	this->destroy(this->_root, vec);

	auto ret = vec->size();

	for (std::vector<Node*>::iterator it = vec->begin();
		it != vec->end(); ++it) 
	{
		delete *it;
	}

	vec->clear();
	delete vec;

	delete this->_root;
	this->_root = new Node(name);

	return ret + 1;
}

void XMLDocument::destroy(Node *node, std::vector<Node*> *nodes)
{
	if (!node)
	{
		return;
	}

	//nodes->push(node);

	if (node->hasChild())
	{
		nodes->push_back(node->getChild());
	}

	if (node->hasNext())
	{
		nodes->push_back(node->getNext());
	}

	destroy(node->getChild(), nodes);
	destroy(node->getNext(), nodes);
	
}


Node* XMLDocument::root() const
{
	return this->_root;
}