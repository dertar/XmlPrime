#pragma once

#include "XMLNode.h"
#include "XMLDocument.h"

#include <stack>
#include <queue>
#include <sstream>

// fabric class that creates xmls from plain texts and vice verse
class XMLConvertor
{
public:
	static XMLConvertor *getIntance();

	// newline will be added in every brackets and data's,
	// tabs will be added in every new line, count of tabs will be depends on depths of current bracket/data
	std::string* toPlain(XMLNode *node, const std::string &newline = "\n", const std::string &tab = "\t");
	std::string* toPlain(const XMLDocument *xml, const std::string &newline = "\n", const std::string &tab = "\t");
	
	XMLDocument* toXML(std::string &buffer);

private:
	// drafts for recreation XMLDocument
	enum class TYPE
	{
		OPEN,
		CLOSED,
		DATA
	};

	std::string *plain;
	std::stack <XMLNode*> *nodes;

	std::string newline;
	std::string tab;
	unsigned int depth;

	// recursive algorithm to create plain text from XMLNode
	void genPlain(XMLNode *node);

	void push(XMLNode* node);
	XMLNode* pop();
	std::string genTabs();
	void putData(const XMLNode *node);

	// parse text to draft
	std::vector < std::pair<std::string, TYPE>* >* parse();

	// checks queue for correct brackets
	void checkQueue(std::vector < std::pair<std::string, TYPE>* >* queue);

	std::vector<std::string> split(const std::string &text, char delim);

	bool checkData(const std::string &data) const noexcept;
	bool checkBracketName(const std::string &data) const noexcept;

	// recreation from drafts to XMLDocument
	XMLDocument* createXML(std::vector < std::pair<std::string, XMLConvertor::TYPE>* >* queue);

	XMLConvertor();
	~XMLConvertor();
	// singleton's principes
	XMLConvertor& operator=(XMLConvertor&) = delete;
	static XMLConvertor *instance;

};

