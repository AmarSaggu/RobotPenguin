#pragma once

#include <chrono>

class Timer {
public:
	static std::chrono::steady_clock::time_point GetTime();
};
