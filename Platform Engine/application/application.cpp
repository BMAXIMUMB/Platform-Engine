// application.cpp

#include "application.h"
#include "../graphics/sprite/sprite.h"
#include "../logprintf.h"
#include "../gui/gui_manager.h"

#include <ctime>

namespace PlatformEngine
{
	CApplication::CApplication()
	{
		// Инициализация
		this->hRC = NULL;
		this->hDC = NULL;
		this->hWnd = NULL;
		this->active = true;										
		this->fullscreen = false;									
		this->mouse = new PE::CMouse;								
		this->keyboard = new PE::CKeyboard;							
		this->spriteManager = new PE::CSpriteManager;
		this->fontManager = new PE::CFontManager;
		this->GUI = new Gui::CGuiManager(this);
		this->render = new PE::CRender;

		this->world = nullptr;
		this->shaderDefault = nullptr;
		this->shaderFontDefault = nullptr;

		odt[0] = NULL; odt[1] = NULL; odt[2] = NULL; odt[3] = NULL; odt[4] = NULL;

		srand((unsigned)time(0));
	}

	CApplication::~CApplication()
	{
		delete mouse;
		delete keyboard;
		delete spriteManager;
		delete fontManager;
		delete render;
	}

	HWND CApplication::GetHWND(void)
	{
		return hWnd;
	}

	void CApplication::SetWorldID(PlatformEngine::CWorld *World)
	{
		CApplication::world = World;
	}

	int CApplication::GetFPS()
	{
		return mFps;
	}

	void CApplication::glInit(void)
	{
		glewInit();
	}

	bool CApplication::Init(ApplicationSettings Settings)
	{
		// Создаем окно
		if(!PECreateWindow(
			Settings.wtitle,
			(int)Settings.wwidth,
			(int)Settings.wheight,
			Settings.wbits,
			Settings.wfullscreen
			)) return false;

		// Инициализируем gl
		glInit();

		// Настраиваем события
		mouse->ButtonDownFunction(Settings.mButtonDown);
		mouse->ButtonUpFunction(Settings.mButtonUp);
		mouse->MoveFunction(Settings.mMove);
		keyboard->KeyDownFunction(Settings.kKeyDown);
		keyboard->KeyUpFunction(Settings.kKeyUp);
		GUI->SetElementClickCallback(Settings.guiOnElementClick);
		GUI->SetElementReleaseCallback(Settings.guiOnElementRelease);
		loopf = Settings.loopf;
		OnRun = Settings.onRunCallback;
		ShutDown = Settings.ShutDown;

		return true;
	}

	bool CApplication::PECreateWindow(LPCSTR title, int width, int height, int bits, bool fullscreen)
	{
		GLuint PixelFormat;								// Хранит результат после поиска
		WNDCLASS wc;									// Структура класса окна
		DWORD dwExStyle;								// Расширенный стиль окна
		DWORD dwStyle;									// Обычный стиль окна

		RECT WindowRect;								// Grabs Rectangle Upper Left / Lower Right Values
		WindowRect.left = (long)0;						// Установить левую составляющую в 0
		WindowRect.right = (long)width;					// Установить правую составляющую в Width
		WindowRect.top = (long)0;						// Установить верхнюю составляющую в 0
		WindowRect.bottom = (long)height;				// Установить нижнюю составляющую в Height

		CApplication::fullscreen = fullscreen;			// Устанавливаем флаг fullscreen					
		CApplication::hInstance = GetModuleHandle(NULL);	// Считаем дескриптор нашего приложения
		CApplication::windowSizeX = width;
		CApplication::windowSizeY = height;

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Перерисуем при перемещении и создаём скрытый DC
		wc.lpfnWndProc = (WNDPROC)PEWndProc;			// Процедура обработки сообщений
		wc.cbClsExtra = 0;								// Нет дополнительной информации для окна
		wc.cbWndExtra = 0;								// Нет дополнительной информации для окна
		wc.hInstance = hInstance;						// Устанавливаем дескриптор
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Загружаем иконку по умолчанию
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);       // Загружаем указатель мышки
		wc.hbrBackground = NULL;						// Фон не требуется для GL
		wc.lpszMenuName = NULL;							// Меню в окне не будет
		wc.lpszClassName = "PEOpenGL";					// Устанавливаем имя классу

		if(!RegisterClass(&wc))							// Пытаемся зарегистрировать класс окна
		{
			MessageBox(NULL, "Невозможно зарегистрировать класс окна", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// Выход и возвращение функцией значения false ! Не получилось:(
		}

		if(fullscreen)																	// Если полноэкранный режим
		{
			DEVMODE dmScreenSettings;													// Режим устройства
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));						// Очистка для хранения установок
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);							// Размер структуры Devmode
			dmScreenSettings.dmPelsWidth = width;										// Ширина экрана
			dmScreenSettings.dmPelsHeight = height;										// Высота экрана
			dmScreenSettings.dmBitsPerPel = bits;										// Глубина цвета
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;	// Режим Пикселя

			if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				if(MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
					"ERROR", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
				{
					fullscreen = false;
					this->fullscreen = false;
				}
				else
				{
					// Выскакивающее окно, сообщающее пользователю о закрытие окна.
					MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
					return false;            // Выход и возвращение функцией false
				}
			}
		}

		if(fullscreen)													// Применим настройки
		{
			dwExStyle = WS_EX_APPWINDOW;								// Расширенный стиль окна
			dwStyle = WS_POPUP;											// Обычный стиль окна
			ShowCursor(false);											// Скрыть указатель мышки
		}
		else
		{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;				 // Расширенный стиль окна
			dwStyle = /*WS_OVERLAPPEDWINDOW*/ WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX;        // Обычный стиль окна
		}
		AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // Подбирает окну подходящие размеры

		hWnd = CreateWindowEx(dwExStyle,			// Расширенный стиль для окна
			("PEOpenGL"),							// Имя класса
			title,									// Заголовок окна
			WS_CLIPSIBLINGS |						// Требуемый стиль для окна
			WS_CLIPCHILDREN |						// Требуемый стиль для окна
			dwStyle,								// Выбираемые стили для окна
			(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,	// Позиция окна
			WindowRect.right - WindowRect.left,		// Вычисление подходящей ширины
			WindowRect.bottom - WindowRect.top,		// Вычисление подходящей высоты
			NULL,									// Нет родительского
			NULL,									// Нет меню
			hInstance,								// Дескриптор приложения
			this);									// Не передаём ничего до WM_CREATE (???)

		if(!hWnd)
		{
			PEKillWindow();                // Восстановить экран
			MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;                // Вернуть false
		}

		static PIXELFORMATDESCRIPTOR pfd =				// pfd сообщает Windows каким будет вывод на экран каждого пикселя
		{
			sizeof(PIXELFORMATDESCRIPTOR),				// Размер дескриптора данного формата пикселей
			1,											// Номер версии
			PFD_DRAW_TO_WINDOW |						// Формат для Окна
			PFD_SUPPORT_OPENGL |						// Формат для OpenGL
			PFD_DOUBLEBUFFER,							// Формат для двойного буфера
			PFD_TYPE_RGBA,								// Требуется RGBA формат
			bits,										// Выбирается бит глубины цвета
			0, 0, 0, 0, 0, 0,							// Игнорирование цветовых битов
			0,											// Нет буфера прозрачности
			0,											// Сдвиговый бит игнорируется
			0,											// Нет буфера накопления
			0, 0, 0, 0,									// Биты накопления игнорируются
			32,											// 32 битный Z-буфер (буфер глубины)
			0,											// Нет буфера трафарета
			0,											// Нет вспомогательных буферов
			PFD_MAIN_PLANE,								// Главный слой рисования
			0,											// Зарезервировано
			0, 0, 0										// Маски слоя игнорируются
		};

		if(!(hDC = GetDC(hWnd)))						// Можем ли мы получить Контекст Устройства?
		{
			PEKillWindow();								// Восстановить экран
			MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// Вернуть false
		}
		if(!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))// Найден ли подходящий формат пикселя?
		{
			PEKillWindow();								// Восстановить экран
			MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// Вернуть false
		}
		if(!SetPixelFormat(hDC, PixelFormat, &pfd))     // Возможно ли установить Формат Пикселя?
		{
			PEKillWindow();								// Восстановить экран
			MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// Вернуть false
		}
		if(!(hRC = wglCreateContext(hDC)))				// Возможно ли установить Контекст Рендеринга?
		{
			PEKillWindow();								// Восстановить экран
			MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// Вернуть false
		}
		if(!wglMakeCurrent(hDC, hRC))					// Попробовать активировать Контекст Рендеринга
		{
			PEKillWindow();								// Восстановить экран
			MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// Вернуть false
		}

		ShowWindow(hWnd, SW_SHOW);				// Показать окно
		SetForegroundWindow(hWnd);				// Слегка повысим приоритет
		SetFocus(hWnd);							// Установить фокус клавиатуры на наше окно
		ReSizeGLScene(width, height);           // Настроим перспективу для нашего OpenGL экрана.

		return true;
	}

	void CApplication::ReSizeGLScene(GLsizei width, GLsizei height)
	{
		if(height == 0)								// Предотвращение деления на ноль
		{
			height = 1;
		}
		glViewport(0, 0, width, height);			// Сброс текущей области вывода
		glMatrixMode(GL_PROJECTION);				// Выбор матрицы проекций
		glLoadIdentity();							// Сброс матрицы проекции

		// Вычисление соотношения геометрических размеров для окна
		//gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

		glMatrixMode(GL_MODELVIEW);					// Выбор матрицы вида модели
		glLoadIdentity();							// Сброс матрицы вида модели
	}

	void CApplication::PEKillWindow(void)
	{
		logprintf("Разрушаем окно");
		if(fullscreen)												// Мы в полноэкранном режиме?
		{
			ChangeDisplaySettings(NULL, 0);							// Если да, то переключаемся обратно в оконный режим
			ShowCursor(true);										// Показать курсор мышки
		}
		if(hRC)
		{
			if(!wglMakeCurrent(NULL, NULL))							// Возможно ли освободить RC и DC?
			{
				MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			}
			if(!wglDeleteContext(hRC))								// Возможно ли удалить RC?
			{
				MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			}
			hRC = NULL;												// Установить RC в NULL
		}
		if(hDC && !ReleaseDC(hWnd, hDC))							// Возможно ли уничтожить DC?
		{
			MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			hDC = NULL;												// Установить DC в NULL
		}
		if(hWnd && !DestroyWindow(hWnd))							// Возможно ли уничтожить окно?
		{
			MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			hWnd = NULL;											// Установить hWnd в NULL
		}
		if(!UnregisterClass("PEOpenGL", hInstance))					// Возможно ли разрегистрировать класс
		{
			MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			hInstance = NULL;										// Установить hInstance в NULL
		}
	}

	LRESULT CALLBACK CApplication::PEWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if(uMsg == WM_CREATE)
		{
			LPCREATESTRUCT pCS = (LPCREATESTRUCT)lParam;
			::SetWindowLong(hWnd, GWL_USERDATA, (DWORD)pCS->lpCreateParams);		//Запоминаем переданный указатель на класс
		}
		CApplication* pThis = (CApplication*)::GetWindowLong(hWnd, GWL_USERDATA);	//берем его 
		return pThis->WndProc(hWnd, uMsg, wParam, lParam);							// вызываем обычный (не static метод)
	}

	LRESULT CApplication::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
			case WM_ACTIVATE:
			{
				if(!HIWORD(wParam))						 // Проверить состояние минимизации
				{
					active = true;          
				}
				else
				{
					active = false;
				}
				return 0;
			}
			case WM_SYSCOMMAND:
			{
				switch(wParam)					// Останавливаем системный вызов
				{
					case SC_SCREENSAVE:			// Пытается ли запустится скринсейвер?
					case SC_MONITORPOWER:       // Пытается ли монитор перейти в режим сбережения энергии?
					return 0;					// Предотвращаем это
				}
				break;
			}
			case WM_CLOSE:
			{
				PostQuitMessage(0);				// Отправить сообщение о выходе
				return 0;						// Вернуться назад
			}

			// Обработка мыши
			case WM_LBUTTONDOWN:
			{
				mouse->buttonPressed[PE_MOUSE_LBUTTON] = true;
				mouse->posx = LOWORD(lParam);
				mouse->posy = HIWORD(lParam);
				if(mouse->ButtonDown != nullptr)
					mouse->ButtonDown(PE_MOUSE_LBUTTON, mouse->posx, mouse->posy);
				GUI->CheckElementCick(PE_MOUSE_LBUTTON, mouse->posx, mouse->posy);
				return 0;
			}
			case WM_RBUTTONDOWN:
			{
				mouse->buttonPressed[PE_MOUSE_RBUTTON] = true;
				mouse->posx = LOWORD(lParam);
				mouse->posy = HIWORD(lParam);
				if(mouse->ButtonDown != nullptr)
					mouse->ButtonDown(PE_MOUSE_RBUTTON, mouse->posx, mouse->posy);
				GUI->CheckElementCick(PE_MOUSE_RBUTTON, mouse->posx, mouse->posy);
				return 0;
			}
			case WM_MBUTTONDOWN:
			{
				mouse->buttonPressed[PE_MOUSE_MBUTTON] = true;
				mouse->posx = LOWORD(lParam);
				mouse->posy = HIWORD(lParam);
				if(mouse->ButtonDown != nullptr)
					mouse->ButtonDown(PE_MOUSE_MBUTTON, mouse->posx, mouse->posy);
				GUI->CheckElementCick(PE_MOUSE_MBUTTON, mouse->posx, mouse->posy);
				return 0;
			}
			case WM_LBUTTONUP:
			{
				mouse->buttonPressed[PE_MOUSE_LBUTTON] = false;
				mouse->posx = LOWORD(lParam);
				mouse->posy = HIWORD(lParam);
				if(mouse->ButtonUp != nullptr)
					mouse->ButtonUp(PE_MOUSE_LBUTTON, mouse->posx, mouse->posy);
				GUI->CheckElementRelease(PE_MOUSE_LBUTTON, mouse->posx, mouse->posy);
				return 0;
			}
			case WM_RBUTTONUP:
			{
				mouse->buttonPressed[PE_MOUSE_RBUTTON] = false;
				mouse->posx = LOWORD(lParam);
				mouse->posy = HIWORD(lParam);
				if(mouse->ButtonUp != nullptr)
					mouse->ButtonUp(PE_MOUSE_RBUTTON, mouse->posx, mouse->posy);
				GUI->CheckElementRelease(PE_MOUSE_RBUTTON, mouse->posx, mouse->posy);
				return 0;
			}
			case WM_MBUTTONUP:
			{
				mouse->buttonPressed[PE_MOUSE_MBUTTON] = false;
				mouse->posx = LOWORD(lParam);
				mouse->posy = HIWORD(lParam);
				if(mouse->ButtonUp != nullptr)
					mouse->ButtonUp(PE_MOUSE_MBUTTON, mouse->posx, mouse->posy);
				GUI->CheckElementRelease(PE_MOUSE_MBUTTON, mouse->posx, mouse->posy);
				return 0;
			}
			/*case WM_MOUSEMOVE:
			{
				CApplication::Mouse->posx = LOWORD(lParam);
				CApplication::Mouse->posy = HIWORD(lParam);
				if(CApplication::Mouse->Move != nullptr)
					CApplication::Mouse->Move(CApplication::Mouse->posx, CApplication::Mouse->posy);
				return 0;
			}*/

			// Обработка клавиатуры
			case WM_KEYDOWN:
			{
				if(keyboard->KeyDown != nullptr) keyboard->KeyDown(wParam);
				keyboard->keys[wParam] = true;
				return 0;
			}
			case WM_KEYUP:
			{
				if(keyboard->KeyUp != nullptr) keyboard->KeyUp(wParam);
				keyboard->keys[wParam] = false;
				return 0;
			}
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
	int CApplication::Run(void)
	{	
		timeBeginPeriod(1);
		pTime = (float)timeGetTime();
		cFpsTime = pTime;
		//QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

		MSG	  msg;						// Структура для хранения сообщения Windows
		BOOL  done = false;				// Логическая переменная для выхода из цикла
		if(OnRun != nullptr) OnRun();
		while(!done)
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))    // Есть ли в очереди какое-нибудь сообщение?
			{
				if(msg.message == WM_QUIT)        // Мы поучили сообщение о выходе?
				{
					if(ShutDown != nullptr) ShutDown();
					done = true;					// Если так, (ган)done=true
				}
				else
				{
					TranslateMessage(&msg);        // Переводим сообщение
					DispatchMessage(&msg);        // Отсылаем сообщение
				}
			}
			else
			{
				if(CApplication::active)					// Активна ли программа?
				{
					/*QueryPerformanceCounter((LARGE_INTEGER*)&time_s);
					double dtt = (time_s.HighPart - time_n.HighPart) / (freq.QuadPart);*/
					//dtt /= 1000;
					// Расчитываем dt
					float cTime = (float)timeGetTime();
					float dTime = cTime - pTime;
					//odt[0] = cTime - pTime;
					if(cTime - cFpsTime >= 1000)
					{
						cFpsTime = cTime;
						mFps = currentFps;
						currentFps = 0;
					}

					// TODO: Фикс
					// ВНИМАНИЕ! БАГА!
					// Иногда dt = 0, скорее всего таймер неточный, или фпс дохуя
					// обязательно пофиксить, ниже - хуёвый фикс.

					//if(!dTime) dTime = 0.0001;
					if(dTime != 0)
					{
						dTime = dTime / CLOCKS_PER_SEC;

						if(loopf != nullptr) loopf();
						CApplication::DrawGLScene(dTime);	// Расчитываем и рисуем сцену
						SwapBuffers(hDC);					// Меняем буфер
						//printf("dTime %f\n", dTime);
						pTime = cTime;
						//QueryPerformanceCounter((LARGE_INTEGER*)&time_n);
					}
				}
			}
			//Sleep(1);
		}
		PEKillWindow();									// Разрушаем окно
		return (msg.wParam);							// Выходим из программы
	}

	void CApplication::GetWindowSize(int &sizeX, int &sizeY)
	{
		sizeX = windowSizeX;
		sizeY = windowSizeY;
	}

	void CApplication::DrawGLScene(float dTime)
	{
		currentFps++;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(world != nullptr)
		{
			world->Update(dTime);
			world->Draw();
		}
		GUI->Update(dTime);
		GUI->DrawElements();
	}
}