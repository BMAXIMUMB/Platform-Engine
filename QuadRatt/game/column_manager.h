// column_manager.h

#ifndef _COLUMN_MANAGER_H_
#define _COLUMN_MANAGER_H_

#include "column.h"

//----------------------------------------------------------------------------------------------------------

class CColumnManager
{

private:

	std::vector<CColumn*> columnElementList;
	PlatformEngine::CWorld *world;

	PlatformEngine::CRandomDevice randomDevice;

	bool isStarted;

	// Создает колонну
	CColumn* CreateColumn(ColumnSettings cs);

	// Удаляет колонну
	void DeleteColumn(CColumn* column);

	// Генерирует настройки для колонн по специальному алгоритму
	ColumnSettings ColumnSettingsGenerate(void);

public:

	CColumnManager(PE::CWorld *world);
	~CColumnManager();

	// Создает колонны на начальном этапе
	void Create(void);

	// Удаляет все колонны
	void DeleteAll(void);

	// Проверяет состояние колонн
	// Создает новые и удаляет не нужные колонны
	void Check(void);
};

#endif //_COLUMN_MANAGER_H_