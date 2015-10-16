#include "stdafx.h"
#include "Health.h"


CHealth::CHealth(CSDL_setup* sdl_setup, int maxHealth, int x, int y, int w, int h)
{
	csdl_setup = sdl_setup;
	health = maxHealth;
	
	healthBar_width = w;
	healthBar_height = h;
	healthBar_xPos = x - (w/2);
	healthBar_yPos = y;
	healthPicture_width = w - 4;
	healthPicture_height = h - 4;
	healthPicture_xPos = x + 2 - (w/2);
	healthPicture_yPos = y + 2;
	

	healthBar_image = "images/health/healthBar.png";
	healthPicture_image = "images/health/health.png";
	healthBall_image = "images/health/healthBall.png";

	healthBar = new Csprites(csdl_setup->GetRenderer(), healthBar_image, healthBar_xPos, healthBar_yPos, healthBar_width, healthBar_height, 400, 80);
	healthPicture = new Csprites(csdl_setup->GetRenderer(), healthPicture_image, healthPicture_xPos, healthPicture_yPos, healthPicture_width, healthPicture_height, 1, 1);

	healthBallsAmount = 100;

	while (currentHealthBall < healthBallsAmount - 1)
	{
		healthBall[currentHealthBall] = new Csprites(csdl_setup->GetRenderer(), healthBall_image, 0, 0, 10, 10, 96, 96);
		currentHealthBall++;
	}
	currentHealthBall = 0;
}


CHealth::~CHealth()
{
	delete healthBall;
	delete healthBar;
	delete healthPicture;
}

void CHealth::showHealth()
{
	//healthBar->drawReg(0, 0);
	//healthPicture->drawReg(0, 0);
	SDL_RenderCopy(csdl_setup->GetRenderer(), healthBar->getTexture(), NULL, &healthBar->getRect());
	SDL_RenderCopy(csdl_setup->GetRenderer(), healthPicture->getTexture(), NULL, &healthPicture->getRect());
	if (healthPicture->getW() > healthPicture_width* (health / 100))
	{
		healthPicture->setW(healthPicture->getW() - 4);
	}
	else if ((healthPicture_width* (health / 100)) - (healthPicture->getW()) > 2)
	{
		healthPicture->setW(healthPicture->getW() + 2);
	}
}

void CHealth::takeDamage(int damage)
{
	health -= damage;
}

void CHealth::heal(int healAmount)
{
	health += healAmount;
}

bool CHealth::checkLife()
{
	if (health > 0)
	{
		return true;
	}
	if (health <= 0)
	{
		return false;
	}
}

void CHealth::updatePosition(int x, int y)
{
	healthBar->setX(x - (healthBar_width / 2));
	healthBar->setY(y);
	healthPicture->setX(x - (healthPicture_width / 2));
	healthPicture->setY(y + 2);
}

int CHealth::getHealth()
{
	return health;
}

void CHealth::setHealth(int newHealth)
{
	health = newHealth;
	healthPicture->setW(healthPicture_width* (health / 100));
}

void CHealth::createHealthBalls(int amount, int creationX, int creationY, int destinationX, int destinationY)
{
	while (currentHealthBall < amount)
	{
		healthBall[currentHealthBall]->setX(creationX);
		healthBall[currentHealthBall]->setY(creationY);
		healthBallSpeed[currentHealthBall] = 4;
		healthBallVerticalDestiny[currentHealthBall] = creationX + (rand() % 200 - 100);
		healthBallVerticalDestiny[currentHealthBall] = creationY + (rand() % 200 - 100);
		showHealthBall[currentHealthBall] = true;
		currentHealthBall++;
	}
	currentHealthBall = 0;
}

void CHealth::genHealthBalls(SDL_Rect destination)
{
	while (currentHealthBall < healthBallsAmount - 1)
	{
		if (showHealthBall[currentHealthBall] == true)
		{
			healthBall[currentHealthBall]->drawReg(0, 0);

			if (healthBallSpeed[currentHealthBall] > 0)
			{
				//healthBall[currentHealthBall]->setX(healthBall[currentHealthBall]->getX + (healthBallSpeed[currentHealthBall] * ()));
			}
		}
		
		currentHealthBall++;


	}
	currentHealthBall = 0;
}