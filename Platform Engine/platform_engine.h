// platform_engine.h

#ifdef PLATFORMENGINE_EXPORTS
#define PLATFORMENGINE_API __declspec(dllexport) 
#else
#define PLATFORMENGINE_API __declspec(dllimport) 
#endif

#define PE PlatformEngine				

#ifndef _PLATFORMENGINE_H_
#define _PLATFORMENGINE_H_

#include <Windows.h>				// Заголовочные файлы для Windows
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\matrix_transform_2d.hpp>

#define _USE_MATH_DEFINES 

#include <math.h>
#include <stdio.h>

PLATFORMENGINE_API int RandomValue(int min, int max);
float FloatRandomValue(float min, float max);

#endif //_PLATFORMENGINE_H_