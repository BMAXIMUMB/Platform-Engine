// platform_engine.cpp

#include "platform_engine.h"

int RandomValue(int min, int max)
{
	return min + rand() % (max-min + 1);
}

float FloatRandomValue(float min, float max)
{
	return (float)(rand()) / RAND_MAX*(max - min) + min;
}