#pragma once
#include "SDL_setup.h"
#include "collision.h"
#include "sprites.h"
class CFloors
{
public:
	CFloors(int amountOfRows, int amountOfBlocksPerRow, int height, CSDL_setup* sdl_setup);
	~CFloors();
	void genFloors(SDL_Rect rect1);
	void resetFloors();
	void getMoveFloor();

	//collisions
	CCollision* playerCollision;
	int playerFloorDistance;

private:
	CSDL_setup* csdl_setup;
	Csprites* block[16][10];
	int currentBlockRow;
	int currentBlockInRow;
	int floorLevel;
	int blockX[16];

	std::string floorImage[16];

	//floor settings
	int blockY;
	int blockH;
	int amountOfBlocksPerRow;
	int amountOfBlockRows;
	int currentBlock;
	int blockSpeed;

	float randomNumber;
	int floorMove;
};

