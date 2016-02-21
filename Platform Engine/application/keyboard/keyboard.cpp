// keyboard.cpp

#include "keyboard.h"

namespace PlatformEngine
{
	CKeyboard::CKeyboard()
	{
		KeyDown = nullptr;
		KeyUp = nullptr;
		for(auto i = 0; i < 256; i++)
		{
			keys[i] = false;
		}
	}

	bool CKeyboard::IsKeyPressed(int key)
	{
		return keys[key];
	}

	void CKeyboard::KeyDownFunction(void(*KeyDown) (int))
	{
		this->KeyDown = KeyDown;
	}

	void CKeyboard::KeyUpFunction(void(*KeyUp) (int))
	{
		this->KeyUp = KeyUp;
	}
};