#include "logprintf.h"

void logprintf(std::string str)
{
	str = str + "\n";
	printf(str.c_str());
}