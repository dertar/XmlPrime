#pragma once

#include "Node.h"
#include "Converter.h"
#include "XMLNodeFactory.h"
#include "Exception.h"

#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>

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

	// parse a text into chunks and translate them into the drafts
	std::vector < std::pair<std::string, TYPE>* >* parse(const std::string &from);

	// checks queue for correct brackets
	void checkQueue(std::vector < std::pair<std::string, TYPE>* >* queue);

	std::vector<std::string> split(const std::string &text, char delim);

	
	bool checkData(const std::string &data) const noexcept;
	bool checkBracketName(const std::string &data) const noexcept;

	// recreation from drafts to XMLDocument
	Node* createXML(std::vector < std::pair<std::string, Converter <std::string, Node*>::TYPE>* >* queue);
	
	bool isNumber(const std::string &s);
};

inline std::vector<std::pair<std::string, Converter<std::string, Node*>::TYPE>*>* Converter<std::string, Node*>::parse(const std::string &from)
{
	auto lems = this->split(from, '<');
	// remove empty element
	lems.erase(lems.begin(), lems.begin() + 1);

	if (lems.size() == 0)
		throw Exception("Parse XML: error", __LINE__, __FILE__, __FUNCTION__);

	auto queue = new std::vector < std::pair<std::string, TYPE>* >();

	for (auto &x : lems)
	{
		auto l = this->split(x, '>');

		int size = l.size();

		if (size == 0)
		{
			delete queue;
			throw Exception("Parse XML: error", __LINE__, __FILE__, __FUNCTION__);
		}

		if (size >= 1)
		{
			auto bracket = new std::pair<std::string, TYPE>();

			if (l.at(0).at(0) == '/')
			{
				bracket->second = TYPE::CLOSED;
				bracket->first = l.at(0).substr(1, l.at(0).size());
			}
			else
			{
				bracket->second = TYPE::OPEN;
				bracket->first = l.at(0);
			}
			queue->push_back(bracket);

			if (size == 2)
			{
				if (l.at(1).empty())
					throw Exception("Parse XML: error", __LINE__, __FILE__, __FUNCTION__);

				auto data = new std::pair<std::string, TYPE>();
				data->second = TYPE::DATA;
				data->first = l.at(1);
				queue->push_back(data);
			}
		}

	}

	return queue;
}

inline void Converter<std::string, Node*>::checkQueue(std::vector<std::pair<std::string, TYPE>*>* queue)
{
	auto stack = std::stack< std::pair<std::string, TYPE>* >();

	for (auto el : *queue)
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

			auto top = stack.top();
			
			if (top->first != el->first || top->second == el->second)
				throw Exception("Parse XML: brackets aren't correct", __LINE__, __FILE__, __FUNCTION__);

			stack.pop();
		}
		else
		{
			if (!this->checkBracketName(el->first))
				throw Exception("Parse XML: the bracket's name has errors", __LINE__, __FILE__, __FUNCTION__);;

			stack.push(el);
		}
	}

	if (stack.size() != 0)
		throw Exception("Parse XML: brackets aren't correct", __LINE__, __FILE__, __FUNCTION__);

}

inline std::vector<std::string> Converter<std::string, Node*>::split(const std::string & text, char delim)
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

inline Node * Converter<std::string, Node*>::createXML(std::vector<std::pair<std::string, Converter<std::string, Node*>::TYPE>*>* queue)
{
	auto stack = new std::stack<Node*>();

	for (auto x : *queue)
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

	auto ret = this->createXML(parsedQueue);

	for (auto &x : *parsedQueue)
	{
		delete x;
	}

	delete parsedQueue;

	return ret;
}

inline bool Converter<std::string, Node*>::isNumber(const std::string &val)
{
	return !val.empty() && std::find_if(val.begin(), val.end(), 
		[](char ch){
			return !isdigit(ch);
		}) == val.end();
}
