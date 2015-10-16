#include "stdafx.h"
#include "Tacano.h"


CTacano::CTacano(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;
	tacosAmount = 72;
	tacoStrength = 3;

	volcano = new Csprites(sdl_Setup->GetRenderer(), "images/Valcano.png", NULL, NULL, 180, 145, 171, 112);
	for (int i = 0; i < 72; i++)
	{
		taco[i] = new Csprites(sdl_Setup->GetRenderer(), "images/taco.png", NULL, NULL, 40, 30, 415, 229);
	}

	VolcanoDestY = sdl_Setup->getScreenHeight - volcano->getH();
}


CTacano::~CTacano()
{
	delete taco;
	delete volcano;
}

void CTacano::spawn()
{
	volcanoAlive = true;
	angered = false;
	leaving = false;
	volcano->setX(rand() % (sdl_Setup->getScreenWidth - volcano->getW()));
	volcano->setY(sdl_Setup->getScreenHeight);

	for(int i = 0; i < 72; i++)
	{
		tacoActive[i] = false;
		taco[i]->setY(sdl_Setup->getScreenHeight);
	}
	tacoCycle = 0;
}

void CTacano::show()
{
	if (volcanoAlive)
	{
		for (int i = 0; i < 72; i++)
		{
			if (tacoActive[i])
			{
				taco[i]->drawReg(0, 0);
			}
		}
		volcano->drawReg(0, 0);
	}
}

void CTacano::shootTaco()
{
	if (tacoTimer + 50 < SDL_GetTicks() & angry & tacoCycle < 72)
	{
		taco[tacoCycle]->setX(rand() % volcano->getW() + volcano->getX());
		taco[tacoCycle]->setY(volcano->getY());
		tacoActive[tacoCycle] = true;
		tacoTimer = SDL_GetTicks();
		taco[tacoCycle]->setAngle(rand() % 360);
		tacoCycle++;
	}
	if (tacoCycle >= 72) { angry = false; }
	if (taco[71]->getY() < 0 && tacoCycle >= 72) { leaving = true; }
}

void CTacano::moveTacano()
{
	if (angry) { volcano->setFrame(1); volcano->setShake(25); }
	if (!angry) { volcano->setFrame(0); }
	if (!leaving) { volcano->setY(volcano->getY() + (VolcanoDestY - (float)volcano->getY()) / 20); }
	if (volcano->getY() == VolcanoDestY && !angered) { angry = true; angered = true; }
	if (leaving) { volcano->setY(volcano->getY() + ((sdl_Setup->getScreenHeight + 20) - (float)volcano->getY()) / 10); }
	if (volcano->getY() > sdl_Setup->getScreenHeight && angered) { volcanoAlive = false; }

	for (int i = 0; i < 72; i++)
	{
			taco[i]->setY(taco[i]->getY() - 20);
			taco[i]->setAngle(taco[i]->getAngle() + 3);
	}
}

bool CTacano::getLife()
{
	return volcanoAlive;
}

int CTacano::getTacosAmount()
{
	return tacosAmount;
}

void CTacano::deactivateTaco(int tacoNumber)
{
	tacoActive[tacoNumber] = false;
}

bool CTacano::getTacoActive(int tacoNumber)
{
	return tacoActive[tacoNumber];
}

SDL_Rect CTacano::getTacoRect(int tacoNumber)
{
	return taco[tacoNumber]->getRect();
}

int CTacano::getTacoStrength()
{
	return tacoStrength;
}