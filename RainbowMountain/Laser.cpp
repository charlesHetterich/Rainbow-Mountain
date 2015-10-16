#include "stdafx.h"
#include "Laser.h"


CLaser::CLaser(CSDL_setup* csdl_setup)
{
	sdl_setup = csdl_setup;

	electricBall = new Csprites(sdl_setup->GetRenderer(), "images/guns/electricball.png", 0, 0, 0, 0, 1683, 1704);
	laser = new Csprites(sdl_setup->GetRenderer(), "images/guns/laser.png", 0, 0, 1800, 0, 1, 1);

	laserShotSound = new CMusic();

	
	electricBallFrameRate = 5;
	electricBallSpeed = 5;

	electricBallSpeedingUp = true;
	direction = 1;
	
	laserStrength = 1;
	laserKnockBack = 1;
}

CLaser::~CLaser(){}

void CLaser::shootLaser(int playerFacing)
{
	laser->setH(30);
	laser->setW(1800);
	laserShotSound->playSound(2);
	direction = playerFacing;
}

void CLaser::showLaser(double x, double y)
{
	destinationDiference = sqrt((electricBall->getX() - x) * (electricBall->getX() - x) + (electricBall->getY() - y) * (electricBall->getY() - y));

	if (destinationDiference != 0)
	{
		if (((electricBall->getX() - x) / destinationDiference) * electricBallSpeed < fabsf(electricBall->getX() - x))
		{
			electricBall->setX(electricBall->getX() - ((electricBall->getX() - x) / destinationDiference) * electricBallSpeed);
		}
		if (((electricBall->getY() - y) / destinationDiference) * electricBallSpeed < fabsf(electricBall->getY() - y))
		{
			electricBall->setY(electricBall->getY() - ((electricBall->getY() - y) / destinationDiference) * electricBallSpeed);
		}
	}

	if (electricBallFrameTime > electricBallFrameRate)
	{
		electricBall->setFrame(electricBall->getFrame() + 1);
		if (electricBall->getFrame() == 3) { electricBall->setFrame(0); electricBall->setFrameRow(electricBall->getFrameRow() + 1); }
		if (electricBall->getFrameRow() == 1) { electricBall->setFrameRow(0); }
		electricBallFrameTime = 0;
	}
	electricBallFrameTime++;

	if (laser->getH() > 0)
	{
		if (direction == 1)
		{
			laser->setH(laser->getH() - 2);

			laser->setX(electricBall->getX() + (electricBall->getW() / 2));
			laser->setY(electricBall->getY() + ((electricBall->getH() - laser->getH()) / 2));

			laser->drawReg(0, 0);
		}

		if (direction == 2)
		{
			laser->setH(laser->getH() - 2);

			laser->setX((electricBall->getX() + (electricBall->getW() / 2)) - laser->getW());
			laser->setY(electricBall->getY() + ((electricBall->getH() - laser->getH()) / 2));

			laser->drawReg(0, 0);
		}
	}
	else
	{
		laser->setW(NULL);
	}

	electricBall->drawReg(0, 0);
}

void CLaser::setStrength(int newStrength)
{
	laserStrength = newStrength;
}

int CLaser::getStrength()
{
	return laserStrength;
}

void CLaser::setKnockBack(int newKnockBack)
{
	laserKnockBack = newKnockBack;
}

int CLaser::getKnockBack()
{
	if (direction == 1) { return laserKnockBack; }
	if (direction == 2) { return -laserKnockBack; }
}