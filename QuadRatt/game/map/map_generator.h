// map_generator.h

#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include <vector>

#include "zone.h"

class CMap;

class CMapGenerator
{
	/**
	*	���������� ������� �� ����� � ������� ����������� ���������� � ������
	*
	*
	*/

private:

	/**
	*	�����, � ������� ��������� ���������
	*/
	CMap* map;

	/**
	*	������� ����
	*/
	IZone * currentZone = nullptr;

	/**
	*	����� ��������� ��������������� ����
	*/
	int lastZoneID	= NULL;

public:
	
	/**
	*	�����������. map - ��������� �� �����
	*/
	CMapGenerator(CMap *map);

	/**
	*	����������. ����� �� ������ ( ���� ) 
	*/
	~CMapGenerator();

	/**
	*	����� ���
	*/
	void Reset(void);

	/**
	*	������� ��������� ��������. � �������� ��������� ���������
	*	��������� �� ������ ��������, ���� ����� �������� ��������������� �������
	*/
	void Generate(/*std::vector<IEntity*> &objectList, float &mapEnd*/);

	/**
	*	������� ����� ����
	*/
	IZone* CreateZone();
};

#endif //_MAP_GENERATOR_H_
