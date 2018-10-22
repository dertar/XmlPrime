#include "pch.h"
#include "XMLNode.h"


XMLNode::XMLNode(const std::string &name) : XMLNode(name, nullptr)
{
}

XMLNode::XMLNode(const std::string &name, const std::string &val) :
	XMLNode(name, &val)
{

}

XMLNode::XMLNode(const std::string &name, const std::string *val)
{
	if (name.empty())
		throw new std::exception("Node's key is empty");

	this->key = new std::string(name);

	if (val != nullptr)
		this->val = new std::string(*val);
}

XMLNode::~XMLNode()
{
	delete this->key;
	delete this->val;
}

XMLNode* XMLNode::get(const std::string &key)
{
	auto ret = this->child;

	if (ret == nullptr)
		return ret;

	do {
		if (ret->getName() == key)
			return ret;

		ret = ret->next;
	} while (ret != nullptr);

	return ret;
}


XMLNode* XMLNode::addChild(const std::string& key)
{
	return this->addChild(key, nullptr);
}

XMLNode* XMLNode::addChild(const std::string& key, const std::string& val)
{
	return this->addChild(key, &val);
}

XMLNode* XMLNode::addChild(const std::string& key, const std::string* val)
{
	return this->addChild(new XMLNode(key, val));
}

XMLNode* XMLNode::addChild(XMLNode* node)
{
	if (this->child == nullptr)
	{
		this->child = node;
	}
	else
	{
		auto last = this->child->getLast();
		last->next = node;
	}

	return node;
}

XMLNode * XMLNode::addNext(XMLNode * node)
{
	if (this->next == nullptr)
	{
		this->next = node;
	}
	else
	{
		auto last = this->next->getLast();
		last->next = node;
	}

	return node;
}

void XMLNode::setData(const std::string & data)
{
	this->val = new std::string(data);
}

XMLNode* XMLNode::getLast()
{
	auto ret = this;

	while (ret->next != nullptr)
	{
		ret = ret->next;
	}

	return ret;
}

XMLNode* XMLNode::getNext() const
{
	return this->next;
}

XMLNode * XMLNode::getChild() const
{
	return this->child;
}

bool XMLNode::hasChild() const
{
	return this->child != nullptr;
}

bool XMLNode::hasNext() const
{
	return this->next != nullptr;
}

bool XMLNode::hasData() const
{
	return this->val != nullptr;
}

const std::string& XMLNode::getName() const
{
	return *(this->key);
}

const std::string* XMLNode::getData() const
{
	return this->val;
}