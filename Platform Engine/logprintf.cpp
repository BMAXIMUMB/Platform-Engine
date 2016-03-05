#include "logprintf.h"

void logprintf(std::string text, ...)
{
	va_list argList;
	char buffer[1024];

	va_start(argList, text);
	vsnprintf(buffer, 1024, text.c_str(), argList);
	va_end(argList);
	strcat(buffer, "\n");

	printf(buffer);
}