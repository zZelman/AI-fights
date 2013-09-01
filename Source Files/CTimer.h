#ifndef CTIMER_H
#define CTIMER_H


#include "stdafx.h"

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


#endif // !CTIMER_H