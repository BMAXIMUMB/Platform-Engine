// zone.cpp

#include "zone.h"

IZone::IZone(PlatformEngine::CWorld *world, int beginPos)
{
	this->world = world;
	this->beginPos = beginPos;
}

IZone::~IZone()
{

}


//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------


SimpleZone::SimpleZone(PlatformEngine::CWorld *world, int beginPos) :IZone(world, beginPos)
{
	lenght = RandomValue(3000, 5000);
}

SimpleZone::~SimpleZone()
{

}

void SimpleZone::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
{
	// ������� �������� ������ ��� ��� ������
	CEntity *object = new CBlock(world);

	// ���������� ��� ���� �������
	float spawnPosX = mapEnd + RandomValue(64, 300);
	float spawnPosY = 182;

	// ������� ��� � ����� � ������ ���� ��������
	object->Create(spawnPosX, spawnPosY);
	objectList.push_back(object);

	mapEnd = spawnPosX;

	logprintf("generate");
}
