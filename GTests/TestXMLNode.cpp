#include "pch.h"
#include "../XmlPrime/XMLNode.h"
#include "../XmlPrime/XMLNodeFactory.h"
TEST(TestNode, TestNodeCreation)
{
	auto node = new XMLNode<int>("root");

	ASSERT_EQ("root", node->getKey());

	delete node;
}

TEST(TestNode, TestNodeCreationException)
{
	ASSERT_ANY_THROW(new XMLNode<int>(""));
}

TEST(TestNode, TestNodeAddChildException)
{
	auto node = new XMLNode<int>("root");

	ASSERT_ANY_THROW(node->addChild(new XMLNode<int>("")));

	delete node;
}

TEST(TestNode, TestNodeAddChild)
{
	auto node = new XMLNode<int>("root");
	auto child = node->addChild(new XMLNode<int>("child"));

	ASSERT_EQ("child", child->getKey());

	delete child;
	delete node;
}

TEST(TestNode, TestNodeAddNext)
{
	auto node = new XMLNode<int>("root");
	auto next = node->addNext(new XMLNode<int>("next"));

	ASSERT_EQ("next", next->getKey());
	ASSERT_TRUE(next == node->getLast());

	delete next;
	delete node;
}

TEST(TestNode, TestNodeHasNext)
{
	auto node = new XMLNode<int>("root");
	auto child = node->addChild(new XMLNode<int>("child"));

	ASSERT_FALSE(node->hasNext());
	ASSERT_FALSE(child->hasNext());

	delete child;
	delete node;
}



TEST(TestNode, TestNodeHasChild)
{
	auto node = new XMLNode<int>("root");
	auto child = node->addChild(new XMLNode<int>("child"));

	ASSERT_TRUE(node->hasChild());
	ASSERT_FALSE(child->hasChild());

	delete child;
	delete node;
}

TEST(TestNode, TestNodeHasChild1)
{
	auto node = new XMLNode<int>("root");
	
	ASSERT_FALSE(node->hasNext());

	delete node;
}


TEST(TestNode, TestNodeAddChild1)
{
	auto node = new XMLNode<int>("root");
	auto child = node->addChild("child");
	auto child1 = node->addChild("child1");

	ASSERT_EQ("child", child->getKey());
	ASSERT_EQ("child1", child1->getKey());

	delete child1;
	delete child;
	delete node;
}

TEST(TestNode, TestNodeGetNext)
{
	auto node = new XMLNode<int>("root");

	ASSERT_EQ(nullptr, node->getNext());

	delete node;
}

TEST(TestNode, TestNodeGetNext1)
{
	auto node = new XMLNode<int>("root");
	auto child = node->addChild("child");
	auto child1 = node->addChild("child1");

	ASSERT_TRUE(child->getNext() == child1);
	ASSERT_EQ(nullptr, child1->getNext());

	delete child1;
	delete child;
	delete node;
}

TEST(TestNode, TestNodeGet)
{
	auto node = new XMLNode<int>("root");
	auto child = node->addChild("child");
	auto child1 = node->addChild("child1");

	ASSERT_TRUE(node->findFirstChild("child") == child);
	ASSERT_TRUE(node->findFirstChild("child1") == child1);

	delete child1;
	delete child;
	delete node;
}

TEST(TestNode, TestNodeGetFalse)
{
	auto node = new XMLNode<int>("root");
	auto child = node->addChild("child");

	ASSERT_FALSE(node->findFirstChild("root") == child);
	ASSERT_TRUE(node->findFirstChild("child1") == nullptr);

	delete child;
	delete node;
}

TEST(TestNode, TestNodeGetData)
{
	std::string magic = "magic_tree";

	auto node = new XMLNode<std::string>("root", magic);
	
	ASSERT_EQ(node->getVal().compare(magic), 0);

	delete node;
}

TEST(TestNode, TestNodeGetData1)
{
	std::string magic = "magic_tree";

	auto node = new XMLNode<std::string>("root", magic);

	ASSERT_EQ(node->getVal().compare(magic), 0);

	delete node;
}

