﻿#ifndef CLASS_VIEW_H
#define CLASS_VIEW_H


#include "ViewTree.h"
#include "../Base/ZTypes.h"


class CClassToolBar : public CMFCToolBar {
    virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler) {
        CMFCToolBar::OnUpdateCmdUI(reinterpret_cast<CFrameWnd*>(GetOwner()), bDisableIfNoHndler);
    }

    virtual BOOL AllowShowOnList() const {
        return FALSE;
    }
};

class CClassView : public CDockablePane {
  public:
    CClassView();
    virtual ~CClassView();

    void AdjustLayout();
    void OnChangeVisualStyle();

  protected:
    CClassToolBar m_wndToolBar;
    CViewTree m_wndClassView;
    CImageList m_ClassViewImages;
    UINT m_nCurrSort;

    void FillClassView();

  public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

  protected:
    afx_msg int32 OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int32 cx, int32 cy);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnClassAddMemberFunction();
    afx_msg void OnClassAddMemberVariable();
    afx_msg void OnClassDefinition();
    afx_msg void OnClassProperties();
    afx_msg void OnNewFolder();
    afx_msg void OnPaint();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
    afx_msg void OnSort(UINT id);
    afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

    DECLARE_MESSAGE_MAP()
};

#endif  // CLASS_VIEW_H