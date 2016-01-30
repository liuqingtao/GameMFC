
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
	return TRUE;
}

void CChildView::OnPaint() 
{
	CDC *cDC=this->GetDC(); // device context for painting
	
	// TODO: Add your message handler code here
	GetClientRect(&m_client);	//获取窗口大小
	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_bgcDC, 0, 0, SRCCOPY);	//将内存DC的内容粘贴到窗口DC中
	m_hero.Draw(*cDC, 100, 400, 60, 60); //绘制PNG图片到DC窗口
	ReleaseDC(cDC);
	// Do not call CWnd::OnPaint() for painting messages
}

