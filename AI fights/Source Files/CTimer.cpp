#include "stdafx.h"

#include "CTimer.h"

CTimer::CTimer()
{
	m_startTicks = 0;
	m_pausedTicks = 0;

	isPaused = false;
	isStarted = false;
}


void CTimer::start()
{
	isStarted = true;
	isPaused = false;

	// get current clock time
	m_startTicks = SDL_GetTicks();
}


void CTimer::stop()
{
	isStarted = false;
	isPaused = false;
}


void CTimer::pause()
{
	if ((isStarted == true) && (isPaused == false))
	{
		isPaused = true;
		m_pausedTicks = SDL_GetTicks() - m_startTicks;
	}
}


void CTimer::unpause()
{
	if (isPaused == true)
	{
		isPaused = false;
		m_startTicks = SDL_GetTicks() - m_pausedTicks;
		m_pausedTicks = 0;
	}
}


Uint32 CTimer::getTime()
{
	if (isStarted == true)
	{
		if (isPaused == true)
		{
			return (Uint32)m_pausedTicks;
		}
		else
		{
			return (Uint32)(SDL_GetTicks() - m_startTicks);
		}
	}

	return (Uint32)0;
}


bool CTimer::getIsStarted()
{
	return isStarted;
}


bool CTimer::getIsPaused()
{
	return isPaused;
}