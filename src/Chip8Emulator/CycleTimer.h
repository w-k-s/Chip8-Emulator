#pragma once

#include <chrono>

class CycleTimer{
private:
	unsigned int _hertz;
	std::chrono::time_point<std::chrono::system_clock> _startTime;

public:
	CycleTimer(unsigned int hertz) : _hertz{hertz}, _startTime{std::chrono::system_clock::now()}{};
	CycleTimer(const CycleTimer&)		= delete;
   	void operator=(const CycleTimer&)	= delete;

	void maintainCycleRate() const;
};