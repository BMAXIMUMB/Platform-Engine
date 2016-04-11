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
		friend CApplication;									// ���� 
	private:
		bool buttonPressed[3];

		int posx;												// X ������� ����
		int posy;												// Y ������� ����

		void(*ButtonDown)	(int, int, int);					// ������� ������� ������
		void(*ButtonUp)		(int, int, int);					// ������� ������� ������
		void(*Move)			(int, int);							// ������� �������� ����

		CMouse();												// �����������

	public:

		// ��������� ������� ����
		PLATFORMENGINE_API	void ButtonDownFunction(void(*ButtonDown) (int button, int posx, int posy));
		PLATFORMENGINE_API	void ButtonUpFunction(void(*ButtonUp) (int button, int posx, int posy));
		PLATFORMENGINE_API	void MoveFunction(void(*Move) (int posx, int posy));

	};
};

#endif //_MOUSE_H_