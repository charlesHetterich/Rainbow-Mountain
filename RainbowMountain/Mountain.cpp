#include "stdafx.h"
#include "Mountain.h"


CMountain::CMountain(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;
	floorHeight = 45;
	floorLevel = -1;
	floorSpeed = 6;

	floorChangeFrequency = 15;

	playerCollision = new CCollision();

	levelsAmount = 15;
	floorsPerLevelAmount = 10;
	ground = new Csprites(sdl_Setup->GetRenderer(), "images/white_block.png", 0, sdl_Setup->getScreenHeight - floorHeight, sdl_Setup->getScreenWidth, floorHeight, 1, 1);
	SDL_SetTextureColorMod(ground->getTexture(), 50, 123, 159);
	for (int i = 0; i < levelsAmount; i++)
	{
		for (int x = 0; x < floorsPerLevelAmount; x++)
		{
			floor[i][x] = new Csprites(sdl_Setup->GetRenderer(), "images/white_block.png", -2000, sdl_Setup->getScreenHeight - (floorHeight*(i+2)), 2000, floorHeight, 1, 1);
			if (i == 0)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 42, 146, 63);
			if (i == 1)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 216, 38, 38);
			if (i == 2)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 139, 26, 168);
			if (i == 3)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 71, 108, 212);
			if (i == 4)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 0, 255, 0);
			if (i == 5)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 240, 214, 208);
			if (i == 6)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 247, 186, 247);
			if (i == 7)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 40, 239, 212);
			if (i == 8)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 157, 230, 170);
			if (i == 9)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 255, 229, 204);
			if (i == 10)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 238, 203, 240);
			if (i == 11)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 178, 237, 243);
			if (i == 12)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 198, 243, 178);
			if (i == 13)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 255, 204, 204);
			if (i == 14)SDL_SetTextureColorMod(floor[i][x]->getTexture(), 255, 223, 251);
		}
	}
}


CMountain::~CMountain()
{
	delete floor;
	delete playerCollision;
	delete ground;
}

void CMountain::showFloor()
{
	ground->drawReg(0, 0);
	for (int i = 0; i < levelsAmount; i++)
	{
		for (int x = 0; x < floorsPerLevelAmount; x++)
		{
			floor[i][x]->drawReg(0, 0);
		}
	}
}

void CMountain::changeLevel()
{
	if (floorChangedLastTime + floorChangeFrequency*(6/(float)floorSpeed) < floorChangeTimer)
	{
		bool moveFloor = rand() % 2;

		if (moveFloor == true && floorLevel < levelsAmount - 1)
			floorLevel++;
		else if (floorLevel > -1)
			floorLevel--;

		floorCycle[floorLevel]++;
		if (floorCycle[floorLevel] == floorsPerLevelAmount) { floorCycle[floorLevel] = 0; }

		if (floorLevel != -1)
		{
			floor[floorLevel][floorCycle[floorLevel]]->setX(sdl_Setup->getScreenWidth);
			floor[floorLevel][floorCycle[floorLevel]]->setW(0);
		}

		floorChangedLastTime = floorChangeTimer;
	}
	floorChangeTimer++;
}

void CMountain::moveFloor()
{
	for (int i = 0; i < levelsAmount; i++)
	{
		for (int x = 0; x < floorsPerLevelAmount; x++)
		{
			floor[i][x]->setX(floor[i][x]->getX() - floorSpeed);
			if (floorLevel >= i && floorCycle[i] == x) { floor[i][x]->setW(floor[i][x]->getW() + floorSpeed); }
		}
	}
}

void CMountain::resetFloors()
{
	floorLevel = -1;
	ground->setX(0);
	ground->setW(sdl_Setup->getScreenWidth);
	for (int i = 0; i < levelsAmount; i++)
	{
		for (int x = 0; x < floorsPerLevelAmount; x++)
		{
			floor[i][x]->setX(sdl_Setup->getScreenWidth);
			floor[i][x]->setW(0);
		}
	}
}

void CMountain::updatePlayerCollsion(SDL_Rect playerRect)
{
	playerCollision->resetCollisionTruth();
	playerFloorDistance = 0;

	playerCollision->checkCollisionState(playerRect, ground->getRect());
	playerFloorDistance = playerCollision->distanceBetween(playerRect.y + playerRect.h, ground->getY());
	for (int i = 0; i < levelsAmount; i++)
	{
		for (int x = 0; x < floorsPerLevelAmount; x++)
		{
			if (floor[i][x]->getW() > 0) { playerCollision->checkCollisionState(playerRect, floor[i][x]->getRect()); }

			if (((playerRect.x > floor[i][x]->getX() && playerRect.x < floor[i][x]->getX() + floor[i][x]->getW()) | (playerRect.x + playerRect.w > floor[i][x]->getX() && playerRect.x + playerRect.w < floor[i][x]->getX() + floor[i][x]->getW())) && playerCollision->distanceBetween(playerRect.y + playerRect.h, floor[i][x]->getY() > playerFloorDistance))
			{
				playerFloorDistance = playerCollision->distanceBetween(playerRect.y + playerRect.h, floor[i][x]->getY());
			}
		}
	}
	playerCollision->checkCollisionState(playerRect, ground->getRect());

}

CCollision* CMountain::getPlayerCollision()
{
	return playerCollision;
}

int CMountain::getPlayerFloorDistance()
{
	return playerFloorDistance;
}

SDL_Rect CMountain::getFloorRect(int level, int floorNumber)
{
	return floor[level][floorNumber]->getRect();
}

void CMountain::setFloorSpeed(int newFloorSpeed)
{
	floorSpeed = newFloorSpeed;
}

int CMountain::getFloorSpeed()
{
	return floorSpeed;
}

void CMountain::greyLevel(bool grey, int level)
{
	if (grey)
	{ 
		if (level >= 0)
		{
			for (int x = 0; x < floorsPerLevelAmount; x++)
			{
				SDL_SetTextureColorMod(floor[level][x]->getTexture(), 20 + level * 10, 20 + level * 10, 20 + level * 10);
			}
		}
		else
			SDL_SetTextureColorMod(ground->getTexture(), 10, 10, 10);
	}
	else
	{
		if (level >= 0)
		{
			for (int x = 0; x < floorsPerLevelAmount; x++)
			{
				if (level == 0)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 42, 146, 63);
				if (level == 1)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 216, 38, 38);
				if (level == 2)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 139, 26, 168);
				if (level == 3)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 71, 108, 212);
				if (level == 4)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 0, 255, 0);
				if (level == 5)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 240, 214, 208);
				if (level == 6)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 247, 186, 247);
				if (level == 7)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 40, 239, 212);
				if (level == 8)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 157, 230, 170);
				if (level == 9)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 255, 229, 204);
				if (level == 10)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 238, 203, 240);
				if (level == 11)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 178, 237, 243);
				if (level == 12)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 198, 243, 178);
				if (level == 13)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 255, 204, 204);
				if (level == 14)SDL_SetTextureColorMod(floor[level][x]->getTexture(), 255, 223, 251);
			}
		}
		else
			SDL_SetTextureColorMod(ground->getTexture(), 50, 123, 159);
	}
}