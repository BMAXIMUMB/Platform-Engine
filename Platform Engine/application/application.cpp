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
		/**
		*	�������������
		*/
		this->hRC = NULL;
		this->hDC = NULL;
		this->hWnd = NULL;
		this->active = true;										
		this->fullscreen = false;		
		this->vSync = false;
		this->mouse = new PE::CMouse;								
		this->keyboard = new PE::CKeyboard;							
		this->spriteManager = new PE::CSpriteManager;
		this->fontManager = new PE::CFontManager;
		this->GUI = new Gui::CGuiManager(this);
		this->render = new PE::CRender;
		this->timer = new PE::CTimer(TIMER_TYPE_SECOND);
		this->fpsMeter = new PE::CFPSMeter;

		this->world = nullptr;
		this->shaderDefault = nullptr;
		this->shaderFontDefault = nullptr;

		/**
		*	��������� ������������
		*/
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

	void CApplication::SetVSync(bool value)
	{
		wglSwapInterval(value ? 1 : 0);
	}

	HWND CApplication::GetHWND(void)
	{
		return hWnd;
	}

	void CApplication::SetWorldID(PlatformEngine::CWorld *World)
	{
		CApplication::world = World;
	}

	void CApplication::glInit(void)
	{
		glewInit();
	}

	bool CApplication::Init(ApplicationSettings Settings)
	{
		// ������� ����
		if(!PECreateWindow(
			Settings.wtitle,
			(int)Settings.wwidth,
			(int)Settings.wheight,
			Settings.wbits,
			Settings.wfullscreen
			)) return false;

		// �������������� gl
		glInit();

		// ����������� �������
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

		wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

#ifdef PRINT_VERSION_GL
		logprintf("OpenGL %s, GLSL %s", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

		return true;
	}

	bool CApplication::PECreateWindow(LPCSTR title, int width, int height, int bits, bool fullscreen)
	{
		GLuint PixelFormat;								// ������ ��������� ����� ������
		WNDCLASS wc;									// ��������� ������ ����
		DWORD dwExStyle;								// ����������� ����� ����
		DWORD dwStyle;									// ������� ����� ����

		RECT WindowRect;								// Grabs Rectangle Upper Left / Lower Right Values
		WindowRect.left = (long)0;						// ���������� ����� ������������ � 0
		WindowRect.right = (long)width;					// ���������� ������ ������������ � Width
		WindowRect.top = (long)0;						// ���������� ������� ������������ � 0
		WindowRect.bottom = (long)height;				// ���������� ������ ������������ � Height

		CApplication::fullscreen = fullscreen;			// ������������� ���� fullscreen					
		CApplication::hInstance = GetModuleHandle(NULL);	// ������� ���������� ������ ����������
		CApplication::windowSizeX = width;
		CApplication::windowSizeY = height;

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// ���������� ��� ����������� � ������ ������� DC
		wc.lpfnWndProc = (WNDPROC)PEWndProc;			// ��������� ��������� ���������
		wc.cbClsExtra = 0;								// ��� �������������� ���������� ��� ����
		wc.cbWndExtra = 0;								// ��� �������������� ���������� ��� ����
		wc.hInstance = hInstance;						// ������������� ����������
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// ��������� ������ �� ���������
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);       // ��������� ��������� �����
		wc.hbrBackground = NULL;						// ��� �� ��������� ��� GL
		wc.lpszMenuName = NULL;							// ���� � ���� �� �����
		wc.lpszClassName = "PEOpenGL";					// ������������� ��� ������

		if(!RegisterClass(&wc))							// �������� ���������������� ����� ����
		{
			MessageBox(NULL, "���������� ���������������� ����� ����", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// ����� � ����������� �������� �������� false ! �� ����������:(
		}

		if(fullscreen)																	// ���� ������������� �����
		{
			DEVMODE dmScreenSettings;													// ����� ����������
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));						// ������� ��� �������� ���������
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);							// ������ ��������� Devmode
			dmScreenSettings.dmPelsWidth = width;										// ������ ������
			dmScreenSettings.dmPelsHeight = height;										// ������ ������
			dmScreenSettings.dmBitsPerPel = bits;										// ������� �����
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;	// ����� �������

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
					// ������������� ����, ���������� ������������ � �������� ����.
					MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
					return false;            // ����� � ����������� �������� false
				}
			}
		}

		if(fullscreen)													// �������� ���������
		{
			dwExStyle = WS_EX_APPWINDOW;								// ����������� ����� ����
			dwStyle = WS_POPUP;											// ������� ����� ����
			ShowCursor(false);											// ������ ��������� �����
		}
		else
		{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;				 // ����������� ����� ����
			dwStyle = /*WS_OVERLAPPEDWINDOW*/ WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX;        // ������� ����� ����
		}
		AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // ��������� ���� ���������� �������

		hWnd = CreateWindowEx(dwExStyle,			// ����������� ����� ��� ����
			("PEOpenGL"),							// ��� ������
			title,									// ��������� ����
			WS_CLIPSIBLINGS |						// ��������� ����� ��� ����
			WS_CLIPCHILDREN |						// ��������� ����� ��� ����
			dwStyle,								// ���������� ����� ��� ����
			(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,	// ������� ����
			WindowRect.right - WindowRect.left,		// ���������� ���������� ������
			WindowRect.bottom - WindowRect.top,		// ���������� ���������� ������
			NULL,									// ��� �������������
			NULL,									// ��� ����
			hInstance,								// ���������� ����������
			this);									// �� ������� ������ �� WM_CREATE (???)

		if(!hWnd)
		{
			PEKillWindow();                // ������������ �����
			MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;                // ������� false
		}

		static PIXELFORMATDESCRIPTOR pfd =				// pfd �������� Windows ����� ����� ����� �� ����� ������� �������
		{
			sizeof(PIXELFORMATDESCRIPTOR),				// ������ ����������� ������� ������� ��������
			1,											// ����� ������
			PFD_DRAW_TO_WINDOW |						// ������ ��� ����
			PFD_SUPPORT_OPENGL |						// ������ ��� OpenGL
			PFD_DOUBLEBUFFER,							// ������ ��� �������� ������
			PFD_TYPE_RGBA,								// ��������� RGBA ������
			bits,										// ���������� ��� ������� �����
			0, 0, 0, 0, 0, 0,							// ������������� �������� �����
			0,											// ��� ������ ������������
			0,											// ��������� ��� ������������
			0,											// ��� ������ ����������
			0, 0, 0, 0,									// ���� ���������� ������������
			32,											// 32 ������ Z-����� (����� �������)
			0,											// ��� ������ ���������
			0,											// ��� ��������������� �������
			PFD_MAIN_PLANE,								// ������� ���� ���������
			0,											// ���������������
			0, 0, 0										// ����� ���� ������������
		};

		if(!(hDC = GetDC(hWnd)))						// ����� �� �� �������� �������� ����������?
		{
			PEKillWindow();								// ������������ �����
			MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// ������� false
		}
		if(!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))// ������ �� ���������� ������ �������?
		{
			PEKillWindow();								// ������������ �����
			MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// ������� false
		}
		if(!SetPixelFormat(hDC, PixelFormat, &pfd))     // �������� �� ���������� ������ �������?
		{
			PEKillWindow();								// ������������ �����
			MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// ������� false
		}
		if(!(hRC = wglCreateContext(hDC)))				// �������� �� ���������� �������� ����������?
		{
			PEKillWindow();								// ������������ �����
			MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// ������� false
		}
		if(!wglMakeCurrent(hDC, hRC))					// ����������� ������������ �������� ����������
		{
			PEKillWindow();								// ������������ �����
			MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;								// ������� false
		}

		ShowWindow(hWnd, SW_SHOW);				// �������� ����
		SetForegroundWindow(hWnd);				// ������ ������� ���������
		SetFocus(hWnd);							// ���������� ����� ���������� �� ���� ����
		ReSizeGLScene(width, height);           // �������� ����������� ��� ������ OpenGL ������.

		return true;
	}

	void CApplication::ReSizeGLScene(GLsizei width, GLsizei height)
	{
		if(height == 0)								// �������������� ������� �� ����
		{
			height = 1;
		}
		glViewport(0, 0, width, height);			// ����� ������� ������� ������
		glMatrixMode(GL_PROJECTION);				// ����� ������� ��������
		glLoadIdentity();							// ����� ������� ��������

		// ���������� ����������� �������������� �������� ��� ����
		//gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

		glMatrixMode(GL_MODELVIEW);					// ����� ������� ���� ������
		glLoadIdentity();							// ����� ������� ���� ������
	}

	void CApplication::PEKillWindow(void)
	{
		if(fullscreen)												// �� � ������������� ������?
		{
			ChangeDisplaySettings(NULL, 0);							// ���� ��, �� ������������� ������� � ������� �����
			ShowCursor(true);										// �������� ������ �����
		}
		if(hRC)
		{
			if(!wglMakeCurrent(NULL, NULL))							// �������� �� ���������� RC � DC?
			{
				MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			}
			if(!wglDeleteContext(hRC))								// �������� �� ������� RC?
			{
				MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			}
			hRC = NULL;												// ���������� RC � NULL
		}
		if(hDC && !ReleaseDC(hWnd, hDC))							// �������� �� ���������� DC?
		{
			MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			hDC = NULL;												// ���������� DC � NULL
		}
		if(hWnd && !DestroyWindow(hWnd))							// �������� �� ���������� ����?
		{
			MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			hWnd = NULL;											// ���������� hWnd � NULL
		}
		if(!UnregisterClass("PEOpenGL", hInstance))					// �������� �� ����������������� �����
		{
			MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			hInstance = NULL;										// ���������� hInstance � NULL
		}
	}

	LRESULT CALLBACK CApplication::PEWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if(uMsg == WM_CREATE)
		{
			LPCREATESTRUCT pCS = (LPCREATESTRUCT)lParam;
			::SetWindowLong(hWnd, GWL_USERDATA, (DWORD)pCS->lpCreateParams);		//���������� ���������� ��������� �� �����
		}
		CApplication* pThis = (CApplication*)::GetWindowLong(hWnd, GWL_USERDATA);	//����� ��� 

		return pThis->WndProc(hWnd, uMsg, wParam, lParam);							// �������� ������� (�� static �����)
	}

	LRESULT CApplication::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
			case WM_ACTIVATE:
			{
				if(!HIWORD(wParam))						 // ��������� ��������� �����������
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
				switch(wParam)					// ������������� ��������� �����
				{
					case SC_SCREENSAVE:			// �������� �� ���������� �����������?
					case SC_MONITORPOWER:       // �������� �� ������� ������� � ����� ���������� �������?
					return 0;					// ������������� ���
				}
				break;
			}
			case WM_CLOSE:
			{
				PostQuitMessage(0);				// ��������� ��������� � ������
				return 0;						// ��������� �����
			}

			// ��������� ����
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

			// ��������� ����������
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
		double timeStart = timer->Start();

		MSG	  msg;											// ��������� ��� �������� ��������� Windows
		BOOL  done = false;									// ���������� ���������� ��� ������ �� �����
		if(OnRun != nullptr) OnRun();
		while(!done)
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))    // ���� �� � ������� �����-������ ���������?
			{
				if(msg.message == WM_QUIT)					// �� ������� ��������� � ������?
				{
					if(ShutDown != nullptr) ShutDown();
					done = true;							// ���� ���, (���)done=true
				}
				else
				{
					TranslateMessage(&msg);					// ��������� ���������
					DispatchMessage(&msg);					// �������� ���������
				}
			}
			else
			{
				if(CApplication::active)					// ������� �� ���������?
				{
					double dTime = timer->GetElapsed();

					// TODO: ����
					// ��������! ����!
					// ������ dt = 0, ������ ����� ������ ��������, ��� ��� �����
					// ����������� ���������, ���� - ����� ����.

					if(dTime != 0)
					{

						if(loopf != nullptr) loopf();
						DrawGLScene((float)dTime);					// ����������� � ������ �����
						SwapBuffers(hDC);					// ������ �����
					}
				}
			}
		}
		PEKillWindow();										// ��������� ����
		return (msg.wParam);								// ������� �� ���������
	}

	void CApplication::GetWindowSize(int &sizeX, int &sizeY)
	{
		sizeX = windowSizeX;
		sizeY = windowSizeY;
	}

	void CApplication::DrawGLScene(float dTime)
	{
		fpsMeter->Tick(dTime);

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