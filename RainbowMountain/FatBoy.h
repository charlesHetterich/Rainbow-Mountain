#pragma once
#include "sprites.h"
#include "Music.h"
#include "SDL_setup.h"
#include "Health.h"

class CFatBoy
{
public:
	CFatBoy(CSDL_setup* csdl_Setup);
	~CFatBoy();

	void spawn();
	void move();
	void grow();
	void show();
	void hurt(int damage);
	bool getAlive();
	SDL_Rect getRect();

private:

	Csprites* fatBoy;

	int speedX;
	int speedY;
	int rotateSpeed;

	float growingRate;
	float size;

	bool alive;

	CSDL_setup* sdl_Setup;
};

