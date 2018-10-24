#pragma once

#include "Node.h"
#include "Converter.h"
#include "XMLNodeFactory.h"
#include "Exception.h"

#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <memory>

template <>
class Converter <std::string, Node*>
{
public:
	Node *convert(std::string &from);

private:
	// drafts for recreation XMLDocument
	enum class TYPE
	{
		OPEN,
		CLOSED,
		DATA
	};

	XMLNodeFactory* factory;

	using pair = std::pair<std::string, TYPE>;
	using sp_pair = std::unique_ptr< pair >;

	// parse a text into chunks and translate them into the drafts
	// return smart pointer of (vector) of (pair) of braket's name and type
	std::unique_ptr< std::vector<sp_pair> > parse(const std::string &from);

	// checks queue for correct brackets 
	void checkQueue(std::unique_ptr<std::vector<sp_pair> > &queue);

	// splits text by delim
	std::vector<std::string> split(const std::string &text, char delim) const;

	// validate methods for bracket's name and data
	bool checkData(const std::string &data) const noexcept;
	bool checkBracketName(const std::string &data) const noexcept;

	// recreation XMLDocument from drafts 
	// smart pointer passes by value, in next step it doesn't need
	Node* createXML(std::unique_ptr<std::vector<sp_pair> >  queue);
	
	bool isNumber(const std::string &s);
};

inline std::unique_ptr< std::vector < Converter<std::string, Node*>::sp_pair > > Converter<std::string, Node*>::parse(const std::string &from)
{
	auto lems = this->split(from, '<');

	// remove empty element
	lems.erase(lems.begin(), lems.begin() + 1);

	if (lems.size() == 0)
		throw Exception("Parse XML: nothing to parse", __LINE__, __FILE__, __FUNCTION__);

	auto queue = std::make_unique< std::vector<sp_pair> >();

	for (auto &x : lems)
	{
		auto l = this->split(x, '>');

		auto size = l.size();

		if (size == 0)
			throw Exception("Parse XML: error", __LINE__, __FILE__, __FUNCTION__);

		if (size >= 1)
		{
			auto bracket = std::make_unique<pair>();

			if (l.at(0).at(0) == '/')
			{
				bracket->second = TYPE::CLOSED;
				//removing first character - slash 
				bracket->first = l.at(0).substr(1, l.at(0).size());
			}
			else
			{
				bracket->second = TYPE::OPEN;
				bracket->first = l.at(0);
			}

			queue->push_back(std::move(bracket));
			
			// bracket has data
			if (size == 2)
			{
				if (l.at(1).empty())
					throw Exception("Parse XML: error", __LINE__, __FILE__, __FUNCTION__);

				auto data = std::make_unique<pair>(l.at(1), TYPE::DATA);

				queue->push_back(std::move(data));
			}
		}

	}

	return queue;
}

inline void Converter<std::string, Node*>::checkQueue(std::unique_ptr< std::vector < sp_pair > > &queue)
{
	auto stack = std::stack<sp_pair>();

	for (auto const &el : *queue)
	{
		if (el->second == TYPE::DATA)
		{
			if (!this->checkData(el->first))
				throw Exception("Parse XML: the data has errors", __LINE__, __FILE__, __FUNCTION__);
		}
		else if (el->second == TYPE::CLOSED)
		{
			if (stack.empty())
				throw Exception("Parse XML: brackets aren't correct", __LINE__, __FILE__, __FUNCTION__);

			auto top = std::move(stack.top());

			if (top->first != el->first || top->second == el->second)
				throw Exception("Parse XML: brackets aren't correct", __LINE__, __FILE__, __FUNCTION__);
			
			stack.pop();
		}
		else
		{
			if (!this->checkBracketName(el->first))
				throw Exception("Parse XML: the bracket's name has errors", __LINE__, __FILE__, __FUNCTION__);;
			
			auto copy = std::make_unique<pair>(el->first, el->second);
			stack.push(std::move(copy));
		}
	}

	if (stack.size() != 0)
		throw Exception("Parse XML: brackets aren't correct", __LINE__, __FILE__, __FUNCTION__);

}

inline std::vector<std::string> Converter<std::string, Node*>::split(const std::string & text, char delim) const
{
	std::vector<std::string> lems;
	std::string lem;
	std::istringstream stream(text);

	while (std::getline(stream, lem, delim))
	{
		lems.push_back(lem);
	}

	return lems;
}

inline bool Converter<std::string, Node*>::checkData(const std::string & data) const noexcept
{
	return true;
}

inline bool Converter<std::string, Node*>::checkBracketName(const std::string & data) const noexcept
{
	return true;
}

inline Node * Converter<std::string, Node*>::createXML(std::unique_ptr<std::vector<sp_pair> > queue)
{
	auto stack = new std::stack<Node*>();

	for (auto &x : *queue)
	{
		if (x->second == TYPE::CLOSED)
		{
			auto child = stack->top();
			stack->pop();

			if (!stack->empty())
			{
				auto parent = stack->top();
				parent->addChild(child);
			}
			else
				stack->push(child);

		}
		else if (x->second == TYPE::OPEN)
		{
			auto node = new Node(x->first);
			stack->push(node);
		}
		else if (x->second == TYPE::DATA)
		{
			if (stack->empty())
				throw Exception("Error parsing XML: hasn't element at top of stack", __LINE__, __FILE__, __FUNCTION__);

			auto node = stack->top();
			stack->pop();

			Node *replace;
			
			if (this->isNumber(x->first))
			{
				Converter<std::string, unsigned int> c;
				
				replace = factory->createNode<unsigned int>(node->getKey(), c.convert(x->first));
			}
			else
			{
				replace = factory->createNode<std::string>(node->getKey(), x->first);
			}
			delete node;
			stack->push(replace);
		}
	}

	return stack->top();
}

inline Node * Converter<std::string, Node*>::convert(std::string &from)
{
	if (this->factory == nullptr)
		this->factory = XMLNodeFactory::getInstance();

	from.erase(std::remove(from.begin(), from.end(), ' '), from.end());
	from.erase(std::remove(from.begin(), from.end(), '\t'), from.end());
	from.erase(std::remove(from.begin(), from.end(), '\n'), from.end());

	auto parsedQueue = this->parse(from);

	this->checkQueue(parsedQueue);

	auto ret = this->createXML(std::move(parsedQueue));

	return ret;
}

inline bool Converter<std::string, Node*>::isNumber(const std::string &val)
{
	return !val.empty() && std::find_if(val.begin(), val.end(), 
		[](char ch){
			return !isdigit(ch);
		}) == val.end();
}
