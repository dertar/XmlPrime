#pragma once

#include "XMLNode.h"
#include <stack>

class XMLDocument
{
public:
	explicit XMLDocument(const std::string &rootName = "root");
	explicit XMLDocument(XMLNode *root);

	~XMLDocument();
	// gets root of document
	XMLNode* root() const;
	// clears XML, returns count of deleted XMLNodes, root name will stay
	unsigned int clear();

private:
	XMLNode *_root = NULL;
	// recursive algorithm to delete tree of XMLNode
	void destroy(XMLNode *node, std::stack<XMLNode*> *nodes, unsigned int &count);
};

