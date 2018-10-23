#pragma once
#include <exception>

class Exception :
	std::exception
{
public:

	explicit Exception(const std::string& message, unsigned int line, const std::string &fileName, const std::string &funcName);

	virtual const char* what() const throw () {
		return msg.c_str();
	}

	unsigned int getLine();
	const std::string& getFileName();
	const std::string& getFuncName();

	Exception();
	virtual ~Exception();

protected:
	std::string msg;
	unsigned int line;
	std::string fileName;
	std::string funcName;
};
