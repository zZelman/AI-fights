#pragma once

#include "stdafx.h"

// converts ms to sec (produces a float)
#define ToSeconds(x) (x/1000.0f)

class CTimer
{
public:
	CTimer();

	// clock actions
	void start(); // (also serves as a re-start)
	void stop();

	void pause();
	void unpause();

	// returns the timer's value
	Uint32 getTime();

	// checks timers state
	bool getIsStarted();
	bool getIsPaused();


private:
	Uint32 m_startTicks;	// the clock time when the timer started
	Uint32 m_pausedTicks;	// the ticks stored when timer was paused

	bool isPaused;	// status of timer
	bool isStarted;	// status of timer
};