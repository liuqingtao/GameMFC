
// ChildView.h : interface of the CChildView class
//


#pragma once


// CChildView window
#define SNOW_NUMBER 100
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	//雪花粒子结构体
	struct snow
	{
		int x;
		int y;
		int number; //粒子编号，共七种粒子
	};
	snow Snow[SNOW_NUMBER];
	CImage msnowMap[7];
	//英雄结构体
	struct shero
	{
		CImage hero;
		int x;
		int y;
		int direct;
		int frame;
	};
	shero Myhero;
	
	CRect mclient;
	CImage mbg;

	int mxMapStart;
	int mMapWidth;

	CDC mcacheDC;
	CBitmap mcacheCBitmap;
// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	void GetMapStartX();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

