#include <stdio.h>
#include <string>
#include "platform_engine.h"

#ifndef _LOGPRINTF_H_
#define _LOGPRINTF_H_

// Функция печати лога
PLATFORMENGINE_API void logprintf(std::string text, ...);

#endif _LOGPRINTF_H_