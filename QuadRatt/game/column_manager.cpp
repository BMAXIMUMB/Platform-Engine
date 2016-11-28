// column_manager.cpp

#include "column_manager.h"

CColumnManager::CColumnManager(PE::CWorld *world)
{
	isStarted = false;
	this->world = world;
	
}

CColumnManager::~CColumnManager()
{
	
}

void CColumnManager::Create()
{
	for(int i = 0; i < COLUMN_COUNT; i++)
	{
		CreateColumn(ColumnSettingsGenerate());
	}
	isStarted = true;
}

ColumnSettings CColumnManager::ColumnSettingsGenerate()
{
	ColumnSettings cs;

	if(!isStarted)
	{
		cs.depth = randomDevice.GetIntValue(20, 100);
		cs.posX = (float)randomDevice.GetIntValue(0, 1300);
		cs.sizeX = (float)randomDevice.GetIntValue(100, 200);
		cs.sizeY = (float)randomDevice.GetIntValue(300, 500);
	}
	else
	{
		cs.depth = randomDevice.GetIntValue(20, 100);
		cs.posX = (float)randomDevice.GetIntValue(1500, 2000);
		cs.sizeX = (float)randomDevice.GetIntValue(100, 200);
		cs.sizeY = (float)randomDevice.GetIntValue(300, 500);
	}

	return cs;
}

void CColumnManager::Check()
{
	// Проверяем, какие колонны больше не нужны
	for(unsigned int i = 0; i < columnElementList.size(); i++)
	{
		float pos[2];
		float size[2];
		float campos[2];
		int wsize[2];

		world->camera->GetPosition(campos[0], campos[1]);
		world->GetApp()->GetWindowSize(wsize[0], wsize[1]);

		columnElementList[i]->GetPosition(pos[0], pos[1]);
		columnElementList[i]->GetSize(size[0], size[1]);

		if(pos[0] + size[0] / 2 < 0)
		{
			DeleteColumn(columnElementList[i]);
			CreateColumn(ColumnSettingsGenerate());
		}
	}
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

void CColumnManager::DeleteColumn(CColumn* column)
{
	for(auto it = columnElementList.begin(); it != columnElementList.end(); it++)
	{
		if(*it == column)
		{
			delete column;
			columnElementList.erase(it);

			break;
		}
	}
}

void CColumnManager::DeleteAll()
{
	for(auto it = columnElementList.begin(); it != columnElementList.end(); it++)
	{
		delete (*it);
	}

	columnElementList.clear();
	isStarted = false;
}