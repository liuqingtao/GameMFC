
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Collisions.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//定义四个方向
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3

//定义窗口大小
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void TransparentPNG(CImage *png)
{
	for (int i = 0; i < png->GetWidth(); i++)
	{
		for (int j = 0; j < png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i, j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}

// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);
//--------------------------------------------------游戏初始化---------------------------------------
	CString path("res\\png\\bg.png");
	mBg.Load(path);
	path = "res\\png\\heroMove.png";
	Myhero.character.Load(path);
	TransparentPNG(&Myhero.character);

	Myhero.width = 80;
	Myhero.height = 80;
	Myhero.direct = UP;
	Myhero.frame = 0;
	Myhero.x = 80;
	Myhero.y = 400;
	
	path = "res\\png\\monster.png";
	Monster.character.Load(path);
	TransparentPNG(&Monster.character);
	Monster.width = 96;
	Monster.height = 96;
	Monster.direct = LEFT;
	Monster.frame = 0;
	Monster.x = 700;
	Monster.y = 100;
	return TRUE;
}

void CChildView::OnPaint() 
{
	CDC *cDC = this->GetDC();
	GetClientRect(&mClient);

	mCacheDC.CreateCompatibleDC(NULL);
	mCacheCBitmap.CreateCompatibleBitmap(cDC, mClient.Width(), mClient.Height());
	mCacheDC.SelectObject(&mCacheCBitmap);

	//------------------------开始绘制-------------------------------------

	mBg.Draw(mCacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	Myhero.character.Draw(mCacheDC, Myhero.x, Myhero.y, 80, 80, Myhero.frame * 80, Myhero.direct * 80, 80, 80);
	Monster.character.Draw(mCacheDC, Monster.x, Monster.y, 96, 96, Monster.frame * 96, Monster.direct * 96, 96, 96);
	//最后将缓冲DC内容输出到窗口DC中
	cDC->BitBlt(0, 0, mClient.Width(), mClient.Height(), &mCacheDC, 0, 0, SRCCOPY);
	//----------------------------绘制结束-------------------------------
	//绘制完成使窗口有效
	ValidateRect(&mClient);
	mCacheDC.DeleteDC();
	mCacheCBitmap.DeleteObject();
	ReleaseDC(cDC);
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

