#include "stdafx.h"
#include "Missle.h"


CMissle::CMissle(CSDL_setup* csdl_setup)
{
	sdl_setup = csdl_setup;

	while (currentMissle < 30)
	{
		missle[currentMissle] = new Csprites(sdl_setup->GetRenderer(), "images/guns/missle.png", 0, 0, 70, 45, 1547, 557);
		MissleShotSound[currentMissle] = new CMusic();
		missleExplosion[currentMissle] = new CExplosion(sdl_setup);
		
		currentMissle++;
	}
	currentMissle = 0;

	knockBack = 20;
	strength = 25;
}


CMissle::~CMissle()
{
	delete missleExplosion;
	delete missle;
	delete MissleShotSound;
}

void CMissle::launchMissle(int x, int y, int direction)
{
	missleDirection[cycledMissleNumber] = direction;
	missle[cycledMissleNumber]->setX(x);
	missle[cycledMissleNumber]->setY(y);
	missleAlive[cycledMissleNumber] = true;
	MissleShotSound[cycledMissleNumber]->playSound(1);

	if (missleDirection[cycledMissleNumber] == 1) { missleSpeed[cycledMissleNumber] = 2; missle[cycledMissleNumber]->setFrame(0); }
	if (missleDirection[cycledMissleNumber] == 2) { missleSpeed[cycledMissleNumber] = -2; missle[cycledMissleNumber]->setFrame(1); }

	cycledMissleNumber++;
	if (cycledMissleNumber == 30) { cycledMissleNumber = 0; }
}

void CMissle::moveMissle()
{
	while (currentMissle < 30)
	{
		if (missleAlive[currentMissle] == true)
		{
			missle[currentMissle]->drawReg(0, 0);
			
			if (missleDirection[currentMissle] == 1)
			{
				missle[currentMissle]->setX(missle[currentMissle]->getX() + missleSpeed[currentMissle]);
				if (missleSpeed[currentMissle] <= 30) { missleSpeed[currentMissle] += 2; }
				if (missle[currentMissle]->getX() > 1600) { missleAlive[currentMissle] = false; }
			}
			if (missleDirection[currentMissle] == 2)
			{
				missle[currentMissle]->setX(missle[currentMissle]->getX() + missleSpeed[currentMissle]);
				if (missleSpeed[currentMissle] >= -30) { missleSpeed[currentMissle] -= 2; }
				if (missle[currentMissle]->getX() + missle[currentMissle]->getW() < 0) { missleAlive[currentMissle] = false; }
			}
			
		}
		else
		{
			missle[currentMissle]->setX(NULL);
			//missleExplosion[currentMissle]->showExplosion();
		}
		currentMissle++;
	}
	currentMissle = 0;
}

void CMissle::destroyMissle(int thisMissle)
{
	missleAlive[thisMissle] = false;
	//if (missleDirection[thisMissle] == 1) { missleExplosion[currentMissle]->explode(1, missle[thisMissle]->getX() + missle[thisMissle]->getW(), missle[thisMissle]->getY() + missle[thisMissle]->getH() / 2); }
	//if (missleDirection[thisMissle] == 2) { missleExplosion[currentMissle]->explode(1, missle[thisMissle]->getX(), missle[thisMissle]->getY() + missle[thisMissle]->getH() / 2); }
}

bool CMissle::checkLife(int thisMissle)
{
	return missleAlive[thisMissle];
}

int CMissle::getStrength()
{
	return strength;
}

void CMissle::setStrength(int newStrength)
{
	strength = newStrength;
}

int CMissle::getKnockBack(int thisMissle)
{
	if (missleDirection[thisMissle] == 1) { return knockBack; }
	if (missleDirection[thisMissle] == 2) { return -knockBack; }
}

void CMissle::setKnockBack(int newKnockBack)
{
	knockBack = newKnockBack;
}