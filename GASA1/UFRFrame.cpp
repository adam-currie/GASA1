/**
* @file		UFRFrame.cpp
* @project	GASA1
* @author	Adam Currie
* @date		2016-02-02
 */
#include "stdafx.h"
#include "UFRFrame.h"

using namespace Gdiplus;

BEGIN_MESSAGE_MAP(UFRFrame, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(OBJ_OUTSIDE_VIEW_WM_MESSAGE, OnObjOutsideView)
END_MESSAGE_MAP()

/**
 * @fn	UFRFrame::UFRFrame()
 *
 * @brief	Default constructor, sets up resources initial conditions of the game.
 */
UFRFrame::UFRFrame() {

	//create window
	Create(
		NULL,
		TEXT("Unhappy Flying Reptiles"),
		WS_OVERLAPPEDWINDOW,
		rectDefault,
		NULL,
		NULL
	);

	//logical viewport
	viewPort.top = 0;
	viewPort.left = 0;
	viewPort.bottom = 400;
	viewPort.right = 640;

	background = new Image(TEXT("img/Background.bmp"), false);
	midground = new Image(TEXT("img/Midground.bmp"), false);
	foreground = new Image(TEXT("img/Foreground.bmp"), false);

	lightGreenColorKey = new ImageAttributes();
	lightGreenColorKey->SetColorKey(
		Color(0, 155, 0),
		Color(150, 255, 150),
		ColorAdjustTypeBitmap
	);

	darkGreenColorKey = new ImageAttributes();
	darkGreenColorKey->SetColorKey(
		Color(0, 100, 0),
		Color(150, 255, 150),
		ColorAdjustTypeBitmap
	);

	Image* slingBackImg = new Image(TEXT("img/slingshot1.png"), false);
	Image* slingFrontImg = new Image(TEXT("img/slingshot2.png"), false);
	slingshotBack = new GameObj(slingBackImg, 75, viewPort.bottom - 110, 50, 110, &viewPort);
	slingshotFront = new GameObj(slingFrontImg, 75, viewPort.bottom - 110, 50, 110, &viewPort);

	Image* birdImg = new Image(TEXT("img/reptile.png"), false);
	bird = new PhysObj(birdImg, 10, viewPort.bottom-60, 50, 50, 2.5, &viewPort, GetSafeHwnd());

	bird->Launch(50, -45, true);

	//gameloop
	SetTimer(UPDATE_TIMER, UPDATE_INTERVAL, NULL);
}

/**
 * @fn	UFRFrame::~UFRFrame()
 *
 * @brief	Destructor.
 */
UFRFrame::~UFRFrame() {
	KillTimer(UPDATE_TIMER);
	delete background;
	delete midground;
	delete foreground;
	delete lightGreenColorKey;
	delete darkGreenColorKey;
	delete slingshotBack;
	delete slingshotFront;
	delete bird;
}

/**
 * @fn	void UFRFrame::OnTimer(UINT_PTR nIDEvent)
 *
 * @brief	Executes the timer action.
 *
 * @param	nIDEvent	The identifier event.
 */
void UFRFrame::OnTimer(UINT_PTR nIDEvent) {
	CFrameWnd::OnTimer(nIDEvent);

	//gameloop
	if (nIDEvent == UPDATE_TIMER) {
		Update();//logic
		Invalidate();//render
	}
}

/**
 * @fn	void UFRFrame::OnPaint()
 *
 * @brief	Paints this window.
 */
void UFRFrame::OnPaint() {
	RECT clientRect;//size of the client portion of the window
	GetClientRect(&clientRect);
	RECT bufRect = clientRect;//size of the buffer image

	if (bufRect.right > MAX_BUFFER_WIDTH) {
		bufRect.right = MAX_BUFFER_WIDTH;
	}
	if (bufRect.bottom > MAX_BUFFER_HEIGHT) {
		bufRect.bottom = MAX_BUFFER_HEIGHT;
	}

	//set up buffer
	Bitmap buf(bufRect.right, bufRect.bottom);
	Graphics* g = Graphics::FromImage(&buf);

	//draw background and midground
	g->DrawImage(background, 0, 0, bufRect.right, bufRect.bottom);
	g->DrawImage(
		midground,
		Rect(0, 0, bufRect.right, bufRect.bottom),
		0, 0, midground->GetWidth(), midground->GetHeight(),
		UnitPixel,
		lightGreenColorKey
	);
	
	//draw game objects
	slingshotBack->Draw(g, bufRect.right, bufRect.bottom);
	bird->Draw(g, bufRect.right, bufRect.bottom);
	slingshotFront->Draw(g, bufRect.right, bufRect.bottom);

	//draw foreground
	g->DrawImage(
		foreground,
		Rect(0, 0, bufRect.right, bufRect.bottom),
		0, 0, foreground->GetWidth(), foreground->GetHeight(),
		UnitPixel,
		darkGreenColorKey
	);

	//push buffer
	CPaintDC dc(this);
	Graphics screenGraphics(dc.m_hDC);
	screenGraphics.DrawImage(&buf, 0, 0, clientRect.right, clientRect.bottom);

	delete g;
}

/**
 * @fn	void UFRFrame::Update()
 *
 * @brief	Updates game logic, called once before every render.
 */
void UFRFrame::Update() {
	bird->Update();
}

/**
 * @fn	BOOL UFRFrame::OnEraseBkgnd(CDC* pDC)
 *
 * @brief	Executes the erase bkgnd action.
 *
 * @param [in,out]	pDC	If non-null, the device-context.
 *
 * @return	Nonzero if it erases the background; otherwise 0.
 */
BOOL UFRFrame::OnEraseBkgnd(CDC* pDC) {
	return FALSE;
}

/**
 * @fn	LRESULT UFRFrame::OnObjOutsideView(WPARAM wParam, LPARAM lParam)
 *
 * @brief	Executes when a PhysObj goes out of view.
 *
 * @param	wParam	The wParam field of the message.
 * @param	lParam	The lParam field of the message.
 *
 * @return	LRESULT
 */
LRESULT UFRFrame::OnObjOutsideView(WPARAM wParam, LPARAM lParam){
	PhysObj* obj = (PhysObj*)wParam;

	if (obj == bird) {
		//relauch bird
		bird->SetX(10);
		bird->SetY(viewPort.bottom - 60);
		bird->Launch(50, -45, true);
	}

	return 0;
}
