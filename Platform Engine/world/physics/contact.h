// contact.h

#ifndef _CONTACT_H_
#define _CONTACT_H_

#include "../../object/object.h"
#include "../../object/quad.h"

#define DIRECTION_VERTICAL								1
#define DIRECTION_HORIZONTAL							2

struct contactinfo
{
	PlatformEngine::CObject *object1;
	PlatformEngine::CObject *object2;

	double overlap_x;
	double overlap_y;

	int direction;
};

namespace PlatformEngine
{
	class CContact
	{
		friend CWorld;

	public:
		CObject *object1;
		CObject *object2;

		double overlapX;
		double overlapY;
		
		int direction;

	public:
		CContact(contactinfo cinfo);

		void SetOverlap(double x, double y);
		void GetOverlap(double &x, double &y);
	};
};

#endif //_CONTACT_H_