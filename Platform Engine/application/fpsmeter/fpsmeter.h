// fpsmeter.h

#ifndef _FPSMETER_H_
#define _FPSMETER_H_

#include "../../platform_engine.h"

namespace PlatformEngine
{
	class CFPSMeter
	{
	private:
		int fpsCurrent;
		int tick;

		double time;

	public:
		PLATFORMENGINE_API CFPSMeter();

		PLATFORMENGINE_API void Tick(double dTime);
		PLATFORMENGINE_API void Check();

		PLATFORMENGINE_API int GetFPS(void);
	};
};

#endif //_FPSMETER_H_
