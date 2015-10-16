#include "stdafx.h"
#include "Meteors.h"


CMeteors::CMeteors(CSDL_setup* sdl_setup, int xPos, int yPos)
{
	x = xPos;
	y = yPos;
	csdl_setup = sdl_setup;

	healthBarYDistance = 40;

	meteorFire[0] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[1] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[2] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[3] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[4] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[5] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[6] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[7] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[8] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[9] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);

	meteorIce[0] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[1] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[2] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[3] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[4] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[5] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[6] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[7] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[8] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[9] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);

	meteorFireSpeed[0] = 0;
	meteorFireSpeed[1] = 0;
	meteorFireSpeed[2] = 0;
	meteorFireSpeed[3] = 0;
	meteorFireSpeed[4] = 0;
	meteorFireSpeed[5] = 0;
	meteorFireSpeed[6] = 0;
	meteorFireSpeed[7] = 0;
	meteorFireSpeed[8] = 0;
	meteorFireSpeed[9] = 0;

	meteorIceSpeed[0] = 0;
	meteorIceSpeed[1] = 0;
	meteorIceSpeed[2] = 0;
	meteorIceSpeed[3] = 0;
	meteorIceSpeed[4] = 0;
	meteorIceSpeed[5] = 0;
	meteorIceSpeed[6] = 0;
	meteorIceSpeed[7] = 0;
	meteorIceSpeed[8] = 0;
	meteorIceSpeed[9] = 0;

	meteorFireHealth[0] = new CHealth(csdl_setup, 1, meteorFire[0]->image->getX() + (meteorFire[0]->image->getW() / 2), meteorFire[0]->image->getY() - healthBarYDistance, 150, 30);
	meteorFireHealth[1] = new CHealth(csdl_setup, 1, meteorFire[1]->image->getX() + (meteorFire[1]->image->getW() / 2), meteorFire[1]->image->getY() - healthBarYDistance, 150, 30);
	meteorFireHealth[2] = new CHealth(csdl_setup, 1, meteorFire[2]->image->getX() + (meteorFire[2]->image->getW() / 2), meteorFire[2]->image->getY() - healthBarYDistance, 150, 30);
	meteorFireHealth[3] = new CHealth(csdl_setup, 1, meteorFire[3]->image->getX() + (meteorFire[3]->image->getW() / 2), meteorFire[3]->image->getY() - healthBarYDistance, 150, 30);
	meteorFireHealth[4] = new CHealth(csdl_setup, 1, meteorFire[4]->image->getX() + (meteorFire[4]->image->getW() / 2), meteorFire[4]->image->getY() - healthBarYDistance, 150, 30);
	meteorFireHealth[5] = new CHealth(csdl_setup, 1, meteorFire[5]->image->getX() + (meteorFire[5]->image->getW() / 2), meteorFire[5]->image->getY() - healthBarYDistance, 150, 30);
	meteorFireHealth[6] = new CHealth(csdl_setup, 1, meteorFire[6]->image->getX() + (meteorFire[6]->image->getW() / 2), meteorFire[6]->image->getY() - healthBarYDistance, 150, 30);
	meteorFireHealth[7] = new CHealth(csdl_setup, 1, meteorFire[7]->image->getX() + (meteorFire[7]->image->getW() / 2), meteorFire[7]->image->getY() - healthBarYDistance, 150, 30);
	meteorFireHealth[8] = new CHealth(csdl_setup, 1, meteorFire[8]->image->getX() + (meteorFire[8]->image->getW() / 2), meteorFire[8]->image->getY() - healthBarYDistance, 150, 30);
	meteorFireHealth[9] = new CHealth(csdl_setup, 1, meteorFire[9]->image->getX() + (meteorFire[9]->image->getW() / 2), meteorFire[9]->image->getY() - healthBarYDistance, 150, 30);

	meteorIceHealth[0] = new CHealth(csdl_setup, 1, meteorIce[0]->image->getX() + (meteorIce[0]->image->getW() / 2), meteorIce[0]->image->getY() - healthBarYDistance, 150, 30);
	meteorIceHealth[1] = new CHealth(csdl_setup, 1, meteorIce[1]->image->getX() + (meteorIce[1]->image->getW() / 2), meteorIce[1]->image->getY() - healthBarYDistance, 150, 30);
	meteorIceHealth[2] = new CHealth(csdl_setup, 1, meteorIce[2]->image->getX() + (meteorIce[2]->image->getW() / 2), meteorIce[2]->image->getY() - healthBarYDistance, 150, 30);
	meteorIceHealth[3] = new CHealth(csdl_setup, 1, meteorIce[3]->image->getX() + (meteorIce[3]->image->getW() / 2), meteorIce[3]->image->getY() - healthBarYDistance, 150, 30);
	meteorIceHealth[4] = new CHealth(csdl_setup, 1, meteorIce[4]->image->getX() + (meteorIce[4]->image->getW() / 2), meteorIce[4]->image->getY() - healthBarYDistance, 150, 30);
	meteorIceHealth[5] = new CHealth(csdl_setup, 1, meteorIce[5]->image->getX() + (meteorIce[5]->image->getW() / 2), meteorIce[5]->image->getY() - healthBarYDistance, 150, 30);
	meteorIceHealth[6] = new CHealth(csdl_setup, 1, meteorIce[6]->image->getX() + (meteorIce[6]->image->getW() / 2), meteorIce[6]->image->getY() - healthBarYDistance, 150, 30);
	meteorIceHealth[7] = new CHealth(csdl_setup, 1, meteorIce[7]->image->getX() + (meteorIce[7]->image->getW() / 2), meteorIce[7]->image->getY() - healthBarYDistance, 150, 30);
	meteorIceHealth[8] = new CHealth(csdl_setup, 1, meteorIce[8]->image->getX() + (meteorIce[8]->image->getW() / 2), meteorIce[8]->image->getY() - healthBarYDistance, 150, 30);
	meteorIceHealth[9] = new CHealth(csdl_setup, 1, meteorIce[9]->image->getX() + (meteorIce[9]->image->getW() / 2), meteorIce[9]->image->getY() - healthBarYDistance, 150, 30);

	currentFire = 0;
	currentIce = 0;

	currentGenFire = 0;
	currentGenIce = 0;

	currentCheckHitFire = 0;
	currentCheckHitIce = 0;

	collision = new CCollision();

	mouseClicked = false;
}


CMeteors::~CMeteors()
{
	delete meteorFire;
	delete meteorIce;

	delete meteorFireHealth;
	delete meteorIceHealth;

	delete collision;
}

void CMeteors::shower(std::string meteorType)
{
	
	if (rand() % 1000 + 1 <= 5)
	{
		if (meteorType == "Fire")
		{
			meteorFire[currentFire]->image->setW(rand() % 50 + 100);
			meteorFire[currentFire]->image->setH(meteorFire[currentFire]->image->getW());
			meteorFire[currentFire]->image->setX(rand() % 1500);
			meteorFire[currentFire]->image->setY(-(meteorFire[currentFire]->image->getH()));

			meteorFireSpeed[currentFire] = rand() % 4 + 2;
			showMeteorFire[currentFire] = true;
			meteorFireHealth[currentFire]->setHealth(1);

			currentFire++;
			if (currentFire == 10)
			{
				currentFire = 0;
			}
		}

		if (meteorType == "Ice")
		{
			meteorIce[currentIce]->image->setW(rand() % 50 + 100);
			meteorIce[currentIce]->image->setH(meteorIce[currentIce]->image->getW());
			meteorIce[currentIce]->image->setX(rand() % 1500);
			meteorIce[currentIce]->image->setY(-(meteorIce[currentIce]->image->getH()));

			meteorIceSpeed[currentIce] = rand() % 4 + 2;

			meteorIceHealth[currentIce]->setHealth(100);

			currentIce++;
			if (currentIce == 10)
			{
				currentIce = 0;
			}
		}
	}
}

void CMeteors::meteorFall()
{
	meteorFire[0]->image->setY(meteorFire[0]->image->getY() + meteorFireSpeed[0]);
	meteorFire[1]->image->setY(meteorFire[1]->image->getY() + meteorFireSpeed[1]);
	meteorFire[2]->image->setY(meteorFire[2]->image->getY() + meteorFireSpeed[2]);
	meteorFire[3]->image->setY(meteorFire[3]->image->getY() + meteorFireSpeed[3]);
	meteorFire[4]->image->setY(meteorFire[4]->image->getY() + meteorFireSpeed[4]);
	meteorFire[5]->image->setY(meteorFire[5]->image->getY() + meteorFireSpeed[5]);
	meteorFire[6]->image->setY(meteorFire[6]->image->getY() + meteorFireSpeed[6]);
	meteorFire[7]->image->setY(meteorFire[7]->image->getY() + meteorFireSpeed[7]);
	meteorFire[8]->image->setY(meteorFire[8]->image->getY() + meteorFireSpeed[8]);
	meteorFire[9]->image->setY(meteorFire[9]->image->getY() + meteorFireSpeed[9]);

	meteorIce[0]->image->setY(meteorIce[0]->image->getY() + meteorIceSpeed[0]);
	meteorIce[1]->image->setY(meteorIce[1]->image->getY() + meteorIceSpeed[1]);
	meteorIce[2]->image->setY(meteorIce[2]->image->getY() + meteorIceSpeed[2]);
	meteorIce[3]->image->setY(meteorIce[3]->image->getY() + meteorIceSpeed[3]);
	meteorIce[4]->image->setY(meteorIce[4]->image->getY() + meteorIceSpeed[4]);
	meteorIce[5]->image->setY(meteorIce[5]->image->getY() + meteorIceSpeed[5]);
	meteorIce[6]->image->setY(meteorIce[6]->image->getY() + meteorIceSpeed[6]);
	meteorIce[7]->image->setY(meteorIce[7]->image->getY() + meteorIceSpeed[7]);
	meteorIce[8]->image->setY(meteorIce[8]->image->getY() + meteorIceSpeed[8]);
	meteorIce[9]->image->setY(meteorIce[9]->image->getY() + meteorIceSpeed[9]);
}

bool CMeteors::genMeteors(SDL_Rect rect1)
{
	collision->resetCollisionTruth();
	while (currentGenFire < 9)
	{
		if (showMeteorFire[currentGenFire] == true)
		{
			if (meteorFireHealth[currentGenFire]->checkLife())
			{
				meteorFire[currentGenFire]->genBlock();
				meteorFireHealth[currentGenFire]->updatePosition(meteorFire[currentGenFire]->image->getX() + (meteorFire[currentGenFire]->image->getW() / 2), meteorFire[currentGenFire]->image->getY() - healthBarYDistance);
				collision->checkCollisionState(rect1, meteorFire[currentGenFire]->image->getRect());
			}
			else if (!meteorFireHealth[currentGenFire]->checkLife())
			{
				meteorFire[currentGenFire]->genBlock();
				meteorFire[currentGenFire]->image->setFrame(1);
				meteorFire[currentGenFire]->image->setAplpha(meteorFire[currentGenFire]->image->getAlpha() - 4);
				if (meteorFire[currentGenFire]->image->getAlpha() - 4 < 0)
				{
					while (meteorFire[currentGenFire]->image->getAlpha() > 0)
					{
						meteorFire[currentGenFire]->image->setAplpha(meteorFire[currentGenFire]->image->getAlpha() - 1);
					}
					showMeteorFire[currentGenFire] = false;
					meteorFire[currentGenFire]->image->setAplpha(255);
					meteorFire[currentGenFire]->image->setFrame(0);
				}
			}
		}

		currentGenFire++;
	}

	while (currentGenIce < 9)
	{
		if (showMeteorIce[currentGenIce] == true)
		{
			if (meteorIceHealth[currentGenIce]->checkLife())
			{
				meteorIce[currentGenIce]->genBlock();
				meteorIceHealth[currentGenIce]->updatePosition(meteorIce[currentGenIce]->image->getX() + (meteorIce[currentGenIce]->image->getW() / 2), meteorIce[currentGenIce]->image->getY() - healthBarYDistance);
				collision->checkCollisionState(rect1, meteorIce[currentGenIce]->image->getRect());
			}

			else if (!meteorIceHealth[currentGenIce]->checkLife())
			{
				meteorIce[currentGenIce]->genBlock();
				meteorIce[currentGenIce]->image->setImage("images/meteors/meteorBroken_ice.png");
				meteorIce[currentGenIce]->image->setAplpha(meteorIce[currentGenIce]->image->getAlpha() - 4);
				if (meteorIce[currentGenIce]->image->getAlpha() - 4 < 0)
				{
					while (meteorIce[currentGenIce]->image->getAlpha() > 0)
					{
						meteorIce[currentGenIce]->image->setAplpha(meteorIce[currentGenIce]->image->getAlpha() - 1);
					}
					showMeteorIce[currentGenIce] = false;
					meteorIce[currentGenIce]->image->setAplpha(255);
					meteorIce[currentGenIce]->image->setImage("images/meteors/meteor_iceplain.png");
				}
			}
		}
		currentGenIce++;
	}
	currentGenFire = 0;
	currentGenIce = 0;
	if (lastHitMeteorType == "fire" && meteorFireHealth[lastHitMeteor]->checkLife()){ meteorFireHealth[lastHitMeteor]->showHealth(); }
	if (lastHitMeteorType == "ice" && meteorIceHealth[lastHitMeteor]->checkLife()) { meteorIceHealth[lastHitMeteor]->showHealth(); }
	return collision->collisionState[4];
}

void CMeteors::meteorsReset()
{
	meteorFire[0] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[1] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[2] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[3] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[4] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[5] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[6] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[7] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[8] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);
	meteorFire[9] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor.png", 80, 80);

	meteorIce[0] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[1] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[2] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[3] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[4] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[5] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[6] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[7] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[8] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);
	meteorIce[9] = new CBlock(csdl_setup, x, y, 0, 0, "images/meteors/meteor_iceplain.png", 80, 80);

	meteorFireSpeed[0] = 0;
	meteorFireSpeed[1] = 0;
	meteorFireSpeed[2] = 0;
	meteorFireSpeed[3] = 0;
	meteorFireSpeed[4] = 0;
	meteorFireSpeed[5] = 0;
	meteorFireSpeed[6] = 0;
	meteorFireSpeed[7] = 0;
	meteorFireSpeed[8] = 0;
	meteorFireSpeed[9] = 0;

	meteorIceSpeed[0] = 0;
	meteorIceSpeed[1] = 0;
	meteorIceSpeed[2] = 0;
	meteorIceSpeed[3] = 0;
	meteorIceSpeed[4] = 0;
	meteorIceSpeed[5] = 0;
	meteorIceSpeed[6] = 0;
	meteorIceSpeed[7] = 0;
	meteorIceSpeed[8] = 0;
	meteorIceSpeed[9] = 0;
	
	currentFire = 0;
	currentIce = 0;
}

int CMeteors::mouseHitMeteor(CMouse* mouse)
{
	amountMeteorsDestroyed = 0;
	if (mouse->mouseLeftClick() && mouseClicked == false)
	{
		mouseClicked = true;
		while (currentCheckHitFire < 9)
		{
			if (collision->checkMouseCollision(mouse->mouseX, mouse->mouseY, meteorFire[currentCheckHitFire]->image->getRect()) && meteorFireHealth[currentCheckHitFire]->checkLife())
			{
				meteorFireHealth[currentCheckHitFire]->takeDamage(20);
				if (meteorFireHealth[currentCheckHitFire]->getHealth() <= 0)
				{
					amountMeteorsDestroyed++;
				}
				lastHitMeteor = currentCheckHitFire;
				lastHitMeteorType = "fire";
			}
			currentCheckHitFire++;
		}

		while (currentCheckHitIce < 9)
		{
			if (collision->checkMouseCollision(mouse->mouseX, mouse->mouseY, meteorIce[currentCheckHitIce]->image->getRect()) && meteorIceHealth[currentCheckHitIce]->checkLife())
			{
				meteorIceHealth[currentCheckHitIce]->takeDamage(20);
				if (meteorIceHealth[currentCheckHitIce]->getHealth() <= 0)
				{
					amountMeteorsDestroyed++;
				}
				lastHitMeteor = currentCheckHitIce;
				lastHitMeteorType = "ice";
			}
			currentCheckHitIce++;
		}
		currentCheckHitFire = 0;
		currentCheckHitIce = 0;
	}
	else if (mouse->mouseLeftClick() == false)
	{
		mouseClicked = false;
	}
	return amountMeteorsDestroyed;
}