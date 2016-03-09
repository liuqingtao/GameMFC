
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Collisions.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//�����ĸ�����
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3

#define TIMER_PAINT 1
#define TIMER_HEROMOVE 2
//���崰�ڴ�С
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
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
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
//--------------------------------------------------��Ϸ��ʼ��---------------------------------------
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

	//------------------------��ʼ����-------------------------------------

	mBg.Draw(mCacheDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	Myhero.character.Draw(mCacheDC, Myhero.x, Myhero.y, 80, 80, Myhero.frame * 80, Myhero.direct * 80, 80, 80);
	Monster.character.Draw(mCacheDC, Monster.x, Monster.y, 96, 96, Monster.frame * 96, Monster.direct * 96, 96, 96);
	
	//����״̬����
	//ˮƽ�����Ͽ���
	if (Monster.x < Myhero.x)
	{
		Monster.x++;
		Monster.direct = RIGHT;
	}
	else if (Monster.x>Myhero.x)
	{
		Monster.x--;
		Monster.direct = LEFT;
	}

	//��ֱ�����Ͽ���
	if (Monster.y < Myhero.y)
		Monster.y++;
	else
		Monster.y--;

	//�ж��Ƿ���ײ
	Myhero.Xcenter = Myhero.x + Myhero.width / 2;
	Myhero.Ycenter = Myhero.y + Myhero.height / 2;
	Monster.Xcenter = Monster.x + Monster.width / 2;
	Monster.Ycenter = Monster.y + Monster.height / 2;

	mCacheDC.SetBkMode(TRANSPARENT); //�������ֱ�Ӱ͸��
	mCacheDC.SetTextColor(RGB(255, 0, 0)); //��������Ϊ��ɫ

	//�ж��Ƿ���ײ
	if (Monster.Xcenter<Myhero.Xcenter + (Myhero.width / 2 + Monster.width / 2) &&
		Monster.Xcenter>Myhero.Xcenter - (Myhero.width / 2 + Monster.width / 2) &&
		Monster.Ycenter < Myhero.Ycenter + (Myhero.height / 2 + Monster.height / 2) &&
		Monster.Ycenter > Myhero.Ycenter - (Myhero.height / 2 + Monster.height / 2))
		mCacheDC.TextOutW(0, 0, _T("������ײ"));
	else
		mCacheDC.TextOutW(0, 0, _T("û����ײ"));

	//��󽫻���DC�������������DC��
	cDC->BitBlt(0, 0, mClient.Width(), mClient.Height(), &mCacheDC, 0, 0, SRCCOPY);
	//----------------------------���ƽ���-------------------------------
	//�������ʹ������Ч
	ValidateRect(&mClient);

	mCacheDC.DeleteDC();
	mCacheCBitmap.DeleteObject();
	ReleaseDC(cDC);
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case 'D':
		Myhero.direct = RIGHT;
		Myhero.x += 5;
		break;
	case 'A':
		Myhero.direct = LEFT;
		Myhero.x -= 5;
		break;
	case 'W':
		Myhero.direct = UP;
		Myhero.y -= 5;
		break;
	case 'S':
		Myhero.direct = DOWN;
		Myhero.y += 5;
		break;
	}
	
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case TIMER_PAINT:
		OnPaint();
		break;
	case TIMER_HEROMOVE:
		Myhero.frame++;
		if (Myhero.frame == 4)
			Myhero.frame = 0;
		Monster.frame++;
		if (Monster.frame == 4)
			Monster.frame = 0;
	}

}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetTimer(TIMER_PAINT, 10, NULL);
	SetTimer(TIMER_HEROMOVE, 100, NULL);
	return 0;
}
