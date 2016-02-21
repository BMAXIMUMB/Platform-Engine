// debug.h

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "main.h"

class CDebug
{
private:

	Gui::CText *textFps;
	Gui::CText *textPc;

	bool debugShowed;

	PE::CApplication *app;

public:
	CDebug(PE::CApplication *App);
	~CDebug();

	void ShowDebugInfo(void);
	void HideDebugInfo(void);

	void Update(void);
	
	bool IsShowed(void){ return debugShowed; }
};

#endif //_DEBUG_H_