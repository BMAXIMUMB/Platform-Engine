// entity.cpp

#include "entity.h"

CEntity::CEntity()
{
	object = nullptr;
}

CEntity::~CEntity()
{
	Delete();
}

void CEntity::Delete()
{
	world->DestroyObject(object);
}

PE::CQuad* CEntity::GetObjectID(void)
{
	return object;
}

void CEntity::SetPosition(float x, float y)
{
	posX = x;
	posY = y;
	object->SetPosition(x, y);
}

void CEntity::GetPosition(float &x, float &y)
{
	object->GetPosition(x, y);
}

void CEntity::SetColor(color4 color)
{
	if(object != nullptr)
	{
		object->SetColor(color);
		this->color = color;
	}
}

////////////////////////////////////////////////////////////////////////////

CPlayer::CPlayer()
{
	startPosX = 0.0f;

	score = new CScore;
	score->LoadBestScoreFromFile();
}
CPlayer::~CPlayer()
{
	delete score;
}

void CPlayer::SetSpawnPosition(float x, float y)
{
	spawnPosX = x;
	spawnPosX = y;
}

void CPlayer::Create(PE::CWorld *world, entitysettings pset)
{
	this->spawnPosX = pset.spawnPosX;
	this->spawnPosX = pset.spawnPosY;
	this->sizeX = pset.sizeX;
	this->sizeY = pset.sizeY;
	this->world = world;
	this->sprite = pset.sprite;
	this->color = pset.color;

	this->posX = spawnPosX;
	this->posY = spawnPosX;
}

void CPlayer::Reset(void)
{
	// —брос данных и респавн игрока

	startPosX = spawnPosX;

	score->Set(0);
	Spawn();
}

void CPlayer::Spawn()
{
	if(object != nullptr)
	{
		Delete();
	}

	object = world->CreateObjectQuad(spawnPosX, spawnPosX, sizeX, sizeY, sprite, OBJECT_TYPE_DYNAMIC);
	object->SetColor(color);
}

bool CPlayer::onGround()
{
	return object->OnGround();
}

void CPlayer::Move(float speed_x, float speed_y)
{
	object->Move(speed_x, speed_y);
}

void CPlayer::GetSpeed(float &x, float &y)
{
	object->GetSpeed(x, y);
}

void CPlayer::SetStartPos(float value)
{
	startPosX = value;
}

void CPlayer::SetStartPos()
{
	float pos[2];

	object->GetPosition(pos[0], pos[1]);
	startPosX = pos[0];
}

void CPlayer::Jump()
{
	if(onGround())
	{
		//Object->SetAcceleration(OBJECT_CURRENT_VALUE, 300.0f);
		Move(OBJECT_CURRENT_VALUE, PLAYER_JUMP_SPEED);
	}
}

int CPlayer::GetScore()
{
	return score->GetScore();
}

int CPlayer::GetBestScore()
{
	return score->GetBestScore();
}

void CPlayer::UpdateScore(void)
{
	score->Update(this);
}

////////////////////////////////////////////////////////////////////////////

CBlock::CBlock(){}
CBlock::~CBlock(){}

void CBlock::Create(PE::CWorld *world, entitysettings pset)
{
	this->posX = pset.spawnPosX;
	this->posY = pset.spawnPosY;
	this->sizeX = pset.sizeX;
	this->sizeY = pset.sizeY;
	this->world = world;
	this->sprite = pset.sprite;

	this->object = world->CreateObjectQuad(posX, posY, sizeX, sizeY, sprite, OBJECT_TYPE_STATIC);
}