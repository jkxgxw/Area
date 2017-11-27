// AreaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Area.h"
#include "AreaDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.14159265

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAreaDlg 对话框




CAreaDlg::CAreaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaDlg::IDD, pParent)
	, m_bSin(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAreaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SPIN, m_EditSpin);
	DDX_Control(pDX, IDC_SLIDER_COLOR, m_Slider);
	DDX_Control(pDX, IDC_COMBO_NUM, m_ComboBox);
	DDX_Control(pDX, IDC_EDIT2, m_EditArea);
	DDX_Control(pDX, IDC_BUTTON_CALCULATE, m_ButtonCalc);
	DDX_Control(pDX, IDC_BUTTON_CONCEL, m_ButtonConcel);
	DDX_Control(pDX, IDC_EDIT_COLOR, m_EditColor);
}

BEGIN_MESSAGE_MAP(CAreaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CAreaDlg::OnBnClickedButtonCalculate)
	ON_BN_CLICKED(IDC_BUTTON_CONCEL, &CAreaDlg::OnBnClickedButtonConcel)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SLIDER_COLOR, &CAreaDlg::OnNMThemeChangedSliderColor)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_COLOR, &CAreaDlg::OnNMCustomdrawSliderColor)
	ON_EN_UPDATE(IDC_EDIT_SPIN, &CAreaDlg::OnEnUpdateEditSpin)
	ON_EN_KILLFOCUS(IDC_EDIT_SPIN, &CAreaDlg::OnEnKillfocusEditSpin)
	ON_CBN_SELCHANGE(IDC_COMBO_NUM, &CAreaDlg::OnCbnSelchangeComboNum)
	ON_BN_CLICKED(IDC_RADIO_SIN, &CAreaDlg::OnBnClickedRadioSin)
	ON_BN_CLICKED(IDC_RADIO_COS, &CAreaDlg::OnBnClickedRadioCos)
END_MESSAGE_MAP()


// CAreaDlg 消息处理程序

BOOL CAreaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_bCalculate = false;
	m_Slider.SetRange(1,100);
	this->GetWindowRect(m_rect);
	m_rect = CRect(m_rect.left + 40,m_rect.top + 10,m_rect.right - 160,m_rect.bottom - 70);
	m_clrref = 255;
	m_Slider.SetPos(50);
	m_a = 50;
	m_EditSpin.SetWindowText(_T("50"));
	m_ComboBox.SetCurSel(0);
	
	CString strVal;
	m_ComboBox.GetLBText(m_ComboBox.GetCurSel(),strVal);
	m_mid_val = _ttoi(strVal);
	m_EditColor.EnableWindow(FALSE);

	CButton *pBtnSin = (CButton*)GetDlgItem(IDC_RADIO_SIN);
	if(NULL != pBtnSin)
		pBtnSin->SetCheck(BST_CHECKED);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAreaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAreaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		// double buffer draw background
		CPaintDC dc(this);
		CRect rc;
		CDC dcMem;
		GetClientRect(&rc);
		CBitmap bmp; //内存中承载临时图象的位图

		dcMem.CreateCompatibleDC(&dc); //依附窗口DC创建兼容内存DC
		//创建兼容位图(必须用pDC创建，否则画出的图形变成黑色)
		bmp.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
		CBitmap *pOldBit=dcMem.SelectObject(&bmp);
		//按原来背景填充客户区，不然会是黑色
		dcMem.FillSolidRect(rc,RGB(236,233,216));
		//画图，添加你要画图的代码，不过用dcMem画，而不是pDC；
		DrawBK(&dcMem);
		DrawImage(&dcMem);
		dc.BitBlt(0,0,rc.Width(),rc.Height(),&dcMem,0,0,SRCCOPY);
		//将内存DC上的图象拷贝到前台
		//绘图完成后的清理
		dcMem.DeleteDC();     //删除DC
		bmp.DeleteObject(); //删除位图

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CAreaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAreaDlg::OnBnClickedButtonCalculate()
{
	if(!m_bSin)
		CalcSin();
	else
		CalcCos();
}

void CAreaDlg::CalcCos()
{
	double nSum = 0.0;
	double nMidLen = double((2 * PI) / 2000.0 * m_mid_val);
	double nUp = 0.0;
	double nDown = 0.0;
	double nHight = nMidLen;
	CString strVal = _T("");

	for(int i = 1; i < 2000 / m_mid_val; i++)
	{
		nDown = abs(m_a * cos(double(nMidLen * i)));
		nSum += (nUp + nDown) * nHight / 2.0;
		nUp = nDown;
	}
	
	strVal.Format(_T("%f"),nSum);
	m_EditArea.SetWindowText(strVal);
	//send msg to draw area shadow
	m_bCalculate = true;
	InvalidateRect(m_rect,false);
}

void CAreaDlg::CalcSin()
{
	//Calculate the area of the shape, S = (a + b) * h / 2.0
	// TODO: 在此添加控件通知处理程序代码
	double nSum = 0.0;
	double nMidLen = double((2 * PI) / 2000.0 * m_mid_val);
	double nUp = 0.0;
	double nDown = 0.0;
	double nHight = nMidLen;
	CString strVal = _T("");

	for(int i = 1; i < 2000 / m_mid_val; i++)
	{
		nDown = abs(m_a * sin(double(nMidLen * i)));
		nSum += (nUp + nDown) * nHight / 2.0;
		nUp = nDown;
	}
	
	strVal.Format(_T("%f"),nSum);
	m_EditArea.SetWindowText(strVal);
	//send msg to draw area shadow
	m_bCalculate = true;
	InvalidateRect(m_rect,false);
}

void CAreaDlg::OnBnClickedButtonConcel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CAreaDlg::OnNMThemeChangedSliderColor(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CAreaDlg::OnNMCustomdrawSliderColor(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}

void CAreaDlg::OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{
	CDialog::OnHScroll(nSBCode,nPos,pScrollBar);

	if(pScrollBar->GetDlgCtrlID() == IDC_SLIDER_COLOR)
	{
		CString strSlider;
		m_a = m_Slider.GetPos();
		strSlider.Format(_T("%d"),m_a);
		m_EditSpin.SetWindowText(strSlider);
		m_EditArea.SetWindowText(NULL);
		//repaint
		InvalidateRect(m_rect,0);
		m_bCalculate = false;
	}
}

void CAreaDlg::OnEnUpdateEditSpin()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数，将 EM_SETEVENTMASK 消息发送到控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CAreaDlg::OnEnKillfocusEditSpin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strVal;

	m_EditSpin.GetWindowText(strVal);
	m_a = _ttoi(strVal);
	m_Slider.SetPos(m_a);
	//repaint
	InvalidateRect(m_rect,0);	
	m_bCalculate = false;
}

void CAreaDlg::DrawBK(CDC* dc)
{
	dc->FillSolidRect(m_rect,RGB(255,255,255));//black area to draw image
	//Pen Color
	CPen pen(PS_SOLID,1,RGB(193,193,193));
	CPen *pOldPen=dc->SelectObject(&pen);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush=dc->SelectObject(pBrush);
	// Horizon
	//0 
	dc->MoveTo(m_rect.left - 5,m_rect.top + m_rect.Height() / 2);
	dc->LineTo(m_rect.right,m_rect.top + m_rect.Height() / 2);
	//100/2 
	dc->MoveTo(m_rect.left - 5,m_rect.top + m_rect.Height() / 4);
	dc->LineTo(m_rect.right,m_rect.top + m_rect.Height() / 4);
	// 100 
	dc->MoveTo(m_rect.left - 5,m_rect.top );
	dc->LineTo(m_rect.right,m_rect.top );
	//-100/2
	dc->MoveTo(m_rect.left - 5,m_rect.bottom - m_rect.Height() / 4);
	dc->LineTo(m_rect.right,m_rect.bottom - m_rect.Height() / 4);
	//-100 
	dc->MoveTo(m_rect.left - 5,m_rect.bottom );
	dc->LineTo(m_rect.right,m_rect.bottom );

	// Verticality
	// 0
	dc->MoveTo(m_rect.left,m_rect.top);
	dc->LineTo(m_rect.left,m_rect.bottom + 5);
	// 1000/2
	dc->MoveTo(m_rect.left + m_rect.Width() / 4,m_rect.top);
	dc->LineTo(m_rect.left + m_rect.Width() / 4,m_rect.bottom + 5);	
	// 1000
	dc->MoveTo(m_rect.left + m_rect.Width() / 2,m_rect.top);
	dc->LineTo(m_rect.left + m_rect.Width() / 2,m_rect.bottom + 5);	
	// 1000 + 1000/2
	dc->MoveTo(m_rect.right - m_rect.Width() / 4 ,m_rect.top);
	dc->LineTo(m_rect.right - m_rect.Width() / 4,m_rect.bottom + 5);	
	// 2000
	dc->MoveTo(m_rect.left + m_rect.Width()  ,m_rect.top);
	dc->LineTo(m_rect.left + m_rect.Width()  ,m_rect.bottom + 5);
 
}

void CAreaDlg::DrawImage(CDC* dc)
{
	//Draw Image
	if(m_bSin)
		DrawSin(dc);
	else 
		DrawCos(dc);
}

void CAreaDlg::DrawSin(CDC* dc)
{
	//Pen Color
	CPen pen(PS_SOLID,1,m_clrref);
	CPen *pOldPen=dc->SelectObject(&pen);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush=dc->SelectObject(pBrush);

	double nA = m_a * m_rect.Height() / 200.0;// ?
	double nMid = (m_rect.Width() / 200.0);// ?
	double nY0 = m_rect.top + m_rect.Height() / 2.0;
	double nX0 = m_rect.left;
	double lX1,lY1;
	double lX2,lY2;

	//(0,0)
	lX1 = nX0;
	lY1 = nY0;
	
	for(int i = 1; i < 200,lX1 < m_rect.right ; i++)
	{
		lX2 = lX1 +  nMid;
		lY2 = nY0 + nA * sin(double(lX2 - nX0) / double(m_rect.Width()) * 2 * PI);
		dc->MoveTo((int)lX1,(int)lY1);
		dc->LineTo((int)lX2,(int)lY2);

		if(m_bCalculate)
		{	
			//draw area shadow
			if(i % 2)
			{
				dc->MoveTo((int)lX1,(int)nY0);
				dc->LineTo((int)lX1,(int)lY2);
			}
		}

		lX1 = lX2;
		lY1 = lY2;
	}
}

void CAreaDlg::DrawCos(CDC* dc)
{
	//Pen Color
	CPen pen(PS_SOLID,1,m_clrref);
	CPen *pOldPen=dc->SelectObject(&pen);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush=dc->SelectObject(pBrush);

	double nA = m_a * m_rect.Height() / 200.0;// ?
	double nMid = (m_rect.Width() / 200.0);// ?
	double nX0 = m_rect.left;
	double nY0 = m_rect.top + m_rect.Height() / 2.0;
	double lX1,lY1;
	double lX2,lY2;

	//(0,0)
	lX1 = nX0;
	lY1 = nY0 + nA * cos(double(nMid) / double(m_rect.Width()) * 2 * PI);
	
	for(int i = 1; i < 200,lX1 < m_rect.right ; i++)
	{
		lX2 = lX1 +  nMid;
		lY2 = nY0 + nA * cos(double(lX2 - nX0) / double(m_rect.Width()) * 2 * PI);
		dc->MoveTo((int)lX1,(int)lY1);
		dc->LineTo((int)lX2,(int)lY2);

		if(m_bCalculate)
		{	
			//draw area shadow
			if(i % 2)
			{
				dc->MoveTo((int)lX1,(int)nY0);
				dc->LineTo((int)lX1,(int)lY2);
			}
		}

		lX1 = lX2;
		lY1 = lY2;
	}
}

void CAreaDlg::OnCbnSelchangeComboNum()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strVal;
	m_ComboBox.GetLBText(m_ComboBox.GetCurSel(),strVal);
	m_mid_val = _ttoi(strVal);
	m_EditArea.SetWindowText(NULL);
}


HBRUSH CAreaDlg::OnCtlColor(CDC* pDC,CWnd *pWnd,UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC: 
		if( pWnd->GetDlgCtrlID() != IDC_SLIDER_COLOR)
		{
			pDC->SetBkMode(TRANSPARENT);
			hbr =  HBRUSH(GetStockObject(HOLLOW_BRUSH));
		}
		break;
	default:
		break;
	}

	if(pWnd->GetDlgCtrlID() == m_EditColor.GetDlgCtrlID() ) 
	{ 
		pDC->SetBkMode(TRANSPARENT);//设置背景透明 
		hbr =  CreateSolidBrush(m_clrref);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;	
 }

void CAreaDlg::OnLButtonUp(UINT nFlags,CPoint point)
{
	CDialog::OnLButtonUp(nFlags,point);
	
	CRect rc;
	m_EditColor.GetWindowRect(rc);

	this->ScreenToClient(rc);
	if(PtInRect(&rc,point))
	{
		CColorDialog clrdlg;

		if( clrdlg.DoModal() > 0 ? true : false)
		{
			m_clrref = clrdlg.GetColor();
			//set background with the same color
			//repaint shape rect and color edit rect
			InvalidateRect(m_rect,false);
			InvalidateRect(rc,false);
		}
	}
}
void CAreaDlg::OnBnClickedRadioSin()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bSin = true;
	InvalidateRect(m_rect,false);
}

void CAreaDlg::OnBnClickedRadioCos()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bSin = false;
	InvalidateRect(m_rect,false);
}
