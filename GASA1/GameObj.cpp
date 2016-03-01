/**
* @file		GameObj.cpp
* @project	GASA1
* @author	Adam Currie
* @date		2016-02-02
 */
#include "stdafx.h"
#include "GameObj.h"

using namespace Gdiplus;

/**
 * @fn	GameObj::GameObj(Image* img, int x, int y, int width, int height, RECT* view)
 *
 * @brief	Constructor.
 *
 * @param [in]	img 		Object Image.
 * @param	x				The x coordinate.
 * @param	y				The y coordinate.
 * @param	width			The width.
 * @param	height			The height.
 * @param [in]	view		Logical viewport of the game.
 */
GameObj::GameObj(Image* img, int x, int y, int width, int height, RECT* view) {
	this->img = img;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->view = view;
}

/**
 * @fn	GameObj::~GameObj()
 *
 * @brief	Destructor.
 */
GameObj::~GameObj() {
	delete img;
}

/**
 * @fn	void GameObj::Draw(Graphics* g, int canvasWidth, int canvasHeight)
 *
 * @brief	Draws the object.
 *
 * @param [in]	g   		Graphics to draw to.
 * @param	canvasWidth 	Width of the canvas.
 * @param	canvasHeight	Height of the canvas.
 */
void GameObj::Draw(Graphics* g, int canvasWidth, int canvasHeight) {
	float xScale = (canvasWidth / float(view->right - view->left));
	float yScale = (canvasHeight / float(view->bottom - view->top));

	int renderX = int((x - view->left) * xScale);
	int renderY = int((y - view->top) * yScale);
	int renderWidth = int(width * xScale);
	int renderHeight = int(height * yScale);

	g->DrawImage(img, renderX, renderY, renderWidth, renderHeight);
}

/**
 * @fn	void GameObj::Update()
 *
 * @brief	Updates this object.
 */
void GameObj::Update() {
}

/**
 * @fn	void GameObj::SetX(int x)
 *
 * @brief	Sets an x coordinate.
 *
 * @param	x	The x coordinate.
 */
void GameObj::SetX(int x) {
	this->x = x;
}

/**
 * @fn	void GameObj::SetY(int y)
 *
 * @brief	Sets a y coordinate.
 *
 * @param	y	The y coordinate.
 */
void GameObj::SetY(int y) {
	this->y = y;
}
