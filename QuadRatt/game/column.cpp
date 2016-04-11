// column.cpp

#include "column.h"

//----------------------------------------------------------------------------------------------------------

void CColumn::Create(PE::CWorld *world, ColumnSettings cs)
{
	this->info = cs;
	this->world = world;

	LayerObjectSettings los;

	los.color = CalculateColor();
	los.posX = info.posX;
	los.posY = COLUMN_POS_Y;
	los.sizeX = info.sizeX;
	los.sizeY = info.sizeY;
	los.depth = (float)-info.depth;

	los.positionSet = LAYER_POSITION_UNFIXED;
	los.moveMode = LAYER_MOVE_MODE_2;
	los.moveFactor = CalculateMoveFactor();

	los.sprite = world->GetApp()->spriteManager->Get(COLUMN_SPRITE_NAME);

	this->layerObject = this->world->background->CreateElement(los);
}

color4 CColumn::CalculateColor()
{
	// Маска цвета
	const int mask = 0xffffffff;

	color4 maskColor;
	color4 color;
	color4 resultColor;

	// Настраиваем маску в зависимости от глубины
	maskColor = mask;
	maskColor -= ((float)info.depth * COLUMN_DEPTH_MULTIPLE / 255);

	// Альфу ставим 1
	maskColor.a = 1;

	color = COLUMN_COLOR;

	// Получаем результирующий цвет
	resultColor = maskColor*color;

	return resultColor;
}

float CColumn::CalculateSizeY()
{
	float sizeY = COLUMN_SIZE_Y;
	sizeY -= info.depth / 2;

	return sizeY;
}

float CColumn::CalculateMoveFactor()
{
	const float multiple = 16.0f;
	float moveFactor = multiple / info.depth;

	return moveFactor;
}