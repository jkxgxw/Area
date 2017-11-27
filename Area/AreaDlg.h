// AreaDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAreaDlg 对话框
class CAreaDlg : public CDialog
{
// 构造
public:
	CAreaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AREA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CRect m_rect;
	COLORREF m_clrref;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CEdit m_EditSpin;
	CSliderCtrl m_Slider;
	CComboBox m_ComboBox;
	CEdit m_EditArea;
	CButton m_ButtonCalc;
	CButton m_ButtonConcel;
	CEdit m_EditColor;
	int m_mid_val;
	int m_a;
	bool m_bCalculate;
	bool m_bSin;

private:
	afx_msg void OnNMThemeChangedSliderColor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderColor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnUpdateEditSpin();
	afx_msg void OnEnKillfocusEditSpin();
	afx_msg void OnCbnSelchangeComboNum();
	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd *pWnd,UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);
	afx_msg void OnBnClickedRadioSin();
	afx_msg void OnBnClickedRadioCos();
	afx_msg void OnBnClickedButtonCalculate();
	afx_msg void OnBnClickedButtonConcel();
	afx_msg void OnBnClickedButtonColor();

private:
	void CalcSin();
	void CalcCos();
	void DrawBK(CDC* dc);
	void DrawImage(CDC* dc);
	void DrawCos(CDC *dc);
	void DrawSin(CDC *dc);
};
