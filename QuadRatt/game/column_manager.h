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

	// ������� �������
	CColumn* CreateColumn(ColumnSettings cs);

	// ������� �������
	void DeleteColumn(CColumn* column);

	// ���������� ��������� ��� ������ �� ������������ ���������
	ColumnSettings ColumnSettingsGenerate(void);

public:

	CColumnManager(PE::CWorld *world);
	~CColumnManager();

	// ������� ������� �� ��������� �����
	void Create(void);

	// ������� ��� �������
	void DeleteAll(void);

	// ��������� ��������� ������
	// ������� ����� � ������� �� ������ �������
	void Check(void);
};

#endif //_COLUMN_MANAGER_H_