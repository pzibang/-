
// testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//串口句柄
HANDLE hCom;


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


// CtestDlg 对话框




CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_edit_string = _T("");
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_T, m_edit);
	DDX_Text(pDX, IDC_EDIT_T, m_edit_string);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CtestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CtestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CtestDlg::OnBnClickedButton1)
	//ON_MESSAGE(WM_COMM_RXCHAR, OnComm)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CtestDlg 消息处理程序

BOOL CtestDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtestDlg::OnPaint()
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
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//[command]
//str1=AT+DMOSETPTT
//str2=AT+DMORESETPTT
//str3=AT+DMOSETPTTTIME=60
//str4=AT+DMOSETGROUP=0,156.8000,156.8000,0,2,0,1


void CtestDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CloseHandle(hCom);
}


void CtestDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	char lpOutBuffer[100] = {0x7f};
	DWORD dwBytesWrite = 100;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	//在读写之前应先使用ClearCommError函数清除错误
	ClearCommError(hCom, &dwErrorFlags, &ComStat);
	bWriteStat = WriteFile(hCom, lpOutBuffer, dwBytesWrite, &dwBytesWrite, NULL);
	if(!bWriteStat){
		AfxMessageBox("write failed ");
	}
	PurgeComm(hCom, PURGE_TXABORT| PURGE_RXABORT |PURGE_TXCLEAR | PURGE_RXCLEAR);
}

void CtestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码.
	hCom = CreateFile("COM1", //串口名称
		GENERIC_READ | GENERIC_WRITE, //允许读写
		0,                    //独占方式
		NULL,
		OPEN_EXISTING,//打开而不是创建的方式
		0,					  //同步方式
		NULL);

	if(hCom == (HANDLE) -1){
		AfxMessageBox("OPEN FAILED");
		return ;
	}

	SetupComm(hCom, 1024, 1024);
	COMMTIMEOUTS TimeOuts;
	//读间隔超时时间
	TimeOuts.ReadIntervalTimeout = 10;

	//读时间系数
	TimeOuts.ReadTotalTimeoutMultiplier = 10;
	//读超时时间
	TimeOuts.ReadTotalTimeoutConstant = 10;

	//写时间系数
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	//写超时时间
	TimeOuts.WriteTotalTimeoutConstant = 2000;

	//设置超时时间
	SetCommTimeouts(hCom, &TimeOuts);

	DCB dcb;
	//获取COM口的设备控制块参数
	GetCommState(hCom, &dcb);
	//波特率
	dcb.BaudRate = 115200;
	//数据位 8位
	dcb.ByteSize = 8;
	//奇偶校验位 无校验位
	dcb.Parity = NOPARITY;
	//停止位 1位
	dcb.StopBits = ONESTOPBIT;
	SetCommState(hCom, &dcb);

	//在读写串口之前清空缓冲区
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);



}

//LONG CtestDlg::OnComm(){
//	char str[100];
//	DWORD wCount;
//	BOOL bReadStat;
//	bReadStat = ReadFile(hCom, str, 100, &wCount, NULL);
//	if(!bReadStat){
//		AfxMessageBox("read failed");
//		return 0;
//	}
//
//	return 1;
//}


void CtestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	char str[100] = {0};
	CString tmp;
	DWORD wCount;
	BOOL bReadStat;
	bReadStat = ReadFile(hCom, str, 100, &wCount, NULL);
	if(!bReadStat){
		AfxMessageBox("read failed");
	}
	tmp.Format("%s", str);
	m_edit.SetWindowTextA(tmp);
}
