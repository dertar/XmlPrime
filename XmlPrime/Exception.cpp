#include "pch.h"
#include "Exception.h"


Exception::Exception(const std::string & message, unsigned int line, const std::string & fileName, const std::string & funcName)
	: msg(message), line(line), fileName(fileName), funcName(funcName)
{

}

unsigned int Exception::getLine()
{
	return this->line;
}

const std::string & Exception::getFileName()
{
	return this->fileName;
}

const std::string & Exception::getFuncName()
{
	return this->funcName;
}

Exception::Exception()
{
}

Exception::~Exception()
{
}
