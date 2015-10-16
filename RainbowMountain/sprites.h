#pragma once;
#include "SDL_setup.h"

class Csprites
{
public:
	Csprites(SDL_Renderer* renderer, std::string FilePath, int x, int y, int w, int h, int imageW, int imageH);
	~Csprites();

	void drawReg(int x, int y);
	void drawStatic();
	void drawMotionBlur(int x, int y, int blurLevel);

	void setAplpha(int solidity);
	int getAlpha();
	void setAngle(double newAngle);
	double getAngle();
	std::string getImage();
	void setImage(std::string FilePath);

	SDL_Rect getRect();
	SDL_Texture* getTexture();

	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	int getW();
	void setW(int w);
	int getH();
	void setH(int h);

	int getFrame();
	void setFrame(int newFrame);
	int getFrameRow();
	void setFrameRow(int newFrameRow);

	//Focusing screen
	void setFocusX(int newFocusX);
	void setFocusY(int newFocusY);
	int getFocusX();
	int getFocusY();
	
	//reaching your view
	void setSightReach(int x, int y);
	int getSightReachX();
	int getSightReachY();

	void setZoom(float Zoom);
	float getZoom();
	void setZoomSpeed(float speed, float decelerate);
	float getZoomSpeed();
	void zeroOutZoomSpeed();

	//abstact effects
	void setShake(int shake);
	int getShake();
	void setHigh(int high);
	int getHigh();
	
private:
	int alpha;
	int imageWidth;
	int imageHeight;
	int frame;
	int frameRow;
	double angle;

	std::string filePath;
	SDL_Texture* image;
	SDL_Rect rect;
	SDL_Rect crop;
	SDL_Renderer* renderer;
};