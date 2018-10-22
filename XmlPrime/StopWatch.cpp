#include "pch.h"
#include "StopWatch.h"


void StopWatch::start()
{
	this->startPoint = Clock::now();
}

long long StopWatch::stop()
{
	auto endPoint = Clock::now();
	this->lastDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - startPoint).count();
	return get();
}

long long StopWatch::get() const noexcept
{
	return this->lastDuration;
}

StopWatch::StopWatch()
{
}


StopWatch::~StopWatch()
{
}
