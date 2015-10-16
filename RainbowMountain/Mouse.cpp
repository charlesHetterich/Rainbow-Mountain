#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse(CSDL_setup* csdl_setup)
{	
	sdl_setup = csdl_setup;
	image = new Csprites(sdl_setup->GetRenderer(), "images/rainbow_pointer.png", 0, 0, 100, 100, 176, 176);
}


CMouse::~CMouse()
{
	delete sdl_setup;
	delete image;
}

void CMouse::mouseImage(int screen)
{
	SDL_ShowCursor(SDL_DISABLE); // hides mouse

	SDL_GetMouseState(&mouseX, &mouseY);

	image->setX(mouseX);
	image->setY(mouseY);
	
	if (screen != 0)
		image->drawReg(0, 0);
}

bool CMouse::mouseLeftClick()
{
	switch (sdl_setup->GetMainEvent()->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (sdl_setup->GetMainEvent()->button.button)
		{
		case SDL_BUTTON_LEFT:
			return true;
			break;
		}
		break;

	case SDL_MOUSEBUTTONUP:
	{
		switch (sdl_setup->GetMainEvent()->button.button)
		{
			case SDL_BUTTON_LEFT:
				
			break;
		}
	}

	default:
		break;
	}
	return false;
}