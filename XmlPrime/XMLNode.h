#pragma once

#include "Node.h"
// node with data
template <typename T>
class XMLNode : public Node
{
public:
	explicit XMLNode<T>(const std::string &key) : Node(key) { }

	XMLNode<T>(const std::string &key, const T &val) : Node(key)
	{
		this->val = val; // copyable object
		this->_hasData = true;
	}

	void setValue(const T &data) noexcept
	{
		this->_hasData = true;
		this->val = data;
	}

	bool hasData() const noexcept
	{
		return this->_hasData;
	}

	T& getVal() noexcept
	{
		return this->val;
	}

	~XMLNode()
	{
	}

private:
	T val;
	bool _hasData = false;
};

// Node for pointers
//template <typename T>
//class XMLNode<T*> : public XMLNode<T>
//{
//public:
//	
//	XMLNode<T>(const std::string &key, const T &val) : Node(key)
//	{
//		this->val = new T(*val);
//	}
//
//	void setValue(const T &data) noexcept
//	{
//		if(this->val != nullptr)
//			delete this->val;
//
//		this->val = new T(data);
//	}
//
//	bool hasData() const noexcept
//	{
//		return this->val != nullptr;
//	}
//
//	T& getVal() const noexcept
//	{
//		return *this->val;
//	}
//
//	~XMLNode()
//	{
//		if (this->hasData())
//			delete val;
//	}
//
//private:
//	T *val = nullptr;
//};
//
