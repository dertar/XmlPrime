#pragma once


class XMLNode
{
public:
	explicit XMLNode(const std::string &name);
	XMLNode(const std::string &name, const std::string &val);
	XMLNode(const std::string &name, const std::string *val);

	~XMLNode();

	XMLNode* get(const std::string &key);

	XMLNode* addChild(const std::string &key);
	XMLNode* addChild(const std::string &key, const std::string &val);
	XMLNode* addChild(const std::string &key, const std::string *val);
	XMLNode* addChild(XMLNode  *node);

	XMLNode* addNext(XMLNode *node);
	void setData(const std::string &data);

	XMLNode* getLast();
	XMLNode* getNext() const;
	XMLNode* getChild() const;

	bool hasChild() const;
	bool hasNext() const;
	bool hasData() const;

	const std::string& getName() const;
	const std::string* getData() const;

private:
	std::string *key = nullptr;
	std::string *val = nullptr;

	XMLNode *next = nullptr;
	XMLNode *child = nullptr;
};
