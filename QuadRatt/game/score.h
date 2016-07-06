// score.h

#ifndef _SCORE_H_
#define _SCORE_H_

class CPlayer;
class CScore
{
private:
	int currentScore;
	int bestScore;

public:
	CScore();
	~CScore();

	bool LoadBestScoreFromFile(void);
	bool SaveBestScoreFromFile(void);

	void Update(CPlayer *Player);
	void Set(int value);

	int GetBestScore(void){ return bestScore; }
	int GetScore(void){ return currentScore; }
};

#endif //_SCORE_H_