#include "stdafx.h"
#include "Floors.h"


CFloors::CFloors(int amountOfFloors, int amountOfBlocksPerFloor, int height, CSDL_setup* sdl_setup)
{
	csdl_setup = sdl_setup;

	blockSpeed = 6;
	amountOfBlockRows = amountOfFloors;
	amountOfBlocksPerRow = amountOfBlocksPerFloor;
	blockH = height;
	blockY = csdl_setup->getScreenHeight;

	floorImage[0] = "images/blocks/block1.png";
	floorImage[1] = "images/blocks/block2.png";
	floorImage[2] = "images/blocks/block3.png";
	floorImage[3] = "images/blocks/block4.png";
	floorImage[4] = "images/blocks/block5.png";
	floorImage[5] = "images/blocks/block6.png";
	floorImage[6] = "images/blocks/block7.png";
	floorImage[7] = "images/blocks/block8.png";
	floorImage[8] = "images/blocks/block9.png";
	floorImage[9] = "images/blocks/block10.png";
	floorImage[10] = "images/blocks/block11.png";
	floorImage[11] = "images/blocks/block12.png";
	floorImage[12] = "images/blocks/block13.png";
	floorImage[13] = "images/blocks/block14.png";
	floorImage[14] = "images/blocks/block15.png";
	floorImage[15] = "images/blocks/block16.png";


	while (currentBlockRow < amountOfBlockRows)
	{
		while (currentBlockInRow < amountOfBlocksPerRow)
		{
			if (currentBlockRow == 0)
			{
				block[currentBlockRow][currentBlockInRow] = new Csprites(csdl_setup->GetRenderer(), floorImage[currentBlockRow], 0 , blockY - blockH, 2000, blockH, 1, 1);
			}
			else
			{
				block[currentBlockRow][currentBlockInRow] = new Csprites(csdl_setup->GetRenderer(), floorImage[currentBlockRow], -2000, blockY - blockH, 2000, blockH, 1, 1);
			}
			currentBlockInRow++;
		}
		currentBlockInRow = 0;
		blockY -= blockH;
		currentBlockRow++;
	}
	blockY = csdl_setup->getScreenHeight;
	currentBlockRow = 0;

	floorLevel = 1;
	playerCollision = new CCollision();
}


CFloors::~CFloors()
{
	delete block;
	delete playerCollision;
}

void CFloors::genFloors(SDL_Rect rect1)
{
	playerCollision->resetCollisionTruth();
	playerFloorDistance = 0;

	while (currentBlockRow < amountOfBlockRows)
	{
		while (currentBlockInRow < amountOfBlocksPerRow)
		{
			if (floorLevel >= currentBlockRow + 1 && blockX[currentBlockRow] == currentBlockInRow + 1)
			{
				block[currentBlockRow][currentBlockInRow]->drawReg(0, 0); block[currentBlockRow][currentBlockInRow]->setX(block[currentBlockRow][currentBlockInRow]->getX() - blockSpeed); block[currentBlockRow][currentBlockInRow]->setW(block[currentBlockRow][currentBlockInRow]->getW() + blockSpeed);
			}
			else
			{
				block[currentBlockRow][currentBlockInRow]->drawReg(0, 0); block[currentBlockRow][currentBlockInRow]->setX(block[currentBlockRow][currentBlockInRow]->getX() - blockSpeed);
			}
			playerCollision->checkCollisionState(rect1, block[currentBlockRow][currentBlockInRow]->getRect());
			if (((rect1.x > block[currentBlockRow][currentBlockInRow]->getX() && rect1.x < block[currentBlockRow][currentBlockInRow]->getX() + block[currentBlockRow][currentBlockInRow]->getW()) | (rect1.x + rect1.w > block[currentBlockRow][currentBlockInRow]->getX() && rect1.x + rect1.w < block[currentBlockRow][currentBlockInRow]->getX() + block[currentBlockRow][currentBlockInRow]->getW())) && playerCollision->distanceBetween(rect1.y + rect1.h, block[currentBlockRow][currentBlockInRow]->getY() > playerFloorDistance))
			{
				playerFloorDistance = playerCollision->distanceBetween(rect1.y + rect1.h, block[currentBlockRow][currentBlockInRow]->getY());
			}
			currentBlockInRow++;
		}
		currentBlockInRow = 0;
		currentBlockRow++;
	}
	currentBlockRow = 0;
	block[0][0]->setX(0); block[0][0]->setW(2000); block[0][0]->drawReg(0, 0);
	playerCollision->checkCollisionState(rect1, block[0][0]->getRect());
}

void CFloors::getMoveFloor()
{
	randomNumber = ((rand() / 32767.0) * 100) + 1;
	if (randomNumber <= 51 && floorLevel < amountOfBlockRows)
	{
		floorLevel += 1;
	}
	else if (randomNumber >= 50 && floorLevel > 1)
	{
		floorLevel -= 1;
	}

	while (currentBlockRow < amountOfBlockRows)
	{
		if (floorLevel == currentBlockRow + 1)
		{
			blockX[currentBlockRow]++;
			if (blockX[currentBlockRow] == 11) { blockX[currentBlockRow] = 1; }
			blockX[0] = 1;
		}
		
		currentBlockRow++;
	}
	currentBlockRow = 0;

	while (currentBlockRow < amountOfBlockRows)
	{
		if (floorLevel == currentBlockRow + 1)
		{
			while (currentBlockInRow < amountOfBlocksPerRow)
			{
				if (blockX[currentBlockRow] == currentBlockInRow + 1)
				{
					block[currentBlockRow][currentBlockInRow]->setX(1600);
					block[currentBlockRow][currentBlockInRow]->setW(100);
				}
				currentBlockInRow++;
			}
		}
		currentBlockInRow = 0;
		currentBlockRow++;
	}
	currentBlockRow = 0;
}

void CFloors::resetFloors()
{
	while (currentBlockRow < amountOfBlockRows)
	{
		while (currentBlockInRow < amountOfBlocksPerRow)
		{
			if (currentBlockRow == 0)
			{
				block[currentBlockRow][currentBlockInRow] = new Csprites(csdl_setup->GetRenderer(), floorImage[currentBlockRow], 0, blockY - blockH, 2000, blockH, 1, 1);
			}
			else
			{
				block[currentBlockRow][currentBlockInRow] = new Csprites(csdl_setup->GetRenderer(), floorImage[currentBlockRow], -2000, blockY - blockH, 2000, blockH, 1, 1);
			}
			currentBlockInRow++;
		}
		currentBlockInRow = 0;
		blockY -= blockH;
		currentBlockRow++;
	}
	blockY = csdl_setup->getScreenHeight;
	currentBlockRow = 0;

	floorLevel = 1;
}