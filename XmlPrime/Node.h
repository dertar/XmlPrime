#pragma once
class Node
{
public:
	Node(const std::string &key);
	virtual ~Node();

	Node* findFirstChild(const std::string &key) noexcept;

	Node* addChild(const std::string &key);
	Node* addChild(Node *node) noexcept;
	Node* addNext(Node *node) noexcept;

	Node* getLast() noexcept;
	Node* getNext() const noexcept;
	Node* getChild() const noexcept;

	bool hasChild() const noexcept;
	bool hasNext() const noexcept;

	const std::string& getKey() const noexcept;

protected:
	std::string key;

	Node *next = nullptr;
	Node *child = nullptr;
};

