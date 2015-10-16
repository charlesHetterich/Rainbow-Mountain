#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Player.h"
#include "Block.h"
#include "Floors.h"
#include "Events.h"
#include "Score.h"
#include "Text.h"
#include "Mouse.h"
#include "Data.h"
#include "Music.h"
#include "Meteors.h"
#include "Collision.h"
#include "Stars.h"
#include "Enemies.h"
#include "Mountain.h"

class CGame
{
public:
	CGame(int w, int h);
	~CGame();

	//main loops
	void gameLoop();
	void StartMenu();
	void introCutSceen();
	int theGame();

	//mouse
	CMouse* mouse;

	//music
	CMusic* music;

	//gets sdl info
	CSDL_setup* csdl_setup;

private: CExplosion* explosion;

	//screen color shades
	Csprites* levelColor[2];

	//image controller
	Csprites* imageController;

	//background stars
	CStars* backgroundStars;

	//collisions
	CCollision* collision;

	//loading & saving data
	CData* data;

	int randomNumber;
	int levelTime;
	int lastLevelTime;

	//creating text
	CText* text[4];

	//scoreing
	CScore* score;
	std::string score_string;
	int highScore;
	std::string highScore_string;
	int deaths;
	std::string deaths_string;

	//Gets Events
	CEvents* events;
	bool flash;

	//sets and gets floor levels
	CFloors* floor;
	CMountain* mountain;

	//general settings
	int currentMenu;
	int programSpeed;
	int runTime;
	int screenWidth;
	int screenHeight;

	//objects
	CPlayer* player;
	Csprites* header;
	Csprites* playButton;

	//enemies
	CEnemies* enemies;

	CMeteors* meteor;

	//////////////////////
	///CUT SCEEN THINGS///
	//////////////////////
	int cutSceenTimer;
	Csprites* rain[100][20];
	float velocityY[100][20];
	float velocityX[100][20];
	bool rainHit[100][20];

	Csprites* lightning;
	Csprites* drGrey;
	Csprites* blackCoverUp;
	Csprites* colorHolders[16];
	int colorHolderDistance[16];
	int amountTextShown;
	CText* introText;
	CText* skipText;

	CMusic* rainSound;
	
	
	//quit boolean
	bool quit;
};

