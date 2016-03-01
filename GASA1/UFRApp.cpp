/**
* @file		UFRApp.cpp
* @project	GASA1
* @author	Adam Currie
* @date		2016-02-02
 */
#include "stdafx.h"
#include "UFRApp.h"
#include "UFRFrame.h"

using namespace Gdiplus;

/**
 * @fn	BOOL UFRApp::InitInstance()
 *
 * @brief	Effective entry point of the application.
 *
 * @return	true if it succeeds, false if it fails.
 */
BOOL UFRApp::InitInstance(){
	//Initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	//main window
	m_pMainWnd = new UFRFrame;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}

/**
 * @fn	int UFRApp::ExitInstance()
 *
 * @brief	Called when the app instance is exiting.
 *
 * @return	0 for success, otherwise an error code.
 */
int UFRApp::ExitInstance() {
	GdiplusShutdown(m_gdiplusToken);
	delete m_pMainWnd;
	return CWinApp::ExitInstance();
}
