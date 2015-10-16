#include "stdafx.h"
#include "Score.h"


CScore::CScore()
{
	score = 0;
	scoreMultiplier = 1;
}


CScore::~CScore()
{
}

void CScore::raiseScore(int playerX, CText* text)
{
	score += 3 * scoreMultiplier;

	if (playerX < 800) { scoreMultiplier = 1; }
	else if (playerX < 1000) { scoreMultiplier = 2; }
	else if (playerX < 1200) { scoreMultiplier = 3; }
	else if (playerX < 1400) { scoreMultiplier = 4; }
	else if (playerX < 1520) { scoreMultiplier = 5; }
	else { scoreMultiplier = 9; }

	scoreMultiplier_string = std::to_string(scoreMultiplier);

	//display the multiplier
	//text->createText(100, "x", 10, 850, 30, 50);
	//text->createText(100, scoreMultiplier_string, 50, 850, 30, 50);
}

long CScore::getScore()
{
	return score;
}

void CScore::setScore(int newScore)
{
	score = newScore;
}