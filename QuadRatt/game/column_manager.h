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

	// ������� �������
	CColumn* CreateColumn(ColumnSettings cs);

	// ������� �������
	void DeleteColumn(CColumn* column);

	// ���������� ��������� ��� ������ �� ������������ ���������
	ColumnSettings ColumnSettingsGenerate(void);

public:

	CColumnManager(PE::CWorld *world);

	// ������� ������� �� ��������� �����
	void Create(void);

	// ��������� ��������� ������
	// ������� ����� � ������� �� ������ �������
	void Check(void);
};

#endif //_COLUMN_MANAGER_H_