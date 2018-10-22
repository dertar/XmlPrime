#include "pch.h"

#include "../XmlPrime/XMLNode.h"
#include "../XmlPrime/XMLConvertor.h"

TEST(TestXMLConverter, TestXMLConverterInit) {
	auto f1 = XMLConvertor::getIntance();
	auto f2 = XMLConvertor::getIntance();

	ASSERT_TRUE(f1 == f2);
}

TEST(TestXMLConverter, TestXMLConverterToPlain) {
	auto convertor = XMLConvertor::getIntance();
	auto node = new XMLNode("root");

	auto plain = convertor->toPlain(node, "", "");

	std::string answer = "<root></root>";

	ASSERT_EQ(answer, *plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlainStyle) {
	auto convertor = XMLConvertor::getIntance();
	auto node = new XMLNode("root");

	auto plain = convertor->toPlain(node);

	std::string answer = "<root>\n</root>\n";

	ASSERT_EQ(answer, *plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlain1) {
	auto convertor = XMLConvertor::getIntance();
	auto node = new XMLDocument();
	node->root()->addChild("intervals");

	auto plain = convertor->toPlain(node, "", "");

	std::string answer = "<root><intervals></intervals></root>";

	ASSERT_EQ(answer, *plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlainStyle1) {
	auto convertor = XMLConvertor::getIntance();
	auto node = new XMLDocument();
	node->root()->addChild("intervals");

	auto plain = convertor->toPlain(node);

	std::string answer = "<root>\n\t<intervals>\n\t</intervals>\n</root>\n";

	ASSERT_EQ(answer, *plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlain2) {
	auto convertor = XMLConvertor::getIntance();
	auto node = new XMLDocument();
	node->root()->addChild("ten", "10");

	auto plain = convertor->toPlain(node, "", "");

	std::string answer = "<root><ten>10</ten></root>";

	ASSERT_EQ(answer, *plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlainStyle2) {
	auto convertor = XMLConvertor::getIntance();
	auto node = new XMLDocument();
	node->root()->addChild("ten", "10");

	auto plain = convertor->toPlain(node);

	std::string answer = "<root>\n\t<ten>\n\t\t10\n\t</ten>\n</root>\n";

	ASSERT_EQ(answer, *plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlain3) {
	auto convertor = XMLConvertor::getIntance();
	auto node = new XMLDocument();
	auto intervals = node->root()->addChild("intervals");
	auto interval = intervals->addChild("interval");
	interval->addChild("low", "10");
	interval->addChild("high", "100");

	auto plain = convertor->toPlain(node, "", "");

	std::string answer = "<root><intervals><interval><low>10</low><high>100</high></interval></intervals></root>";

	ASSERT_EQ(answer, *plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToPlain4) {
	auto convertor = XMLConvertor::getIntance();
	auto node = new XMLDocument();
	auto intervals = node->root()->addChild("intervals");
	auto interval = intervals->addChild("interval");
	interval->addChild("low", "10");
	interval->addChild("high", "100");

	auto interval1 = intervals->addChild("interval");
	interval1->addChild("low", "20");
	interval1->addChild("high", "200");


	auto plain = convertor->toPlain(node, "", "");

	std::string answer = "<root><intervals><interval><low>10</low><high>100</high></interval><interval><low>20</low><high>200</high></interval></intervals></root>";

	ASSERT_EQ(answer, *plain);

	delete node;
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root><root>";

	ASSERT_ANY_THROW(convertor->toXML(text));
}


TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt1) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "</root>";

	ASSERT_ANY_THROW(convertor->toXML(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt2) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<rootA></rootB>";

	ASSERT_ANY_THROW(convertor->toXML(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt3) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root><</root>";

	ASSERT_ANY_THROW(convertor->toXML(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrupt4) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root>></root>";

	ASSERT_ANY_THROW(convertor->toXML(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrect) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root></root>";

	ASSERT_NO_THROW(convertor->toXML(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrect1) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root><low></low</root>";

	ASSERT_NO_THROW(convertor->toXML(text));
}

TEST(TestXMLConverter, TestXMLConverterToXMLCorrect2) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root><low>100</low</root>";

	ASSERT_NO_THROW(convertor->toXML(text));
}


TEST(TestXMLConverter, TestXMLConverterToXML) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root></root>";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml, "", "");

	ASSERT_EQ(text, *atext);

	delete xml;
}

TEST(TestXMLConverter, TestXMLConverterToXML2) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root><low></low></root>";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml, "", "");

	ASSERT_EQ(text, *atext);

	delete xml;
}

TEST(TestXMLConverter, TestXMLConverterToXML3) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root><low>10</low></root>";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml, "", "");

	ASSERT_EQ(text, *atext);

	delete xml;
}

TEST(TestXMLConverter, TestXMLConverterToXML4) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root><low>10</low><high>20</high></root>";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml, "", "");

	ASSERT_EQ(text, *atext);

	delete xml;
}


TEST(TestXMLConverter, TestXMLConverterRootValue) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root>100</root>";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml, "", "");

	ASSERT_EQ(text, *atext);

	delete xml;
}



TEST(TestXMLConverter, TestXMLConverterToXML5) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root><intervals><interval><low>10</low><high>100</high></interval><interval><low>20</low><high>200</high></interval></intervals></root>";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml, "", "");

	ASSERT_EQ(text, *atext);

	delete xml;
}

TEST(TestXMLConverter, TestXMLConverterToXML6) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root><interval><low>10</low><high>100</high></interval><interval><low>20</low><high>200</high></interval></root>";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml, "", "");

	ASSERT_EQ(text, *atext);

	delete xml;
}

TEST(TestXMLConverter, TestXMLConverterToXMLStyle) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "  <root>\n  </root >\n";
	std::string answer = "<root>\n</root>\n";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml);

	ASSERT_EQ(answer, *atext);

	delete xml;
	delete atext;
}

TEST(TestXMLConverter, TestXMLConverterToXMLStyle2) {
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<  root  >  <intervals>\t\n  </intervals>  </root>";
	std::string answer = "<root><intervals></intervals></root>";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml, "", "");

	ASSERT_EQ(answer, *atext);

	delete xml;
	delete atext;
}

TEST(TestXMLConverter, TestXMLConverterToXMLStyle3) {
	
	auto convertor = XMLConvertor::getIntance();

	std::string text = "<root>\n\t<intervals>\n\t</intervals>\n</root>\n";
	std::string answer = "<root><intervals></intervals></root>";

	auto xml = convertor->toXML(text);

	auto atext = convertor->toPlain(xml, "", "");

	ASSERT_EQ(answer, *atext);

	delete xml;
	delete atext;
}
