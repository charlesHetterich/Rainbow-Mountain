#pragma once
#include "SDL_setup.h"
#include "Block.h"
#include "Health.h"
#include "Collision.h"
#include "Mouse.h"

class CMeteors
{
public:

	CMeteors(CSDL_setup* sdl_setup, int xPos, int yPos);
	~CMeteors();
	void shower(std::string meteorType);
	void meteorFall();
	bool genMeteors(SDL_Rect rect1);
	int mouseHitMeteor(CMouse* mouse);

	//////////////////////////////////////////////////
	//////////////////WORK ON THIS////////////////////
	//////////////////////////////////////////////////
	bool meteorExplode(int x, int y, int w, int h);

	void meteorsReset();

	CBlock* meteorFire[10];
	CBlock* meteorIce[10];
	CHealth* meteorIceHealth[10];
	CHealth* meteorFireHealth[10];
	CCollision* collision;

private:
	int lastHitMeteor;
	std::string lastHitMeteorType;

	int amountMeteorsDestroyed;

	bool mouseClicked;
	bool showMeteorFire[10];
	bool showMeteorIce[10];

	int x;
	int y;
	CSDL_setup* csdl_setup;

	int currentCheckHitFire;
	int currentCheckHitIce;
	int currentGenFire;
	int currentGenIce;
	int currentFire;
	int currentIce;

	int meteorFireSpeed[10];
	
	int healthBarYDistance;

	int meteorIceSpeed[10];
	
	

};

