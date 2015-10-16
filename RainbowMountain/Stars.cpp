#include "stdafx.h"
#include "Stars.h"


CStars::CStars(CSDL_setup* csdl_setup)
{
	sdl_Setup = csdl_setup;

	while (currentStar < 100)
	{
		star[currentStar] = new Csprites(sdl_Setup->GetRenderer(), "images/small_Star.png", 0, 0, 0, 0, 33, 32);
		currentStar++;
	}
	currentStar = 0;
}


CStars::~CStars()
{
	delete star;
}

void CStars::genStars()
{
	while (currentStar < 100)
	{
		if (currentSize[currentStar] <= 0)
		{
			star[currentStar]->setX(rand() % 1600);
			star[currentStar]->setY(rand() % 900);
			star[currentStar]->setW(rand() % 10 + 20);
			star[currentStar]->setH(star[currentStar]->getW());

			currentSize[currentStar] = star[currentStar]->getW();
		}
		star[currentStar]->setW(star[currentStar]->getW() - 1);
		star[currentStar]->setH(star[currentStar]->getH() - 1);

		currentSize[currentStar]--;

		star[currentStar]->drawReg(0, 0);

		currentStar++;
	}
	currentStar = 0;
}