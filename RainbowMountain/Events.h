#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Meteors.h"

class CEvents
{
public:
	CEvents(CSDL_setup* csdl_setup);
	~CEvents();
	void Levels();
	int speedUp();
	bool deathFlash();
	void meteorShower();

private:

	CSDL_setup* sdl_setup;



	//death flash
	Csprites* whiteFlash;

	//All level related things
	Csprites* levelColor[2];
	int levelTime;
	int levelChangeTime;
	int level;
	int currentProminentLevel;
	bool changingLevels;
	int colorChangeSpeed;

	//dont need this
	CMeteors* meteors;
	bool currentMeteorShower;


	int fade;

	int speedUpTimer;
};

class CExplosion
{
public:
	CExplosion(CSDL_setup* csdl_setup);
	~CExplosion();
	void explode(float Size, int x, int y);
	void showExplosion();
private:
	//explosion things
	float size;
	float explosionHSpeed[100];
	float explosionVSpeed[100];
	float X[100];
	float Y[100];
	float W[100];
	float H[100];
	int currentExplosionPart;
	Csprites* grayPuff[100];
	int maxGrayPuffs;
	Csprites* yellowFire[5];
	int maxYellowFire;
	Csprites* orangeFire[5];
	int maxOrangeFire;
	Csprites* grayCoverUp[10];
	int maxGrayCoverUps;
	Csprites* whiteSparks[20];
	int maxWiteSparks;

	CSDL_setup* sdl_setup;
};