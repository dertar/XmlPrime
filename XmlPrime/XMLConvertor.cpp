#include "pch.h"
#include "XMLConvertor.h"


XMLConvertor* XMLConvertor::getIntance()
{
	if (instance == NULL)
		instance = new XMLConvertor();

	return instance;
}

std::vector<std::string> XMLConvertor::split(const std::string &text, char delim)
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

bool XMLConvertor::checkData(const std::string & data) const noexcept
{
	return true;
}

bool XMLConvertor::checkBracketName(const std::string & data) const noexcept
{
	return true;
}

XMLDocument* XMLConvertor::createXML(std::vector<std::pair<std::string, XMLConvertor::TYPE>*>* queue)
{
	auto stack = new std::stack<XMLNode*>();

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
			}else
				stack->push(child);
			
		}else if (x->second == TYPE::OPEN)
		{
			auto node = new XMLNode(x->first);
			stack->push(node);

		}else if (x->second == TYPE::DATA)	
		{
			auto node = stack->top();
			node->setData(x->first);
		}
	}

	return new XMLDocument(stack->top());
}

std::vector < std::pair<std::string, XMLConvertor::TYPE>* >* XMLConvertor::parse()
{
	auto lems = this->split(*this->plain, '<');
	// remove empty element
	lems.erase(lems.begin(), lems.begin() + 1);

	if (lems.size() == 0)
		throw std::exception("Parse XML: error");

	auto queue = new std::vector < std::pair<std::string, TYPE>* >();

	for (auto &x : lems)
	{
		auto l = this->split(x, '>');

		int size = l.size();

		if (size == 0) 
		{
			delete queue;
			throw std::exception("Parse XML: error");
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
					throw std::exception("Parse XML: error");

				auto data = new std::pair<std::string, TYPE>();
				data->second = TYPE::DATA;
				data->first = l.at(1);
				queue->push_back(data);
			}
		}
		
	}

	return queue;
}

void XMLConvertor::checkQueue(std::vector<std::pair<std::string, TYPE>*>* queue)
{
	auto stack = std::stack< std::pair<std::string, TYPE>* >();

	for (auto el : *queue)
	{
		if (el->second == TYPE::DATA)
		{
			if (!this->checkData(el->first))
				throw std::exception("Parse XML: the data has errors");
		}
		else if (el->second == TYPE::CLOSED)
		{
			if(stack.empty())
				throw std::exception("Parse XML: brackets aren't correct");
			
			auto top = stack.top();
			
			if (top->first != el->first || top->second == el->second)
				throw std::exception("Parse XML: brackets aren't correct");

			stack.pop();
		}
		else
		{
			if (!this->checkBracketName(el->first))
				throw std::exception("Parse XML: the bracket's name has errors");
			
			stack.push(el);
		}
	}

	if(stack.size() != 0)
		throw std::exception("Parse XML: brackets aren't correct");
	
}

void XMLConvertor::push(XMLNode* node)
{
	this->nodes->push(node);

	*this->plain += (this->genTabs() + "<" + node->getName() + ">" + this->newline);

	this->depth++;
}

XMLNode* XMLConvertor::pop()
{
	auto ret = this->nodes->top();
	this->nodes->pop();

	this->depth--;

	*this->plain += (this->genTabs() + "</" + ret->getName() + ">" + this->newline);

	return ret;
}

std::string XMLConvertor::genTabs()
{
	unsigned int d = 0;
	std::string tabs = "";

	while (d++ < this->depth)
		tabs += this->tab;
	
	return tabs;
}

void XMLConvertor::putData(const XMLNode *node)
{	
	*this->plain += (this->genTabs() + *node->getData() + this->newline);
}

void XMLConvertor::genPlain(XMLNode *node)
{
	
	if (!node)
	{
		if (this->nodes->empty())
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
	} else if(node->hasData())
	{
		this->putData(node);
		
		this->pop();
	}
	
	this->genPlain(node->getNext());
}

std::string* XMLConvertor::toPlain(const XMLDocument *xml, const std::string &newline, const std::string &tab)
{
	return this->toPlain(xml->root(), newline, tab);
}

std::string* XMLConvertor::toPlain(XMLNode *root, const std::string &newline, const std::string &tab)
{
	this->newline = newline;
	this->tab = tab;
	this->plain = new std::string();
	
	this->depth = 0;

	while (!this->nodes->empty())
		this->nodes->pop();

	this->genPlain(root);

	return this->plain;
}

XMLDocument* XMLConvertor::toXML(std::string &buffer)
{
	this->plain = &buffer;


	this->plain->erase(std::remove(this->plain->begin(), this->plain->end(), ' '), this->plain->end());
	this->plain->erase(std::remove(this->plain->begin(), this->plain->end(), '\t'), this->plain->end());
	this->plain->erase(std::remove(this->plain->begin(), this->plain->end(), '\n'), this->plain->end());


	auto parsedQueue = this->parse();

	this->checkQueue(parsedQueue);

	auto ret = this->createXML(parsedQueue);

	for (auto &x : *parsedQueue)
	{
		delete x;
	}

	delete parsedQueue;

	return ret;
}

XMLConvertor::XMLConvertor()
{
	this->nodes = new std::stack<XMLNode*>();
	this->plain = nullptr;
	this->depth = 0;
}

XMLConvertor::~XMLConvertor()
{
	delete this->nodes;
	this->plain = nullptr;
}

XMLConvertor* XMLConvertor::instance = NULL;