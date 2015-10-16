#include "stdafx.h"
#include "Events.h"


CEvents::CEvents(CSDL_setup* csdl_setup)
{
	sdl_setup = csdl_setup;
	
	//screen color shades
	levelColor[0] = new Csprites(csdl_setup->GetRenderer(), "images/blocks/block1.png", 0, 0, sdl_setup->getScreenWidth, sdl_setup->getScreenHeight, 1, 1);
	levelColor[0]->setAplpha(100);
	levelColor[1] = new Csprites(csdl_setup->GetRenderer(), "images/blocks/block2.png", 0, 0, sdl_setup->getScreenWidth, sdl_setup->getScreenHeight,1 , 1);
	levelColor[1]->setAplpha(0);
	levelChangeTime = 1;
	colorChangeSpeed = 10;

	whiteFlash = new Csprites(sdl_setup->GetRenderer(), "images/white_block.png", 0, 0, sdl_setup->getScreenWidth, sdl_setup->getScreenHeight, 1, 1);
	speedUpTimer = 0;
	fade = 255;
	currentMeteorShower = false;

	levelTime = SDL_GetTicks();
}

CEvents::~CEvents()
{
	delete levelColor;
	delete sdl_setup;
	delete whiteFlash;
}

int CEvents::speedUp()
{
	speedUpTimer++;
	if (speedUpTimer == 20) //this says how often the program speeds up the speed of the blocks
	{
		speedUpTimer = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

bool CEvents::deathFlash()
{
	if (fade > 0)
	{
		whiteFlash->drawReg(0, 0);
		whiteFlash->setAplpha(fade);
		fade-=6;
		return true;
	}
	else
	{
		fade = 255;
		return false;
	}
}

void CEvents::meteorShower()
{
	int randomNumber = ((rand() / 32767.0) * 100) + 1;
	
	if (randomNumber <= 5 && currentMeteorShower == false)
	{
		//meteors->shower();
	}
}

void CEvents::Levels()
{
	if (SDL_GetTicks() >= levelTime + levelChangeTime)
	{
		changingLevels = true;
		levelTime = SDL_GetTicks();
	}
	
	if (changingLevels == true)
	{
		if (currentProminentLevel == 0)
		{
			levelColor[0]->setAplpha(levelColor[0]->getAlpha() - colorChangeSpeed);
			levelColor[1]->setAplpha(levelColor[1]->getAlpha() + colorChangeSpeed);
			if (levelColor[0]->getAlpha() <= 0)
			{
				bool colorIsChanged = false;
				changingLevels = false;
				currentProminentLevel = 1;
				if (levelColor[0]->getImage() == "images/blocks/block1.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block3.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block2.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block4.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block3.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block5.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block4.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block6.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block5.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block7.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block6.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block8.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block7.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block9.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block8.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block10.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block9.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block11.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block10.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block12.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block11.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block13.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block12.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block14.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block13.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block15.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block14.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block16.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block15.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block1.png"); colorIsChanged = true; }
				else if (levelColor[0]->getImage() == "images/blocks/block16.png" && colorIsChanged == false) { levelColor[0]->setImage("images/blocks/block2.png"); colorIsChanged = true; }
				levelColor[0]->setAplpha(0);
			}
		}
		else
		{
			levelColor[1]->setAplpha(levelColor[1]->getAlpha() - colorChangeSpeed);
			levelColor[0]->setAplpha(levelColor[0]->getAlpha() + colorChangeSpeed);
			if (levelColor[1]->getAlpha() <= 0)
			{
				bool colorIsChanged = false;
				changingLevels = false;
				currentProminentLevel = 0;
				if (levelColor[1]->getImage() == "images/blocks/block1.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block3.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block2.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block4.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block3.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block5.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block4.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block6.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block5.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block7.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block6.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block8.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block7.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block9.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block8.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block10.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block9.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block11.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block10.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block12.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block11.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block13.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block12.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block14.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block13.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block15.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block14.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block16.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block15.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block1.png"); colorIsChanged = true; }
				else if (levelColor[1]->getImage() == "images/blocks/block16.png" && colorIsChanged == false) { levelColor[1]->setImage("images/blocks/block2.png"); colorIsChanged = true; }
				levelColor[1]->setAplpha(0);
			}
		}
	}
	levelColor[0]->drawReg(0, 0);
	levelColor[1]->drawReg(0, 0);
}

CExplosion::CExplosion(CSDL_setup* csdl_setup)
{
	sdl_setup = csdl_setup;
	maxGrayPuffs = 20;
	maxYellowFire = 5;
	maxOrangeFire = 5;
	maxGrayCoverUps = 10;
	maxWiteSparks = 20;


	while (currentExplosionPart < maxGrayPuffs)
	{
		grayPuff[currentExplosionPart] = new Csprites(sdl_setup->GetRenderer(), "images/guns/explosionColors.png", NULL, NULL, NULL, NULL, 100, 106);
		if (currentExplosionPart % 2 == 0) { grayPuff[currentExplosionPart]->setFrame(3); }
		if (currentExplosionPart % 10 == 0) { grayPuff[currentExplosionPart]->setFrame(1); }
		//grayPuff[currentExplosionPart]->setAplpha(100);
		currentExplosionPart++;
	}
	currentExplosionPart = 0;
}

CExplosion::~CExplosion()
{
	delete grayPuff;
}

void CExplosion::explode(float Size, int x, int y)
{
	size = Size;
	while (currentExplosionPart < maxGrayPuffs)
	{
		X[currentExplosionPart] = x;
		Y[currentExplosionPart] = y;
		W[currentExplosionPart] = 60 * size;
		H[currentExplosionPart] = 60 * size;

		//grayPuff[currentExplosionPart]->setX(x);
		//grayPuff[currentExplosionPart]->setY(y);
		//grayPuff[currentExplosionPart]->setW(30 * size);
		//grayPuff[currentExplosionPart]->setH(30 * size);
		explosionHSpeed[currentExplosionPart] = ((rand() % 20000 + -10000) * size)/1000;
		explosionVSpeed[currentExplosionPart] = ((rand() % 20000 + -10000) * size)/1000;
		//if (explosionHSpeed[currentExplosionPart] > 0) { explosionVSpeed[currentExplosionPart] = 10 - explosionHSpeed[currentExplosionPart]; }
		//if (explosionHSpeed[currentExplosionPart] < 0) { explosionVSpeed[currentExplosionPart] = -10 - explosionHSpeed[currentExplosionPart]; }
		currentExplosionPart++;
	}
	currentExplosionPart = 0;
}

void CExplosion::showExplosion()
{
	/*
	while (currentExplosionPart < maxGrayPuffs)
	{
		X[currentExplosionPart] += explosionHSpeed[currentExplosionPart];
		Y[currentExplosionPart] += explosionVSpeed[currentExplosionPart];
		if (explosionHSpeed[currentExplosionPart] > 0) { explosionHSpeed[currentExplosionPart] -= 1 * size; }
		else if (explosionHSpeed[currentExplosionPart] < 0) { explosionHSpeed[currentExplosionPart] += 1 * size; }
		if (explosionVSpeed[currentExplosionPart] > 0) { explosionVSpeed[currentExplosionPart] -= 1 * size; }
		else if (explosionVSpeed[currentExplosionPart] < 0) { explosionVSpeed[currentExplosionPart] += 1 * size; }

		if (explosionHSpeed[currentExplosionPart] < 1 && explosionHSpeed[currentExplosionPart] > -1)
		{
			X[currentExplosionPart] += (2 * size) / 2;
			Y[currentExplosionPart] -= 1 * size;
			W[currentExplosionPart] -= 3 * size;
			H[currentExplosionPart] -= 3 * size;
		//grayPuff[currentExplosionPart]->setW(grayPuff[currentExplosionPart]->getW() - 1 * size);
		//grayPuff[currentExplosionPart]->setH(grayPuff[currentExplosionPart]->getH() - 1 * size);
		//grayPuff[currentExplosionPart]->setY(grayPuff[currentExplosionPart]->getY() - 1 * size);
		//grayPuff[currentExplosionPart]->setX(grayPuff[currentExplosionPart]->getX() + (1 * size)/2);
		//grayPuff[currentExplosionPart]->setAplpha(grayPuff[currentExplosionPart]->getAlpha() - 3);
		}
		
		grayPuff[currentExplosionPart]->setX(X[currentExplosionPart]);
		grayPuff[currentExplosionPart]->setY(Y[currentExplosionPart]);
		grayPuff[currentExplosionPart]->setW(W[currentExplosionPart]);
		grayPuff[currentExplosionPart]->setH(H[currentExplosionPart]);
		grayPuff[currentExplosionPart]->drawReg(0, 0);

		currentExplosionPart++;
	}
	currentExplosionPart = 0;
	*/
}