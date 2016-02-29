// color.h

#ifndef _COLOR_H_
#define _COLOR_H_

#include "../../platform_engine.h"

class color4
{

public:

	float r, g, b, a;

	PLATFORMENGINE_API color4 operator *(float value);
	PLATFORMENGINE_API color4 operator *(color4 c);
	PLATFORMENGINE_API color4 operator +=(color4 c);
	PLATFORMENGINE_API color4 operator -=(color4 c);
	PLATFORMENGINE_API color4 operator -=(float value);
	PLATFORMENGINE_API color4 operator =(int colorRGBA);
};

PLATFORMENGINE_API color4 Color(int colorRGBA);
PLATFORMENGINE_API color4 Color(BYTE r, BYTE g, BYTE b, BYTE a);

#endif //_COLOR_H_