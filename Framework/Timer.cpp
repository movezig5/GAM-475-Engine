//----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
//----------------------------------------------------------------------------
// Timer 
//    v.2.1.0
//    v.2.5
//    v.2.6   - Baseline
//    v.2.6.1 - fixed warning TestRegistry
//    v.2.7   - Baseline
//    v.2.8   - warning 5039 windows.h
//    v.2.9   - fence
//    v.2.10  - msc_ver 1914, win 10.0.17
//    v.2.11  - warning fixes 
//    v.2.12  - mutex on all trace::out
//    v.2.13  - fixed warnings on mutex and default copy const / assignment
//    v.2.14  - FileIO remove new... so you can overload new/delete
//    v.2.15  - number tests pass reformat
//    v.2.16  - fixing static analysis issues
//    v.2.17  - missing deleted copy constructor and assignment operator in macro
//    v.2.18  - teardown issue
//---------------------------------------------------------------------------- 

#include <assert.h>
#include <stdio.h>

// locals
#include "Timer.h"

Timer::Timer() noexcept
	:
	ticTime(),
	tocTime(),
	deltaTime(),
	SecondsPerCycle(0.0f),
	timeSeconds(0.0f)
{
	this->privInitTimer();
	this->Reset();
}

void Timer::privInitTimer() noexcept
{
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	this->SecondsPerCycle = 1.0f / Frequency.QuadPart;
}

LARGE_INTEGER Timer::privGetTimer() noexcept
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time;
}

void Timer::Tic() noexcept
{
	// Forces a Fence... 
	printf("tic()\n");

	this->ticTime = this->privGetTimer();
}

void Timer::Toc() noexcept
{
	this->tocTime = this->privGetTimer();
	assert( this->tocTime.QuadPart >= this->ticTime.QuadPart );
	this->deltaTime.QuadPart = this->tocTime.QuadPart - this->ticTime.QuadPart;

	// Forces a Fence... 
	printf("toc()\n");
}

void Timer::Reset() noexcept
{
	this->ticTime.QuadPart = 0;
	this->tocTime.QuadPart = 0;
	this->deltaTime.QuadPart = 0;
}

float Timer::TimeInSeconds() noexcept 
{
	float floatTime;
	floatTime = static_cast<float>(this->deltaTime.QuadPart);
	floatTime *= this->SecondsPerCycle;
	return floatTime;
}

// ---  End of File ---------------
