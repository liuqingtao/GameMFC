
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "GameMFC.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//定时器的名称
#define TIMER_PAINT 1
#define TIMER_HEROMOVE 2
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

void TransparentPNG(CImage *png) {
	for (int i = 0; i < png->GetWidth(); i++) {
		for (int j = 0; j < png->GetHeight(); j++) {
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
	mbgcDC.CreateCompatibleDC(NULL);	//创建一个DC
	mbgBitmap.LoadBitmap(IDB_BITMAP1);	//加载位图
	mbgcDC.SelectObject(&mbgBitmap);	//将位图与DC关联
	CString path("res\\hero.png");
	mhero.Load(path); //加载PNG图片
	TransparentPNG(&mhero); //去掉白色底板
	mheroPoint.left = 100;
	mheroPoint.right = 100+60;
	mheroPoint.top = 400;
	mheroPoint.bottom = 400 + 60;
	return TRUE;
}

void CChildView::OnPaint() 
{
	CDC *cDC=this->GetDC(); // device context for painting
	
	// TODO: Add your message handler code here
	GetClientRect(&mclient);	//获取窗口大小
	cDC->BitBlt(0, 0, mclient.Width(), mclient.Height(), &mbgcDC, 0, 0, SRCCOPY);	//将内存DC的内容粘贴到窗口DC中
	mhero.Draw(*cDC, mheroPoint); //绘制PNG图片到DC窗口
	ValidateRect(&mclient); //在绘制完图后,使窗口区有效
	ReleaseDC(cDC);
	// Do not call CWnd::OnPaint() for painting messages
}


//添加键盘WASD响应事件
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case 'd':
	case 'D':
		mheroPoint.left += 60;
		mheroPoint.right += 60;
		break;
	case 'a':
	case 'A':
		mheroPoint.left -= 60;
		mheroPoint.right -= 60;
		break;
	case 'w':
	case 'W':
		mheroPoint.top -= 60;
		mheroPoint.bottom -= 60;
		break;
	case 's':
	case 'S':
		mheroPoint.top += 60;
		mheroPoint.bottom += 60;
		break;
	case 't':
	case 'T':
		SetTimer(TIMER_HEROMOVE, 100, NULL); //创建定时器
		break;
	case 'i':
	case 'I':
		KillTimer(TIMER_HEROMOVE); //撤销定时器
		break;
	default:
		break;
	}
	
}

//添加鼠标左键单击响应函数
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mheroPoint.left = point.x;
	mheroPoint.right = mheroPoint.left + 60;
	mheroPoint.top = point.y;
	mheroPoint.bottom = mheroPoint.top + 60;
	
}

//定时器响应函数
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	switch (nIDEvent)
	{
	case TIMER_PAINT:OnPaint(); break; //若是重绘定时器，不执行OnPint函数
	case TIMER_HEROMOVE:	//控制人物移动的定时器
	{
		mheroPoint.left += 10;
		mheroPoint.right += 10;
	}
	break;
	}
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetTimer(TIMER_PAINT, 10, NULL); //创建一个10毫秒产生一次消息的定时器
	return 0;
}
