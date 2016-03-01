/**
* @file		PhysObj.h
* @project	GASA1
* @author	Adam Currie
* @date		2016-02-02
 */
#pragma once
#include "stdafx.h"
#include "GameObj.h"

#define PI 3.14159265

/**
 * @class	PhysObj
 *
 * @brief	Game physics object.
 */
class PhysObj : public GameObj{
public:
	PhysObj(Gdiplus::Image* img, int x, int y, int width, int height, float gravity, RECT* view, HWND parent);
	~PhysObj();
	void Update();
	void Launch(float velocity, float angle, bool ignoreOldVelocity);
protected:
	HWND parentHwnd;
	bool isSendingOutsideViewMessages;
	double xVelocity, yVelocity;
	float gravity;
};

