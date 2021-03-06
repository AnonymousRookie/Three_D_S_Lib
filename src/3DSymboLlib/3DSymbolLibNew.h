﻿
// 3DSymbolLibNew.h : 3DSymbolLibNew 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "MFCFrameWork/resource.h"       // 主符号
// #include "GdiPlus.h"
#include "stdafx.h"
#include "GlobalVariable.h"

#include "ProjectFileSetting.h"
#include "Base/ZTypes.h"




// CMy3DSymbolLibNewApp:
// 有关此类的实现，请参阅 3DSymbolLibNew.cpp
//

class CMy3DSymbolLibNewApp : public CWinAppEx {
  public:
    CMy3DSymbolLibNewApp();


  // 重写
  public:
    virtual BOOL InitInstance();
    virtual int32 ExitInstance();

    // 实现
    UINT  m_nAppLook;
    BOOL  m_bHiColorIcons;

    virtual void PreLoadState();
    virtual void LoadCustomState();
    virtual void SaveCustomState();

    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()

    GdiplusStartupInput   m_gdiplusStartupInput;   // 只需要在程序运行最开始初始化一次
    ULONG_PTR             m_gdiplusToken;          // 只需要在程序运行最开始初始化一次
};

extern CMy3DSymbolLibNewApp theApp;
