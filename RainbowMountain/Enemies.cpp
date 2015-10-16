#include "stdafx.h"
#include "Enemies.h"


CEnemies::CEnemies(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;

	//hell boy
	amountHellBoys = 5;

	while (currentHellBoy < amountHellBoys)
	{
		hellBoy[currentHellBoy] = new CHellBoy(sdl_Setup);
		currentHellBoy++;
	}
	currentHellBoy = 0;

	//tacano
	tacano = new CTacano(sdl_Setup);

	//high cloud
	highCloud = new CHighCloud(sdl_Setup);

	//fat boy
	fatBoysAmount = 1;
	for (int i = 0; i < fatBoysAmount; i++)
	{
		fatBoy[i] = new CFatBoy(sdl_Setup);
	}
}


CEnemies::~CEnemies()
{
	delete hellBoy;
	delete tacano;
	delete highCloud;
	delete fatBoy;
}

void CEnemies::spawnEnemies()
{
	//hell boy
	while (currentHellBoy < amountHellBoys)
	{
		if (rand() % 10000 + 1 <= 5 && !hellBoy[currentHellBoy]->health->checkLife() && hellBoy[currentHellBoy]->boy->getRect().y > sdl_Setup->getScreenHeight)
		{
			hellBoy[currentHellBoy]->spawn();
		}
		 currentHellBoy++;
	}
	currentHellBoy = 0;

	//tacano
	if (rand() % 2000 + 1 <= 5 && !tacano->getLife())
	{
		tacano->spawn();
	}

	//high cloud
	if (rand() % 2000 + 1 <= 5 && !highCloud->getHealth()->checkLife() && highCloud->getCloudRect().y > sdl_Setup->getScreenHeight)
	{
		highCloud->spawnCloud();
	}

	//fat boy
	for (int i = 0; i < fatBoysAmount; i++)
	{
		if (!fatBoy[i]->getAlive())
			fatBoy[i]->spawn();
	}
}

void CEnemies::loadEnemies(SDL_Rect playerRect)
{
	//evil boy
	while (currentHellBoy < amountHellBoys)
	{
		hellBoy[currentHellBoy]->moveAround(playerRect);
		currentHellBoy++;
	}
	currentHellBoy = 0;

	//tacano
	tacano->moveTacano();
	tacano->show();
	tacano->shootTaco();

	//high cloud
	highCloud->moveCould(playerRect);
	highCloud->showCloud();

	//fat boy
	for (int i = 0; i < fatBoysAmount; i++)
	{
		fatBoy[i]->grow();
		fatBoy[i]->move();
		fatBoy[i]->show();
	}
}