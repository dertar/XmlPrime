#pragma once

#include "XMLNode.h"
#include <stack>
#include <vector>

class XMLDocument
{
public:
	explicit XMLDocument(const std::string &rootName = "root");
	explicit XMLDocument(Node *root);

	~XMLDocument();
	// gets root of document
	Node* root() const;
	// clears XML, returns count of deleted XMLNode<std::string>s, root name will stay
	unsigned int clear();

private:
	Node *_root = nullptr;
	// recursive algorithm to destroy the tree
	void destroy(Node *node, std::vector<Node*>* vec);
};

