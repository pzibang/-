
// testDlg.h : ͷ�ļ�
//

#pragma once


// CtestDlg �Ի���
class CtestDlg : public CDialogEx
{
// ����
public:
	CtestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_DIALOG };

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
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CEdit m_edit;
	afx_msg void OnBnClickedButton1();
	CString m_edit_string;
	//afx_msg LONG OnComm();

	afx_msg void OnBnClickedButton2();
};