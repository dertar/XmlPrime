#include "pch.h"

#include "../XmlPrime/XMLNode.h"
#include "../XmlPrime/XMLDocument.h"
#include "../XmlPrime/ConverterPlainToXML.h"
#include "../XmlPrime/ConverterXMLToPlain.h"

TEST(TestXMLConverter, TestXMLConverterToPlain) {
	Converter<Node*, std::string> toPlain;
	auto node = new XMLNode<std::string>("root");
	
	auto plain = toPlain.convert(node);

	std::string answer = "<root></root>";

	ASSERT_EQ(answer, plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlainStyle) {
	Converter<Node*, std::string> toPlain;
	auto node = new XMLNode<std::string>("root");

	auto plain = toPlain.convert(node, "\n" , "");

	std::string answer = "<root>\n</root>\n";

	ASSERT_EQ(answer, plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlain1) {
	Converter<Node*, std::string> toPlain;
	auto node = new XMLDocument();
	node->root()->addChild("intervals");

	auto plain = toPlain.convert(node->root(), "", "");

	std::string answer = "<root><intervals></intervals></root>";

	ASSERT_EQ(answer, plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlainStyle1) {
	Converter<Node*, std::string> toPlain;
	auto node = new XMLDocument();
	node->root()->addChild("intervals");

	auto plain = toPlain.convert(node->root(), "\n", "\t");

	std::string answer = "<root>\n\t<intervals>\n\t</intervals>\n</root>\n";

	ASSERT_EQ(answer, plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlain2) {
	auto factory = XMLNodeFactory::getInstance();
	Converter<Node*, std::string> toPlain;
	auto node = new XMLDocument();
	
	node->root()->addChild(factory->createNode<std::string>("ten", "10"));

	auto plain = toPlain.convert(node->root(), "", "");

	std::string answer = "<root><ten>10</ten></root>";

	ASSERT_EQ(answer, plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlainStyle2) {
	auto factory = XMLNodeFactory::getInstance();
	Converter<Node*, std::string> toPlain;

	auto node = new XMLDocument();

	node->root()->addChild(factory->createNode<unsigned int>("ten", 10));

	auto plain = toPlain.convert(node->root(), "\n", "\t");

	std::string answer = "<root>\n\t<ten>\n\t\t10\n\t</ten>\n</root>\n";

	ASSERT_EQ(answer, plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlain3) {
	auto factory = XMLNodeFactory::getInstance();
	Converter<Node*, std::string> toPlain;

	auto node = new XMLDocument();
	auto intervals = node->root()->addChild("intervals");
	auto interval = intervals->addChild("interval");
	interval->addChild(factory->createNode<std::string>("low", "10"));
	interval->addChild(factory->createNode<unsigned int>("high", 100));
	
	auto plain = toPlain.convert(node->root(), "", "");

	std::string answer = "<root><intervals><interval><low>10</low><high>100</high></interval></intervals></root>";

	ASSERT_EQ(answer, plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlain4) {
	auto factory = XMLNodeFactory::getInstance();
	Converter<Node*, std::string> toPlain;

	auto node = new XMLDocument();
	auto intervals = node->root()->addChild("intervals");
	auto interval = intervals->addChild("interval");
	interval->addChild(factory->createNode<std::string>("low", "10"));
	interval->addChild(factory->createNode<unsigned int>("high", 100));

	auto interval1 = intervals->addChild("interval");
	interval1->addChild(factory->createNode<std::string>("low", "20"));
	interval1->addChild(factory->createNode<unsigned int>("high", 200));

	auto plain = toPlain.convert(node->root(), "", "");

	std::string answer = "<root><intervals><interval><low>10</low><high>100</high></interval><interval><low>20</low><high>200</high></interval></intervals></root>";

	ASSERT_EQ(answer, plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt) {
	Converter<std::string, Node*> toXML;

	std::string text = "<root><root>";

	ASSERT_ANY_THROW(toXML.convert(text));
}


TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt1) {
	Converter<std::string, Node*> toXML;

	std::string text = "</root>";
	ASSERT_ANY_THROW(toXML.convert(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt2) {
	Converter<std::string, Node*> toXML;

	std::string text = "<rootA></rootB>";
	ASSERT_ANY_THROW(toXML.convert(text));;
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt3) {
	Converter<std::string, Node*> toXML;

	std::string text = "<root><</root>";
	ASSERT_ANY_THROW(toXML.convert(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt4) {
	Converter<std::string, Node*> toXML;

	std::string text = "<root>></root>";
	ASSERT_ANY_THROW(toXML.convert(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrect) {
	Converter<std::string, Node*> toXML;

	std::string text = "<root></root>";

	ASSERT_NO_THROW(toXML.convert(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrect1) {
	Converter<std::string, Node*> toXML;

	std::string text = "<root><low></low</root>";

	ASSERT_NO_THROW(toXML.convert(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrect2) {
	Converter<std::string, Node*> toXML;

	std::string text = "<root><low>100</low</root>";

	ASSERT_NO_THROW(toXML.convert(text));
}


TEST(TestXMLConverter, TestXMLConverterToXML) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "<root></root>";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "", "");

	ASSERT_EQ(text, atext);
}

TEST(TestXMLConverter, TestXMLConverterToXML2) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "<root><low></low></root>";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "", "");

	ASSERT_EQ(text, atext);
}

TEST(TestXMLConverter, TestXMLConverterToXML3) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "<root><low>10</low></root>";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "", "");

	ASSERT_EQ(text, atext);
}

TEST(TestXMLConverter, TestXMLConverterToXML4) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "<root><low>10</low><high>20</high></root>";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "", "");

	ASSERT_EQ(text, atext);
}


TEST(TestXMLConverter, TestXMLConverterRootValue) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "<root>100</root>";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "", "");

	ASSERT_EQ(text, atext);
}



TEST(TestXMLConverter, TestXMLConverterToXML5) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "<root><intervals><interval><low>10</low><high>100</high></interval><interval><low>20</low><high>200</high></interval></intervals></root>";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "", "");

	ASSERT_EQ(text, atext);
}

TEST(TestXMLConverter, TestXMLConverterToXML6) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "<root><interval><low>10</low><high>100</high></interval><interval><low>20</low><high>200</high></interval></root>";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "", "");

	ASSERT_EQ(text, atext);
}


TEST(TestXMLConverter, TestXMLConverterToXMLStyle) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "  <root>\n  </root >\n";
	std::string answer = "<root>\n</root>\n";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "\n", "");

	ASSERT_EQ(answer, atext);
}

TEST(TestXMLConverter, TestXMLConverterToXMLStyle2) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "<  root  >  <intervals>\t\n  </intervals>  </root>";
	std::string answer = "<root><intervals></intervals></root>";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "", "");

	ASSERT_EQ(answer, atext);

}

TEST(TestXMLConverter, TestXMLConverterToXMLStyle3) {
	Converter<std::string, Node*> toXML;
	Converter<Node*, std::string> toPlain;

	std::string text = "<root>\n\t<intervals>\n\t</intervals>\n</root>\n";
	std::string answer = "<root><intervals></intervals></root>";

	auto xml = toXML.convert(text);

	auto atext = toPlain.convert(xml, "", "");

	ASSERT_EQ(answer, atext);
}
