// column_manager.cpp

#include "column_manager.h"

CColumnManager::CColumnManager(PE::CWorld *world)
{
	this->world = world;
}

void CColumnManager::Create()
{
	for(int i = 0; i < COLUMN_START_COUNT; i++)
	{
		CreateColumn(ColumnSettingsGenerate());
	}
}

ColumnSettings CColumnManager::ColumnSettingsGenerate()
{
	ColumnSettings cs;

	cs.depth = RandomValue(20, 100);
	cs.posX = (float)RandomValue(300, 5000);
	cs.sizeX = (float)RandomValue(100, 200);
	cs.sizeY = (float)RandomValue(300, 500);

	return cs;
}

void CColumnManager::Check()
{

}

CColumn* CColumnManager::CreateColumn(ColumnSettings cs)
{
	// Создаем объект
	CColumn* column = new CColumn;
	column->Create(world, cs);

	// Пихаем в список
	columnElementList.push_back(column);

	return column;
}