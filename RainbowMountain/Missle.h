#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Music.h"
#include "Events.h"

class CMissle
{
public:
	CMissle(CSDL_setup* csdl_setup);
	~CMissle();
	void launchMissle(int x, int y, int direction);
	void moveMissle();
	void destroyMissle(int thisMissle);
	bool checkLife(int thisMissle);
	int getStrength();
	void setStrength(int newStrength);
	int getKnockBack(int thisMissle);
	void setKnockBack(int newKnockBack);
	Csprites* missle[30];
private:

	CExplosion* missleExplosion[30];
	CMusic* MissleShotSound[30];
	int currentMissle;

	bool missleAlive[30];
	float missleSpeed[30];
	int missleDirection[30]; //1:right 2:left 3:up 4:down
	int cycledMissleNumber;

	//stats
	int strength;
	int knockBack;

	CSDL_setup* sdl_setup;
};

