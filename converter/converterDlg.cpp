
// converterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "converter.h"
#include "converterDlg.h"
#include "afxdialogex.h"
#include "../rapidjson/include/filereadstream.h"
#include "XcsdFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CconverterDlg 对话框



CconverterDlg::CconverterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONVERTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CconverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CconverterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CconverterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CconverterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CconverterDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CconverterDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CconverterDlg::OnBnClickedButton4)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CconverterDlg 消息处理程序

BOOL CconverterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_JsonFilePath = _T("");
	m_CsdFilePath = _T("");
	
	m_progress.ShowWindow(false);
	m_progress.SetRange(0, 100);
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CconverterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CconverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CconverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CconverterDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	TCHAR szFilter[] = _T("文本文件(*.json)|*.json");
	CFileDialog fileDlg(TRUE, _T("json"), NULL, 0, szFilter, this);
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		m_JsonFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, m_JsonFilePath);
	}
}


void CconverterDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("文本文件(*.csd)|*.csd");
	// 构造保存文件对话框   
	CFileDialog fileDlg(FALSE, _T("csd"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		m_CsdFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT2, m_CsdFilePath);
	}
}


void CconverterDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	this->DestroyWindow();
}


void CconverterDlg::OnBnClickedButton3()
{
	// 读取json文件内容
	if (m_JsonFilePath.GetLength() > 0)
	{

		FILE *pFile = fopen(m_JsonFilePath.GetBuffer(m_JsonFilePath.GetLength()), "r");
		
		fseek(pFile, 0, SEEK_END);
		int len = ftell(pFile);
		m_pBuf = new char[len + 1];
		m_pBuf[len] = 0;
		rewind(pFile);


		rewind(pFile);   //指针复位  

		rapidjson::FileReadStream is(pFile, m_pBuf, sizeof(m_pBuf));
		m_jsonDoc.ParseStream(is);
		fclose(pFile);
		MessageBox(_T("读取完毕"));

	}
}


void CconverterDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_CsdFilePath.GetLength() > 0)
	{
		/*XcsdFile *csd = new XcsdFile(m_CsdFilePath.GetBuffer(m_CsdFilePath.GetLength()), "csd.cfg");
		csd->BeginCsd();
		csd->WritePropertyGroup(m_jsonDoc);
		csd->WriteContent(m_jsonDoc);
		csd->EndCsd();*/
		XcsdFile csd(m_CsdFilePath.GetBuffer(m_CsdFilePath.GetLength()), "csd.cfg");
		csd.BeginCsd();
		csd.WritePropertyGroup(m_jsonDoc);
		csd.WriteContent(m_jsonDoc);
		csd.EndCsd();
		delete[] m_pBuf;
		m_pBuf = NULL;
		
		MessageBox(_T("转化完毕"));
	}
}





void CconverterDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	
	// TODO: 在此处添加消息处理程序代码
}
