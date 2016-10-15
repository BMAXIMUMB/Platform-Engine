// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

class CMap;

struct MapInfo
{
	// ���������� � �����

	/**
	*	��������� ���� ���������� ��������
	*/
	std::vector<IEntity*> objectList;

	/**
	*	����� ��������������� �����
	*/
	float mapEnd;
};


struct ZoneInfo
{
	CMap* map;

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

	CMap* map;

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

	/**
	*	������ �� ���� ���� ������
	*/
	bool isCreated;

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

	/**
	*	������ ����-���������
	*/
	const float restMiniPlatformSize = 64.0f;

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
	virtual void Generate() = 0;
};

class TowerHole :public IZone
{

public:

	TowerHole(ZoneInfo zi);
	~TowerHole();

	void Generate();

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

	void Generate();

private:
	
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

	//----------------------------------------------------------------------------------------------------------

	/**
	*	������� �����
	*/
	void TowerCreate(int holeLevel);
};

class PlatformStairs :public IZone
{

public:
	PlatformStairs(ZoneInfo zi);
	~PlatformStairs();

	void Generate();

private:

	/**
	*	������� ���������� �������
	*/
	int lastLevel;

	/**
	*	����������� ��������� �������
	*	������������ ��� ��������� ���������� � ������� ������� � ���� �������
	*/
	int lastDirection;
	
	/**
	*	������� �������� � ��������� ������������
	*	���� ������������ ������� � ������������ "0", ������� ������������
	*/
	int directionCounter;

	//----------------------------------------------------------------------------------------------------------

	/**
	*	���������� ����� ��������� (� ������)
	*/
	const int restStageDistance = 4;

	/**
	*	��������� ������ ( ������ ������ ��������� )
	*/
	const float restStartPosY = 202.0f;

	//----------------------------------------------------------------------------------------------------------
};

#endif // _ZONE_H_