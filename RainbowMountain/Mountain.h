#pragma once
#include "SDL_setup.h"
#include "collision.h"
#include "sprites.h"
class CMountain
{
public:
	CMountain(CSDL_setup* csdl_Setup);
	~CMountain();

	void changeLevel();
	void showFloor();
	void moveFloor();
	void resetFloors();
	void updatePlayerCollsion(SDL_Rect playerRect);
	CCollision* getPlayerCollision();
	int getPlayerFloorDistance();
	SDL_Rect getFloorRect(int level, int floorNumber);

	void greyLevel(bool grey, int level);

	void setFloorSpeed(int newFloorSpeed);
	int getFloorSpeed();


private:
	Csprites* ground;
	Csprites* floor[15][10];
	int floorsPerLevelAmount;
	int levelsAmount;
	int floorHeight;

	int floorCycle[16];

	int floorLevel;
	int floorSpeed;

	int floorChangeFrequency;
	int floorChangeTimer;
	int floorChangedLastTime;

	CCollision* playerCollision;
	int playerFloorDistance;

	CSDL_setup* sdl_Setup;
};

