// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

struct MapInfo
{
	// ���������� � �����

	/*
	*	��������� ���� ���������� ��������
	*/
	std::vector<CEntity*> objectList;

	/*
	*	����� ��������������� �����
	*/
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

	/**
	*	���, � ������� ����� ����������� �������
	*/
	PlatformEngine::CWorld *world = nullptr;

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

class TowerHole :public IZone
{
	// �������� ������� ����


public:

	TowerHole(PlatformEngine::CWorld *world, int beginPos);
	~TowerHole();

	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);

private:

	enum TowerType
	{
		Null,
		Type1,
		Type2,
		Type3
	};

	TowerType lastTowerType;

	/*
	*	���������� ����� �������
	*/
	const float restTowerDistance = 448.0f;

	/*
	*	�������������� ������ ��� ��������� � �����
	*/
	const float restMoreHoleSize = 10.0f;
};

#endif // _ZONE_H_