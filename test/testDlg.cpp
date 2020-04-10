
// testDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//���ھ��
HANDLE hCom;


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CtestDlg �Ի���




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


// CtestDlg ��Ϣ�������

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestDlg::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CloseHandle(hCom);
}


void CtestDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char lpOutBuffer[100] = {0x7f};
	DWORD dwBytesWrite = 100;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	//�ڶ�д֮ǰӦ��ʹ��ClearCommError�����������
	ClearCommError(hCom, &dwErrorFlags, &ComStat);
	bWriteStat = WriteFile(hCom, lpOutBuffer, dwBytesWrite, &dwBytesWrite, NULL);
	if(!bWriteStat){
		AfxMessageBox("write failed ");
	}
	PurgeComm(hCom, PURGE_TXABORT| PURGE_RXABORT |PURGE_TXCLEAR | PURGE_RXCLEAR);
}

void CtestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������.
	hCom = CreateFile("COM1", //��������
		GENERIC_READ | GENERIC_WRITE, //�����д
		0,                    //��ռ��ʽ
		NULL,
		OPEN_EXISTING,//�򿪶����Ǵ����ķ�ʽ
		0,					  //ͬ����ʽ
		NULL);

	if(hCom == (HANDLE) -1){
		AfxMessageBox("OPEN FAILED");
		return ;
	}

	SetupComm(hCom, 1024, 1024);
	COMMTIMEOUTS TimeOuts;
	//�������ʱʱ��
	TimeOuts.ReadIntervalTimeout = 10;

	//��ʱ��ϵ��
	TimeOuts.ReadTotalTimeoutMultiplier = 10;
	//����ʱʱ��
	TimeOuts.ReadTotalTimeoutConstant = 10;

	//дʱ��ϵ��
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	//д��ʱʱ��
	TimeOuts.WriteTotalTimeoutConstant = 2000;

	//���ó�ʱʱ��
	SetCommTimeouts(hCom, &TimeOuts);

	DCB dcb;
	//��ȡCOM�ڵ��豸���ƿ����
	GetCommState(hCom, &dcb);
	//������
	dcb.BaudRate = 115200;
	//����λ 8λ
	dcb.ByteSize = 8;
	//��żУ��λ ��У��λ
	dcb.Parity = NOPARITY;
	//ֹͣλ 1λ
	dcb.StopBits = ONESTOPBIT;
	SetCommState(hCom, &dcb);

	//�ڶ�д����֮ǰ��ջ�����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
