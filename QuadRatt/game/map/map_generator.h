// map_generator.h

#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include <vector>

#include "zone.h"

class CMapGenerator
{
	/*
		���������� ������� �� ����� � ������� ����������� ���������� � ������

	
	*/

private:

	// ���, � ������� ����� ����������� �������
	PlatformEngine::CWorld *world;

	// ������� �������� �������. ���������� ��������� �� ��������� ������
	CEntity* CreateObject(float &mapEnd);

public:
	
	// �����������. world - ��������� �� ������ ����
	CMapGenerator(PlatformEngine::CWorld *world);

	// ����������. ����� �� ������ ( ���� ) 
	~CMapGenerator();

	// ������� ��������� ��������. � �������� ��������� ���������
	// ��������� �� ������ ��������, ���� ����� �������� ��������������� �������
	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);
};

#endif //_MAP_GENERATOR_H_
