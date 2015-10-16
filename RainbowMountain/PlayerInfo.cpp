#include "stdafx.h"
#include "PlayerInfo.h"


CPlayerInfo::CPlayerInfo(CSDL_setup* csdl_setup, CPlayer* Player)
{
	player = Player;
	sdl_setup = csdl_setup;

	missle = new Csprites(sdl_setup->GetRenderer(), "images/guns/missle.png", NULL, NULL, NULL, NULL, 1547, 557);
	laser = new Csprites(sdl_setup->GetRenderer(), "images/guns/electricball.png", NULL, NULL, NULL, NULL, 1683, 1704);
	bomb = new Csprites(sdl_setup->GetRenderer(), "images/guns/bomb.png", NULL, NULL, NULL, NULL, 334, 306);
}


CPlayerInfo::~CPlayerInfo()
{
	delete missle;
	delete laser;
	delete bomb;
}

void CPlayerInfo::showMenu()
{
	missle->drawReg(0,0);
	laser->drawReg(0, 0);
	bomb->drawReg(0, 0);
}