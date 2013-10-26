// CUP8583Utility.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCUP8583UtilityApp:
// See CUP8583Utility.cpp for the implementation of this class
//

class CCUP8583UtilityApp : public CWinApp
{
public:
	CCUP8583UtilityApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCUP8583UtilityApp theApp;