﻿
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "../Base/ZTypes.h"

class CMainFrame : public CFrameWndEx {

  protected:  // 仅从序列化创建
    CMainFrame();
    DECLARE_DYNCREATE(CMainFrame)

    // 重写
  public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);  // NOLINT
    virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

    // 实现
  public:
    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;  // NOLINT
#endif

  protected:  // 控件条嵌入成员
    CMFCMenuBar       m_wndMenuBar;
    CMFCToolBar       m_wndToolBar;
    CMFCStatusBar     m_wndStatusBar;
    CMFCToolBarImages m_UserImages;
    CFileView         m_wndFileView;
    CClassView        m_wndClassView;
    COutputWnd        m_wndOutput;
    CPropertiesWnd    m_wndProperties;

    // 生成的消息映射函数
  protected:
    afx_msg int32 OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnViewCustomize();
    afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
    afx_msg void OnApplicationLook(UINT id);
    afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    DECLARE_MESSAGE_MAP()

    BOOL CreateDockingWindows();
    void SetDockingWindowIcons(BOOL bHiColorIcons);

  public:
    void Set_BarText(int32 index, CString strText);
};


