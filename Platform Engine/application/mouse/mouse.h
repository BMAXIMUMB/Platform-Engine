// mouse.h

#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "../../platform_engine.h"

#define PE_MOUSE_LBUTTON		0x0
#define PE_MOUSE_RBUTTON		0x1
#define PE_MOUSE_MBUTTON		0x2

namespace PlatformEngine
{
	class CApplication;

	class CMouse
	{
		friend CApplication;									// Друг 
	private:
		bool buttonPressed[3];

		int posx;												// X позиция мыши
		int posy;												// Y позиция мыши

		void(*ButtonDown)	(int, int, int);					// Событие нажатия кнопки
		void(*ButtonUp)		(int, int, int);					// Событие отжатия кнопки
		void(*Move)			(int, int);							// Событие движения мыши

		CMouse();												// Конструктор

	public:

		// Настройки событий мыши
		PLATFORMENGINE_API	void ButtonDownFunction(void(*ButtonDown) (int button, int posx, int posy));
		PLATFORMENGINE_API	void ButtonUpFunction(void(*ButtonUp) (int button, int posx, int posy));
		PLATFORMENGINE_API	void MoveFunction(void(*Move) (int posx, int posy));

	};
};

#endif //_MOUSE_H_