#pragma once
#include "Player.h"
#include "Score.h"
#include "sprites.h"
#include "SDL_setup.h"
class CPlayerInfo
{
public:
	CPlayerInfo(CSDL_setup* csdl_setup, CPlayer* Player);
	~CPlayerInfo();
	void showMenu();

private:
	CSDL_setup* sdl_setup;
	Csprites* missle;
	Csprites* laser;
	Csprites* bomb;

	CPlayer* player;
};

