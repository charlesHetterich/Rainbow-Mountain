#pragma once
#include "sprites.h"
#include "SDL_setup.h"
#include "Collision.h"
#include "Health.h"
#include "Music.h"

//weapons
#include "Missle.h"
#include "Laser.h"
#include "Bomb.h"

//enemies
#include "Meteors.h"
#include "Enemies.h"

class CPlayer
{
public:
	CPlayer(CSDL_setup* csdl_setup, CMusic* Music, int x, int y);
	~CPlayer();
	void genPlayer();
	void genHealth();
	void playerMovement(bool ableMove1, bool ableMove2, bool ableMove3, bool ableMove4, bool ableMove5, int floorDistance);
	int getPlayerHealth();
	void playerHeal(int amount);
	void playerHitByMeteor();

	void loadWeapons(CMeteors* meteors, CEnemies* enemies);

	void resetPlayer(CMusic* Music);

	void playerHitMountain();
	void resetMeteorHit();
	Csprites* image;
	CHealth* playerHealth;
	float getHSpeed();
	void setHSpeed(float speed);

	void checkEnemyHurtPlayer(CEnemies* enemies);
private:
	bool ableMove[5];

	//collisions
	CCollision* floorCollisions;
	CCollision* heathBarCollision;
	CCollision* meteorCollision;
	bool meteorHit;
	CCollision* enemy_WeaponCollision;
	CCollision* enemy_PlayerCollision;

	CSDL_setup* sdl_setup;
	CMusic* music;

	
	
	std::string playerImage;
	int xPos;
	int yPos;
	int height;
	int width;

	//mobility settings
	float gravity;
	float jumpSpeed;
	float fallSpeed;
	float horizontalSpeed;
	int jumpNumber;
	int maxJumps;
	int playerFacing; //1:right 2:left

	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;

	//weapons
	int weaponChangeRefresh;
	int weaponChangeTime;
	int weaponsHoldingAmount;
	int weaponHolding;

	CMissle* missles;
	int missleFireSpeed;
	int missleLoading;

	CLaser* laser;
	int laserFireSpeed;
	int laserRecharge;

	CBomb* bomb;
	int bombFireSpeed;
	int bombReLoading;
	int letDetinateTime;
	int detinateTime;
};

