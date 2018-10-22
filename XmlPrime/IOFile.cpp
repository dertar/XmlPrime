#include "pch.h"
#include "IOFile.h"


std::string IOFile::read(const std::string & file)
{
	std::ifstream readStream;
	readStream.open(file);
	
	if (!readStream.is_open()) 
	{
		throw std::exception("IOFile error read file");
	}
	
	std::stringstream buffer;
	buffer << readStream.rdbuf();

	if (readStream.bad())
	{
		readStream.close();
		throw std::exception("IOFile error bad bit");
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
		throw std::exception("IOFile error open file to write");
	}

	out << data;
	out.flush();

	if (out.bad())
	{
		out.close();
		throw std::exception("IOFile error bad bit");
	}

	out.close();
}