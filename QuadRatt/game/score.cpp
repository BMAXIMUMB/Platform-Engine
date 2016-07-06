// score.cpp
#include "score.h"
#include "entity.h"
#include "../main.h"

CScore::CScore()
{
	bestScore = 0;
	currentScore = 0;
}

CScore::~CScore()
{
	SaveBestScoreFromFile();
}

bool CScore::LoadBestScoreFromFile(void)
{
	PE::CFile File;

	if(File.Open(SCORE_FILE_PATH))
	{
		bestScore = File.GetInt(SCORE_SECTION_NAME, SCORE_KEY_NAME);
		return true;
	}

	return false;
}

bool CScore::SaveBestScoreFromFile(void)
{
	PE::CFile File;

	if(File.Open(SCORE_FILE_PATH))
	{
		File.Set(SCORE_SECTION_NAME, SCORE_KEY_NAME, bestScore);
		return true;
	}

	return false;
}

void CScore::Update(CPlayer *player)
{
	float pos[2];
	player->GetPosition(pos[0], pos[1]);

	currentScore = int((pos[0]-player->GetStartPos()) / PLAYER_SCORE_DIVIDER);

	if(currentScore > bestScore)
	{
		bestScore = currentScore;
		//SaveBestScoreFromFile();
	}
}

void CScore::Set(int value)
{
	currentScore = value;
}