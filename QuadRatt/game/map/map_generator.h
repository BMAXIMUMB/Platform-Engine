// map_generator.h

#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include <vector>

#include "zone.h"

class CMapGenerator
{
	/**
	*	���������� ������� �� ����� � ������� ����������� ���������� � ������
	*
	*
	*/

private:

	// ���, � ������� ����� ����������� �������
	PlatformEngine::CWorld *world;

	// ������� ����
	IZone * currentZone = nullptr;

public:
	
	// �����������. world - ��������� �� ������ ����
	CMapGenerator(PlatformEngine::CWorld *world);

	// ����������. ����� �� ������ ( ���� ) 
	~CMapGenerator();

	void Reset(void);

	/**
	*	������� ��������� ��������. � �������� ��������� ���������
	*	��������� �� ������ ��������, ���� ����� �������� ��������������� �������
	*/
	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);

	/**
	*	������� ����� ����
	*	beginPos - ������� ������ ���� �� X
	*/
	IZone* CreateZone(float beginPos);
};

#endif //_MAP_GENERATOR_H_
