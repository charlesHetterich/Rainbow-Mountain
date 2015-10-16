#include "stdafx.h"
#include "sprites.h"

int focusY;
int focusX;
int sightReachX;
int sightReachY;
float zoom = 1;
float zoomNumber;
float zoomSpeed[2];

//abstactaffects
int shake;
int high;

Csprites::Csprites(SDL_Renderer* renderer, std::string FilePath, int x, int y, int w, int h, int imageW, int imageH)
{
	this->renderer = renderer;
	filePath = FilePath;
	image = NULL;
	image = IMG_LoadTexture(renderer, FilePath.c_str());

	if (image == NULL && filePath.c_str() != NULL)
	{
		std::cout << "Couldn't load " << filePath.c_str() << std::endl;
	}
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	imageWidth = imageW;
	imageHeight = imageH;

	crop.x = 0;
	crop.y = 0;
	crop.w = imageWidth;
	crop.h = imageHeight;

	alpha = 255;
}

Csprites::~Csprites()
{
	SDL_DestroyTexture(image);
}

void Csprites::drawReg(int x, int y)
{
	int OGRectX = rect.x;
	int OGRectY = rect.y;
	int OGRectW = rect.w;
	int OGRectH = rect.h;
	if (shake > 0)
	{
		rect.x = ((rect.x - focusX)*zoom) + sightReachX + rand() % (2 * shake) - shake + cos(clock() / 300.0f) * high;
		rect.y = ((rect.y - focusY)*zoom) + sightReachY + rand() % (2 * shake) - shake + sin(clock() / 300.0f) * high;
	}
	else
	{
		rect.x = ((rect.x - focusX)*zoom) + sightReachX + cos(clock() / 300.0f) * high;
		rect.y = ((rect.y - focusY)*zoom) + sightReachY + sin(clock() / 300.0f) * high;
	}
	SDL_RenderCopyEx(renderer, image, &crop, &rect, angle, NULL, SDL_FLIP_NONE);

	if (high > 0)
	{
		if (alpha - 150 > 0)
			SDL_SetTextureAlphaMod(image, alpha - 150);
		else
			SDL_SetTextureAlphaMod(image, 0);
		if (shake > 0)
		{
			rect.x = ((rect.x - focusX)*zoom) + sightReachX + rand() % (2 * shake) - shake + cos(M_PI + clock() / 300.0f) * high;
			rect.y = ((rect.y - focusY)*zoom) + sightReachY + rand() % (2 * shake) - shake + sin(M_PI + clock() / 300.0f) * high;
		}
		else
		{
			rect.x = ((rect.x - focusX)*zoom) + sightReachX + cos(M_PI + clock() / 300.0f) * high;
			rect.y = ((rect.y - focusY)*zoom) + sightReachY + sin(M_PI + clock() / 300.0f) * high;
		}
	
		SDL_RenderCopyEx(renderer, image, &crop, &rect, angle, NULL, SDL_FLIP_NONE);
		SDL_SetTextureAlphaMod(image, alpha);
	}

	rect.w = rect.w * zoom;
	rect.h = rect.h * zoom;

	rect.x = OGRectX;
	rect.y = OGRectY;
	rect.w = OGRectW;
	rect.h = OGRectH;
}

void Csprites::drawStatic()
{
	SDL_RenderCopy(renderer, image, &crop, &rect);
}

void Csprites::drawMotionBlur(int x, int y, int blurLevel)
{
	int OGRectX = rect.x;
	int OGRectY = rect.y;
	rect.x += x;
	rect.y += y;

	SDL_RenderCopy(renderer, image, NULL, &rect);

	rect.x = OGRectX;
	rect.y = OGRectY;
}

void Csprites::setAplpha(int solidity)
{
	alpha = solidity;
	SDL_SetTextureAlphaMod(image, alpha);
	
}

int Csprites::getAlpha()
{
	return alpha;
}

void Csprites::setAngle(double newAngle)
{
	angle = newAngle;
}

double Csprites::getAngle()
{
	return angle;
}

int Csprites::getX()
{
	return rect.x;
}

void Csprites::setX(int x)
{
	rect.x = x;
}

int Csprites::getY()
{
	return rect.y;
}

void Csprites::setY(int y)
{
	rect.y = y;
}

int Csprites::getW()
{
	return rect.w;
}

void Csprites::setW(int w)
{
	rect.w = w;
}

int Csprites::getH()
{
	return rect.h;
}

void Csprites::setH(int h)
{
	rect.h = h;
}

SDL_Rect Csprites::getRect()
{
	return rect;
}

std::string Csprites::getImage()
{
	return filePath;
	SDL_SetTextureAlphaMod(image, alpha);
}

void Csprites::setImage(std::string FilePath)
{
	filePath = FilePath;
	image = IMG_LoadTexture(renderer, filePath.c_str());
	
}

int Csprites::getFrame()
{
	return frame;
}

void Csprites::setFrame(int newFrame)
{
	frame = newFrame;
	crop.x = imageWidth*frame;
}

int Csprites::getFrameRow()
{
	return frameRow;
}

void Csprites::setFrameRow(int newFrameRow)
{
	frameRow = newFrameRow;
	crop.y = imageHeight*frameRow;
}

void Csprites::setFocusX(int newFocusX)
{
	focusX = newFocusX;
}

void Csprites::setFocusY(int newFocusY)
{
	focusY = newFocusY;
}

int Csprites::getFocusX()
{
	return focusX;
}

int Csprites::getFocusY()
{
	return focusY;
}

void Csprites::setSightReach(int x, int y)
{
	sightReachX = x;
	sightReachY = y;
}

int Csprites::getSightReachX()
{
	return sightReachX;
}

int Csprites::getSightReachY()
{
	return sightReachY;
}

float Csprites::getZoom()
{
	return zoomNumber;
}

void Csprites::setZoom(float Zoom)
{
	zoomNumber = Zoom;
	zoom = pow(1.01, zoomNumber);
}

void Csprites::setZoomSpeed(float speed, float deceleration)
{
	zoomSpeed[0] = speed;
	zoomSpeed[1] = deceleration;
}

float Csprites::getZoomSpeed()
{
	return zoomSpeed[0];
}

void Csprites::zeroOutZoomSpeed()
{
	if (zoomSpeed[0] > 0) { zoomSpeed[0] -= zoomSpeed[1]; }
	else if (zoomSpeed[0] < 0) { zoomSpeed[0] += zoomSpeed[1]; }

	if (abs(zoomSpeed[0]) <= zoomSpeed[1]) { zoomSpeed[0] = 0; }
}

SDL_Texture* Csprites::getTexture()
{
	return image;
}

void Csprites::setShake(int Shake)
{
	shake = Shake;
}

int Csprites::getShake()
{
	return shake;
}

void Csprites::setHigh(int High)
{
	high = High;
}

int Csprites::getHigh()
{
	return high;
}