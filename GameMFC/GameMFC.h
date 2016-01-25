
// GameMFC.h : main header file for the GameMFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGameMFCApp:
// See GameMFC.cpp for the implementation of this class
//

class CGameMFCApp : public CWinApp
{
public:
	CGameMFCApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGameMFCApp theApp;
