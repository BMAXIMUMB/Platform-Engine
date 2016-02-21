// barrier.cpp

#include "barrier.h"

CBarrierInfo::CBarrierInfo()
{
	
}

CBarrierInfo::~CBarrierInfo()
{

}

float CBarrierInfo::GetSize()
{
	return sizeX;
}

bool CBarrierInfo::LoadFromFile(const char *path, PE::CSpriteManager *SM)
{
	PE::CFile File;

	if(!File.Open(path))
	{
		logprintf("Невозможно открыть файл: " + (std::string)path);
		return false;
	}

	// Считываем основную информацию
	sizeX = File.GetFloat("barrier_info", "size");
	int block_count = File.GetInt("barrier_info", "bcount");

	// Считываем информацию о блоках
	char buff[40];
	float temp[4];
	std::string temp_sp;
	std::string name_sp;

	for(int i = 0; i < block_count; i++)
	{
		sprintf(buff, "block%d", i + 1);
		temp[0] = File.GetFloat(buff, "px");
		temp[1] = File.GetFloat(buff, "py");
		temp[2] = File.GetFloat(buff, "sx");
		temp[3] = File.GetFloat(buff, "sy");
		name_sp = File.GetString(buff, "s");
		temp_sp = File.GetString("sprite_info", (char*)name_sp.c_str());

		CBarrierElement *be = new CBarrierElement(temp[0], temp[1], temp[2], temp[3], SM->Load(temp_sp.c_str(), name_sp));
		elementList.push_back(be);
	}

	return true;
}
////////////////////////////////////////////////////////////////////

CBarrier::~CBarrier()
{
	Destroy();
}

void CBarrier::Create(PE::CWorld *World, CBarrierInfo *Binfo, float offset_x)
{
	for(unsigned int i = 0; i < Binfo->elementList.size(); i++)
	{
		CreateElement(World, Binfo->elementList[i], offset_x);
	}

	offset = offset_x;
	barrierInfo = Binfo;
}

void CBarrier::CreateElement(PE::CWorld *World, CBarrierElement *be, float offset_x)
{
	CBlock *b = new CBlock();

	entitysettings es;
	beinfo info = be->GetInfo();

	es.spawnPosX = info.posX + offset_x;
	es.spawnPosY = info.posY;
	es.sizeX = info.sizeX;
	es.sizeY = info.sizeY;
	es.sprite = info.sprite;

	b->Create(World, es);
	blockList.push_back(b);
}

void CBarrier::Destroy()
{
	for(unsigned int i = 0; i < blockList.size(); i++)
	{
		delete blockList[i];
	}
	blockList.clear();
}

float CBarrier::GetOffset(void)
{
	return offset;
}

float CBarrier::GetSize(void)
{
	return barrierInfo->GetSize();
}

////////////////////////////////////////////////////////////////////

CBarrierElement::CBarrierElement(float px, float py, float sx, float sy, PE::CSprite *Spr)
{
	posX = px;
	posY = py;
	sizeX = sx;
	sizeY = sy;
	sprite = Spr;
}

CBarrierElement::~CBarrierElement()
{
	//Destroy();
}

beinfo CBarrierElement::GetInfo(void)
{
	beinfo info;
	info.posX = posX;
	info.posY = posY;
	info.sizeX = sizeX;
	info.sizeY = sizeY;
	info.sprite = sprite;

	return info;
}
