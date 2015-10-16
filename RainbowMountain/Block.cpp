#include "stdafx.h"
#include "Block.h"


CBlock::CBlock(CSDL_setup* csdl_setup, int x, int y, int w, int h, std::string picture, int imageW, int imageH)
{
	height = h;
	width = w;
	xPos = x;
	yPos = y;
	blockImage = picture;
	image = new Csprites(csdl_setup->GetRenderer(), blockImage, xPos, yPos, width, height, imageW, imageH);
	sdl_setup = csdl_setup;
}


CBlock::~CBlock()
{
	delete image;
	delete sdl_setup;
}

void CBlock::genBlock()
{

	image->drawReg(0,0);
}