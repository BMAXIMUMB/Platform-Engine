// timer.cpp

#include "timer.h"

namespace PlatformEngine
{
	CTimer::CTimer(TimerType timerType)
	{
		this->timerType = timerType;

		started = false;
	}

	double CTimer::Start()
	{
		startTime = (double)timeGetTime();
		started = true;

		return startTime;
	}

	double CTimer::Stop()
	{
		stopTime = (double)timeGetTime();
		elapsedTime = stopTime - startTime;
		if(timerType = TIMER_TYPE_SECOND)
		{
			elapsedTime /= 1000;
		}

		started = false;

		return stopTime;
	}

	void CTimer::Reset()
	{
		startTime = 0.0;
		stopTime = 0.0;
		elapsedTime = 0.0;

		if(started)
		{
			startTime = (double)timeGetTime();
		}
	}

	double CTimer::GetElapsed()
	{
		if(started)
		{
			stopTime = (double)timeGetTime();

			double tempElapsed = stopTime - startTime;

			#ifdef TIMER_AUTORESET
				startTime = stopTime;
			#endif
			
			if(timerType == TIMER_TYPE_SECOND)
			{
				tempElapsed = tempElapsed/ 1000;
			}

			return tempElapsed;
		}
		else
		{
			return elapsedTime;
		}

		return 0;
	}

	bool CTimer::IsStarted()
	{
		return started;
	}
};