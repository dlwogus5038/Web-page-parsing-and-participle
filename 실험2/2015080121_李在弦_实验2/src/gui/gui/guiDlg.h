
// guiDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "stdafx.h"
#include "gui.h"
#include "guiDlg.h"
#include "afxdialogex.h"
#include "My_CharString.h"
#include "My_CharStringLink.h"
#include "My_Stack.h"
#include "UsefulLabel.h"
#include "get_files.h"
#include "extractInfo.h"
#include "My_HashTable.h"
#include "divideWords.h"
#include "AVL.h"
#include "My_BatchSearch.h"
#include <string>


// CguiDlg 对话框
class CguiDlg : public CDialogEx
{
// 构造
public:
	CguiDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GUI_DIALOG };

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
	afx_msg void OnBnClickedInitbutton();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnStnClickedLink1();
	afx_msg void OnStnClickedLink2();
	afx_msg void OnStnClickedLink3();
	afx_msg void OnStnClickedLink4();
	afx_msg void OnStnClickedLink5();
	afx_msg void OnStnClickedLink6();
	afx_msg void OnStnClickedLink7();
	afx_msg void OnStnClickedLink8();
	afx_msg void OnStnClickedLink9();
	afx_msg void OnStnClickedLink10();
	afx_msg void OnStnClickedLink11();
	afx_msg void OnStnClickedLink12();
	afx_msg void OnStnClickedLink13();
	afx_msg void OnStnClickedLink14();
	afx_msg void OnStnClickedLink15();
	afx_msg void OnStnClickedLink16();
	afx_msg void OnStnClickedLink17();
	afx_msg void OnStnClickedLink18();
	afx_msg void OnStnClickedLink19();
	afx_msg void OnStnClickedLink20();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_keyWord;
	CEdit m_record;
	My_AVL *MAVL;
	My_BatchSearch MBS;
	int MaxDicNum;
	int *checkLabelNum;
	std::string inputPath;
	std::string outputPath;
	CString state;
	CString *resultFileName;
	int CSnum;
	int lastLine;
};
