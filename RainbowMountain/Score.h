#pragma once
#include "Text.h"
class CScore
{
public:
	CScore();
	~CScore();
	long getScore();
	void setScore(int newScore);
	void raiseScore(int playerX, CText* text);
	

private:
	long score;
	int scoreMultiplier;
	std::string scoreMultiplier_string;
};

