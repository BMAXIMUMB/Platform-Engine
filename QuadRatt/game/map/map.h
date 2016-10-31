// map.h

#ifndef _MAP_H_
#define _MAP_H_

#include <vector>

#include "map_generator.h"

class CMap
{
private:
	 
	/**
	*	��������� ���� ���������� ��������
	*/
	std::vector <IEntity*> objectList;
	
	/**
	*	��������� �����
	*/
	CMapGenerator *mapGenerator;

	/**
	*	���, � ������� ����� ����������� �������
	*/
	PlatformEngine::CWorld *world;

	/**
	*	����� ��������������� �����
	*/
	float mapEnd;

public:

	CMap(PlatformEngine::CWorld *world);
	~CMap();
	
	/**
	*	������� ��� ������� � �����
	*/
	void Clear(void);

	/**
	*	������� �������� ��������
	*/
	void Check(void);

	/**
	*	�������� ��������� ������� ��������� �����
	*/
	void SetGeneratePos(float position);

	/**
	*	��������� ��� ��������� �������
	*/
	int GetObjectCount(void)
	{
		return objectList.size();
	}

	/**
	*	�������� ������� X ����� �����
	*/
	float GetMapEnd(void);

	/**
	*	�������� ������� X ����� �����
	*/
	void SetMapEnd(float value)
	{
		mapEnd = value;
	}


	/**
	*	��������� ������ �������� � �������� ��������
	*/

	CBlock*				CreateBlock(float posX, float posY);
	CTriangle*			CreateTriangle(float posX, float posY);
	CMiniPlatform*		CreateMiniPlatform(float posX, float posY);
	CMiniTriangle*		CreateMiniTriangle(float posX, float posY);


	/**
	* ������� ����� ������, ������������� �� IEntity
	*/
	bool DeleteEntity(IEntity* entity);

	/**
	*	������� ������� ������ CBlock
	*/
	bool DeleteBlock(CBlock *block);

	/**
	*	������� ������� ������ CMiniPlatform
	*/
	bool DeleteMiniPlatform(CMiniPlatform *miniPlatform);

	/**
	*	������� ������� ������ Triangle
	*/
	bool DeleteTriangle(CTriangle *triangle);

	/**
	*	������� ������� ������ MiniTriangle
	*/
	bool DeleteMiniTriangle(CMiniTriangle *triangle);
};

#endif //_MAP_H_