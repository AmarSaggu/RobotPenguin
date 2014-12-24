#include "Timer.hpp"

std::chrono::steady_clock::time_point Timer::GetTime()
{
	return std::chrono::steady_clock::now();
}
