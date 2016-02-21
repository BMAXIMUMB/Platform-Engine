// contact.cpp

#include "contact.h"

namespace PlatformEngine
{
	CContact::CContact(contactinfo cinfo)
	{
		object1 = cinfo.object1;
		object2 = cinfo.object2;
		overlapX = cinfo.overlap_x;
		overlapY = cinfo.overlap_y;
		routPush = cinfo.rout_push;
	}

	void CContact::SetOverlap(double x, double y)
	{
		overlapX = x;
		overlapY = y;
	}

	void CContact::GetOverlap(double &x, double &y)
	{
		x = overlapX;
		y = overlapY;
	}
};