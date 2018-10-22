#pragma once
#include <chrono>

class StopWatch
{
using Clock = std::chrono::high_resolution_clock;
using ClockPoint = Clock::time_point;

public:
	void start();
	long long stop();
	long long get() const noexcept;

	StopWatch();
	~StopWatch();
private:
	ClockPoint startPoint;
	long long lastDuration;
};

