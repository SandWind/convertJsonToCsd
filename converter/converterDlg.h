
// converterDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include<cstdlib>
#include<string>
#include "../rapidjson/include/document.h"
#include "../rapidjson/include/writer.h"


// CconverterDlg 对话框
class CconverterDlg : public CDialogEx
{
// 构造
public:
	CconverterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONVERTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 转换进度，读取进度
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
