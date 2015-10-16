#include "stdafx.h"
#include "HellBoy.h"


CHellBoy::CHellBoy(CSDL_setup* csdl_setup)
{
	sdl_setup = csdl_setup;
	amountOfBlood = 30;
	noises = new CMusic();

	boy = new Csprites(sdl_setup->GetRenderer(), "images/enemies/evilboy.png", NULL, NULL, NULL, NULL, 292, 501);
	hurtFlash = new Csprites(sdl_setup->GetRenderer(), "images/enemies/hurt_evilBoy.png", NULL, NULL, NULL, NULL, 292, 501);
	hurtFlash->setAplpha(0);

	while (currentBlood < amountOfBlood)
	{
		blood[currentBlood] = new Csprites(sdl_setup->GetRenderer(), "images/enemies/bloodanimation.png", NULL, NULL, NULL, NULL, 313, 295);
		blood[currentBlood]->setAplpha(200);
		currentBlood++;
	}
	currentBlood = 0;

	boySpeed = 4;
	bloodFireRate = 5;

	health = new CHealth(sdl_setup, 100, 0, 0, 0, 0);
	health->setHealth(0);
}


CHellBoy::~CHellBoy()
{
	delete boy;
	delete blood;
	delete health;
}

void CHellBoy::spawn()
{
	boy->setX(1800);
	boy->setY(-200);
	boy->setW(120);
	boy->setH(200);
	boy->setAngle(0);
	hurtFlash->setW(120);
	hurtFlash->setH(200);
	health->setHealth(100);
	SDL_SetTextureColorMod(boy->getTexture(), 255, 255, 255);

	while (currentBlood < amountOfBlood)
	{
		blood[currentBlood]->setW(25);
		blood[currentBlood]->setH(25);
		currentBlood++;
	}
	currentBlood = 0;
}

void CHellBoy::moveAround(SDL_Rect playerRect)
{
	if (hurtFlash->getAlpha() <= 0)
	{
		if (!attacking && health->checkLife())
		{
			int x = playerRect.x;
			int y = playerRect.y - (playerRect.h);

			destinationDistance = sqrt((boy->getX() - x) * (boy->getX() - x) + (boy->getY() - y) * (boy->getY() - y));

			if (destinationDistance != 0)
			{
				if (((boy->getX() - x) / destinationDistance) * boySpeed < fabsf(boy->getX() - x))
				{
					boyLocationX = boy->getX() - ((boy->getX() - x) / destinationDistance) * boySpeed;
				}
				if (((boy->getY() - y) / destinationDistance) * boySpeed < fabsf(boy->getY() - y))
				{
					boyLocationY = boy->getY() - ((boy->getY() - y) / destinationDistance) * boySpeed;
				}
			}

			boy->setX(boyLocationX);
			boy->setY(boyLocationY);

			if (((boy->getX() - x) / destinationDistance) * boySpeed < 0)
			{
				boy->setFrameRow(1);
				boyFacing = 0;
			}
			else
			{
				boy->setFrameRow(0);
				boyFacing = 1;
			}

			if (destinationDistance < 200)
			{
				boy->setFrame(1);
				attacking = true;
			}
			else
			{
				boy->setFrame(0);
			}
		}

		//firing blood
		if (attacking)
		{
			if (bloodReloading > bloodFireRate)
			{
				blood[bloodCycle]->setFrame(0);
				bloodHit[bloodCycle] = false;
				blood[bloodCycle]->setX(boy->getX() + 50);
				blood[bloodCycle]->setY(boy->getY() + 110);
				bloodVSpeed[bloodCycle] = rand() % 3 + 1;
				if (boyFacing == 0){ bloodHSpeed[bloodCycle] = rand() % 3 + 1; }
				else { bloodHSpeed[bloodCycle] = -(rand() % 3 + 1); }
				bloodReloading = 0;
				bloodCycle++;
			}
			bloodReloading++;
			if (bloodCycle == amountOfBlood)
			{
				attacking = false;
				bloodCycle = 0;
			}
		}
	}
	else if (health->checkLife())
	{
		if (hurtFlash->getAlpha() > 10) { hurtFlash->setAplpha(hurtFlash->getAlpha() - 10); }
		else { hurtFlash->setAplpha(0); }
		boy->setX(boy->getX() + boyFallBackSpeed);
		hurtFlash->setX(boy->getX());
		hurtFlash->setY(boy->getY());
		if (boyFallBackSpeed > 0) { boyFallBackSpeed -= 4; }
		if (boyFallBackSpeed < 0) { boyFallBackSpeed += 4; }
		if (abs(boyFallBackSpeed) < 4) {boyFallBackSpeed = 0;}
	}
	if(!health->checkLife())
	{
		fallingAngle += 10;
		fallingSpeed += 0.5;
		boy->setY(boy->getY() + fallingSpeed);
		boy->setX(boy->getX() + pushBackFallingSpeed);
		boy->setAngle(fallingAngle);

	}

		boy->drawReg(0, 0);
		hurtFlash->drawReg(0, 0);

		while (currentBlood < amountOfBlood)
		{
			if (bloodHit[currentBlood]) { blood[currentBlood]->setFrame(blood[currentBlood]->getFrame() + 1); }
			blood[currentBlood]->setX(blood[currentBlood]->getX() + bloodHSpeed[currentBlood]);
			blood[currentBlood]->setY(blood[currentBlood]->getY() - bloodVSpeed[currentBlood]);
			bloodVSpeed[currentBlood] -= 0.2;
			blood[currentBlood]->drawReg(0, 0);
			currentBlood++;
		}
		currentBlood = 0;
}

bool CHellBoy::getIfBoolHit(int thisBlood)
{
	return bloodHit[thisBlood];
}

void CHellBoy::setBloodHit(int thisBlood, bool hit)
{
	bloodHit[thisBlood] = hit;
}

void CHellBoy::dying()
{
	attacking = false;
	hurtFlash->setAplpha(0);
	boyFallBackSpeed = 0;
	bloodCycle = 0;
}

void CHellBoy::hurtHellBoy(int damageAmount, int knockBack)
{
	health->takeDamage(damageAmount);
	attacking = false;
	bloodCycle = 0;
	
	if (health->checkLife())
	{
		hurtFlash->setAplpha(255);
		boyFallBackSpeed = knockBack;
		if (boyFacing == 0) { hurtFlash->setFrameRow(1); }
		if (boyFacing == 1) { hurtFlash->setFrameRow(0); }
	}
	else
	{
		fallingSpeed = -abs(knockBack);
		pushBackFallingSpeed = knockBack/10;
		SDL_SetTextureColorMod(boy->getTexture(), 50, 50, 50);
	}
}