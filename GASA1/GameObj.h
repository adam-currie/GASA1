/**
* @file		GameObj.h
* @project	GASA1
* @author	Adam Currie
* @date		2016-02-02
 */
#pragma once
#include "stdafx.h"

/**
 * @class	GameObj
 *
 * @brief	Represents a physical object in the game.
 */
class GameObj {
public:
	GameObj(Gdiplus::Image* img, int x, int y, int width, int height, RECT* view);
	virtual ~GameObj();
	virtual void Draw(Gdiplus::Graphics* g, int canvasWidth, int canvasHeight);
	virtual void Update();
	void SetX(int x);
	void SetY(int y);
protected:
	Gdiplus::Image* img;
	RECT* view;//logical viewport of the game
	int x, y;
	int width, height;
};

