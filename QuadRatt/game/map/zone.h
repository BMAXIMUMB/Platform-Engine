// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

struct MapInfo
{
	// ���������� � �����

	// ��������� ���� ���������� ��������
	std::vector<CEntity*> objectList;

	// ����� ��������������� �����
	float mapEnd;
};

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

class IZone
{

protected:

	// ����� ����, ��������� ��������� �������� � �������� ���������
	// �������� ����� ���� ������ � ������ ���� ����
	int lenght;

	// ���, � ������� ����� ����������� �������
	PlatformEngine::CWorld *world;

public:

	IZone(PlatformEngine::CWorld *world);
	~IZone();

	virtual void Generate(std::vector<CEntity*> &objectList, float &mapEnd) = 0;
};

class SimpleZone :public IZone
{
	// �������� ������� ����


public:

	SimpleZone(PlatformEngine::CWorld *world);
	~SimpleZone();

	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);
};

#endif // _ZONE_H_