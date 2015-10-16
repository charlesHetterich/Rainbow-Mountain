#pragma once
#include "sprites.h"
#include "Music.h"
#include "SDL_setup.h"
#include "Health.h"

class CTacano
{
public:
	CTacano(CSDL_setup* csdl_Setup);
	~CTacano();
	void spawn();
	void show();
	void shootTaco();
	void moveTacano();
	void deactivateTaco(int tacoNumber);
	bool getTacoActive(int tacoNumber);
	int getTacosAmount();
	bool getLife();
	int getTacoStrength();

	SDL_Rect getTacoRect(int tacoNumber);


private:

	Csprites* volcano;
	bool volcanoAlive;
	bool angry;
	bool angered;
	bool leaving;
	float VolcanoDestY;
	
	Csprites* taco[72];
	bool tacoActive[72];
	int tacosAmount;
	int tacoStrength;

	int tacoTimer;
	int tacoCycle;

	CSDL_setup* sdl_Setup;
};

