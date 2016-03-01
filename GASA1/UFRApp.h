/**
* @file		UFRApp.h
* @project	GASA1
* @author	Adam Currie
* @date		2016-02-02
 */
#pragma once

/**
 * @class	UFRApp
 *
 * @brief	Unhappy Flying Reptiles game application.
 */
class UFRApp : public CWinApp {
public:
	virtual BOOL InitInstance();
	int ExitInstance();
	ULONG_PTR m_gdiplusToken;
};

UFRApp theApp;

