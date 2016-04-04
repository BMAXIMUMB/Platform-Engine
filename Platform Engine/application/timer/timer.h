// timer.h

#ifndef _TIMER_H_
#define _TIMER_H_

#include <windows.h>
#include "../../logprintf.h"

#define AUTORESET

namespace PlatformEngine
{
	enum TimerType
	{
		TIMER_TYPE_SECOND,
		TIMER_TYPE_MILLISECOND
	};

	class CTimer
	{
	private:
		bool started;

		double startTime;
		double stopTime;
		double elapsedTime;

		TimerType timerType;

	public:
		CTimer(TimerType timerType);

		double Start(void);
		double Stop(void);
		void Reset(void);

		bool IsStarted(void);
		double GetElapsed(void);

	};
};

#endif //_TIMER_H_
