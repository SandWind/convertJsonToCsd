
// converterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include<cstdlib>
#include<string>
#include "../rapidjson/include/document.h"
#include "../rapidjson/include/writer.h"


// CconverterDlg �Ի���
class CconverterDlg : public CDialogEx
{
// ����
public:
	CconverterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONVERTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	
	afx_msg void OnBnClickedButton2();

	CString m_JsonFilePath;
	CString m_CsdFilePath;
	// ת�����ȣ���ȡ����
	CProgressCtrl m_progress;
	
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
private:
	
	rapidjson::Document m_jsonDoc;
	char *m_pBuf;
public:
	afx_msg void OnDestroy();
};
