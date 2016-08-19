// entity.cpp

#include "entity.h"

CEntity::CEntity(PlatformEngine::CWorld *world)
{
	this->world = world;

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

PlatformEngine::CQuad* CEntity::GetObjectID(void)
{
	return object;
}

void CEntity::SetPosition(float x, float y)
{
	object->SetPosition(x, y);
	world->camera->Update();
}

void CEntity::GetPosition(float &x, float &y)
{
	object->GetPosition(x, y);
}

void CEntity::GetSize(float &x, float &y)
{
	object->GetSize(x, y);
}

void CEntity::SetColor(color4 color)
{
	if(object != nullptr)
	{
		object->SetColor(color);
		options.color = color;
	}
}

////////////////////////////////////////////////////////////////////////////

CPlayer::CPlayer(PlatformEngine::CWorld *world) : CEntity(world)
{
	// ������ ��������� ������

	options.sizeX = 64;
	options.sizeY = 64;
	options.color = 0xffffffff;
	options.sprite = world->GetApp()->spriteManager->Get("s_player");

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
	options.spawnPosX = x;
	options.spawnPosY = y;
}

void CPlayer::Create(float spawnPosX, float spawnPosY)
{
	options.spawnPosX = spawnPosX;
	options.spawnPosY = spawnPosY;
}

void CPlayer::Reset(void)
{
	// ����� ������ � ������� ������

	this->startPosX = options.spawnPosX;

	score->Set(0);
	Spawn();
}

void CPlayer::Spawn()
{
	if(object != nullptr)
	{
		Delete();
	}
	
	object = world->CreateObjectQuad(options.spawnPosX, options.spawnPosY, options.sizeX, options.sizeY, options.sprite, OBJECT_TYPE_DYNAMIC);
	object->SetColor(options.color);
}

void CPlayer::Respawn()
{
	SetPosition(options.spawnPosX, options.spawnPosY);
	score->Set(0);

	this->startPosX = options.spawnPosX;
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

	GetPosition(pos[0], pos[1]);
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

CBlock::CBlock(PlatformEngine::CWorld *world) : CEntity(world)
{
	// ������ ��������� �������

	options.sizeX = 64;
	options.sizeY = 64;
	options.color = 0xffffffff;
	options.sprite = world->GetApp()->spriteManager->Get("s_block");
}

CBlock::~CBlock()
{

}

void CBlock::Create(float posX, float posY)
{
	options.spawnPosX = posX;
	options.spawnPosY = posY;

	// ������� ������ � �������� ���� �� ������
	this->object = world->CreateObjectQuad(posX, posY, options.sizeX, options.sizeY, options.sprite, OBJECT_TYPE_STATIC);
	this->object->SetColor(this->options.color);
}