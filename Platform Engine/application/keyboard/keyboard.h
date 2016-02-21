// keyboard.h

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "../../platform_engine.h"

namespace PlatformEngine
{
	class CApplication;
	class CKeyboard
	{
		friend CApplication;
	private:
		void(*KeyDown)	(int);									// ������� ������� �������
		void(*KeyUp)	(int);									// �������� ������� �������

		bool  keys[256];										// ������ ��� �������� � �����������

		CKeyboard();											// �����������

	public:
		PLATFORMENGINE_API bool		IsKeyPressed(int key);							// ������ �� ������
		PLATFORMENGINE_API void		KeyDownFunction(void(*KeyDown) (int key));		// ����������� ������� ������
		PLATFORMENGINE_API void		KeyUpFunction(void(*KeyUp) (int key));			// ����������� ������� ������
	};
};

#endif //_KEYBOARD_H_