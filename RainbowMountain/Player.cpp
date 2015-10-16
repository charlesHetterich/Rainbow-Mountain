#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer(CSDL_setup* csdl_setup, CMusic* Music, int x, int y)
{
	height = 80;
	width = 80;
	xPos = x;
	yPos = y;
	playerImage = "images/player/sad_guy.png";
	image = new Csprites(csdl_setup->GetRenderer(), playerImage, xPos, yPos, width, height, 3129, 3031);
	music = Music;
	sdl_setup = csdl_setup;
	horizontalSpeed = 0;
	fallSpeed = 2;
	jumpSpeed = 5;
	maxJumps = 30;
	gravity = 2;

	moveUp = false;
	moveDown = true;
	moveLeft = false;
	moveRight = false;
	playerHealth = new CHealth(sdl_setup, 1000, 780, 20, 800, 50);

	heathBarCollision = new CCollision();

	meteorCollision = new CCollision();
	meteorHit = false;

	enemy_WeaponCollision = new CCollision();
	enemy_PlayerCollision = new CCollision();

	playerFacing = 1;

	//weapons
	weaponChangeRefresh = 15;
	weaponsHoldingAmount = 3;
	weaponHolding = 1;

	missles = new CMissle(sdl_setup);
	missleFireSpeed = 10;

	laser = new CLaser(sdl_setup);
	laserFireSpeed = 80;

	bomb = new CBomb(sdl_setup, 100);
	bombFireSpeed = 50;
	letDetinateTime = 10;
}

CPlayer::~CPlayer()
{
	delete missles;
	delete laser;
	delete bomb;
	delete enemy_PlayerCollision;
	delete enemy_WeaponCollision;
	delete music;
	delete floorCollisions;
	delete heathBarCollision;
	delete playerHealth;
	delete meteorCollision;
	delete image;
	delete sdl_setup;
}

void CPlayer::genPlayer()
{
	image->drawReg(0, 0);
}

void CPlayer::genHealth()
{	
	heathBarCollision->checkCollisionState(playerHealth->healthBar->getRect(), image->getRect());

	/*if (heathBarCollision->collisionState[4] && playerHealth->healthBar->getAlpha() > 100)
	{
		playerHealth->healthBar->setAplpha(playerHealth->healthBar->getAlpha() - 5);
		playerHealth->healthPicture->setAplpha(playerHealth->healthPicture->getAlpha() - 5);
	}
	else if (playerHealth->healthBar->getAlpha() < 255 && !heathBarCollision->collisionState[4])
	{
		playerHealth->healthBar->setAplpha(playerHealth->healthBar->getAlpha() + 5);
		playerHealth->healthPicture->setAplpha(playerHealth->healthPicture->getAlpha() + 5);
		
	}*/

	heathBarCollision->resetCollisionTruth();
	playerHealth->showHealth();
}

void CPlayer::playerMovement(bool ableMove1, bool ableMove2, bool ableMove3, bool ableMove4, bool ableMove5, int floorDistance)
{
	ableMove[0] = ableMove1;
	ableMove[1] = ableMove2;
	ableMove[2] = ableMove3;
	ableMove[3] = ableMove4;
	ableMove[4] = ableMove5;
	
	switch (sdl_setup->GetMainEvent()->type)
	{
	case SDL_KEYDOWN:

		switch (sdl_setup->GetMainEvent()->key.keysym.sym)
		{
		case SDLK_LEFT:
			if (moveLeft == false) { moveLeft = true; image->setFrame(1); playerFacing = 2; }
			break;
		case SDLK_UP:
			//FIRING WEAPONS
			//missles
			if (weaponHolding == 1)
			{
				if (missleLoading > missleFireSpeed)
				{
					missles->launchMissle(image->getX(), image->getY(), playerFacing); missleLoading = 0;
					if (playerFacing == 1) { horizontalSpeed -= 15; }
					if (playerFacing == 2) { horizontalSpeed += 15; }
				}
			}
			//laser
			if (weaponHolding == 2)
			{
				if (laserRecharge > laserFireSpeed)
				{
					laser->shootLaser(playerFacing); 
					laserRecharge = 0;
				}
			}
			//bomb
			if (weaponHolding == 3)
			{
				if (bombReLoading > bombFireSpeed && !bomb->getLife())
				{
					if (playerFacing == 1) { bomb->throwBomb(image->getX(), image->getY(), 10, 10); }
					if (playerFacing == 2) { bomb->throwBomb(image->getX(), image->getY(), -10, 10); }
					bombReLoading = 0;
					detinateTime = 0;
				}
				if (bomb->getLife() == true && detinateTime > letDetinateTime) { bomb->setOffBomb(); }
				
			}
			break;
		case SDLK_SPACE:
			if (jumpNumber < maxJumps)
			{
				if (jumpNumber == 0) { moveUp = true; jumpNumber++; jumpSpeed = 20; }
				else { moveUp = true; jumpNumber++; jumpSpeed = 15; horizontalSpeed = -horizontalSpeed; }
				music->playSound(0);
			}
			break;

		case SDLK_RIGHT:
			if (moveRight == false) { moveRight = true; image->setFrame(0); playerFacing = 1; }
			break;

		case SDLK_DOWN:
			if (weaponChangeTime > weaponChangeRefresh)
			{
				weaponHolding++;
				if (weaponHolding > weaponsHoldingAmount)
				{
					weaponHolding = 1;
				}
				weaponChangeTime = 0;
			}
			break;
		}
		break;

	case SDL_KEYUP:
					  switch (sdl_setup->GetMainEvent()->key.keysym.sym)
					  {
					  case SDLK_LEFT:
						  moveLeft = false;
						  break;
					  case SDLK_s:
						  //moveDown = false;
						  break;
					  case SDLK_w:
						  //moveUp = false;
						  break;
					  case SDLK_RIGHT:
						  moveRight = false;
						  break;
					  case SDLK_DOWN:
						  weaponChangeTime = weaponChangeRefresh + 1;
						  break;
					  }

	default:
		break;
	}

	//player move up
	if (moveUp /*&& ableMove[0]*/)
	{
		image->setY(image->getY() - jumpSpeed);
		jumpSpeed -= gravity;

		if (jumpSpeed <= 2)
		{
			moveUp = false;
			jumpSpeed = 15;
			fallSpeed = 2;
		}

		if (image->getY() < 0)
		{
			image->setY(0);
			moveUp = false;
			fallSpeed = 2;
			jumpSpeed = 15;
		}
	}
	//reset JumpSpeed;
	if (!ableMove[1])
	{
		fallSpeed = 2;
		jumpSpeed = 15;
		
	}

	//player move down (falling)
	if (!moveUp && ableMove[1])
	{		
		if (fallSpeed > floorDistance)
		{
			image->setY(image->getY() + floorDistance);
			fallSpeed = 0;
			jumpNumber = 0;
		}
		image->setY(image->getY() + fallSpeed);
		if (fallSpeed <= 18)
		{
			fallSpeed += gravity / 2;
		}
	}

	//player move left
	if (moveLeft && ableMove[2] && horizontalSpeed > -10)
	{
		horizontalSpeed -= 4;
		//image->setX(image->getX() - horizontalSpeed);
	}

	//player move right
	if (moveRight && ableMove[3] && horizontalSpeed < 10)
	{
		horizontalSpeed += 4;
		//image->setX(image->getX() + horizontalSpeed);
	}

	//keeps player in the screen
	if (image->getX() + image->getW() > 1600)
	{
		image->setX(1600 - image->getW());
		horizontalSpeed = 0;
	}
	if (image->getX() < 0)
	{
		image->setX(0);
		horizontalSpeed = 0;
	}

	//stopping
	if (moveLeft == false && horizontalSpeed < 0)
	{
		horizontalSpeed+= 4;
		if (horizontalSpeed > 0) { horizontalSpeed = 0; }
	}
	if (moveRight == false && horizontalSpeed > 0)
	{
		horizontalSpeed-= 4;
		if (horizontalSpeed < 0) { horizontalSpeed = 0; }
	}

	image->setX(image->getX() + horizontalSpeed);
}

int CPlayer::getPlayerHealth()
{
	return playerHealth->getHealth();
}

void CPlayer::playerHitByMeteor()
{
	if (meteorHit == false)
	{
		playerHealth->takeDamage(10);
	}
	meteorHit = true;
}

void CPlayer::resetMeteorHit()
{
	meteorHit = false;
}

void CPlayer::playerHitMountain()
{
	playerHealth->takeDamage(10);
	image->setX(100);
	image->setY(-image->getH() + 50);
	horizontalSpeed = 0;
	jumpNumber = 0;
}

void CPlayer::playerHeal(int amount)
{
	playerHealth->heal(amount);
	if (playerHealth->getHealth() > 100)
	{
		playerHealth->setHealth(100);
	}
}

float CPlayer::getHSpeed()
{
	return horizontalSpeed;
}

void CPlayer::setHSpeed(float speed)
{
	horizontalSpeed = speed;
}

void CPlayer::loadWeapons(CMeteors* meteors, CEnemies* enemies)
{
	weaponChangeTime++;

	int currentEnemy = 0;

	///////////////////////////////
	////////MISSLE COLLISIOS///////
	///////////////////////////////
	missles->moveMissle();
	int currentMissle = 0;

	while (currentMissle < 30)
	{	
		//meteor - missle
		while (currentEnemy < 10)
		{
			if (meteors->meteorFireHealth[currentEnemy]->getHealth() > 0 && missles->checkLife(currentMissle))
			{
				/*meteorCollision->resetCollisionTruth();
				meteorCollision->checkCollisionState(meteors->meteorFire[currentEnemy]->image->getRect(), missles->missle[currentMissle]->getRect());
				if (meteorCollision->collisionState[4])
				{
					meteors->meteorFireHealth[currentEnemy]->takeDamage(25);
					if (!meteors->meteorFireHealth[currentEnemy]->checkLife()){ playerHeal(5); }
					missles->destroyMissle(currentMissle);			
				}*/
				if (enemy_PlayerCollision->aabbCollision(meteors->meteorFire[currentEnemy]->image->getRect(), missles->missle[currentMissle]->getRect()))
				{
					meteors->meteorFireHealth[currentEnemy]->takeDamage(25);
					if (!meteors->meteorFireHealth[currentEnemy]->checkLife()){ playerHeal(5); }
					missles->destroyMissle(currentMissle);
				}
			}
			currentEnemy++;
		}
		currentEnemy = 0;
		
		//missle - evil boy
		while (currentEnemy < 5)
		{
			if (enemies->hellBoy[currentEnemy]->health->checkLife() && missles->checkLife(currentMissle))
			{
				/*enemy_WeaponCollision->resetCollisionTruth();
				enemy_WeaponCollision->checkCollisionState(enemies->hellBoy[currentEnemy]->boy->getRect(), missles->missle[currentMissle]->getRect());
				if (enemy_WeaponCollision->collisionState[4])
				{
					enemies->hellBoy[currentEnemy]->hurtHellBoy(missles->getStrength(), missles->getKnockBack(currentMissle));
					if (!enemies->hellBoy[currentEnemy]->health->checkLife()){ playerHeal(10); enemies->hellBoy[currentEnemy]->dying(); }
					missles->destroyMissle(currentMissle);
				}*/
				if (enemy_PlayerCollision->aabbCollision(enemies->hellBoy[currentEnemy]->boy->getRect(), missles->missle[currentMissle]->getRect()))
				{
					enemies->hellBoy[currentEnemy]->hurtHellBoy(missles->getStrength(), missles->getKnockBack(currentMissle));
					if (!enemies->hellBoy[currentEnemy]->health->checkLife()){ playerHeal(10); enemies->hellBoy[currentEnemy]->dying(); }
					missles->destroyMissle(currentMissle);
				}
			}
			currentEnemy++;
		}
		currentEnemy = 0;

		//missile - highCloud
		if (enemies->highCloud->getHealth()->checkLife() && missles->checkLife(currentMissle))
		{
			if (enemy_PlayerCollision->aabbCollision(enemies->highCloud->getCloudRect(), missles->missle[currentMissle]->getRect()))
			{
				enemies->highCloud->hurtCloud(missles->getStrength(), missles->getKnockBack(currentMissle));
				//if (!enemies->hellBoy[currentEnemy]->health->checkLife()){ playerHeal(10); enemies->hellBoy[currentEnemy]->dying(); }
				missles->destroyMissle(currentMissle);
			}
		}

		//missle - fat boy
		for (int i = 0; i < enemies->fatBoysAmount; i++)
		{
			if (enemy_PlayerCollision->circleCollision(missles->missle[currentMissle]->getRect().h, missles->missle[currentMissle]->getRect(), enemies->fatBoy[i]->getRect().w, enemies->fatBoy[i]->getRect()));
			{
				//enemies->fatBoy[i]->hurt(missles->getStrength());
				//missles->destroyMissle(currentMissle);
			}
		}

		currentMissle++;
	}
	currentMissle = 0;

	missleLoading++;

	/////////////////////////////
	//////LASER COLLISIONS///////
	/////////////////////////////
	laser->showLaser(image->getX() + (image->getW() / 2), image->getY() - 20);
	if (weaponHolding == 2 && laser->electricBall->getW() < 50) { laser->electricBall->setW(laser->electricBall->getW() + 10); laser->electricBall->setH(laser->electricBall->getH() + 10); }
	if (weaponHolding != 2 && laser->electricBall->getW() > 0) { laser->electricBall->setW(laser->electricBall->getW() - 10); laser->electricBall->setH(laser->electricBall->getH() - 10); }
	
	//laser - meteors
	while (currentEnemy < 10)
	{
		if (meteors->meteorFireHealth[currentEnemy]->checkLife() && laser->electricBall->getH() > 0)
		{
			/*meteorCollision->resetCollisionTruth();
			meteorCollision->checkCollisionState(meteors->meteorFire[currentEnemy]->image->getRect(), laser->laser->getRect());
			if (meteorCollision->collisionState[4])
			{
				meteors->meteorFireHealth[currentEnemy]->takeDamage(laser->getStrength());
				if (!meteors->meteorFireHealth[currentEnemy]->checkLife()){ playerHeal(5); }
			}*/
			if (enemy_PlayerCollision->aabbCollision(meteors->meteorFire[currentEnemy]->image->getRect(), laser->laser->getRect()))
			{
				meteors->meteorFireHealth[currentEnemy]->takeDamage(laser->getStrength());
				if (!meteors->meteorFireHealth[currentEnemy]->checkLife()){ playerHeal(5); }
			}
		}
		currentEnemy++;
	}
	currentEnemy = 0;

	//laser - evil boy
	while (currentEnemy < 5)
	{
		if (enemies->hellBoy[currentEnemy]->health->checkLife() && laser->electricBall->getH() > 0)
		{
			/*enemy_WeaponCollision->resetCollisionTruth();
			enemy_WeaponCollision->checkCollisionState(enemies->hellBoy[currentEnemy]->boy->getRect(), laser->laser->getRect());
			if (enemy_WeaponCollision->collisionState[4])
			{
				enemies->hellBoy[currentEnemy]->hurtHellBoy(laser->getStrength(), laser->getKnockBack());
				if (!enemies->hellBoy[currentEnemy]->health->checkLife()){ playerHeal(10); enemies->hellBoy[currentEnemy]->dying(); }
			}*/
			if (enemy_PlayerCollision->aabbCollision(enemies->hellBoy[currentEnemy]->boy->getRect(), laser->laser->getRect()))
			{
				enemies->hellBoy[currentEnemy]->hurtHellBoy(laser->getStrength(), laser->getKnockBack());
				if (!enemies->hellBoy[currentEnemy]->health->checkLife()){ playerHeal(10); enemies->hellBoy[currentEnemy]->dying(); }
			}
		}
		currentEnemy++;
	}
	currentEnemy = 0;

	laserRecharge++;

	/////////////////////////////
	///////BOMB COLLISIONS///////
	/////////////////////////////
	bomb->showBomb();
	//bomb - meteors
	while (currentEnemy < 10)
	{
		if (meteors->meteorFireHealth[currentEnemy]->checkLife() && bomb->getHurting())
		{
			/*meteorCollision->resetCollisionTruth();
			meteorCollision->checkCollisionState(meteors->meteorFire[currentEnemy]->image->getRect(), bomb->getHurtingArea());
			if (meteorCollision->collisionState[4])
			{
				meteors->meteorFireHealth[currentEnemy]->takeDamage(bomb->getStrength());
				if (!meteors->meteorFireHealth[currentEnemy]->checkLife()){ playerHeal(5); }
			}*/
			if (enemy_PlayerCollision->aabbCollision(meteors->meteorFire[currentEnemy]->image->getRect(), bomb->getHurtingArea()))
			{
				meteors->meteorFireHealth[currentEnemy]->takeDamage(bomb->getStrength());
				if (!meteors->meteorFireHealth[currentEnemy]->checkLife()){ playerHeal(5); }
			}
		}
		currentEnemy++;
	}
	currentEnemy = 0;
	//bomb - evil boy
	while (currentEnemy < 5)
	{
		if (enemies->hellBoy[currentEnemy]->health->checkLife() && bomb->getHurting())
		{
			/*enemy_WeaponCollision->resetCollisionTruth();
			enemy_WeaponCollision->checkCollisionState(enemies->hellBoy[currentEnemy]->boy->getRect(), bomb->getHurtingArea());
			if (enemy_WeaponCollision->collisionState[4])
			{
				enemies->hellBoy[currentEnemy]->hurtHellBoy(bomb->getStrength(), bomb->getKnockBack(enemies->hellBoy[currentEnemy]->boy->getRect()));
				if (!enemies->hellBoy[currentEnemy]->health->checkLife()){ playerHeal(10); enemies->hellBoy[currentEnemy]->dying(); }
			}*/
			if (enemy_PlayerCollision->aabbCollision(enemies->hellBoy[currentEnemy]->boy->getRect(), bomb->getHurtingArea()))
			{
				enemies->hellBoy[currentEnemy]->hurtHellBoy(bomb->getStrength(), bomb->getKnockBack(enemies->hellBoy[currentEnemy]->boy->getRect()));
				if (!enemies->hellBoy[currentEnemy]->health->checkLife()){ playerHeal(10); enemies->hellBoy[currentEnemy]->dying(); }
			}

		}
		currentEnemy++;
	}
	currentEnemy = 0;

	bombReLoading++;
	detinateTime++;
}

void CPlayer::checkEnemyHurtPlayer(CEnemies* enemies)
{
	int currentEnemy = 0;
	int currentEnemiesWeapon = 0;
	
	//evil boy
	while (currentEnemy < 5)
	{
		while (currentEnemiesWeapon < 30)
		{
			/*enemy_PlayerCollision->resetCollisionTruth();
			enemy_PlayerCollision->checkCollisionState(enemies->hellBoy[currentEnemy]->blood[currentEnemiesWeapon]->getRect(), image->getRect());
			if (enemy_PlayerCollision->collisionState[4] && !enemies->hellBoy[currentEnemy]->getIfBoolHit(currentEnemiesWeapon))
			{
				playerHealth->takeDamage(1);
				enemies->hellBoy[currentEnemy]->setBloodHit(currentEnemiesWeapon, true);
			}*/

			if (enemy_PlayerCollision->aabbCollision(enemies->hellBoy[currentEnemy]->blood[currentEnemiesWeapon]->getRect(), image->getRect()) && !enemies->hellBoy[currentEnemy]->getIfBoolHit(currentEnemiesWeapon))
			{
				playerHealth->takeDamage(1);
				enemies->hellBoy[currentEnemy]->setBloodHit(currentEnemiesWeapon, true);
			}
			currentEnemiesWeapon++;
		}
		currentEnemiesWeapon = 0;
		currentEnemy++;
	}
	currentEnemy = 0;

	//tocano
	for (int i = 0; i < enemies->tacano->getTacosAmount(); i++)
	{
		if (enemy_PlayerCollision->aabbCollision(enemies->tacano->getTacoRect(i), image->getRect()) && enemies->tacano->getTacoActive(i))
		{
			enemies->tacano->deactivateTaco(i);
			playerHealth->takeDamage(enemies->tacano->getTacoStrength());
		}
	}

}

void CPlayer::resetPlayer(CMusic* Music)
{
	height = 80;
	width = 80;
	image->setX(200);
	image->setY(700);
	music = Music;
	horizontalSpeed = 0;
	fallSpeed = 2;
	jumpSpeed = 5;
	maxJumps = 30;
	gravity = 2;

	moveUp = false;
	moveDown = true;
	moveLeft = false;
	moveRight = false;

	playerHealth->setHealth(1000);

	playerFacing = 1;
}