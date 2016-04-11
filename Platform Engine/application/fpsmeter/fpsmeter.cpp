// fpsmeter.cpp

#include "fpsmeter.h"

namespace PlatformEngine
{
	CFPSMeter::CFPSMeter()
	{
		time = 0.0;
		fpsCurrent = 0;
	}

	void CFPSMeter::Tick(double dTime)
	{
		tick++;
		time += dTime;

		#ifdef FPSMETER_AUTOCHECK
			Check();
		#endif
	}

	void CFPSMeter::Check()
	{
		if(time >= 1)
		{
			fpsCurrent = tick;

			time = 0.0;
			tick = 0;
		}
	}

	int CFPSMeter::GetFPS()
	{
		return fpsCurrent;
	}
};