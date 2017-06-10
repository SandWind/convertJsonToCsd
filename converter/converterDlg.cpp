
// converterDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CconverterDlg �Ի���



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


// CconverterDlg ��Ϣ�������

BOOL CconverterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_JsonFilePath = _T("");
	m_CsdFilePath = _T("");
	
	m_progress.ShowWindow(false);
	m_progress.SetRange(0, 100);
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CconverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CconverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CconverterDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	TCHAR szFilter[] = _T("�ı��ļ�(*.json)|*.json");
	CFileDialog fileDlg(TRUE, _T("json"), NULL, 0, szFilter, this);
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
		m_JsonFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, m_JsonFilePath);
	}
}


void CconverterDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("�ı��ļ�(*.csd)|*.csd");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg(FALSE, _T("csd"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		m_CsdFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT2, m_CsdFilePath);
	}
}


void CconverterDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->DestroyWindow();
}


void CconverterDlg::OnBnClickedButton3()
{
	// ��ȡjson�ļ�����
	if (m_JsonFilePath.GetLength() > 0)
	{

		FILE *pFile = fopen(m_JsonFilePath.GetBuffer(m_JsonFilePath.GetLength()), "r");
		
		fseek(pFile, 0, SEEK_END);
		int len = ftell(pFile);
		m_pBuf = new char[len + 1];
		m_pBuf[len] = 0;
		rewind(pFile);


		rewind(pFile);   //ָ�븴λ  

		rapidjson::FileReadStream is(pFile, m_pBuf, sizeof(m_pBuf));
		m_jsonDoc.ParseStream(is);
		fclose(pFile);
		MessageBox(_T("��ȡ���"));

	}
}


void CconverterDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		
		MessageBox(_T("ת�����"));
	}
}





void CconverterDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	
	// TODO: �ڴ˴������Ϣ����������
}
