#include "pch.h"
#include "../XmlPrime/IOFile.h"
#include "../XmlPrime/XMLPrime.h"
#include "../XmlPrime/StopWatch.h"

TEST(TestComplex, TestComplex1)
{
	auto rawXml = IOFile::read("../GTests//XMLFiles//xml00.xml");
	
	XMLPrime prime;

	auto outXml = prime.get(rawXml);

	IOFile::write("../GTests//XMLFiles//out_xml00.xml", outXml);

}

TEST(TestComplex, TestComplex2)
{
	auto rawXml = IOFile::read("../GTests//XMLFiles//xml03.xml");

	XMLPrime prime;

	auto outXml = prime.get(rawXml);

	IOFile::write("../GTests//XMLFiles//out_xml03.xml", outXml);

	auto correctPrimes = IOFile::read("../GTests//XMLFiles//out_correct_xml03.xml");

	ASSERT_EQ(correctPrimes.compare(outXml),0 );
}

TEST(TestComplex, TestComplex3)
{
	auto rawXml = IOFile::read("../GTests//XMLFiles//xml04.xml");

	XMLPrime prime;

	auto outXml = prime.get(rawXml);

	IOFile::write("../GTests//XMLFiles//out_xml04.xml", outXml);

	auto correctPrimes = IOFile::read("../GTests//XMLFiles//out_correct_xml04.xml");

	ASSERT_EQ(correctPrimes.compare(outXml), 0);
}

TEST(TestXMLPrime, TestXMLPrimeMaxDataInteger)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval><low>0</low><high>4294967296</high></interval></interval></root>";

	ASSERT_ANY_THROW(prime.get(xml));
}

TEST(TestXMLPrime, TestXMLPrimeIncorrectXML)
{
	XMLPrime prime;
	std::string xml = "<root><max>4294967296</max></root>";

	ASSERT_ANY_THROW(prime.get(xml));
}

TEST(TestXMLPrime, TestXMLPrimeIncorrectXML1)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval><high>100</high></interval></interval></root>";

	ASSERT_ANY_THROW(prime.get(xml));

}

TEST(TestXMLPrime, TestXMLPrimeIncorrectXML5)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval><low></low><high>100</high></interval></interval></root>";

	ASSERT_ANY_THROW(prime.get(xml));
}

TEST(TestXMLPrime, TestXMLPrimeIncorrectXML6)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval><low>0</low><high>100</high><low>33</low></interval></interval></root>";

	ASSERT_ANY_THROW(prime.get(xml));
}

TEST(TestXMLPrime, TestXMLPrimeIncorrectXML2)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval></interval></interval></root>";

	ASSERT_ANY_THROW(prime.get(xml));
}

TEST(TestXMLPrime, TestXMLPrimeIncorrectXML3)
{
	XMLPrime prime;
	std::string xml = "<root><intervals></interval></root>";

	ASSERT_ANY_THROW(prime.get(xml));
}

TEST(TestXMLPrime, TestXMLPrimeIncorrectXML4)
{
	XMLPrime prime;
	std::string xml = "<root><intervals></interval></root>";

	ASSERT_ANY_THROW(prime.get(xml));
}

TEST(TestXMLPrime, TestXMLPrimeMaxDataNegative)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval><low>-10</low><high>100</high></interval></interval></root>";

	ASSERT_ANY_THROW(prime.get(xml));
}

TEST(TestXMLPrime, TestXMLPrimeMaxDataViceVersa)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval><low>100</low><high>0</high></interval></intervals></root>";

	ASSERT_ANY_THROW(prime.get(xml));
}

TEST(TestXMLPrime, TestXMLPrimeMaxDataDuplicate)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval><low>0</low><high>10</high></interval><interval><low>0</low><high>10</high></interval></intervals></root>";
	auto x = prime.get(xml, true, false);
	
	auto correctPrimes = IOFile::read("../GTests//XMLFiles//out_correct_duplicate.xml");

	ASSERT_EQ(correctPrimes.compare(x), 0);
}

TEST(TestXMLPrime, TestXMLPrimeMaxDataRemoveDuplicate)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval><low>0</low><high>10</high></interval><interval><low>0</low><high>10</high></interval></intervals></root>";
	auto x = prime.get(xml);

	auto correctPrimes = IOFile::read("../GTests//XMLFiles//out_correct_rduplicate.xml");

	ASSERT_EQ(correctPrimes.compare(x), 0);
}

TEST(TestXMLPrime, TestXMLPrimeMaxDataRemoveDuplicate1)
{
	XMLPrime prime;
	std::string xml = "<root><intervals><interval><low>0</low><high>10</high></interval><interval><low>0</low><high>10</high></interval></intervals></root>";
	auto x = prime.get(xml, false, true);

	auto correctPrimes = IOFile::read("../GTests//XMLFiles//out_correct_rduplicate.xml");

	ASSERT_EQ(correctPrimes.compare(x), 0);
}

TEST(TestSpeed, TestSpeedOneVsTwo)
{
	auto rawXml = IOFile::read("../GTests//XMLFiles//xml03.xml");

	XMLPrime one(1);
	XMLPrime multi(2);
	auto timer = StopWatch();
	
	timer.start();
	auto outXml = one.get(rawXml);
	auto oneTime = timer.stop();

	timer.start();
	auto outXml1 = multi.get(rawXml);
	auto twoTime = timer.stop();
	
	ASSERT_GT(oneTime, twoTime);
}

TEST(TestSpeed, TestSpeedOneVsFour)
{
	auto rawXml = IOFile::read("../GTests//XMLFiles//xml03.xml");

	XMLPrime one(1);
	XMLPrime multi(4);
	auto timer = StopWatch();

	timer.start();
	auto outXml = one.get(rawXml);
	auto oneTime = timer.stop();

	timer.start();
	auto outXml1 = multi.get(rawXml);
	auto twoTime = timer.stop();

	ASSERT_GT(oneTime, twoTime);
	timer.start();
}

TEST(TestSpeed, TestSpeedTwo)
{
	auto rawXml = IOFile::read("../GTests//XMLFiles//xml03.xml");

	XMLPrime multi(2);

	auto outXml1 = multi.get(rawXml);
}

TEST(TestSpeed, TestSpeedFour)
{
	auto rawXml = IOFile::read("../GTests//XMLFiles//xml03.xml");

	XMLPrime multi(2);

	auto outXml1 = multi.get(rawXml);
}