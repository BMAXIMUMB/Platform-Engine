// application.h

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "../platform_engine.h"
#include "mouse\mouse.h"
#include "keyboard\keyboard.h"
#include "math\random.h"
#include "../graphics/shader/shader.h"
#include "../object/quad.h"
#include "../world/world.h"
#include "../graphics/render/render.h"
#include "../graphics/color/color.h"
#include "timer\timer.h"
#include "fpsmeter\fpsmeter.h"
#include "../logprintf.h"

#define PRINT_VERSION_GL

//----------------------------------------------------------------------------------------------------------

namespace Gui
{
	class CGuiManager;
	class CGuiElement;
};

typedef void(*_OnElementClick)(int, Gui::CGuiElement*);
typedef void(*_OnElementRelease)(Gui::CGuiElement*);
typedef void(*_OnRun)(void);
typedef void(*_ShutDown)(void);

typedef BOOL(WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);

struct ApplicationSettings
{
	// Информация об окне
	float wwidth							= NULL;
	float wheight							= NULL;
	LPCSTR wtitle							= "";
	int wbits								= NULL;
	bool wfullscreen						= NULL;

	// Мышь
	void(*mButtonDown)		(int, int, int)	= nullptr;
	void(*mButtonUp)		(int, int, int) = nullptr;
	void(*mMove)			(int, int)		= nullptr;

	// Клавиатура
	void(*kKeyDown)		(int)				= nullptr;
	void(*kKeyUp)		(int)				= nullptr;
	void(*loopf)		(void)				= nullptr;

	// События
	_OnRun				onRunCallback		= nullptr;
	_OnElementClick		guiOnElementClick	= nullptr;
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
		bool		vSync;					// Вертикальная синхронизация

		int			windowSizeX;
		int			windowSizeY;

		CTimer		*timer;

		/**
		*	VSync func
		*/
		PFNWGLSWAPINTERVALEXTPROC wglSwapInterval;

		void(*loopf)		(void);
		_ShutDown			ShutDown;
		_OnRun				OnRun;

		/**
		*	Обычный обработчик
		*/
		LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

		/**
		*	Уничножение окна
		*/
		void PEKillWindow(void);

		/**
		*	Перерисовать GL сцену
		*/
		void ReSizeGLScene(GLsizei, GLsizei);

	public:
		CMouse		*mouse;														// Указатель на мышь
		CKeyboard	*keyboard;													// Указатель на клавиатуру
		CShader		*shaderDefault;												// Шейдер по умолчанию
		CShader		*shaderFontDefault;											// Стандартный шейдер для текста
		CWorld		*world;														// Объект мира
		CSpriteManager *spriteManager;											// Менеджер спрайтов
		CFontManager *fontManager;												// Менеджер шрифтов
		CRender		*render;													// Рендер
		CFPSMeter	*fpsMeter;
		Gui::CGuiManager *GUI;

		////////////////////////////////////////////////////////////////////////////////

		PLATFORMENGINE_API CApplication();
		PLATFORMENGINE_API ~CApplication();

		/**
		*	Статический обработчик 
		*/
		static LRESULT  CALLBACK PEWndProc(HWND, UINT, WPARAM, LPARAM);

		/**
		*	Инициализация приложения
		*/
		PLATFORMENGINE_API bool Init(ApplicationSettings Settings);

		/**
		*	Cоздание окна приложения
		*/
		PLATFORMENGINE_API bool PECreateWindow(LPCSTR title, int width, int height, int bits, bool fullscreen);

		/**
		*	Запуск основного цикла
		*/
		PLATFORMENGINE_API int Run(void);

		/**
		*	Инициализация openGL
		*/
		PLATFORMENGINE_API void glInit(void);

		/**
		*	Функция отрисовки
		*/
		PLATFORMENGINE_API void DrawGLScene(float dTime);

		/**
		*	Вспомогательные функции
		*/
		PLATFORMENGINE_API HWND GetHWND(void);
		PLATFORMENGINE_API void GetWindowSize(int &sizeX, int &sizeY);
		PLATFORMENGINE_API void SetWorldID(PlatformEngine::CWorld *World);

		/**
		*	Включить/отключить вертикальную синхронизацю
		*/
		PLATFORMENGINE_API void SetVSync(bool);
	};
};


#endif //_APPLICATION_H_