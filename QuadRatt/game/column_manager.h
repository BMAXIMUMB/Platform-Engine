// column_manager.h

#ifndef _COLUMN_MANAGER_H_
#define _COLUMN_MANAGER_H_

#include "column.h"

//----------------------------------------------------------------------------------------------------------

class CColumnManager
{

private:

	std::vector<CColumn*> columnElementList;
	PE::CWorld *world;

	bool isStarted;

	// Создает колонну
	CColumn* CreateColumn(ColumnSettings cs);

	// Удаляет колонну
	void DeleteColumn(CColumn* column);

	// Генерирует настройки для колонн по специальному алгоритму
	ColumnSettings ColumnSettingsGenerate(void);

public:

	CColumnManager(PE::CWorld *world);

	// Создает колонны на начальном этапе
	void Create(void);

	// Проверяет состояние колонн
	// Создает новые и удаляет не нужные колонны
	void Check(void);
};

#endif //_COLUMN_MANAGER_H_