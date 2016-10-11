﻿#ifndef SKY_BOX_H
#define SKY_BOX_H


#include "Base/Uncopyable.h"


class SkyBox : Base::Uncopyable {
public:
    SkyBox();
    ~SkyBox();


public:
    CString m_SkyBoxFolder;
    CString m_SkyBoxKindFolder;
    CString m_SkyBoxTP;
    CString m_SkyBoxLT;
    CString m_SkyBoxRT;
    CString m_SkyBoxBK;
    CString m_SkyBoxFR;

    bool iSkyBoxLoaded_;
    UINT g_texSkyBox[5];
};


#endif  // SKY_BOX_H