
// ChildView.h : interface of the CChildView class
//


#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	//人物结构体
	struct character
	{
		CImage character;
		int x;
		int y;
		int direct;
		int frame;
		int width;
		int height;
		int Xcenter;
		int Ycenter;
	}Myhero,Monster;
	CRect mClient;
	CImage mBg;


	CDC mCacheDC;
	CBitmap mCacheCBitmap;
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
};

