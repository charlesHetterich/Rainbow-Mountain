#include "stdafx.h"
#include "FatBoy.h"


CFatBoy::CFatBoy(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;
	fatBoy = new Csprites(sdl_Setup->GetRenderer(), "images/fatguy.png", NULL, NULL, NULL, NULL, 1606, 1653);

	growingRate = 2;

	rotateSpeed = 2;
}


CFatBoy::~CFatBoy()
{
	delete fatBoy;
}

void CFatBoy::show()
{
	//fatBoy->drawReg(0, 0);
}

void CFatBoy::spawn()
{
	fatBoy->setX(300);
	fatBoy->setY(300);
	fatBoy->setW(300);
	fatBoy->setH(300);
	size = 300;
	speedX = 4;
	speedY = 4;
	alive = true;
}

void CFatBoy::grow()
{
	//if (size < 600)
		//size += growingRate;

	fatBoy->setW(fatBoy->getW() + (size - fatBoy->getW())/10);
	fatBoy->setH(fatBoy->getW() + (size - fatBoy->getH())/10);
	fatBoy->setX(fatBoy->getX() - growingRate / 2);
	fatBoy->setY(fatBoy->getY() - growingRate / 2);
}

void CFatBoy::move()
{
	fatBoy->setAngle(fatBoy->getAngle() + rotateSpeed);
	fatBoy->setX(fatBoy->getX() + speedX);
	fatBoy->setY(fatBoy->getY() + speedY);
	if (fatBoy->getX() <= 0 || fatBoy->getX() + fatBoy->getW() >= sdl_Setup->getScreenWidth)
	{
		fatBoy->setX(fatBoy->getX() - speedX);
		speedX *= -1;
	}
	if (fatBoy->getY() <= 0 || fatBoy->getY() + fatBoy->getH() >= sdl_Setup->getScreenHeight)
	{
		fatBoy->setY(fatBoy->getY() - speedY);
		speedY *= -1;
	}
}

void CFatBoy::hurt(int damage)
{
	size -= damage;
}

bool CFatBoy::getAlive()
{
	return alive;
}

SDL_Rect CFatBoy::getRect()
{
	return fatBoy->getRect();
}