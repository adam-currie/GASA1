/**
* @file		PhysObj.cpp
* @project	GASA1
* @author	Adam Currie
* @date		2016-02-02
 */
#include "stdafx.h"
#include "PhysObj.h"
#include <math.h>

using namespace Gdiplus;

/**
 * @fn	PhysObj::PhysObj(Image* img, int x, int y, int width, int height, float gravity, RECT* view, HWND parent)
 *
 * @brief	Constructor.
 *
 * @param [in]	img 		Object iamge.
 * @param	x				The x coordinate.
 * @param	y				The y coordinate.
 * @param	width			The width.
 * @param	height			The height.
 * @param	gravity			The gravity acceleration applied on updates(pixels per update).
 * @param [in]	view		Logical viewport of the game.
 * @param	parent			Handle of the parent window.
 */
PhysObj::PhysObj(Image* img, int x, int y, int width, int height, float gravity, RECT* view, HWND parent)
	: GameObj(img, x, y, width, height, view) {
	xVelocity = 0;
	yVelocity = 0;
	this->gravity = gravity;
	parentHwnd = parent;
	isSendingOutsideViewMessages = true;//todo: set default false and add getter and setter
}

/**
 * @fn	PhysObj::~PhysObj()
 *
 * @brief	Destructor.
 */
PhysObj::~PhysObj(){
}

/**
 * @fn	void PhysObj::Update()
 *
 * @brief	Updates this object.
 */
void PhysObj::Update() {
	yVelocity += gravity;
	
	x += int(xVelocity + .5);
	y += int(yVelocity + .5);

	//outside viewport check
	if (isSendingOutsideViewMessages) {
		if (x < view->left || x > view->right || y < view->top || y > view->bottom) {
			PostMessage(parentHwnd, OBJ_OUTSIDE_VIEW_WM_MESSAGE, (WPARAM)this, NULL);
		}
	}
}

/**
 * @fn	void PhysObj::Launch(float velocity, float angle, bool ignoreOldVelocity)
 *
 * @brief	Launches the object in a direction.
 *
 * @param	velocity		 	The velocity.
 * @param	angle			 	The angle in degrees, 0 is right, increases clockwise.
 * @param	ignoreOldVelocity	true to ignore old velocity.
 */
void PhysObj::Launch(float velocity, float angle, bool ignoreOldVelocity) {
	if (ignoreOldVelocity) {
		xVelocity = 0;
		yVelocity = 0;
	}

	//conver to radians
	float rad = float(angle * PI / 180.0);

	//convert to horizontal and vertical velocities
	xVelocity += cos(rad)*velocity;
	yVelocity += sin(rad)*velocity;
}
