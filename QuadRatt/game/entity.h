// entity.h

#include "../main.h"
#include "score.h"

#ifndef _ENTITY_H_
#define _ENTITY_H_

// ��� ��������� ������ ��������� �������
struct EntityOptions
{
	//	��������� ������� �� X � Y
	float spawnPosX					= NULL;
	float spawnPosY					= NULL;

	//	������� �� X � Y
	float sizeX						= NULL;
	float sizeY						= NULL;

	//	������ �������
	PlatformEngine::CSprite *sprite	= NULL;

	//	���� �������. ���������� ����� 255.255.255.255 (RGBA)
	color4 color					= Color(0xffffffff);

	/**
	*	��������� ������������ �� ����������� ���� ( ����������� ���������
	*	�� ���������)
	*	�� ��������� false
	*/
	bool disableHorizontalCollision = false;
};

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

/**
*	������� ����� ������ ������
*/
class IEntity
{
protected:

	EntityOptions options;

	PlatformEngine::CQuad *object;
	PlatformEngine::CWorld *world;

public:

	IEntity(PlatformEngine::CWorld *world);
	~IEntity();

	void Delete(void);
	PlatformEngine::CQuad* GetObjectID(void);

	void SetPosition(float x, float y);
	void SetColor(color4 color);
	void SetRotate(float angle);

	void GetPosition(float &x, float &y);
	void GetSize(float &x, float &y);
	bool GetHorizontalCollisionState(void);

	virtual void Create(float posX, float posY) = 0;
};

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

/**
*	����� ������
*/
class CPlayer :public IEntity
{
private:
	float startPosX;

	CScore *score;

	/**
	*	debug
	*/
	float d_jumpPos;
	float d_jumpDistance;

public:

	CPlayer(PlatformEngine::CWorld *world);
	~CPlayer();

	void Create(float posX, float posY);
	void SetSpawnPosition(float pos_x, float pos_y);
	void GetSpeed(float &x, float &y);
	bool onGround(void);
	void Spawn(void);
	void Respawn(void);
	void Reset(void);
	void Move(float speed_x, float speed_y);
	void Jump(void);

	float GetStartPos(void){ return startPosX; }
	void SetStartPos(float value);
	void SetStartPos(void);

	int GetScore(void);
	int GetBestScore(void);
	void UpdateScore(void);
};

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

/**
*	���������� ����
*	������� - 64�64 px
*	�������� - s_block
*/

class CBlock :public IEntity
{

public:
	CBlock(PlatformEngine::CWorld *world);
	~CBlock();

	void Create(float posX, float posY);
};

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

/**
*	���� ���������
*	������� - 64x24
*	�������� - s_mplatform
*/

class CMiniPlatform :public IEntity
{

public:
	CMiniPlatform(PlatformEngine::CWorld *world);
	~CMiniPlatform();

	void Create(float posX, float posY);

};

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

/**
*	�����������
*	������� - 64x64
*	�������� s_triangle
*/

class CTriangle :public IEntity
{
public:
	CTriangle(PlatformEngine::CWorld *world);
	~CTriangle();

	void Create(float posX, float posY);
};

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

/**
*	����-�����������
*	������� - 64x32
*	�������� s_triangle
*/

class CMiniTriangle :public IEntity
{
public:
	CMiniTriangle(PlatformEngine::CWorld *world);
	~CMiniTriangle();

	void Create(float posX, float posY);
};

#endif /*_ENTITY_H_*/