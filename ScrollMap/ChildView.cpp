
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "ScrollMap.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//定义四个方向
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3

//窗口大小
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

//将png贴图透明  
void TransparentPNG(CImage *png)
{
	for (int i = 0; i < png->GetWidth(); i++)
	{
		for (int j = 0; j < png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(png->GetPixelAddress(i, j));
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

	//---------------------------------游戏数据初始化部分--------------------------------------------------------------
	
	CString bgPath("res\\bigbg.png");
	mbg.Load(bgPath);
	//获取背景地图宽度
	mMapWidth = mbg.GetWidth();
	
	CString heroPath("res\\heroMove.png");
	Myhero.hero.Load(heroPath);
	TransparentPNG(&Myhero.hero);

	Myhero.direct = UP;
	Myhero.frame = 0;
	Myhero.x = 80;
	Myhero.y = 400;

	mxMapStart = 0;
	return TRUE;
}
//计算左端X开始位置
void CChildView::GetMapStartX()
{
	//如果人物不在最左边和最右边半个屏幕内时，地图的起始坐标是需要根据人物位置计算的
	if (Myhero.x<mMapWidth - WINDOW_WIDTH / 2 && Myhero.x>WINDOW_WIDTH / 2)
	{
		mxMapStart = Myhero.x - WINDOW_WIDTH / 2;
	}
}
//获取人物在屏幕上的坐标
int GetScreenX(int xHero, int mapWidth)
{
	//如果人物不在最左边和最右边半个屏幕内时，那么人物就在屏幕中间
	if (xHero<mapWidth - WINDOW_WIDTH / 2 && xHero>WINDOW_WIDTH / 2)
		return WINDOW_WIDTH / 2;
	else if (xHero < WINDOW_WIDTH / 2)
		return xHero;
	else
		return WINDOW_WIDTH - (mapWidth - xHero);
}
void CChildView::OnPaint() 
{
	
	//获取窗口DC指针
	CDC *cDC = this->GetDC();
	//获取窗口大小
	GetClientRect(&mclient);
	//创建缓冲DC
	mcacheDC.CreateCompatibleDC(NULL);
	mcacheCBitmap.CreateCompatibleBitmap(cDC,mclient.Width(),mclient.Height());
	mcacheDC.SelectObject(&mcacheCBitmap);
	//计算地图起始位置
	GetMapStartX();
	//------------------开始绘制---------------------------------------------
	//贴背景，现在贴图就是贴在缓冲DC:mcacheDC中了
	mbg.Draw(mcacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, mxMapStart, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//贴英雄
	Myhero.hero.Draw(mcacheDC, GetScreenX(Myhero.x, mMapWidth), Myhero.y, 80, 80, Myhero.frame * 80, Myhero.direct * 80, 80, 80);
	//最后将缓冲DC内容输出到窗口DC中
	cDC->BitBlt(0, 0, mclient.Width(), mclient.Height(), &mcacheDC, 0, 0, SRCCOPY);
	//------------------绘制完毕--------------------------------------------
	ValidateRect(&mclient);
	mcacheDC.DeleteDC();
	mcacheCBitmap.DeleteObject();
	ReleaseDC(cDC);
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

