﻿#ifndef FILE_VIEW_H
#define FILE_VIEW_H

#include "ViewTree.h"
#include "../Base/ZTypes.h"

class CFileViewToolBar : public CMFCToolBar {
    virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler) {
        CMFCToolBar::OnUpdateCmdUI(reinterpret_cast<CFrameWnd*>(GetOwner()), bDisableIfNoHndler);
    }

    virtual BOOL AllowShowOnList() const {
        return FALSE;
    }
};

class CFileView : public CDockablePane {
  public:
    CFileView();

    void AdjustLayout();
    void OnChangeVisualStyle();

  protected:
    CViewTree m_wndFileView;
    CImageList m_FileViewImages;
    CFileViewToolBar m_wndToolBar;

  protected:
    void FillFileView();

    // 实现
  public:
    virtual ~CFileView();

  protected:
    afx_msg int32 OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int32 cx, int32 cy);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnProperties();
    afx_msg void OnFileOpen();
    afx_msg void OnFileOpenWith();
    afx_msg void OnDummyCompile();
    afx_msg void OnEditCut();
    afx_msg void OnEditCopy();
    afx_msg void OnEditClear();
    afx_msg void OnPaint();
    afx_msg void OnSetFocus(CWnd* pOldWnd);

    DECLARE_MESSAGE_MAP()
};

#endif  // FILE_VIEW_H