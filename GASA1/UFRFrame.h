/**
* @file		UFRFrame.h
* @project	GASA1
* @author	Adam Currie
* @date		2016-02-02
 */
#pragma once
#include "stdafx.h"
#include "GameObj.h"
#include "PhysObj.h"

#define UPDATE_TIMER 1
#define UPDATE_INTERVAL 32//ms between updates
#define MAX_BUFFER_WIDTH 640
#define MAX_BUFFER_HEIGHT 400

/**
 * @class	UFRFrame
 *
 * @brief	Main game frame of the Happy Flying Reptiles app.
 */
class UFRFrame : public CFrameWnd {

public:
	UFRFrame();
	~UFRFrame();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnObjOutsideView(WPARAM wParam, LPARAM lParam);

private:
	void Update();

	RECT viewPort;//logical dimensions of the viewport

	Gdiplus::Image* background;
	Gdiplus::Image* midground;
	Gdiplus::Image* foreground;

	Gdiplus::ImageAttributes* lightGreenColorKey;
	Gdiplus::ImageAttributes* darkGreenColorKey;

	GameObj* slingshotBack;
	GameObj* slingshotFront;
	PhysObj* bird;

	DECLARE_MESSAGE_MAP()
};

