#include "pch.h"

#include "../XmlPrime/IOFile.h"

TEST(TestIOFile, TestIOFileRead) {
	auto xml = IOFile::read("../GTests//XMLFiles//xml01.xml");

	ASSERT_EQ(xml, "<root></root>");
}

TEST(TestIOFile, TestIOFileRead1) {
	auto xml = IOFile::read("../GTests//XMLFiles//xml02.xml");

	ASSERT_EQ(xml, "<root>\n\t<A>\n\t</A>\n</root>");
}

TEST(TestIOFile, TestIOFileReadErrorName) {
	ASSERT_ANY_THROW(IOFile::read("error"));
}
