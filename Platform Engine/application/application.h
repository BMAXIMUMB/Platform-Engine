// application.h

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "../platform_engine.h"
#include "mouse\mouse.h"
#include "keyboard\keyboard.h"
#include "../graphics/shader/shader.h"
#include "../object/quad.h"
#include "../world/world.h"
#include "../graphics/render/render.h"
#include "../graphics/color/color.h"
#include "../logprintf.h"

namespace Gui
{
	class CGuiManager;
	class CGuiElement;
};

typedef void(*_OnElementClick)(int, Gui::CGuiElement*);
typedef void(*_OnElementRelease)(Gui::CGuiElement*);
typedef void(*_OnRun)(void);
typedef void(*_ShutDown)(void);

struct ApplicationSettings
{
	// ���������� �� ����
	float wwidth							= NULL;
	float wheight							= NULL;
	LPCSTR wtitle							= "";
	int wbits								= NULL;
	bool wfullscreen						= NULL;

	// ����
	void(*mButtonDown)	(int, int, int)		= nullptr;
	void(*mButtonUp)		(int, int, int) = nullptr;
	void(*mMove)			(int, int)		= nullptr;

	// ����������
	void(*kKeyDown)		(int)				= nullptr;
	void(*kKeyUp)		(int)				= nullptr;
	void(*loopf)		(void)				= nullptr;

	// �������
	_OnRun onRunCallback					= nullptr;
	_OnElementClick	guiOnElementClick		= nullptr;
	_OnElementRelease	guiOnElementRelease = nullptr;
	_ShutDown			ShutDown			= nullptr;
};

namespace PlatformEngine					// ������������ ���� ������
{
	class CApplication						// ����� ����������
	{
	private:
		HGLRC		hRC;					// ���������� �������� ����������
		HDC			hDC;					// ��������� �������� ���������� GDI
		HWND		hWnd;					// ����� ����� �������� ���������� ����
		HINSTANCE	hInstance;				// ����� ����� �������� ���������� ����������

		bool		active;					// ���� ���������� ����
		bool		fullscreen;				// ���� ������ ����

		int			windowSizeX;
		int			windowSizeY;

		int			mFps;
		int			currentFps;
		float		cFpsTime;

		float		pTime;
		float		odt[20];

		LARGE_INTEGER time_s, freq, time_n;

		void(*loopf)		(void);
		_ShutDown			ShutDown;
		_OnRun				OnRun;

		LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);				// ������� ����������
		void PEKillWindow(void);											// ����������� ����
		void ReSizeGLScene(GLsizei, GLsizei);								// ���������� �������� GL �����

	public:
		CMouse *mouse;						// ��������� �� ����
		CKeyboard *keyboard;					// ��������� �� ����������
		CShader *shaderDefault;				// ������ �� ���������
		CShader *shaderFontDefault;			// ����������� ������ ��� ������
		CWorld *world;						// ������ ����
		CSpriteManager *spriteManager;			// �������� ��������
		CFontManager *fontManager;
		CRender *render;
		Gui::CGuiManager *GUI;

		////////////////////////////////////////////////////////////////////////////////

		PLATFORMENGINE_API CApplication();									// �����������
		PLATFORMENGINE_API ~CApplication();									// ����������

		static LRESULT  CALLBACK PEWndProc(HWND, UINT, WPARAM, LPARAM);		// ����������� ����������

		PLATFORMENGINE_API bool Init(ApplicationSettings Settings);
		PLATFORMENGINE_API bool PECreateWindow(LPCSTR title, int width, int height, int bits, bool fullscreen);
		PLATFORMENGINE_API int Run(void);
		PLATFORMENGINE_API void glInit(void);
		PLATFORMENGINE_API void DrawGLScene(float dTime);

		PLATFORMENGINE_API HWND GetHWND(void);
		PLATFORMENGINE_API void GetWindowSize(int &sizeX, int &sizeY);
		PLATFORMENGINE_API void SetWorldID(PlatformEngine::CWorld *World);
		PLATFORMENGINE_API int GetFPS(void);

		void UpdateFPS(void);
	};
};


#endif //_APPLICATION_H_