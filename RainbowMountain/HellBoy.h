#pragma once
#include "sprites.h"
#include "Music.h"
#include "SDL_setup.h"
#include "Health.h"

class CHellBoy
{
public:
	CHellBoy(CSDL_setup* csdl_setup);
	~CHellBoy();
	void attack();
	void spawn();
	void moveAround(SDL_Rect playerRect);
	void dying();
	void hurtHellBoy(int damageAmount, int knockBack);

	bool getIfBoolHit(int thisBlood);
	void setBloodHit(int thisBlood, bool hit);

	Csprites* boy;
	Csprites* blood[30];

	CHealth* health;

	

private:
	Csprites* hurtFlash;
	int boyFallBackSpeed;
	CMusic* noises;
	int attackCoolDown;

	float boyLocationX;
	float boyLocationY;

	int currentBlood;
	int amountOfBlood;
	int bloodCycle;
	float bloodVSpeed[30];
	float bloodHSpeed[30];
	bool bloodHit[30];

	int bloodFireRate;
	int bloodReloading;

	float destinationDistance;
	int boySpeed;
	int boyFacing; //0:right 1:left

	bool attacking;

	//deathstuff
	float fallingSpeed;
	float fallingAngle;
	float pushBackFallingSpeed;

	CSDL_setup* sdl_setup;
};

