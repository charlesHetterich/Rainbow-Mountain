#pragma once
#include "SDL_setup.h"
#include "sprites.h"

class CStars
{
public:
	CStars(CSDL_setup* csdl_setup);
	~CStars();

	void genStars();

private:

	CSDL_setup* sdl_Setup;

	Csprites* star[100];
	int currentStar;
	int currentSize[100];

};

