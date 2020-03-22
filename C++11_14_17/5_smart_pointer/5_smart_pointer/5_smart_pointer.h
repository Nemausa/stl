
// 5_smart_pointer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy5_smart_pointerApp:
// See 5_smart_pointer.cpp for the implementation of this class
//

class CMy5_smart_pointerApp : public CWinApp
{
public:
	CMy5_smart_pointerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy5_smart_pointerApp theApp;