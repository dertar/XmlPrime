#include "pch.h"
#include "../XmlPrime/XMLDocument.h"


TEST(TestXMLDocument, TestXMLDocCreation) {
	auto xml = new XMLDocument();
	delete xml;
}

TEST(TestXMLDocument, TestXMLDocAddChild) {
	auto xml = new XMLDocument();
	auto interval = xml->root()->addChild("interval");

	ASSERT_EQ(interval->getKey(), "interval");

	delete xml;
}

TEST(TestXMLDocument, TestXMLDocAddChildExeption) {
	auto xml = new XMLDocument();
	ASSERT_ANY_THROW(xml->root()->addChild(""));
	delete xml;
}

TEST(TestXMLDocument, TestXMLDocClear1)
{
	auto xml = new XMLDocument();

	ASSERT_EQ(xml->clear(), 1);

	delete xml;
}


TEST(TestXMLDocument, TestXMLDocClear2)
{
	auto xml = new XMLDocument();
	auto child = xml->root()->addChild("child");
	auto child1 = xml->root()->addChild("child1");

	ASSERT_EQ(xml->clear(), 3);
	
	delete xml;
}


TEST(TestXMLDocument, TestXMLDocDispose)
{
	auto xml = new XMLDocument();
	auto child = xml->root()->addChild("child");
	auto child1 = xml->root()->addChild("child1");

	ASSERT_NO_FATAL_FAILURE( delete xml );
}

TEST(TestXMLDocument, TestXMLDocGet)
{
	auto xml = new XMLDocument();
	auto child = xml->root()->addChild("child");
	auto child1 = xml->root()->addChild("child1");

	ASSERT_TRUE(xml->root()->findFirstChild("child") == child);
	ASSERT_TRUE(xml->root()->findFirstChild("child1") == child1);

	delete xml;
}

