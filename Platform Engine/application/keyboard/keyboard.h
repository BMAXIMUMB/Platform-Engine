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
		void(*KeyDown)	(int);									// Событие нажатия клавиши
		void(*KeyUp)	(int);									// Событияе отжатия клавиши

		bool  keys[256];										// Массив для операций с клавиатурой

		CKeyboard();											// Конструктор

	public:
		PLATFORMENGINE_API bool		IsKeyPressed(int key);							// Нажата ли кнопка
		PLATFORMENGINE_API void		KeyDownFunction(void(*KeyDown) (int key));		// Регистрация нажатия клавиш
		PLATFORMENGINE_API void		KeyUpFunction(void(*KeyUp) (int key));			// Регистрация нажатия клавиш
	};
};

#endif //_KEYBOARD_H_