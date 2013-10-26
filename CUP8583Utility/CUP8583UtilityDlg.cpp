// CUP8583UtilityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CUP8583Utility.h"
#include "CUP8583UtilityDlg.h"

#include "8583/8583Protocol.h"
#include "Utils/Utils.h"
#include "tlv/TlvDecoder.h"
#include "8583/element.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CEdit *disp;
CEdit *dispDE55;

CCUP8583UtilityDlg *dlg;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCUP8583UtilityDlg dialog




CCUP8583UtilityDlg::CCUP8583UtilityDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCUP8583UtilityDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCUP8583UtilityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Original8583Msg, m_ceOriginal8583Msg);
	DDX_Control(pDX, IDC_DE55, m_cdDE55);
	DDX_Control(pDX, IDC_EDIT1, m_ceFieldContent);
}

BEGIN_MESSAGE_MAP(CCUP8583UtilityDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_Original8583Msg, &CCUP8583UtilityDlg::OnEnChangeOriginal8583msg)
	ON_EN_CHANGE(IDC_EDIT1, &CCUP8583UtilityDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CCUP8583UtilityDlg message handlers

BOOL CCUP8583UtilityDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	disp = &m_ceFieldContent;
	dispDE55 = &m_cdDE55;
	
	int count = 1;

	for (int i = IDC_FIELD1; i<=IDC_FIELD66; i++)
	{
		CString str;
		
		str.Format(_T("%d"), count);
		GetDlgItem(i)->SetWindowText(str);
		count ++;
	}

	dlg = this;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCUP8583UtilityDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCUP8583UtilityDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCUP8583UtilityDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


static  int32 saveTlv(byte *tag, byte tagLen,int32 len, byteArray value, void *tlvObjRepo)
{
	CString str;
	char buff[1024];
	WCHAR wbuff[1024];
	int Tag;
	char tagValue[512];
	
	Tag = tag[0];

	if (tagLen > 1)
	{
		Tag = (Tag << 8) + tag[1];
	}

	memset(tagValue, 0x00, sizeof(tagValue));
	byteArrayToHexString(tagValue, value, len);
	dispDE55->GetWindowText(str);
	memset(buff, 0x00, sizeof(buff));
	memset(wbuff, 0x00, sizeof(wbuff));
	sprintf(buff,"Tag:%X\r\nLength:%d\r\nValue:%s\r\n\r\n", Tag, len,tagValue);
	MultiByteToWideChar (CP_ACP, 0, buff, -1, wbuff, 1024);  
	str.AppendFormat(_T("%s"), wbuff);
	dispDE55->SetWindowText(str);
	return 0;
}



static int saveData(int fid, char *value, int len)
{
	CString str;
	char buff[1024];
	WCHAR wbuff[1024];
	unsigned char de55[512];
	int de55Len = 0;
	CButton *cb;

	disp->GetWindowText(str);
	memset(buff, 0x00, sizeof(buff));
	memset(wbuff, 0x00, sizeof(wbuff));

	switch (fid)
	{
	case FIELD_TPDU:
		strcpy(buff, "TPDU: ");
			memcpy(buff+strlen(buff), value, len);
			memcpy(buff+strlen(buff), "\r\n\r\n", strlen("\r\n\r\n"));

		break;

	case FIELD_MSG_HEADER:
		strcpy(buff, "Message Header: ");
			memcpy(buff+strlen(buff), value, len);
			strcat(buff, "\r\n\r\n");
		break;
	case FIELD_MSG_CODE:
		strcpy(buff, "Message Code: ");
			memcpy(buff+strlen(buff), value, len);
			strcat(buff, "\r\n\r\n");
		break;
	default:
		sprintf(buff,"Field:%d\r\nLength:%d\r\nValue:%s\r\n\r\n", fid, len,value);

		cb = (CButton*)dlg->GetDlgItem(IDC_FIELD1-1 + fid);
		cb->SetState(TRUE);
		cb->SetCheck(1);

		break;
	}

	
	 MultiByteToWideChar (CP_ACP, 0, buff, -1, wbuff, 1024);  
	 str.AppendFormat(_T("%s"), wbuff);
	disp->SetWindowText(str);

	if (fid == 55)
	{
		//add save DE55 logic
		memset(de55, 0x00, sizeof(de55));
		hexStringToByteArray(de55, &de55Len, value);
		decodeAllConstructedTlvObj(saveTlv, de55, de55Len, NULL);
	}


	return 0;
}


void CCUP8583UtilityDlg::OnEnChangeOriginal8583msg()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	unsigned char src8583Msg[1024];
	int srcLen = 0;
	CString text;
	char buff[2048];
	char cusor;
	
	int count = 1;
	CButton *cb;

	for (int i = IDC_FIELD1; i<=IDC_FIELD66; i++)
	{
		CString str;

		str.Format(_T("%d"), count);
		cb = (CButton*)GetDlgItem(i);
		cb->SetCheck(0);
		cb->SetState(FALSE);
		count ++;
	}


	memset(buff, 0x00, sizeof(buff));
	disp->SetWindowText(_T(""));
	dispDE55->SetWindowText(_T(""));
	m_ceOriginal8583Msg.GetWindowText(text);
	text.Remove(' ');
	WideCharToMultiByte(CP_ACP,0,text.GetBuffer(),wcslen(text.GetBuffer()),buff,2017,NULL,NULL); 
	
	saveData(FIELD_TPDU, buff, LEN_TPDU);
	cusor = LEN_TPDU;
	saveData(FIELD_MSG_HEADER, buff+cusor, LEN_MSG_HEADER);
	cusor += LEN_MSG_HEADER;
	saveData(FIELD_MSG_CODE, buff+cusor, LEN_MSG_CODE);
	cusor += LEN_MSG_CODE;

	hexStringToByteArray(src8583Msg, &srcLen, buff+cusor);
	parseISO8583Msg(src8583Msg, srcLen, (SaveFieldData) saveData);
}


void CCUP8583UtilityDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
