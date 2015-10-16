#include "stdafx.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	CGame* cgame = new CGame(1600, 900);

	cgame->gameLoop();

	return 0;
}