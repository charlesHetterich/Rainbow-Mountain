#include "stdafx.h"
#include "Music.h"


CMusic::CMusic()
{
	//Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_OpenAudio(88200, MIX_DEFAULT_FORMAT, 2, NULL);

	//music
	music[0] = Mix_LoadMUS("music/runaway.wav");
	music[1] = Mix_LoadMUS("music/Jumper_titleScreenMusic_.wav");
	music[2] = Mix_LoadMUS("music/finalstoke.wav");
	music[3] = Mix_LoadMUS("music/sounds/2minutethunderstorm.wav");

	//sound
	sound[0] = Mix_LoadWAV("music/sounds/bass1.wav");
	sound[1] = Mix_LoadWAV("music/sounds/missle_launch.wav");
	sound[2] = Mix_LoadWAV("music/sounds/laserShot.wav");
	sound[3] = Mix_LoadWAV("music/sounds/beep.wav");
	sound[4] = Mix_LoadWAV("music/sounds/rain.wav");
	sound[5] = Mix_LoadWAV("music/sounds/lightningstrike.wav");
	sound[6] = Mix_LoadWAV("music/sounds/click.wav");


	if (music[0] == NULL)
	{
		std::cout << "music was not loaded!";
	}
}


CMusic::~CMusic()
{
	Mix_FreeMusic(music[0]);
	Mix_FreeMusic(music[1]);
	Mix_FreeMusic(music[2]);
	Mix_FreeMusic(music[3]);

	Mix_FreeChunk(sound[0]);
	Mix_FreeChunk(sound[1]);
	Mix_FreeChunk(sound[2]);
	Mix_FreeChunk(sound[3]);
	Mix_FreeChunk(sound[4]);
	Mix_FreeChunk(sound[5]);
	Mix_FreeChunk(sound[6]);


	Mix_CloseAudio();
}

void CMusic::playMusic(int song)
{
	Mix_PlayMusic(music[song], -1);
}

void CMusic::fadeInMusic(int song, int loopAmount, int ms)
{
	Mix_FadeInMusic(music[song], loopAmount, ms);
}

void CMusic::fadeOutMusic(int ms)
{
	Mix_FadeOutMusic(ms);
}

void CMusic::playSound(int soundNumber)
{
	Mix_PlayChannel(-1, sound[soundNumber], 0);
}

void CMusic::loopSound(int soundNumber, int numberOfTimes)
{
	Mix_PlayChannel(-1, sound[soundNumber], numberOfTimes);
}
