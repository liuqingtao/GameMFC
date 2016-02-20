
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "ScrollMap.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//�����ĸ�����
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3

//���ڴ�С
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

//��png��ͼ͸��  
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

	//---------------------------------��Ϸ���ݳ�ʼ������--------------------------------------------------------------
	
	CString bgPath("res\\bigbg.png");
	mbg.Load(bgPath);
	//��ȡ������ͼ���
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
//�������X��ʼλ��
void CChildView::GetMapStartX()
{
	//������ﲻ������ߺ����ұ߰����Ļ��ʱ����ͼ����ʼ��������Ҫ��������λ�ü����
	if (Myhero.x<mMapWidth - WINDOW_WIDTH / 2 && Myhero.x>WINDOW_WIDTH / 2)
	{
		mxMapStart = Myhero.x - WINDOW_WIDTH / 2;
	}
}
//��ȡ��������Ļ�ϵ�����
int GetScreenX(int xHero, int mapWidth)
{
	//������ﲻ������ߺ����ұ߰����Ļ��ʱ����ô���������Ļ�м�
	if (xHero<mapWidth - WINDOW_WIDTH / 2 && xHero>WINDOW_WIDTH / 2)
		return WINDOW_WIDTH / 2;
	else if (xHero < WINDOW_WIDTH / 2)
		return xHero;
	else
		return WINDOW_WIDTH - (mapWidth - xHero);
}
void CChildView::OnPaint() 
{
	
	//��ȡ����DCָ��
	CDC *cDC = this->GetDC();
	//��ȡ���ڴ�С
	GetClientRect(&mclient);
	//��������DC
	mcacheDC.CreateCompatibleDC(NULL);
	mcacheCBitmap.CreateCompatibleBitmap(cDC,mclient.Width(),mclient.Height());
	mcacheDC.SelectObject(&mcacheCBitmap);
	//�����ͼ��ʼλ��
	GetMapStartX();
	//------------------��ʼ����---------------------------------------------
	//��������������ͼ�������ڻ���DC:mcacheDC����
	mbg.Draw(mcacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, mxMapStart, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//��Ӣ��
	Myhero.hero.Draw(mcacheDC, GetScreenX(Myhero.x, mMapWidth), Myhero.y, 80, 80, Myhero.frame * 80, Myhero.direct * 80, 80, 80);
	//��󽫻���DC�������������DC��
	cDC->BitBlt(0, 0, mclient.Width(), mclient.Height(), &mcacheDC, 0, 0, SRCCOPY);
	//------------------�������--------------------------------------------
	ValidateRect(&mclient);
	mcacheDC.DeleteDC();
	mcacheCBitmap.DeleteObject();
	ReleaseDC(cDC);
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

