#pragma once
#include "SDL_setup.h"
#include "sprites.h"

class CHealth
{
public:
	CHealth(CSDL_setup* sdl_setup, int maxHealth, int x, int y, int w, int h);
	~CHealth();

	void setHealth(int newHealth);
	bool checkLife();
	void takeDamage(int damage);
	void heal(int healAmount);
	void showHealth();
	void updatePosition(int x, int y);
	int getHealth();	
	Csprites* healthBar;
	Csprites* healthPicture;

	void createHealthBalls(int amount, int creationX, int creationY, int destinationX, int destinationY);
	void genHealthBalls(SDL_Rect destination);
	Csprites* healthBall[100];

private:
	
	//keeps track while health ball a function is on
	int healthBallsAmount;
	float healthBallSpeed[100];
	float healthBallVerticalDestiny[100];
	float healthBallHorizontalDestiny[100];
	bool showHealthBall[100];
	int currentHealthBall;

	CSDL_setup* csdl_setup;

	//All health related images
	std::string healthBar_image;
	std::string healthPicture_image;
	std::string healthBall_image;


	float healthBar_xPos;
	float healthBar_yPos;
	float healthBar_width;
	float healthBar_height;

	float healthPicture_xPos;
	float healthPicture_yPos;
	float healthPicture_width;
	float healthPicture_height;

	float health;
};

