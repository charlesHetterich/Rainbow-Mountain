#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Music.h"

class CLaser
{
public:
	CLaser(CSDL_setup* csdl_setup);
	~CLaser();
	void shootLaser(int playerFacing);
	void showLaser(double x, double y);
	void setStrength(int newStrength);
	int getStrength();
	void setKnockBack(int newKnockBack);
	int getKnockBack();

	Csprites* electricBall;
	Csprites* laser;
private:
	CSDL_setup* sdl_setup;

	int direction; //1:right 2:left 3:up 4:down

	float electricBallVertSpeed;
	int electricBallFloatingDirection;
	bool electricBallSpeedingUp;

	double electricBallSpeed;
	int destinationDiference;

	int electricBallFrameRate;
	int electricBallFrameTime;
	
	int laserStrength;
	int laserKnockBack;

	CMusic* laserShotSound;
};

