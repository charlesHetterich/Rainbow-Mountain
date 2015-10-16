#pragma once
#include "sprites.h"
#include "Music.h"
#include "SDL_setup.h"
#include "Health.h"

class CHighCloud
{
public:
	CHighCloud(CSDL_setup* csdl_Setup);
	~CHighCloud();
	void showCloud();
	void moveCould(SDL_Rect playerRect);
	void spawnCloud();
	CHealth* getHealth();
	void hurtCloud(int damage, int KnockBack);

	bool getAlive();


	SDL_Rect getCloudRect();

private:

	Csprites* cloud;
	int cloudSpeed;
	
	float angleTraveling;
	
	int directionToggle;
	int movementtimer;
	bool alive;
	bool inShock;

	int knockBack;
	int hurtTimer;

	int highPower;

	float deadFallingSpeed;
	float deadPushBackSpeed;
	int fallingAngle;

	CHealth* health;
	CSDL_setup* sdl_Setup;
};

