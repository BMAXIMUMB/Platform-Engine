// map_generator.h

#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include <vector>
#include "../entity.h"

class CMapGenerator
{
private:

	// ���, � ������� ����� ����������� �������
	PlatformEngine::CWorld *world;

	// ������� �������� �������. ���������� ��������� �� ��������� ������
	CEntity* CreateObject(void);

public:
	
	// �����������. world - ��������� �� ������ ����
	CMapGenerator(PlatformEngine::CWorld *world);

	// ����������. ����� �� ������
	~CMapGenerator();

	// ������� ��������� ��������. � �������� ��������� ���������
	// ��������� �� ������ ��������, ���� �������� ��������������� �������
	void Generate(std::vector<CEntity*> objectList);
};

#endif //_MAP_GENERATOR_H_
