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
class CMapGenerator;

class IZone
{

	friend CMapGenerator;

protected:

	/**
	*	����� ����, ��������� ��������� �������� � �������� ���������
	*	�������� ����� ���� ������ � ������ ���� ����
	*/
	int lenght;

	/**
	*	���������� X ������ ����
	*/
	int beginPos;

	// ���, � ������� ����� ����������� �������
	PlatformEngine::CWorld *world;

public:

	/*
	*	world - ���, � ������� ����� ����������� �������
	*	beginPos - ������� ������ ���� �� X
	*/
	IZone(PlatformEngine::CWorld *world, int beginPos);
	~IZone();

	/**
	*	���������� ������� �� ��������� ���������
	*/
	virtual void Generate(std::vector<CEntity*> &objectList, float &mapEnd) = 0;
};

class SimpleZone :public IZone
{
	// �������� ������� ����


public:

	SimpleZone(PlatformEngine::CWorld *world, int beginPos);
	~SimpleZone();

	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);
};

#endif // _ZONE_H_