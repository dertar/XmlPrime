#include "pch.h"
#include "../XmlPrime/XMLNode.h"
#include "../XmlPrime/XMLNodeFactory.h"


TEST(TestNodeFactory, TestNodeFactoryTest)
{
	auto factory = XMLNodeFactory::getInstance();

	auto node = new XMLNode<std::string>("root");
	auto child = node->addChild(new XMLNode<std::string>("child", "data"));


	delete child;
	delete node;
}

TEST(TestNodeFactory, TestNodeField)
{
	auto factory = XMLNodeFactory::getInstance();

	auto node = new XMLNode<std::string>("root");
	auto child = node->addChild(new XMLNode<std::string>("child", "data"));

	//factory->f<int>(child);

	delete child;
	delete node;
}

TEST(TestNodeFactory, TestNodeFactoryHasString)
{
	auto factory = XMLNodeFactory::getInstance();

	auto node = new XMLNode<std::string>("root");
	auto child = node->addChild(new XMLNode<std::string>("child", "data"));

	ASSERT_TRUE(factory->hasData<std::string>(child));

	delete child;
	delete node;
}

TEST(TestNodeFactory, TestNodeFactoryHasDataInt)
{
	auto factory = XMLNodeFactory::getInstance();
	auto node = new XMLNode<int>("root");
	auto child = node->addChild(new XMLNode<int>("child", 1));

	ASSERT_TRUE(factory->hasData<int>(child));

	delete child;
	delete node;
}

TEST(TestNodeFactory, TestNodeFactoryHasDataMissType)
{
	auto factory = XMLNodeFactory::getInstance();
	auto node = new XMLNode<int>("root");
	auto child = node->addChild(new XMLNode<int>("child", 1));

	ASSERT_ANY_THROW(factory->getData<std::string>(child));

	delete child;
	delete node;
}

TEST(TestNodeFactory, TestNodeFactory)
{
	auto factory = XMLNodeFactory::getInstance();

	auto node = new Node("root");
	auto child1 = node->addChild(factory->createNode<int>("child1"));
	auto child2 = node->addChild(factory->createNode<std::string>("child2"));
	
	factory->setValue<int>(child1, 10);
	factory->setValue<std::string>(child2, "ten");

	ASSERT_EQ("child1", child1->getKey());
	ASSERT_EQ("child2", child2->getKey());

	ASSERT_EQ(factory->getData<int>(child1), 10);
	ASSERT_EQ(factory->getData<std::string>(child2), "ten");

	delete child2;
	delete child1;
	delete node;
}


TEST(TestNodeFactory, TestNodeFactoryField)
{
	auto factory = XMLNodeFactory::getInstance();

	auto node = new XMLNode<std::string>("root");
	auto intervals = node->addChild("intervals");

	auto interval0 = intervals->addChild("interval");
	auto interval1 = intervals->addChild("interval");

	auto low0 = interval0->addChild(factory->createNode<std::string>("low", "10"));
	auto high0 = interval0->addChild(factory->createNode<std::string>("high", "100"));

	auto low1 = interval1->addChild(factory->createNode<std::string>("low", "20"));
	auto high1 = interval1->addChild(factory->createNode<std::string>("high", "200"));


	auto first = node->findFirstChild("intervals")->findFirstChild("interval")->findFirstChild("low");
	ASSERT_EQ(factory->getData<std::string>(first), "10");

	auto second = node->findFirstChild("intervals")->findFirstChild("interval")->findFirstChild("low")->getNext();
	ASSERT_EQ(factory->getData<std::string>(second), "100");

	auto third = node->findFirstChild("intervals")->findFirstChild("interval")->getNext()->findFirstChild("low");
	ASSERT_EQ(factory->getData<std::string>(third), "20");

	auto fourth = node->findFirstChild("intervals")->findFirstChild("interval")->getNext()->findFirstChild("high");
	ASSERT_EQ(factory->getData<std::string>(fourth), "200");

	delete low1;
	delete high1;

	delete low0;
	delete high0;

	delete interval0;
	delete interval1;

	delete intervals;
	delete node;
}

TEST(TestNode, TestNodeField1)
{
	auto factory = XMLNodeFactory::getInstance();

	auto node = new XMLNode<int>("root");
	auto intervals = node->addChild("intervals");

	auto interval0 = intervals->addChild("interval");
	auto interval1 = intervals->addChild("interval");

	auto low0 = interval0->addChild(factory->createNode<int>("low", 10));
	auto high0 = interval0->addChild(factory->createNode<int>("high", 100));

	auto low1 = interval1->addChild(factory->createNode<int>("low", 20));
	auto high1 = interval1->addChild(factory->createNode<int>("high", 200));



	auto ten = node->findFirstChild("intervals")->findFirstChild("interval")->findFirstChild("low");
	ASSERT_EQ(factory->getData<int>(ten), 10);

	auto oneT = node->findFirstChild("intervals")->findFirstChild("interval")->findFirstChild("high");
	ASSERT_EQ(factory->getData<int>(oneT), 100);



	delete low1;
	delete high1;

	delete low0;
	delete high0;

	delete interval0;
	delete interval1;

	delete intervals;
	delete node;
}

TEST(TestNodeFactory, TestNodeDocument)
{
	auto factory = XMLNodeFactory::getInstance();

	//auto node = factory->createSNode<int>("root");

	//auto child = factory->createSNode<int>("child");

	//node->addChild(child.get);
	
}