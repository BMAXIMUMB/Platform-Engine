// column.h

#ifndef _COLUMN_H_
#define _COLUMN_H_

#include "background.h"

class CColumn :public CBackgroundElement
{

private:

	ColumnSettings info;

	// ����������� ���� ������� � ����������� �� �������
	// ��� ������, ��� ������
	color4 CalculateColor(void);

	// ����������� ������ �� Y � ����������� �� �������
	float CalculateSizeY(void);

	// ����������� ��������� �������� ������� � ����������� �� �������
	// ��� ������ �������, ��� ��������� ���������
	float CalculateMoveFactor(void);

public:

	void Create(PE::CWorld *world, ColumnSettings cs);

};

#endif //_COLUMN_H_