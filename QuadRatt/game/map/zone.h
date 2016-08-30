// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

struct MapInfo
{
	// ���������� � �����

	/**
	*	��������� ���� ���������� ��������
	*/
	std::vector<CEntity*> objectList;

	/**
	*	����� ��������������� �����
	*/
	float mapEnd;
};


struct ZoneInfo
{
	PlatformEngine::CWorld *world;

	int beginPos;

	int lastZoneID;
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

	/**
	*	���, � ������� ����� ����������� �������
	*/
	PlatformEngine::CWorld *world = nullptr;

	/**
	*	ID ���������� ����
	*/
	int prevZoneID;

	//----------------------------------------------------------------------------------------------------------

	/**
	*	����������� � ������� ��������� ��� ���� ���
	*/
	const float restMaxJumpHeight = 135.8f;

	/**
	*	���������� �� Y ������� ������� ��� ������
	*/
	const float restGroundLevel = 182.0f;

	/**
	*	������ ����������� �����
	*/
	const float restBlockSize = 64.0f;

public:

	/**
	*	world - ���, � ������� ����� ����������� �������
	*	beginPos - ������� ������ ���� �� X
	*/
	IZone(ZoneInfo zi);
	~IZone();

	/**
	*	���������� ������� �� ��������� ���������
	*/
	virtual void Generate(std::vector<CEntity*> &objectList, float &mapEnd) = 0;
};

class TowerHole :public IZone
{

public:

	TowerHole(ZoneInfo zi);
	~TowerHole();

	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);

private:

	enum class TowerType
	{
		Null,
		Type1,
		Type2,
		Type3
	};

	TowerType lastTowerType;

	/**
	*	���������� ����� �������
	*/
	const float restTowerDistance = 448.0f;

	/**
	*	�������������� ������ ��� ��������� � �����
	*/
	const float restMoreHoleSize = 10.0f;
};

class TowerStairs :public IZone
{

public:
	TowerStairs(ZoneInfo zi);
	~TowerStairs();

	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);

private:
	
	/**
	*	������� �� ���� ���� �����
	*/
	bool isCreated;

	/**
	*	������ ������� ��������� �����
	*/
	int lastHoleLevel;

	//----------------------------------------------------------------------------------------------------------

	/**
	*	���������� ����� �������
	*/
	const float restTowerDistance = 192.0f;

	/**
	*	���������� ����� ����� ������ ������ � ���������� �����
	*/
	const float restZoneDistance = 640;

	/**
	*	������ ������� � ������
	*/
	const float restHoleSize = 3;

	/**
	*	������ �����
	*/
	const int restTowerHeight = 8;

	void TowerCreate(int holeLevel, float &mapEnd, std::vector<CEntity*> &objectList);
};

#endif // _ZONE_H_