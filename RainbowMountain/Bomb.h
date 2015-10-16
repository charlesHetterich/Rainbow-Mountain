#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Music.h"
#include "Events.h"
class CBomb
{
public:
	CBomb(CSDL_setup* csdl_setup, int Size);
	~CBomb();
	void throwBomb(int x, int y, float HSpeed, float VSpeed);
	void showBomb();
	void setOffBomb();
	int getStrength();
	int getKnockBack(SDL_Rect enemyRect);
	bool getLife();
	bool getHurting();
	SDL_Rect getHurtingArea();

private:
	CSDL_setup* sdl_Setup;

	int size;
	SDL_Rect hurtingArea;
	Csprites* bomb;
	Csprites* redGlow;


	float bombHSpeed;
	float bombVSpeed;

	int clickSpeed;
	int clickTime;
	int clicksLeft;
	
	int strength;
	int knockBack;

	bool alive;
	bool hurting;

	CExplosion* explosion;
	CMusic* explosionNoise;
	

};

