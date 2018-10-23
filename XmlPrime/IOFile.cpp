#include "pch.h"
#include "IOFile.h"
#include "Exception.h"

std::string IOFile::read(const std::string & file)
{
	std::ifstream readStream;
	readStream.open(file);
	
	if (!readStream.is_open()) 
	{
		throw Exception("IOFile error read file", __LINE__, __FILE__, __FUNCTION__);
	}
	
	std::stringstream buffer;
	buffer << readStream.rdbuf();

	if (readStream.bad())
	{
		readStream.close();
		throw Exception("IOFile error bad bit", __LINE__, __FILE__, __FUNCTION__);
	}

	readStream.close();
	return buffer.str();
}

void IOFile::write(const std::string &fileName, const std::string &data)
{
	std::ofstream out;
	out.open(fileName);

	if (!out.is_open())
	{
		throw Exception("IOFile error open file to write", __LINE__, __FILE__, __FUNCTION__);
	}

	out << data;
	out.flush();

	if (out.bad())
	{
		out.close();
		throw Exception("IOFile error bad bit", __LINE__, __FILE__, __FUNCTION__);
	}

	out.close();
}