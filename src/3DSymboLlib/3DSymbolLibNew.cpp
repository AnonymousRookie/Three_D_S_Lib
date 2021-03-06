﻿#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "3DSymbolLibNew.h"
#include "MFCFrameWork/MainFrm.h"

#include "MFCFrameWork/3DSymbolLibNewDoc.h"
#include "3DSymbolLibNewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DSymbolLibNewApp

BEGIN_MESSAGE_MAP(CMy3DSymbolLibNewApp, CWinAppEx)
    ON_COMMAND(ID_APP_ABOUT, &CMy3DSymbolLibNewApp::OnAppAbout)
    // 基于文件的标准文档命令
    ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
    // 标准打印设置命令
    ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


CMy3DSymbolLibNewApp::CMy3DSymbolLibNewApp() {
    m_bHiColorIcons = TRUE;
    // 支持重新启动管理器
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
    // 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
    //     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
    //     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
    System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif
    // TODO(jason): 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
    // 为 CompanyName.ProductName.SubProduct.VersionInformation
    SetAppID(_T("3DSymbolLibNew.AppID.NoVersion"));
}

// 唯一的一个 CMy3DSymbolLibNewApp 对象

CMy3DSymbolLibNewApp theApp;


// CMy3DSymbolLibNewApp 初始化

BOOL CMy3DSymbolLibNewApp::InitInstance() {
    // 如果一个运行在 Windows XP 上的应用程序清单指定要
    // 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
    // 则需要 InitCommonControlsEx()。否则，将无法创建窗口。
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // 将它设置为包括所有要在应用程序中使用的
    // 公共控件类。
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);
    CWinAppEx::InitInstance();
    // 初始化 OLE 库
    if (!AfxOleInit()) {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }
    AfxEnableControlContainer();
    EnableTaskbarInteraction(FALSE);
    // 使用 RichEdit 控件需要  AfxInitRichEdit2()
    // AfxInitRichEdit2();
    // 标准初始化
    // 如果未使用这些功能并希望减小
    // 最终可执行文件的大小，则应移除下列
    // 不需要的特定初始化例程
    // 更改用于存储设置的注册表项
    SetRegistryKey(_T("三维符号库"));
    LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
    // 最近文件列表
    if (m_pRecentFileList != NULL) {
        int32 nMRUSize = m_pRecentFileList->GetSize();
        CString strMRUFile = "";
        g_strRecentOpenedFileArray.RemoveAll();
        // 将MRU列表里的工程文件提取出来
        for (int32 i = 0; i < nMRUSize; ++i) {
            strMRUFile = m_pRecentFileList->m_arrNames[i];
            if (strMRUFile != "") {
                g_strRecentOpenedFileArray.Add(strMRUFile);
            }
        }
    }
    // InitContextMenuManager();
    InitKeyboardManager();
    InitTooltipManager();
    CMFCToolTipInfo ttParams;
    ttParams.m_bVislManagerTheme = TRUE;
    theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
            RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);
    // 注册应用程序的文档模板。文档模板
    // 将用作文档、框架窗口和视图之间的连接
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CMy3DSymbolLibNewDoc),
        RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
        RUNTIME_CLASS(CMy3DSymbolLibNewView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);
    // 分析标准 shell 命令、DDE、打开文件操作的命令行
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);
    // 调度在命令行中指定的命令。如果
    // 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;
    // 唯一的一个窗口已初始化，因此显示它并对其进行更新
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    // 仅当具有后缀时才调用 DragAcceptFiles
    // 在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
    // 初始化GID+
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
    // Init google log lib
    FLAGS_log_dir = ".\\Log";  // 设置日志文件保存目录,这个目录必须是已经存在的,否则不能生成日志文件.
    CString strLogFolderPath = ".\\Log";
    // 判断路径是否存在
    if (!PathIsDirectory(strLogFolderPath)) {
        if (!CreateDirectory(strLogFolderPath, NULL)) {
            CString strMsg;
            strMsg.Format("创建路径\"%s\"失败！是否继续?", strLogFolderPath);
            AfxMessageBox(strMsg, MB_YESNO);
        }
    }
    // GLog生成的文件名格式是[文件名].[计算机名].[Windows用户名].[log].[等级].[年月日时分秒].[PID]例如:GOOGLE.ZHANGJIE-PC.zhangjie.log.INFO.20160121-194510.4532
    // 每个进程中至少要执行1次InitGoogleLogging(),否则不产生日志文件.例如:只在xxApp::InitInstance()中调用一次InitGoogleLogging(),xxDlg中不必调用也会把日志输出到指定文件.
    google::InitGoogleLogging("LOG-3DLIB");  // 设置日志文件名中的"文件名"字段.
    // ==============================================================
    // 读取系统设置配置文件
    // ==============================================================
    char systemConfigureDir[256];
    GetCurrentDirectoryA(256, systemConfigureDir);
    g_systemConfigureFile = strcat(systemConfigureDir, "\\system.ini");  // NOLINT
    CFileFind systemConfigureFinder;
    BOOL isSystemConfigureFind = systemConfigureFinder.FindFile(g_systemConfigureFile.c_str());
    if (!isSystemConfigureFind) {
        MessageBox(NULL, "Can not find system configure file!", "warning", MB_OK);
    }
    CString tmpPath;
    enum { MaxBufferSize = 256 };  // 读写配置文件Buffer大小
    ::GetPrivateProfileStringA("SceneDataPath", "path", "error", tmpPath.GetBuffer(MaxBufferSize), MaxBufferSize, g_systemConfigureFile.c_str());
    g_sceneDataPath = tmpPath.GetBuffer(0);
    tmpPath.ReleaseBuffer();
    // ==============================================================
    // 读取符号配置文件
    // ==============================================================
    /*char symbolsConfigureDir[256];
    GetCurrentDirectoryA(256,symbolsConfigureDir);
    g_symbolConfigureFile = strcat(symbolsConfigureDir,"\\symbols.xml");

    CFileFind symbolConfigureFinder;
    BOOL isSymbolConfigureFind = symbolConfigureFinder.FindFile(g_symbolConfigureFile.c_str());
    if(!isSymbolConfigureFind)
    {
        MessageBox(NULL,"Can not symbols.xml!","warning",MB_OK);
    }*/
    char symbolsConfigureDir[256];
    // GetCurrentDirectoryA(256,symbolsConfigureDir);
    strcpy(symbolsConfigureDir, g_sceneDataPath.c_str());  // NOLINT
    // g_symbolConfigureFile = strcat(symbolsConfigureDir,"\\SymbolLibrary\\symbols.xml");
    g_point_symbolConfigureFile = strcat(symbolsConfigureDir, "\\SymbolLibrary\\point.plib");  // NOLINT
    g_line_symbolConfigureFile = strcat(symbolsConfigureDir, "\\SymbolLibrary\\line.llib");  // NOLINT
    g_area_symbolConfigureFile = strcat(symbolsConfigureDir, "\\SymbolLibrary\\area.alib");  // NOLINT
    CFileFind symbolConfigureFinder;
    BOOL isSymbolConfigureFind = symbolConfigureFinder.FindFile(g_point_symbolConfigureFile.c_str());
    if (!isSymbolConfigureFind) {
        MessageBox(NULL, "Can not point.plib!", "warning", MB_OK);
    }
    // ==============================================================
    // 将XML文件中的信息读入全局list中
    // ==============================================================
    CoInitialize(NULL);  // 初始化COM
    CComPtr<IXMLDOMDocument> spDoc;  // DOM
    spDoc.CoCreateInstance(CLSID_DOMDocument);
    VARIANT_BOOL vb;
    spDoc->load(CComVariant(g_point_symbolConfigureFile.c_str()), &vb);  // 加载XML文件
    CComPtr<IXMLDOMElement> spRootEle;
    spDoc->get_documentElement(&spRootEle);  // 根节点
    CComPtr<IXMLDOMNodeList> spNodeList[5];
    string tmp[5];
    for (int32 i = 0; i < g_modelKindNumber; ++i) {
        tmp[i] = g_modelTree[i]._noteDirectory;
    }
    for (int32 i = 0; i < g_modelKindNumber; ++i) {
        spRootEle->selectNodes(_bstr_t(tmp[i].c_str()), &spNodeList[i]);
        long nLen;  // 子节点数  // NOLINT
        spNodeList[i]->get_length(&nLen);  // 子节点数
        for (int64 j = 0; j != nLen; ++j) {  // 遍历子节点
            CComPtr<IXMLDOMNode> spNode;
            spNodeList[i]->get_item(j, &spNode);
            BSTR text;
            spNode->get_text(&text);
            list<string>::iterator iter;
            string tmpStr = (_bstr_t)(text);
            iter = find(g_modelList[i].begin(), g_modelList[i].end(), tmpStr);
            if (iter == g_modelList[i].end()) {
                g_modelList[i].push_back(tmpStr);
            }
        }
    }
    CoUninitialize();
    // ==============================================================
    // 新建工程  OR  打开工程
    CProjectFileSetting prjFileSetDlg;
    prjFileSetDlg.DoModal();
    return TRUE;
}

int32 CMy3DSymbolLibNewApp::ExitInstance() {
    GdiplusShutdown(m_gdiplusToken);
    // 停止GLog, 与InitGoogleLogging()成对使用, 没有这句会造成内存泄漏
    google::ShutdownGoogleLogging();
    AfxOleTerm(FALSE);
    return CWinAppEx::ExitInstance();
}

class CAboutDlg : public CDialogEx {
  public:
    CAboutDlg();

    // 对话框数据
    enum { IDD = IDD_ABOUTBOX };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
  protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMy3DSymbolLibNewApp::OnAppAbout() {
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

// CMy3DSymbolLibNewApp 自定义加载/保存方法

void CMy3DSymbolLibNewApp::PreLoadState() {
    BOOL bNameValid;
    CString strName;
    bNameValid = strName.LoadString(IDS_EDIT_MENU);
    ASSERT(bNameValid);
    GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
    bNameValid = strName.LoadString(IDS_EXPLORER);
    ASSERT(bNameValid);
    GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMy3DSymbolLibNewApp::LoadCustomState() {
}

void CMy3DSymbolLibNewApp::SaveCustomState() {
}