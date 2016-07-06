// debug.h

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "main.h"

class CGame;

class CDebug
{
private:

	Gui::CText *textFps;
	Gui::CText *textPc;

	bool debugShowed;

	CGame *game;
	PE::CApplication *app;

public:
	CDebug(PE::CApplication *App, CGame *game);
	~CDebug();

	void ShowDebugInfo(void);
	void HideDebugInfo(void);

	void Update(void);
	
	bool IsShowed(void){ return debugShowed; }
};

#endif //_DEBUG_H_