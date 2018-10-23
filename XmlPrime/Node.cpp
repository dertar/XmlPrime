#include "pch.h"
#include "Node.h"
#include "Exception.h"

Node::Node(const std::string &key) : key(key) 
{
	if (key.empty())
		throw Exception("error creation a node, key is empty", __LINE__, __FILE__, __FUNCTION__);

}

Node::~Node() {}

Node* Node::findFirstChild(const std::string &key) noexcept
{
	auto ret = this->child;

	if (ret == nullptr)
		return ret;

	do {
		if (ret->getKey() == key)
			return ret;

		ret = ret->next;
	} while (ret != nullptr);

	return ret;
}

Node* Node::addChild(const std::string &key)
{
	return this->addChild(new Node(key));
}

Node* Node::addChild(Node *node) noexcept
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

Node* Node::addNext(Node *node) noexcept
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

Node* Node::getLast() noexcept 
{
	auto ret = this;

	while (ret->next != nullptr)
	{
		ret = ret->next;
	}

	return ret;
}

Node* Node::getNext() const noexcept
{
	return this->next;
}

Node* Node::getChild() const noexcept
{
	return this->child;
}

bool Node::hasChild() const noexcept
{
	return this->child != nullptr;
}

bool Node::hasNext() const noexcept
{
	return this->next != nullptr;
}

const std::string& Node::getKey() const noexcept
{
	return this->key;
}
