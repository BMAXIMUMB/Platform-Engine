// program.cpp

#include "program.h"
#include "input\input.h"

//----------------------------------------------------------------------------------------------------------

CProgram::CProgram(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	this->hInstance = hInstance;
	this->hPrevInstance = hPrevInstance;

	console = new CConsole;

	game = nullptr;
}

CProgram::~CProgram()
{
	console->Destroy();

	if(game != nullptr) delete game;
	delete console;
}

void CProgram::InitGL()
{
	logprintf("Инициализация GL..");
	//glShadeModel(GL_SMOOTH);							// Разрешить плавное цветовое сглаживание
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0f);									// Разрешить очистку буфера глубины
	//glEnable(GL_DEPTH_TEST);							// Разрешить тест глубины
	//glDepthFunc(GL_LEQUAL);								// Тип теста глубины
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Улучшение в вычислении перспективы
	glEnable(GL_TEXTURE_2D);							// Включим 2D текстуры (ИAXYR)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_MULTISAMPLE);
	/*glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);*/
}

bool CProgram::Start()
{
	logprintf("Старт приложения...");

	app = new PE::CApplication;
	ApplicationSettings AppSet;

	AppSet.wtitle = "QuadRatt";
	AppSet.wfullscreen = false;
	AppSet.wbits = 32;
	AppSet.wwidth = 1280;
	AppSet.wheight = 720;
	AppSet.kKeyDown = KeyDown;
	AppSet.kKeyUp = KeyUp;
	AppSet.mButtonDown = MouseDown;
	AppSet.mButtonUp = MouseUp;
	AppSet.mMove = MouseMove;
	AppSet.loopf = loopF;
	AppSet.ShutDown = ShutDown;

	if(app->Init(AppSet))
	{
		InitGL();
		app->SetVSync(false);
		if(LoadShaders())
		{
			game = new ::CGame(app);
			app->Run();
			return true;
		}
	}
	return false;
}

int CProgram::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	console->Create();
	setlocale(LC_ALL, "Russian");
	return Start();
}

bool CProgram::LoadShaders()
{
	PE::CShader *Shader = new PE::CShader; 
	PE::CShader *FShader = new PE::CShader;
	if(Shader->LoadShaders("resources\\shaders\\shader.vert", "resources\\shaders\\shader.frag"))
	{
		app->shaderDefault = Shader;
		if(FShader->LoadShaders("resources\\shaders\\font\\shader.vert", "resources\\shaders\\font\\shader.frag"))
		{
			app->shaderFontDefault = FShader;
			return true;
		}
	}
	return false;
}

void CProgram::onKeyDown(int key)
{
	if(key == VK_ESCAPE)
	{
		if(MessageBoxA(app->GetHWND(), "Хотите выйти?", "Выход", MB_YESNO | MB_ICONWARNING) == IDYES)
		{
			SendMessageA(app->GetHWND(), WM_CLOSE, NULL, NULL);
			return;
		}
	}
	if(game != NULL)
	{
		game->onKeyDown(key);
	}
}

void CProgram::onKeyUp(int key)
{
	if(game != NULL)
	{
		game->onKeyUp(key);
	}
}

void CProgram::onMouseDown(int button, int x, int y)
{
	if(game != NULL)
	{
		game->onMouseDown(button, x, y);
	}
}

void CProgram::onMouseUp(int button, int x, int y)
{
	if(game != NULL)
	{
		game->onMouseUp(button, x, y);
	}
}

void CProgram::onMouseMove(int x, int y)
{
	if(game != NULL)
	{
		game->onMouseMove(x, y);
	}
}

void CProgram::LoopFunction()
{
	game->LoopFunction();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////