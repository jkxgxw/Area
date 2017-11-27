// AreaDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAreaDlg �Ի���
class CAreaDlg : public CDialog
{
// ����
public:
	CAreaDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AREA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CRect m_rect;
	COLORREF m_clrref;

	// ���ɵ���Ϣӳ�亯��
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
