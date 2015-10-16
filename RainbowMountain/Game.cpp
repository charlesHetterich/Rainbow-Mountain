#include "stdafx.h"
#include "Game.h"

CGame::CGame(int w, int h)
{
	int screenWidth = w;
	int screenHeight = h;
	quit = false;
	csdl_setup = new CSDL_setup(&quit, screenWidth, screenHeight, true, true);
	csdl_setup->setWindowHidden(true);

	//show banner while loading game
	CSDL_setup loadingWindow(&quit, 400, 410, false, false);
	Csprites banner(loadingWindow.GetRenderer(), "images/banner.png", 0, 0, loadingWindow.getScreenWidth, loadingWindow.getScreenHeight, 953, 924);
	loadingWindow.begin();
	banner.drawReg(0, 0);
	loadingWindow.end();

	//all text here
	for (int i = 0; i < 4; i++)
	{
		text[i] = new CText(csdl_setup);
	}

	//image controller
	imageController = new Csprites(NULL, "", NULL, NULL, NULL, NULL, NULL, NULL);

	//background stars
	backgroundStars = new CStars(csdl_setup);

	//define objects
	player = new CPlayer(csdl_setup, music, 200, 700);

	header = new Csprites(csdl_setup->GetRenderer(), "images/rainbowmountainheader.png", 350, 30, 900, 400, 707, 323);
	playButton = new Csprites(csdl_setup->GetRenderer(), "images/rainbowmountainplaybutton.png", 650, 600, 300, 150, 332, 182);

	meteor = new CMeteors(csdl_setup, 0, -100);

	runTime = SDL_GetTicks();

	//FPS basically
	programSpeed = 12; //about 80 fps

	//floors
	floor = new CFloors(16, 10, 45, csdl_setup);
	mountain = new CMountain(csdl_setup);

	//block speed

	srand(time(NULL));

	levelTime = 0;

	//events
	events = new CEvents(csdl_setup);

	//score
	score = new CScore();
	highScore = data->load("data/highscore");

	//mouse
	mouse = new CMouse(csdl_setup);

	//music
	music = new CMusic();

	//collision
	collision = new CCollision();

	//enemies
	enemies = new CEnemies(csdl_setup);

	explosion = new CExplosion(csdl_setup);

	//////////////////////
	///CUT SCEEN THINGS///
	//////////////////////
	for (int i = 0; i < 100; i++)
	{
		for (int x = 0; x < 20; x++)
		{
			//rain[i][x] = new Csprites(csdl_setup->GetRenderer(), "images/white_block.png", i * 25 + (x % 2) * 25, 30 * x, 2, 15, 1, 1);
			rain[i][x] = new Csprites(csdl_setup->GetRenderer(), "images/white_block.png", rand() % csdl_setup->getScreenWidth, rand() % csdl_setup->getScreenHeight, 2, 15, 1, 1);
			SDL_SetTextureColorMod(rain[i][x]->getTexture(), 50, 50, 70);
		}
	}
	for (int i = 0; i < 16; i++)
	{
		colorHolders[i] = new Csprites(csdl_setup->GetRenderer(), "images/white_block.png", NULL, NULL, 8, 8, 1, 1);
		colorHolders[i]->setAplpha(0);
		colorHolderDistance[i] = 1500;
	}
	SDL_SetTextureColorMod(colorHolders[0]->getTexture(), 50, 123, 159);
	SDL_SetTextureColorMod(colorHolders[1]->getTexture(), 42, 146, 63);
	SDL_SetTextureColorMod(colorHolders[2]->getTexture(), 216, 38, 38);
	SDL_SetTextureColorMod(colorHolders[3]->getTexture(), 139, 26, 168);
	SDL_SetTextureColorMod(colorHolders[4]->getTexture(), 71, 108, 212);
	SDL_SetTextureColorMod(colorHolders[5]->getTexture(), 0, 255, 0);
	SDL_SetTextureColorMod(colorHolders[6]->getTexture(), 240, 214, 208);
	SDL_SetTextureColorMod(colorHolders[7]->getTexture(), 247, 186, 247);
	SDL_SetTextureColorMod(colorHolders[8]->getTexture(), 40, 239, 212);
	SDL_SetTextureColorMod(colorHolders[9]->getTexture(), 157, 230, 170);
	SDL_SetTextureColorMod(colorHolders[10]->getTexture(), 255, 229, 204);
	SDL_SetTextureColorMod(colorHolders[11]->getTexture(), 238, 203, 240);
	SDL_SetTextureColorMod(colorHolders[12]->getTexture(), 178, 237, 243);
	SDL_SetTextureColorMod(colorHolders[13]->getTexture(), 198, 243, 178);
	SDL_SetTextureColorMod(colorHolders[14]->getTexture(), 255, 204, 204);
	SDL_SetTextureColorMod(colorHolders[15]->getTexture(), 255, 223, 251);

	drGrey = new Csprites(csdl_setup->GetRenderer(), "images/dr.grey.png", 200, 400, 100, 250, 65, 135);
	drGrey->setAplpha(0);
	lightning = new Csprites(csdl_setup->GetRenderer(), "images/white_block.png", 0, 0, csdl_setup->getScreenWidth, csdl_setup->getScreenHeight, 1, 1);
	lightning->setAplpha(0);
	blackCoverUp = new Csprites(csdl_setup->GetRenderer(), "images/white_block.png", 0, 0, csdl_setup->getScreenWidth, csdl_setup->getScreenHeight, 1, 1);
	SDL_SetTextureColorMod(blackCoverUp->getTexture(), 0, 0, 0);
	introText = new CText(csdl_setup);
	skipText = new CText(csdl_setup);
	rainSound = new CMusic();
	rainSound->fadeInMusic(3, 1, 5000);

	//now that everything is loaded, lets show the real window
	csdl_setup->setWindowHidden(false);

	loadingWindow.setWindowHidden(true);
}
CGame::~CGame()
{
	delete explosion;
	delete enemies;
	delete backgroundStars;
	delete floor;
	delete mountain;
	delete collision;
	delete meteor;
	delete mouse;
	delete csdl_setup;
	delete player;
	delete events;
	delete score;
	delete text;
}

void CGame::gameLoop()
{
	while (!quit && csdl_setup->mainEvent->type != SDL_QUIT)
	{
		
		if (runTime + programSpeed <= SDL_GetTicks())
		{
			csdl_setup->begin();
			if (currentMenu == 0)
			{
				introCutSceen();
			}
			if (currentMenu == 1)
			{
				StartMenu();
			}
			else if (currentMenu == 2)
			{
				theGame();
			}

			std::cout << mouse->mouseX << "   " << mouse->mouseY << std::endl;

			mouse->mouseImage(currentMenu); //changes the image of the mouse

			//images controller things
			if (imageController->getHigh() > 0)
				imageController->setHigh(imageController->getHigh() - 1);
			if (imageController->getShake() > 0)
				imageController->setShake(imageController->getShake() - 1);

			csdl_setup->end();

			//calculate desired fps vs actual fps
			csdl_setup->setFpsRatio((((double)SDL_GetTicks() - (double)runTime) / programSpeed));
			//std::cout << SDL_GetTicks() - runTime << "    " << csdl_setup->getFpsRatio() << "\n";
			runTime = SDL_GetTicks();
		}
	}
}

void CGame::introCutSceen()
{
	cutSceenTimer++;

	mountain->moveFloor();
	mountain->showFloor();

	mountain->changeLevel();

			lightning->drawReg(0, 0);

			drGrey->setY(400 + 15 * sin((float)cutSceenTimer*(M_PI / 180)));
			drGrey->drawReg(0, 0);

			for (int i = 0; i < 16; i++)
			{
				colorHolders[i]->setX(drGrey->getX() + 113 + colorHolderDistance[i] * cos((i*22.5 + (float)cutSceenTimer)*(M_PI / 180)));
				colorHolders[i]->setY(drGrey->getY() + 10 + colorHolderDistance[i] * sin((i*22.5 + (float)cutSceenTimer)*(M_PI / 180)));
				colorHolders[i]->drawReg(0, 0);
				if (cutSceenTimer > 2000  + i * 10 && cutSceenTimer < 2300) { colorHolderDistance[i] += (40 - colorHolderDistance[i]) / 5; }
				//else if (cutSceenTimer > 2300 + i * 10) { colorHolderDistance[i] += (colorHolderDistance[i] - 30) / 5; }
			}

			for (int i = 0; i < 100; i++)
			{
				for (int x = 0; x < 2; x++)
				{
					rain[i][x]->drawReg(0, 0);

					if (!rainHit[i][x])
						rain[i][x]->setY(rain[i][x]->getY() + 20);
					else
					{
						velocityY[i][x] -= 0.7;
						rain[i][x]->setX(rain[i][x]->getX() + velocityX[i][x]);
						rain[i][x]->setY(rain[i][x]->getY() - velocityY[i][x]);
						if (rain[i][x]->getW() > 0)
						{
							rain[i][x]->setW(rain[i][x]->getW() - 1);
							rain[i][x]->setH(rain[i][x]->getH() - 1);
						}
					}


					if (rain[i][x]->getY() > csdl_setup->getScreenHeight - 45)
					{
						if (rainHit[i][x])
						{
							rain[i][x]->setX(rand() % csdl_setup->getScreenWidth);
							rain[i][x]->setY(0 + 20);
							rain[i][x]->setW(rand() % 3 + 1);
							rain[i][x]->setH(rand() % 5 + 10);
							rainHit[i][x] = false;
						}
						else
						{
							int size = rand() % 3 + 5;
							rain[i][x]->setW(size);
							rain[i][x]->setH(size);
							velocityX[i][x] = (rand() % 1 + 2);
							velocityY[i][x] = rand() % 1 + 3;
							if (rand() % 2 == 0)
								velocityX[i][x] *= -1;

							velocityX[i][x] -= 6;
							rainHit[i][x] = true;

							rain[i][x]->setY(csdl_setup->getScreenHeight - 45 - rain[i][x]->getH());
						}
					}

					for (int level = 0; level < 15; level++)
					{
						for (int floorNumber = 0; floorNumber < 10; floorNumber++)
						{
							if (collision->aabbCollision(rain[i][x]->getRect(), mountain->getFloorRect(level, floorNumber)))
							{
								if (rainHit[i][x])
								{
									rain[i][x]->setX(rand() % csdl_setup->getScreenWidth);
									rain[i][x]->setY(0 + 20);
									rain[i][x]->setW(rand() % 3 + 1);
									rain[i][x]->setH(rand() % 5 + 10);
									rainHit[i][x] = false;
								}
								else
								{
									int size = rand() % 3 + 5;
									rain[i][x]->setW(size);
									rain[i][x]->setH(size);
									velocityX[i][x] = (rand() % 1 + 2);
									velocityY[i][x] = rand() % 1 + 3;
									if (rand() % 2 == 0)
										velocityX[i][x] *= -1;

									velocityX[i][x] -= 6;
									rainHit[i][x] = true;

									rain[i][x]->setY(mountain->getFloorRect(level, floorNumber).y - rain[i][x]->getH());
								}
							}
						}
					}
				}
			}

			if (lightning->getAlpha() > 10)
			{
				lightning->setAplpha(lightning->getAlpha() - 4);
				if (lightning->getAlpha() < 10) { lightning->setAplpha(10); }
				for (int i = 0; i < 100; i++)
				{
					for (int x = 0; x < 20; x++)
					{
						SDL_SetTextureColorMod(rain[i][x]->getTexture(), 50 * (10 / lightning->getAlpha()), 50 * (10 / lightning->getAlpha()), 70 * (10 / lightning->getAlpha()));
					}
				}
				SDL_SetTextureColorMod(drGrey->getTexture(), 255 - lightning->getAlpha(), 255 - lightning->getAlpha(), 255 - lightning->getAlpha());
			}
			//std::cout << cutSceenTimer << "\n";

			//background sound and small flash corralation
			if (cutSceenTimer == 530) { lightning->setAplpha(200); }
			if (cutSceenTimer == 800) { lightning->setAplpha(160); }
			if (cutSceenTimer == 1500) { lightning->setAplpha(160); }
			if (cutSceenTimer == 1700) { lightning->setAplpha(160); }
			if (cutSceenTimer == 1800) { lightning->setAplpha(160); }
			if (cutSceenTimer == 1900) { lightning->setAplpha(200); }
			if (cutSceenTimer == 2500) { lightning->setAplpha(110); }
			if (cutSceenTimer == 3100) { lightning->setAplpha(220); }
			if (cutSceenTimer == 4200) { lightning->setAplpha(170); }
			if (cutSceenTimer == 5500) { lightning->setAplpha(200); }
			if (cutSceenTimer == 5540) { lightning->setAplpha(160); }
			if (cutSceenTimer == 5630) { lightning->setAplpha(170); }
			if (cutSceenTimer == 6000) { lightning->setAplpha(120); }
			if (cutSceenTimer == 6700) { lightning->setAplpha(160); }
			if (cutSceenTimer == 7750) { lightning->setAplpha(200); }
			if (cutSceenTimer == 7780) { lightning->setAplpha(160); }
			if (cutSceenTimer == 8000) { lightning->setAplpha(160); }
			if (cutSceenTimer == 9030) { lightning->setAplpha(160); }
			if (cutSceenTimer == 9150) { lightning->setAplpha(160); }
			if (cutSceenTimer == 9450) { lightning->setAplpha(100); }
			if (cutSceenTimer == 10100) { lightning->setAplpha(160); }
			if (cutSceenTimer == 10300) { lightning->setAplpha(200); }
			if (cutSceenTimer == 1150) { lightning->setAplpha(200); }

			//big flashes
			if (cutSceenTimer == 400) { rainSound->playSound(5); lightning->setAplpha(255); }
			if (cutSceenTimer == 800) { rainSound->playSound(5); lightning->setAplpha(255); }
			if (cutSceenTimer == 1420) { rainSound->playSound(5); lightning->setAplpha(255); drGrey->setAplpha(255); }
			if (cutSceenTimer == 1560) { rainSound->playSound(5); lightning->setAplpha(255); }
			if (cutSceenTimer == 2000) { rainSound->playSound(5); lightning->setAplpha(255); drGrey->setFrame(1); drGrey->setW(127); for (int i = 0; i < 16; i++) { colorHolders[i]->setAplpha(255); } for (int i = 0; i < 16; i++) { mountain->greyLevel(true, i - 1); } }
			if (cutSceenTimer == 2300) { rainSound->playSound(5); lightning->setAplpha(255); drGrey->setAplpha(0); for (int i = 0; i < 16; i++) { colorHolders[i]->setAplpha(0); } }

			//intro text
			if (cutSceenTimer > 30 && cutSceenTimer < 1000 && blackCoverUp->getAlpha() > 0) { blackCoverUp->setAplpha(blackCoverUp->getAlpha() - 1); }
			if (cutSceenTimer > 820 && introText->getAlpha() > 0) { introText->setAlpha(introText->getAlpha() - 1); }
			
			std::string titleFull = "One stormy night on Rainbow Mountain....";
			std::string titleShown;

			if (cutSceenTimer == 200 + amountTextShown * 10 && amountTextShown < titleFull.length()-1) {  amountTextShown++; while (titleFull.at(amountTextShown) == ' ') { amountTextShown++; } rainSound->playSound(6); }

			for (int i = 0; i < amountTextShown; i++) { titleShown += titleFull[i]; }

			if (amountTextShown > 0)
				introText->write("fonts/rough_typewriter.otf", 50, titleShown, 220, 200, 1400, NULL, NULL);

			skipText->write("fonts/rough_typewriter.otf", 30, "Press space to skip", 600, 860, 1000, NULL, NULL);
			skipText->setAlpha(255/2 * sin(cutSceenTimer*(M_PI / 180)) + 255/2);

			blackCoverUp->drawReg(0, 0);

			//fade out
			if (cutSceenTimer > 2600 && blackCoverUp->getAlpha() < 255) { blackCoverUp->setAplpha(blackCoverUp->getAlpha() + 1); }
			if (cutSceenTimer == 2600) { rainSound->fadeOutMusic(5000); }

			//done with cutscene
			if (cutSceenTimer == 2900)
			{
				currentMenu = 1;
				music->playMusic(0);
				for (int i = 0; i < 16; i++) { mountain->greyLevel(false, i - 1); }
			}

			switch (csdl_setup->GetMainEvent()->type)
			{
			case SDL_KEYDOWN:

				switch (csdl_setup->GetMainEvent()->key.keysym.sym)
				{
				case SDLK_SPACE:
					currentMenu = 1;
					music->playMusic(0);
					for (int i = 0; i < 16; i++) { mountain->greyLevel(false, i - 1); }
					break;
				}
				break;

			default:
				break;
			}
	
}

void CGame::StartMenu()
{
	backgroundStars->genStars();

	//floor->genFloors(player->image->getRect());
	mountain->moveFloor();
	mountain->showFloor();

	mountain->changeLevel();

	if (collision->checkMouseCollision(mouse->mouseX, mouse->mouseY, playButton->getRect()))
	{
		playButton->setX(600);
		playButton->setY(575);
		playButton->setW(400);
		playButton->setH(200);

		if (mouse->mouseLeftClick() == true)
		{
			currentMenu = 2;
			music->playMusic(2);

			player->resetPlayer(music);

			//floor->resetFloors();
			mountain->resetFloors();
		
			meteor->meteorsReset();

			levelTime = 0;
			lastLevelTime = 0;

			//reset score
			score->setScore(0);

			deaths = 0;
		}
	}
	else
	{
		playButton->setX(650);
		playButton->setY(600);
		playButton->setW(300);
		playButton->setH(150);
	}

	header->drawReg(0, 0);
	playButton->drawReg(0, 0);

	//std::cout << rand() % 25 << "\n";
	text[0]->write("fonts/stocky.ttf", 50, "Controls:arrows and space", 10, 800, 1500, 0, 0);
	text[1]->write("fonts/stocky.ttf", 50, "Click the meteors!", 10, 850, 1000, 0, 0);
	text[2]->write("fonts/stocky.ttf", 30, "Created by Charles Hetterich", 1040, 850, 1000, 0, 0);
	//text->createText(100, "Controls: wasd", 10, 700, 350, 100);
	//text->createText(100, "Click the meteors!", 10, 800, 500, 100);
	//text->createText(100, "Created by Charles Hetterich", 1240, 850, 350, 50);
}

int CGame::theGame()
{
	data->save("data/highscore", highScore);

	events->Levels();
	backgroundStars->genStars();

	mountain->changeLevel();

	//generating blocks and say if block should move/elongate
	//floor->genFloors(player->image->getRect());
	mountain->moveFloor();
	mountain->updatePlayerCollsion(player->image->getRect());
	mountain->showFloor();
	
	//all meteor stuff
	meteor->shower("Ice");
	meteor->shower("Fire");
	meteor->meteorFall();
	meteor->genMeteors(player->image->getRect());
	player->playerHeal(meteor->mouseHitMeteor(mouse) * 5);

	//enemies
	enemies->loadEnemies(player->image->getRect());
	enemies->spawnEnemies();

	//gen player
	player->loadWeapons(meteor, enemies);
	player->checkEnemyHurtPlayer(enemies);
	player->genPlayer();
	player->genHealth();
	//player->playerMovement(floor->playerCollision->collisionState[0], floor->playerCollision->collisionState[1], floor->playerCollision->collisionState[2], floor->playerCollision->collisionState[3], floor->playerCollision->collisionState[4], floor->playerFloorDistance);
	player->playerMovement(mountain->getPlayerCollision()->collisionState[0], mountain->getPlayerCollision()->collisionState[1], mountain->getPlayerCollision()->collisionState[2], mountain->getPlayerCollision()->collisionState[3], mountain->getPlayerCollision()->collisionState[4], mountain->getPlayerFloorDistance());
	if (meteor->collision->collisionState[4])
	{
		player->playerHitByMeteor();
	}
	else
	{
		player->resetMeteorHit();
	}

	//////////////////////////////////////////////////////////
	///////////////////////PLAYER DYING///////////////////////
	//////////////////////////////////////////////////////////

	//when player loses (hits left side of block) game restarts
	if (/*floor->playerCollision->collisionState[4]*/mountain->getPlayerCollision()->collisionState[4])
	{
		std::cout << "AHHH";
		player->playerHitMountain();
	}
	if (/*player->getPlayerHealth() <= 0*/ !player->playerHealth->checkLife())
	{
		//////////WORK ON THIS////////////////
		player->resetPlayer(music);

		//floor->resetFloors();
		mountain->resetFloors();
		meteor->meteorsReset();

		levelTime = 0;
		lastLevelTime = 0;

		//reset score
		score->setScore(0);

		//makes a flash on death
		flash = true;
		deaths++;
	}

	
	//*****REMEMBER TO: put all the score stuff in functions in CScore because having it here is pointless!!!!!!!!!!!!!!
	///////////////////////////////////////////
	//////////////////SCORING//////////////////
	///////////////////////////////////////////
	//score multiplier

	//current score
	score->raiseScore(player->image->getX(), text[2]);
	score_string = std::to_string(score->getScore());
	highScore_string = std::to_string(highScore);
	deaths_string = std::to_string(deaths);
	//highscore
	if (score->getScore() >= highScore)
	{
		highScore = score->getScore();
	}
	
	//display score
	//text[0]->write("fonts/stocky.ttf", 40, "Current Score:", 1200, 0, 1000, NULL, NULL);
	/////////////////////////////////////text[1]->write("fonts/trench.otf", 80, score_string, 10, 2, 1000, NULL, NULL);
	//text->createText(100, "Current Score: ", 1200, 0, 200, 75);
	//text->createText(100, score_string, 1200 + 210, 0, 150, 75);

	//text[1]->write("fonts/stocky.ttf", 40, "High Score:", 1200, 80, 1000, NULL, NULL);
	//text->createText(100, "High Score: ", 1200, 80, 200, 75);
	//text->createText(100, highScore_string, 1200 + 210, 80, 150, 75);

	//text->createText(100, "Deaths: ", 1200, 0, 200, 75);
	//text->createText(100, deaths_string, 1200 + 210, 0, 100, 75);

	

	//flash on death
	if (flash == true) { flash = events->deathFlash(); }
	explosion->showExplosion();


	//checks if player is quites the actual game
		switch (csdl_setup->GetMainEvent()->type)
		{
		case SDL_KEYDOWN:

			switch (csdl_setup->GetMainEvent()->key.keysym.sym)
			{
			case SDLK_ESCAPE:
				music->playMusic(0);
				currentMenu = 1;
				//floor->resetFloors();
				mountain->resetFloors();
				break;
			case SDLK_a:
				explosion->explode(2, 1000, 500);
				break;
			}
			break;

		default:
			break;
		}
	

	return 0;
}