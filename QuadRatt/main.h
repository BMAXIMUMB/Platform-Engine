// main.h

#ifndef ___MAIN_H___
#define ___MAIN_H___

#include "../Platform Engine/application/application.h"
#include "../Platform Engine/logprintf.h"
#include "../Platform Engine/world/layer.h"
#include "../Platform Engine/world/physics/contact.h"
#include "../Platform Engine/resource/resource.h"
#include "../Platform Engine/gui/gui_manager.h"
#include "../Platform Engine/gui/gui.h"

#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

#define _USE_MATH_DEFINES 
#include <ctime>
#include <math.h>

//ICON SETTINGS
#define ICON_SIZE										64
#define ICON_POS_Y										102

//SCORE SETTINGS
#define SCORE_FILE_PATH									"save\\save.ini"
#define SCORE_SECTION_NAME								"save"
#define SCORE_KEY_NAME									"score"

// GROUND SETTINGS
#define GROUND_ELEMENT_SIZE_X							215
#define GROUND_ELEMENT_SIZE_Y							150
#define GROUND_ELEMENT_COUNT							7
#define START_ELEMENT_POS								-610

// COLUMN SETTINGS
#define COLUMN_COLOR									0x1aee42ff
#define COLUMN_POS_Y									200
#define COLUMN_SIZE_Y									350
#define COLUMN_DEPTH_MULTIPLE							1.04f
#define COLUMN_COUNT									15
#define COLUMN_SPRITE_NAME								"s_column"

// BARRIER SETTINGS
#define BINFO_PATH										"resources\\bpatterns\\"
#define BINFO_MASK										"*.ini"
#define START_BARRIER_OFFSET							1200.0f

// PLAYER SETTINGS
#define PLAYER_JUMP_SPEED								800.0f
#define PLAYER_SCORE_DIVIDER							700.0f
#define START_PLAYER_POSX								100.0f
#define START_PLAYER_POSY								300.0f

// MACROS
#define randomDouble() static_cast<double>(rand()) / RAND_MAX
#define RGB256(value) value/255

// CALLBACKS

void ShutDown(void);
void loopF(void);
void OnObjCollision(PE::CContact *c);

#endif //___MAIN_H___