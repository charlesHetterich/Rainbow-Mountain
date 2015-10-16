#pragma once
#include "sprites.h"
#include "SDL_setup.h"

class CBlock
{
public:
	CBlock(CSDL_setup* csdl_setup, int x, int y, int w, int h, std::string picture, int imageW, int imageH);
	~CBlock();
	void genBlock();
	Csprites* image;
private:

	CSDL_setup* sdl_setup;


	std::string blockImage;
	int xPos;
	int yPos;
	int height;
	int width;
};

