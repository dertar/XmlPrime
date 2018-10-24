#pragma once

#include "Node.h"
// node with data
template <typename T>
class XMLNode : public Node
{
public:
	explicit XMLNode<T>(const std::string &key) : Node(key) { }

	XMLNode<T>(const std::string &key, const T &val) 
		: Node(key), val(val), _hasData(true)
	{
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
