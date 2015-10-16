#pragma once
#include "SDL_setup.h"
#include "Music.h"
#include "sprites.h"
#include "HellBoy.h"
#include "Tacano.h"
#include "HighCloud.h"
#include "FatBoy.h"

class CEnemies
{
public:
	CEnemies(CSDL_setup* csdl_Setup);
	~CEnemies();
	void spawnEnemies();
	void loadEnemies(SDL_Rect playerRect);

	CHellBoy* hellBoy[5];
	CTacano* tacano;
	CHighCloud* highCloud;
	CFatBoy* fatBoy[1];
	
	int fatBoysAmount;
private:
	int currentHellBoy;
	int amountHellBoys;

	

	CSDL_setup* sdl_Setup;

};

