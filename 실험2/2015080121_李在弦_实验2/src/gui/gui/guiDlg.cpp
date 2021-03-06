
// guiDlg.cpp : 实现文件
//

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
#include "FindResultTxt.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <locale>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CguiDlg 对话框



CguiDlg::CguiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CguiDlg::IDD, pParent)
	, m_keyWord(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CguiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KeyWord, m_keyWord);
	DDX_Control(pDX, IDC_Record, m_record);
}

BEGIN_MESSAGE_MAP(CguiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INITBUTTON, &CguiDlg::OnBnClickedInitbutton)
	ON_BN_CLICKED(IDC_Search, &CguiDlg::OnBnClickedSearch)
	ON_STN_CLICKED(IDC_Link1, &CguiDlg::OnStnClickedLink1)
	ON_STN_CLICKED(IDC_Link2, &CguiDlg::OnStnClickedLink2)
	ON_STN_CLICKED(IDC_Link3, &CguiDlg::OnStnClickedLink3)
	ON_STN_CLICKED(IDC_Link4, &CguiDlg::OnStnClickedLink4)
	ON_STN_CLICKED(IDC_Link5, &CguiDlg::OnStnClickedLink5)
	ON_STN_CLICKED(IDC_Link6, &CguiDlg::OnStnClickedLink6)
	ON_STN_CLICKED(IDC_Link7, &CguiDlg::OnStnClickedLink7)
	ON_STN_CLICKED(IDC_Link8, &CguiDlg::OnStnClickedLink8)
	ON_STN_CLICKED(IDC_Link9, &CguiDlg::OnStnClickedLink9)
	ON_STN_CLICKED(IDC_Link10, &CguiDlg::OnStnClickedLink10)
	ON_STN_CLICKED(IDC_Link11, &CguiDlg::OnStnClickedLink11)
	ON_STN_CLICKED(IDC_Link12, &CguiDlg::OnStnClickedLink12)
	ON_STN_CLICKED(IDC_Link13, &CguiDlg::OnStnClickedLink13)
	ON_STN_CLICKED(IDC_Link14, &CguiDlg::OnStnClickedLink14)
	ON_STN_CLICKED(IDC_Link15, &CguiDlg::OnStnClickedLink15)
	ON_STN_CLICKED(IDC_Link16, &CguiDlg::OnStnClickedLink16)
	ON_STN_CLICKED(IDC_Link17, &CguiDlg::OnStnClickedLink17)
	ON_STN_CLICKED(IDC_Link18, &CguiDlg::OnStnClickedLink18)
	ON_STN_CLICKED(IDC_Link19, &CguiDlg::OnStnClickedLink19)
	ON_STN_CLICKED(IDC_Link20, &CguiDlg::OnStnClickedLink20)
END_MESSAGE_MAP()


// CguiDlg 消息处理程序

BOOL CguiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_record.SetWindowTextW(_T("请输入关键词！\n")); // 记录部分的变量（m_record）
	GetDlgItem(IDC_Search)->EnableWindow(false); // 初始化前不允许使用搜索功能
	inputPath = "output/";
	outputPath = "output/";
	MaxDicNum = 0;
	checkLabelNum = 0;
	resultFileName = NULL;
	CSnum = 0; // 文档个数
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CguiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CguiDlg::OnPaint()
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
HCURSOR CguiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CguiDlg::OnBnClickedInitbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = 0;
	int CSnum = 0;

	GetDlgItem(IDC_Status)->SetWindowTextW(_T("START INITIALIZATION.."));
	GetDlgItem(IDC_INITBUTTON)->EnableWindow(false); // 初始化只能做一次就可以
	lastLine = m_record.LineIndex(m_record.GetLineCount() - 1);

	_wsetlocale(LC_ALL, L"China");
	setlocale(LC_CTYPE, "");

	UpdateData(true);

	MAVL = new My_AVL;

	m_record.SetWindowTextW(_T("请输入关键词！\n"));

	state = _T("网页解析开始..\r\n");

	m_record.SetSel(lastLine + 1, lastLine + 2, 0);
	m_record.ReplaceSel(state);  // 在最后一行添加新的内容


	extractInfo(checkLabelNum, inputPath, outputPath); //网页解析

	state = _T("网页解析结束!\r\n");

	lastLine = m_record.LineIndex(m_record.GetLineCount() - 1);
	m_record.SetSel(lastLine + 1, lastLine + 2, 0);
	m_record.ReplaceSel(state);  // 在最后一行添加新的内容

	state = _T("载入词库开始..\r\n");

	lastLine = m_record.LineIndex(m_record.GetLineCount() - 1);
	m_record.SetSel(lastLine + 1, lastLine + 2, 0);
	m_record.ReplaceSel(state);  // 在最后一行添加新的内容

	MAVL->initDictionary(MaxDicNum, MAVL); //保存“词库”里面的所有单词到自定义的哈希表里

	state = _T("载入词库结束!\r\n");

	lastLine = m_record.LineIndex(m_record.GetLineCount() - 1);
	m_record.SetSel(lastLine + 1, lastLine + 2, 0);
	m_record.ReplaceSel(state);  // 在最后一行添加新的内容

	state = _T("分词操作开始..\r\n");

	lastLine = m_record.LineIndex(m_record.GetLineCount() - 1);
	m_record.SetSel(lastLine + 1, lastLine + 2, 0);
	m_record.ReplaceSel(state);  // 在最后一行添加新的内容

	divideWords(MAVL, outputPath, outputPath, checkLabelNum, MaxDicNum); //分词算法

	state = _T("分词操作结束!\r\n");

	lastLine = m_record.LineIndex(m_record.GetLineCount() - 1);
	m_record.SetSel(lastLine + 1, lastLine + 2, 0);
	m_record.ReplaceSel(state);  // 在最后一行添加新的内容

	GetDlgItem(IDC_Status)->SetWindowTextW(_T("INITIALIZATION COMPLETE!"));
	GetDlgItem(IDC_Search)->EnableWindow(true); // 允许使用搜索功能，可以按了
	UpdateData(false);
}


void CguiDlg::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = 0;
	CString LinkName = _T("");

	UpdateData(true);

	state.Format(_T("%s%s%s"), _T("对 \""), m_keyWord, _T("\" 开始批量搜索.."));
	state += _T("\r\n"); 

	lastLine = m_record.LineIndex(m_record.GetLineCount() - 1);
	m_record.SetSel(lastLine + 1, lastLine + 2, 0);
	m_record.ReplaceSel(state);  // 在最后一行添加新的内容

	MBS.startSearch(MAVL, MaxDicNum, m_keyWord);

	state = _T("批量搜索结束!\r\n");

	lastLine = m_record.LineIndex(m_record.GetLineCount() - 1);
	m_record.SetSel(lastLine + 1, lastLine + 2, 0);
	m_record.ReplaceSel(state);  // 在最后一行添加新的内容

	GetDlgItem(IDC_Search)->EnableWindow(true);
	GetDlgItem(IDC_Status)->SetWindowTextW(_T("SEARCH COMPLETE!"));

	FindResultTxt(resultFileName , CSnum); // 从‘gui’的结果文件‘result_gui.txt’中获取文档

	for (i = 0; i < CSnum; i++) // 命名结果‘text’
	{
		if (i == 0)
		{
			LinkName += _T("1. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link1)->SetWindowTextW(LinkName);
		}
		else if (i == 1)
		{
			LinkName += _T("2. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link2)->SetWindowTextW(LinkName);
		}
		else if (i == 2)
		{
			LinkName += _T("3. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link3)->SetWindowTextW(LinkName);
		}
		else if (i == 3)
		{
			LinkName += _T("4. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link4)->SetWindowTextW(LinkName);
		}
		else if (i == 4)
		{
			LinkName += _T("5. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link5)->SetWindowTextW(LinkName);
		}
		else if (i == 5)
		{
			LinkName += _T("6. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link6)->SetWindowTextW(LinkName);
		}
		else if (i == 6)
		{
			LinkName += _T("7. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link7)->SetWindowTextW(LinkName);
		}
		else if (i == 7)
		{
			LinkName += _T("8. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link8)->SetWindowTextW(LinkName);
		}
		else if (i == 8)
		{
			LinkName += _T("9. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link9)->SetWindowTextW(LinkName);
		}
		else if (i == 9)
		{
			LinkName += _T("10. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link10)->SetWindowTextW(LinkName);
		}
		else if (i == 10)
		{
			LinkName += _T("11. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link11)->SetWindowTextW(LinkName);
		}
		else if (i == 11)
		{
			LinkName += _T("12. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link12)->SetWindowTextW(LinkName);
		}
		else if (i == 12)
		{
			LinkName += _T("13. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link13)->SetWindowTextW(LinkName);
		}
		else if (i == 13)
		{
			LinkName += _T("14. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link14)->SetWindowTextW(LinkName);
		}
		else if (i == 14)
		{
			LinkName += _T("15. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link15)->SetWindowTextW(LinkName);
		}
		else if (i == 15)
		{
			LinkName += _T("16. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link16)->SetWindowTextW(LinkName);
		}
		else if (i == 16)
		{
			LinkName += _T("17. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link17)->SetWindowTextW(LinkName);
		}
		else if (i == 17)
		{
			LinkName += _T("18. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link18)->SetWindowTextW(LinkName);
		}
		else if (i == 18)
		{
			LinkName += _T("19. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link19)->SetWindowTextW(LinkName);
		}
		else if (i == 19)
		{
			LinkName += _T("20. ");
			LinkName += resultFileName[i] + _T(".html");
			GetDlgItem(IDC_Link20)->SetWindowTextW(LinkName);
		}
		LinkName = _T("");
	}

	for (; i < 20; i++) // 剩下的部分只显示数字
	{
		if (i == 0)
		{
			LinkName += _T("1. ");
			GetDlgItem(IDC_Link1)->SetWindowTextW(LinkName);
		}
		else if (i == 1)
		{
			LinkName += _T("2. ");
			GetDlgItem(IDC_Link2)->SetWindowTextW(LinkName);
		}
		else if (i == 2)
		{
			LinkName += _T("3. ");
			GetDlgItem(IDC_Link3)->SetWindowTextW(LinkName);
		}
		else if (i == 3)
		{
			LinkName += _T("4. ");
			GetDlgItem(IDC_Link4)->SetWindowTextW(LinkName);
		}
		else if (i == 4)
		{
			LinkName += _T("5. ");
			GetDlgItem(IDC_Link5)->SetWindowTextW(LinkName);
		}
		else if (i == 5)
		{
			LinkName += _T("6. ");
			GetDlgItem(IDC_Link6)->SetWindowTextW(LinkName);
		}
		else if (i == 6)
		{
			LinkName += _T("7. ");
			GetDlgItem(IDC_Link7)->SetWindowTextW(LinkName);
		}
		else if (i == 7)
		{
			LinkName += _T("8. ");
			GetDlgItem(IDC_Link8)->SetWindowTextW(LinkName);
		}
		else if (i == 8)
		{
			LinkName += _T("9. ");
			GetDlgItem(IDC_Link9)->SetWindowTextW(LinkName);
		}
		else if (i == 9)
		{
			LinkName += _T("10. ");
			GetDlgItem(IDC_Link10)->SetWindowTextW(LinkName);
		}
		else if (i == 10)
		{
			LinkName += _T("11. ");
			GetDlgItem(IDC_Link11)->SetWindowTextW(LinkName);
		}
		else if (i == 11)
		{
			LinkName += _T("12. ");
			GetDlgItem(IDC_Link12)->SetWindowTextW(LinkName);
		}
		else if (i == 12)
		{
			LinkName += _T("13. ");
			GetDlgItem(IDC_Link13)->SetWindowTextW(LinkName);
		}
		else if (i == 13)
		{
			LinkName += _T("14. ");
			GetDlgItem(IDC_Link14)->SetWindowTextW(LinkName);
		}
		else if (i == 14)
		{
			LinkName += _T("15. ");
			GetDlgItem(IDC_Link15)->SetWindowTextW(LinkName);
		}
		else if (i == 15)
		{
			LinkName += _T("16. ");
			GetDlgItem(IDC_Link16)->SetWindowTextW(LinkName);
		}
		else if (i == 16)
		{
			LinkName += _T("17. ");
			GetDlgItem(IDC_Link17)->SetWindowTextW(LinkName);
		}
		else if (i == 17)
		{
			LinkName += _T("18. ");
			GetDlgItem(IDC_Link18)->SetWindowTextW(LinkName);
		}
		else if (i == 18)
		{
			LinkName += _T("19. ");
			GetDlgItem(IDC_Link19)->SetWindowTextW(LinkName);
		}
		else if (i == 19)
		{
			LinkName += _T("20. ");
			GetDlgItem(IDC_Link20)->SetWindowTextW(LinkName);
		}
		LinkName = _T("");
	}
	UpdateData(false);
}


void CguiDlg::OnStnClickedLink1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[0] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL); // 按‘text’，就打开相关文件 （一下都一样）
}


void CguiDlg::OnStnClickedLink2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[1] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[2] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[3] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[4] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[5] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink7()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[6] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink8()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[7] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink9()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[8] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink10()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[9] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink11()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[10] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink12()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[11] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink13()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[12] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink14()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[13] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink15()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[14] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink16()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[15] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink17()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[16] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink18()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[17] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink19()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[18] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


void CguiDlg::OnStnClickedLink20()
{
	// TODO: 在此添加控件通知处理程序代码
	CString LinkName = resultFileName[19] + _T(".html");
	ShellExecute(0, _T("open"), LinkName, NULL, _T("input"), SW_NORMAL);
}


BOOL CguiDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (pMsg->wParam)
	{
	case VK_RETURN: {} // 按‘ENTER'也不会退出
	case VK_ESCAPE:
		return true; 
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
