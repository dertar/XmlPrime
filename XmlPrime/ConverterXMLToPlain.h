#pragma once
#include "Converter.h"
#include "Node.h"
#include "XMLNodeFactory.h"
#include <string>
#include <stack>

template <>
class Converter <Node*, std::string>
{
public:

	Converter()
	{
		this->factory = XMLNodeFactory::getInstance();
	}

	std::string convert(Node *from)
	{
		this->init();

		this->genPlain(from);

		return this->plain;
	}

	// newline will be added in every brackets and data's,
	// tabs will be added in every new line, count of tabs will be depends on depths of current bracket/data
	std::string convert(Node *from, const std::string &newLine, const std::string &tab)
	{
		this->newline = newLine;
		this->tab = tab;

		return this->convert(from);
	}

private:
	// don't do that
	// maybe leaks resources
	std::stack <Node*> nodes;

	std::string plain;

	std::string newline;
	std::string tab;
	unsigned int depth;
	
	XMLNodeFactory *factory;

	// recursive algorithm to create plain text from XMLNode
	void genPlain(Node *node);

	void push(Node* node);
	Node* pop();
	std::string genTabs();
	void putData(Node* node);

	void init();
};

inline void Converter<Node*, std::string>::genPlain(Node * node)
{
	if (!node)
	{
		if (this->nodes.empty())
			return;

		node = this->pop();

		this->genPlain(node->getNext());
		return;
	}

	this->push(node);

	if (node->hasChild())
	{
		this->genPlain(node->getChild());
		return;
	}
	else if (!this->factory->isSimpleNode(node))
	{
		this->putData(node);
		this->pop();
	}

	this->genPlain(node->getNext());
}

inline void Converter<Node*, std::string>::push(Node * node)
{
	this->nodes.push(node);

	this->plain += (this->genTabs() + "<" + node->getKey() + ">" + this->newline);

	this->depth++;
}

inline Node * Converter<Node*, std::string>::pop()
{
	auto ret = this->nodes.top();
	this->nodes.pop();

	this->depth--;

	this->plain += (this->genTabs() + "</" + ret->getKey() + ">" + this->newline);

	return ret;
}

inline std::string Converter<Node*, std::string>::genTabs()
{
	unsigned int d = 0;
	std::string tabs = "";

	while (d++ < this->depth)
		tabs += this->tab;

	return tabs;
}

inline void Converter<Node*, std::string>::putData(Node *node)
{
	Converter<unsigned int, std::string> c;

	std::string data;
	if (this->factory->isData<unsigned int>(node))
	{
		data = c.convert(this->factory->getData<unsigned int>(node));
	}
	else if (this->factory->isData<std::string>(node))
	{
		data = this->factory->getData<std::string>(node);
	}

	if(!data.empty())
		this->plain += (this->genTabs() + data + this->newline);
}

inline void Converter<Node*, std::string>::init()
{
	this->plain.erase();

	this->depth = 0;

	while (!this->nodes.empty())
	{
		auto node = this->nodes.top();
		this->nodes.pop();
		
		delete node;
	}
	
}
