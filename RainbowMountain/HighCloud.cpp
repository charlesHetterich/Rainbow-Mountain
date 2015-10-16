#include "stdafx.h"
#include "HighCloud.h"


CHighCloud::CHighCloud(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;
	cloudSpeed = 10;
	highPower = 100;

	cloud = new Csprites(sdl_Setup->GetRenderer(), "images/highcloud.png", NULL, NULL, NULL, NULL, 369, 262);

	health = new CHealth(sdl_Setup, 200, NULL, NULL, NULL, NULL);
	health->setHealth(0);
}


CHighCloud::~CHighCloud()
{
	delete cloud;
	delete health;
}

void CHighCloud::spawnCloud()
{
	alive = true;
	cloud->setX(sdl_Setup->getScreenWidth + 100);
	cloud->setY(-200);
	cloud->setW(300);
	cloud->setH(180);
	cloud->setAngle(0);
	cloud->setFrame(0);
	
	SDL_SetTextureColorMod(cloud->getTexture(), 255, 255, 255);

	movementtimer = 0;
	health->setHealth(200);
}

void CHighCloud::showCloud()
{
	cloud->drawReg(0, 0);
}

void CHighCloud::moveCould(SDL_Rect playerRect)
{
	if (health->checkLife())
	{
		if (!inShock)
		{
			float playerCenterX = playerRect.x + playerRect.w / 2;
			float playerCenterY = playerRect.y + playerRect.h / 2;
			float cloudCenterX = cloud->getX() + cloud->getW() / 2;
			float cloudCenterY = cloud->getY() + cloud->getH() / 2;

			if (movementtimer * 5 % 180 == 0)
			{
			if (cloudCenterX - playerCenterX != 0) { angleTraveling = (180 / M_PI) * atan((cloudCenterY - playerCenterY) / (cloudCenterX - playerCenterX)); }
			//else  angleTraveling = (180 / M_PI) * atan((cloudCenterY - playerCenterY) / (cloudCenterX - playerCenterX)+0.01);
			if (cloudCenterY - playerCenterY <= 0 & cloudCenterX - playerCenterX >= 0) { angleTraveling = 180 + angleTraveling; }
			if (cloudCenterY - playerCenterY >= 0 & cloudCenterX - playerCenterX >= 0) { angleTraveling = 180 + angleTraveling; }
			if (cloudCenterY - playerCenterY >= 0 & cloudCenterX - playerCenterX <= 0) { angleTraveling = 360 + angleTraveling; }
			}

			movementtimer++;
			if (movementtimer * 5 % 180 == 0)
			{
				if (movementtimer * 5 % 360 == 0)
					directionToggle = 1;
				else
					directionToggle = -1;
			}

			cloud->setX(cloud->getX() + (SDL_cos(angleTraveling*(M_PI / 180))*cloudSpeed)*(directionToggle*SDL_sin((float)movementtimer * 5 * (M_PI / 180))));
			cloud->setY(cloud->getY() + (SDL_sin(angleTraveling*(M_PI / 180))*cloudSpeed)*(directionToggle*SDL_sin((float)movementtimer * 5 * (M_PI / 180))));

			float distance = sqrt((cloudCenterX - playerCenterX)*(cloudCenterX - playerCenterX) + (cloudCenterY - playerCenterY)*(cloudCenterY - playerCenterY));
			if (distance / 3 < highPower)
				cloud->setHigh(highPower - (distance / 3));
		}
		else
		{
			hurtTimer++;

			if (knockBack > 0)
				knockBack--;
			if (knockBack < 0)
				knockBack++;

			cloud->setX(cloud->getX() + knockBack);

			if (hurtTimer > 15)
			{
				cloud->setFrame(0);
				inShock = false;
				hurtTimer = 0;
			}
		}
	}
	else
	{
		fallingAngle += 10;
		deadFallingSpeed += 0.5;
		cloud->setY(cloud->getY() + deadFallingSpeed);
		cloud->setX(cloud->getX() + deadPushBackSpeed);
		cloud->setAngle(fallingAngle);
	}
}

SDL_Rect CHighCloud::getCloudRect()
{
	return cloud->getRect();
}

bool CHighCloud::getAlive()
{
	return alive;
}

CHealth* CHighCloud::getHealth()
{
	return health;
}

void CHighCloud::hurtCloud(int damage, int KnockBack)
{
	health->takeDamage(damage);

	if (health->checkLife())
	{
		knockBack = KnockBack/2;
		inShock = true;
		cloud->setFrame(1);
	}
	else
	{
		deadFallingSpeed = -abs(KnockBack);
		deadPushBackSpeed = KnockBack / 10;
		SDL_SetTextureColorMod(cloud->getTexture(), 50, 50, 50);
		cloud->setFrame(1);
	}
}