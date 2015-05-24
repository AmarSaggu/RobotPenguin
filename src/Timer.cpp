#include "Timer.hpp"

#include <SDL2/SDL.h>

static uint64_t GetTicks()
{
	return SDL_GetPerformanceCounter();
}

Timer::Timer()
{
	frequency = SDL_GetPerformanceFrequency();
	Reset();
}

Timer::~Timer()
{}

void Timer::Start()
{
	startTime = GetTicks();
	isRunning = true;
}

void Timer::Stop()
{
	stopTime = GetTicks();
	isRunning = false;
}

void Timer::Reset()
{
	// The current elapsed time is 0
	startTime = GetTicks();
	stopTime = startTime;
	
	isRunning = false;
}

bool Timer::IsRunning() const
{
	return isRunning;
}

double Timer::GetElapsedTime()
{
	if (isRunning) {
		stopTime = GetTicks();
	}
	
	return (stopTime - startTime) / (double) frequency;
}
