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
	// Информация об окне
	float wwidth							= NULL;
	float wheight							= NULL;
	LPCSTR wtitle							= "";
	int wbits								= NULL;
	bool wfullscreen						= NULL;

	// Мышь
	void(*mButtonDown)	(int, int, int)		= nullptr;
	void(*mButtonUp)		(int, int, int) = nullptr;
	void(*mMove)			(int, int)		= nullptr;

	// Клавиатура
	void(*kKeyDown)		(int)				= nullptr;
	void(*kKeyUp)		(int)				= nullptr;
	void(*loopf)		(void)				= nullptr;

	// События
	_OnRun onRunCallback					= nullptr;
	_OnElementClick	guiOnElementClick		= nullptr;
	_OnElementRelease	guiOnElementRelease = nullptr;
	_ShutDown			ShutDown			= nullptr;
};

namespace PlatformEngine					// Пространство имен движка
{
	class CApplication						// Класс приложения
	{
	private:
		HGLRC		hRC;					// Постоянный контекст рендеринга
		HDC			hDC;					// Приватный контекст устройства GDI
		HWND		hWnd;					// Здесь будет хранится дескриптор окна
		HINSTANCE	hInstance;				// Здесь будет хранится дескриптор приложения

		bool		active;					// Флаг активности окна
		bool		fullscreen;				// Флаг режима окна

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

		LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);				// Обычный обработчик
		void PEKillWindow(void);											// Уничтожение окна
		void ReSizeGLScene(GLsizei, GLsizei);								// Применение размеров GL сцены

	public:
		CMouse *mouse;						// Указатель на мышь
		CKeyboard *keyboard;					// Указатель на клавиатуру
		CShader *shaderDefault;				// Шейдер по умолчанию
		CShader *shaderFontDefault;			// Стандартный шейдер для текста
		CWorld *world;						// Объект мира
		CSpriteManager *spriteManager;			// Менеджер спрайтов
		CFontManager *fontManager;
		CRender *render;
		Gui::CGuiManager *GUI;

		////////////////////////////////////////////////////////////////////////////////

		PLATFORMENGINE_API CApplication();									// Конструктор
		PLATFORMENGINE_API ~CApplication();									// Деструктор

		static LRESULT  CALLBACK PEWndProc(HWND, UINT, WPARAM, LPARAM);		// Статический обработчик

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