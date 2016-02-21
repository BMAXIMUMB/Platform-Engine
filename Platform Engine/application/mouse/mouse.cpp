// mouse.cpp

#include "mouse.h"

namespace PlatformEngine
{
	CMouse::CMouse()
	{
		ButtonDown = nullptr;
		ButtonUp = nullptr;
		Move = nullptr;

		for(int i = 0; i < 3; i++) buttonPressed[i] = false;
	}
	
	void CMouse::ButtonDownFunction(void(*ButtonDown) (int button, int posx, int posy))
	{
		CMouse::ButtonDown = ButtonDown;
	}

	void CMouse::ButtonUpFunction(void(*ButtonUp) (int button, int posx, int posy))
	{
		CMouse::ButtonUp = ButtonUp;
	}

	void CMouse::MoveFunction(void(*Move) (int posx, int posy))
	{
		CMouse::Move = Move;
	}
};