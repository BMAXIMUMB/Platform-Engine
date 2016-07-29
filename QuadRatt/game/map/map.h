// map.h

#ifndef _MAP_H_
#define _MAP_H_

#include <vector>

#include "map_generator.h"

class CMap
{
private:

	// ��������� ���� ���������� ��������
	std::vector <CEntity*> objectList;
	
	// ��������� �����
	CMapGenerator *mapGenerator;

	// ���, � ������� ����� ����������� �������
	PlatformEngine::CWorld *world;

public:

	CMap(PlatformEngine::CWorld *world);
	~CMap();
	
	// ������� ��� ������� � �����
	void Clear(void);
};

#endif //_MAP_H_