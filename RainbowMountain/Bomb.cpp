#include "stdafx.h"
#include "Bomb.h"


CBomb::CBomb(CSDL_setup* csdl_setup, int Size)
{
	sdl_Setup = csdl_setup;
	size = Size;
	bomb = new Csprites(sdl_Setup->GetRenderer(), "images/guns/bomb.png", NULL, NULL, NULL, NULL, 334, 306);
	redGlow = new Csprites(sdl_Setup->GetRenderer(), "images/guns/redGlow.png", NULL, NULL, size + 10, size + 10, 434, 434);
	redGlow->setAplpha(100);
	explosion = new CExplosion(sdl_Setup);
	explosionNoise = new CMusic();
	clickSpeed = 0;

	hurtingArea.w = size * 2;
	hurtingArea.h = size * 2;

	strength = 50;
	knockBack = 40;
}


CBomb::~CBomb()
{
	delete sdl_Setup;
	delete bomb;
	delete explosion;
	delete explosionNoise;
}

void CBomb::throwBomb(int x, int y, float HSpeed, float VSpeed)
{
	bomb->setX(x);
	bomb->setY(y);
	bomb->setW(size);
	bomb->setH(size);

	bombHSpeed = HSpeed;
	bombVSpeed = VSpeed;

	clicksLeft = 32;
	clickSpeed = 32;
	clickTime = 0;

	alive = true;
}

void CBomb::showBomb()
{
	bomb->setX(bomb->getX() + bombHSpeed);
	bomb->setY(bomb->getY() - bombVSpeed);
	bombVSpeed -= 0.4;

	if (clickSpeed != 0) { bomb->drawReg(0, 0); }

	clickTime++;

	redGlow->setX((bomb->getX() + bomb->getW() / 2) - redGlow->getW()/2);
	redGlow->setY((bomb->getY() + bomb->getH() / 2) - redGlow->getH() / 2);

	if (clickSpeed != 0)
	{
		if (clickTime >= clickSpeed / 2)
		{
			if (clickTime == clickSpeed / 2) { explosionNoise->playSound(3); }
			redGlow->drawReg(0, 0);
		}
	}

	hurtingArea.x = bomb->getX() - bomb->getW() / 2;
	hurtingArea.y = bomb->getY() - bomb->getH() / 2;
	hurting = false;
	if (clickTime == clickSpeed)
	{
		clickTime = 0;
		if (clickSpeed != 1) { clickSpeed = clickSpeed / 2; }
		if (clickSpeed == 1)
		{
			explosion->explode(2, bomb->getX() + bomb->getW() / 2, bomb->getY() + bomb->getH() / 2);
			alive = false;
			clickSpeed = 0;
			hurting = true;
		}
	}
	explosion->showExplosion();
}

void CBomb::setOffBomb()
{
	clickSpeed = 1;
	clickTime = 0;
}

bool CBomb::getLife()
{
	return alive;
}

bool CBomb::getHurting()
{
	return hurting;
}

SDL_Rect CBomb::getHurtingArea()
{
	return hurtingArea;
}

int CBomb::getStrength()
{
	return strength;
}

int CBomb::getKnockBack(SDL_Rect enemyRect)
{
	if ((bomb->getX() + bomb->getW() / 2) < (enemyRect.x + enemyRect.w / 2)){ return knockBack; }
	else { return -knockBack; }
}