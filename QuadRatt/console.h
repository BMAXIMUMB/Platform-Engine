// console.h

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "main.h"

class CConsole
{
private:
	bool isCreated;

public:
	CConsole();
	~CConsole();

	bool IsCreated(void);
	bool Create(void);
	void Destroy(void);
};

#endif /*_CONSOLE_H_*/