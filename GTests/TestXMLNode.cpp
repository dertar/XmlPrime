#include "pch.h"
#include "../XmlPrime/XMLNode.h"

TEST(TestNode, TestNodeCreation)
{
	auto node = new XMLNode("root");

	ASSERT_EQ("root", node->getName());

	delete node;
}

TEST(TestNode, TestNodeCreationException)
{
	ASSERT_ANY_THROW(new XMLNode(""));

}

TEST(TestNode, TestNodeAddChildException)
{
	auto node = new XMLNode("root");

	ASSERT_ANY_THROW(node->addChild(""));

	delete node;
}

TEST(TestNode, TestNodeAddChild)
{
	auto node = new XMLNode("root");
	auto child = node->addChild("child");

	ASSERT_EQ("child", child->getName());

	delete child;
	delete node;
}

TEST(TestNode, TestNodeAddNext)
{
	auto node = new XMLNode("root");
	auto next = node->addNext(new XMLNode("next"));

	ASSERT_EQ("next", next->getName());
	ASSERT_TRUE(next == node->getLast());

	delete next;
	delete node;
}

TEST(TestNode, TestNodeHasNext)
{
	auto node = new XMLNode("root");
	auto child = node->addChild("child");

	ASSERT_FALSE(node->hasNext());
	ASSERT_FALSE(child->hasNext());

	delete child;
	delete node;
}


TEST(TestNode, TestNodeHasData)
{
	auto node = new XMLNode("root");
	auto child = node->addChild("child", "data");

	ASSERT_FALSE(node->hasData());
	ASSERT_TRUE(child->hasData());

	delete child;
	delete node;
}

TEST(TestNode, TestNodeHasChild)
{
	auto node = new XMLNode("root");
	auto child = node->addChild("child");

	ASSERT_TRUE(node->hasChild());
	ASSERT_FALSE(child->hasChild());

	delete child;
	delete node;
}

TEST(TestNode, TestNodeHasChild1)
{
	auto node = new XMLNode("root");
	
	ASSERT_FALSE(node->hasNext());

	delete node;
}



TEST(TestNode, TestNodeAddChild1)
{
	auto node = new XMLNode("root");
	auto child = node->addChild("child");
	auto child1 = node->addChild("child1");

	ASSERT_EQ("child", child->getName());
	ASSERT_EQ("child1", child1->getName());

	delete child1;
	delete child;
	delete node;
}

TEST(TestNode, TestNodeGetNext)
{
	auto node = new XMLNode("root");

	ASSERT_EQ(NULL, node->getNext());

	delete node;
}

TEST(TestNode, TestNodeGetNext1)
{
	auto node = new XMLNode("root");
	auto child = node->addChild("child");
	auto child1 = node->addChild("child1");

	ASSERT_TRUE(child->getNext() == child1);
	ASSERT_EQ(NULL, child1->getNext());

	delete child1;
	delete child;
	delete node;
}

TEST(TestNode, TestNodeGet)
{
	auto node = new XMLNode("root");
	auto child = node->addChild("child");
	auto child1 = node->addChild("child1");

	ASSERT_TRUE(node->get("child") == child);
	ASSERT_TRUE(node->get("child1") == child1);

	delete child1;
	delete child;
	delete node;
}

TEST(TestNode, TestNodeGetFalse)
{
	auto node = new XMLNode("root");
	auto child = node->addChild("child");

	ASSERT_FALSE(node->get("root") == child);
	ASSERT_TRUE(node->get("child1") == NULL);

	delete child;
	delete node;
}

TEST(TestNode, TestNodeGetData)
{
	std::string magic = "magic_tree";

	auto node = new XMLNode("root", magic);

	ASSERT_EQ(node->getData()->compare(magic), 0);

	delete node;
}


TEST(TestNode, TestNodeField)
{
	auto node = new XMLNode("root");
	auto intervals = node->addChild("intervals");

	auto interval0 = intervals->addChild("interval");
	auto interval1 = intervals->addChild("interval");

	auto low0 = interval0->addChild("low", "10");
	auto high0 = interval0->addChild("high", "100");

	auto low1 = interval1->addChild("low", "20");
	auto high1 = interval1->addChild("high", "200");


	auto ten = node->get("intervals")->get("interval")->get("low")->getData();
	ASSERT_EQ(*ten, "10");

	delete low1;
	delete high1;

	delete low0;
	delete high0;

	delete interval0;
	delete interval1;

	delete intervals;
	delete node;
}

