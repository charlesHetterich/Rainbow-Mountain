#pragma once
#include "SDL_setup.h"
#include "sprites.h"
class CMouse
{
public:
	CMouse(CSDL_setup* csdl_setup);
	~CMouse();
	void mouseImage(int screen);
	bool mouseLeftClick();
	int mouseX;
	int mouseY;

private:
	CSDL_setup* sdl_setup;
	Csprites* image;

	
};

