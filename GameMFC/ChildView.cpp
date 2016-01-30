
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "GameMFC.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	m_bgcDC.CreateCompatibleDC(NULL);	//创建一个DC
	m_bgBitmap.LoadBitmap(IDB_BITMAP1);	//加载位图
	m_bgcDC.SelectObject(&m_bgBitmap);	//将位图与DC关联
	CString path("res\\hero.png");
	m_hero.Load(path); //加载PNG图片
	TransparentPNG(&m_hero); //去掉白色底板
	m_heroPoint.left = 100;
	m_heroPoint.right = 100+60;
	m_heroPoint.top = 400;
	m_heroPoint.bottom = 400 + 60;
	return TRUE;
}

void CChildView::OnPaint() 
{
	CDC *cDC=this->GetDC(); // device context for painting
	
	// TODO: Add your message handler code here
	GetClientRect(&m_client);	//获取窗口大小
	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_bgcDC, 0, 0, SRCCOPY);	//将内存DC的内容粘贴到窗口DC中
	m_hero.Draw(*cDC, m_heroPoint); //绘制PNG图片到DC窗口
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
		m_heroPoint.left += 60;
		m_heroPoint.right += 60;
		break;
	case 'a':
	case 'A':
		m_heroPoint.left -= 60;
		m_heroPoint.right -= 60;
		break;
	case 'w':
	case 'W':
		m_heroPoint.top -= 60;
		m_heroPoint.bottom -= 60;
		break;
	case 's':
	case 'S':
		m_heroPoint.top += 60;
		m_heroPoint.bottom += 60;
		break;
	default:
		break;
	}
	
}

//添加鼠标左键单击响应函数
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_heroPoint.left = point.x;
	m_heroPoint.right = m_heroPoint.left + 60;
	m_heroPoint.top = point.y;
	m_heroPoint.bottom = m_heroPoint.top + 60;
	
}
