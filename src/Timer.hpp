#pragma once

#include <chrono>

#include <cstdint>

class Timer {
	uint64_t startTime, stopTime;
	uint64_t frequency;
	
	bool isRunning;
	
public:
	Timer();
	~Timer();
	
	void Start();
	void Stop();	
	void Reset();

	bool IsRunning() const;
	
	double GetElapsedTime();
};
