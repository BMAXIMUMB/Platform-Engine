// map.h

#ifndef _MAP_H_
#define _MAP_H_

#include <vector>

#include "map_generator.h"

class CMap
{
private:
	 
	// ��������� ���� ���������� ��������
	std::vector <IEntity*> objectList;
	
	// ��������� �����
	CMapGenerator *mapGenerator;

	// ���, � ������� ����� ����������� �������
	PlatformEngine::CWorld *world;

	// ����� ��������������� �����
	float mapEnd;

public:

	CMap(PlatformEngine::CWorld *world);
	~CMap();
	
	// ������� ��� ������� � �����
	void Clear(void);

	// ������� �������� ��������
	void Check(void);

	// �������� ��������� ������� ��������� �����
	void SetGeneratePos(float position);
};

#endif //_MAP_H_