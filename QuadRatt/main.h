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
#define COLUMN_DEPTH_MULTIPLE							1.04
#define COLUMN_COUNT									15
#define COLUMN_SPRITE_NAME								"s_column"

// BARRIER SETTINGS
#define BINFO_PATH										"resources\\bpatterns\\"
#define BINFO_MASK										"*.ini"
#define START_BARRIER_OFFSET							2000.0f

// PLAYER SETTINGS
#define PLAYER_JUMP_SPEED								730.0f
#define PLAYER_SCORE_DIVIDER							700.0f
#define START_PLAYER_POSX								00.0f
#define START_PLAYER_POSY								600.0f

// MACROS
#define randomDouble() static_cast<double>(rand()) / RAND_MAX
#define RGB256(value) value/255

// CALLBACKS

void ShutDown(void);
void loopF(void);
void OnObjCollision(PE::CContact *c);

#endif //___MAIN_H___