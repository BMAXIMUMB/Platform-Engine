// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

class IZone
{

private:

	// ����� ����, ��������� ��������� �������� � �������� ���������
	// �������� ����� ���� ������ � ������ ���� ����
	int lenght;

public:

	IZone();
	~IZone();
};

class SimpleZone :public IZone
{
	// �������� ������� ����


public:

	SimpleZone();
	~SimpleZone();
};

#endif // _ZONE_H_