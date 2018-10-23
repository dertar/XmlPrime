#pragma once

#include "XMLNode.h"
#include "Exception.h"

// factory class that helps to manage XMLNode 
class XMLNodeFactory
{
public:

	template <typename T>
	XMLNode<T>* createNode(const std::string &key)
	{
		return new XMLNode<T>(key);
	}

	template <typename T>
	XMLNode<T>* createNode(const std::string &key, const T &val)
	{
		return new XMLNode<T>(key, val);
	}

	template <typename T>
	Node* setValue(Node *node, const T &data)
	{
		if (typeid(XMLNode<T>) == typeid(*node))
		{
			XMLNode<T>* casted = static_cast< XMLNode<T>* > (node);
			casted->setValue(data);
		}else
		{
			throw Exception("XMLNode creation failed: had tried to push improper val", __LINE__, __FILE__, __FUNCTION__);
		}
			
		return node;
	}

	template <typename T>
	bool hasData(Node *node)
	{
		if (typeid(XMLNode<T>) == typeid(*node))
		{
			XMLNode<T>* casted = static_cast<XMLNode<T>*> (node);
			
			return casted->hasData();
		}
		return false;
	}

	template <typename T>
	T& getData(Node *node)
	{
		if (typeid(XMLNode<T>) != typeid(*node))
			throw Exception("Error tried to get unsuitable type in node", __LINE__, __FILE__, __FUNCTION__);

		XMLNode<T>* casted = static_cast<XMLNode<T>*> (node);
		return casted->getVal();
	}

	bool isSimpleNode(Node *node)
	{
		return typeid(Node) == typeid(*node);
	}

	template <typename T>
	bool isData(Node *node)
	{
		if (typeid(XMLNode<T>) == typeid(*node))
		{
			return true;
		}
		return false;
	}

	static XMLNodeFactory *getInstance()
	{
		if (instance == nullptr)
			instance = new XMLNodeFactory();

		return instance;
	}

	~XMLNodeFactory() {}
private:
	static XMLNodeFactory *instance;
	XMLNodeFactory& operator=(XMLNodeFactory&) = delete;
	XMLNodeFactory(const XMLNodeFactory&) = delete;

	XMLNodeFactory() {}
	
};

