#pragma once
#include <string>
#include "Exception.h"

// class that helps to convert data types
// more complex converters handed down in another .h files


// by reference from
template <typename F, typename T>
class Converter
{
public:
	Converter() {};
	virtual ~Converter() {};

	virtual T convert(F &from)
	{
		throw Exception("not implemented", __LINE__, __FILE__, __FUNCTION__);
	}

	// if we need extra args
	template<class... Args>
	T convert(F &from, Args&&... args)
	{
		throw Exception("not implemented", __LINE__, __FILE__, __FUNCTION__);
	}
};

// by pointer from
template <typename F, typename T>
class Converter<F*, T>
{
public:
	Converter() {};
	virtual ~Converter() {};

	virtual T convert(F *from)
	{
		throw Exception("not implemented", __LINE__, __FILE__, __FUNCTION__);
	}

	template<class... Args>
	T convert(F *from, Args&&... args)
	{
		throw Exception("not implemented", __LINE__, __FILE__, __FUNCTION__);
	}
};

template<>
class Converter<unsigned int, std::string>
{
public:
	std::string convert(const unsigned int &from)
	{
		return std::to_string(from);
	}
};

template<>
class Converter<std::string, unsigned int>
{
public:
	unsigned int convert(const std::string &from)
	{
		return std::stoul(from, nullptr, 0);
	}
};