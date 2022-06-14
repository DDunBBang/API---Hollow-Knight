#include "stdafx.h"
#include "Dash.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CDash::CDash()
{
}


CDash::~CDash()
{
}

void CDash::Initialize(void)
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 150.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/dash/dash_effect.bmp", L"Dash_Effect");

	m_pFrameKey = L"Dash_Effect";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	if (m_eDir == DIR_LEFT)
		m_tFrame.iMotion = 0;
	else
		m_tFrame.iMotion = 1;

	m_tFrame.dwFrameSpeed = 30;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CDash::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CDash::Late_Update(void)
{
	Move_Frame();
}
void CDash::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tRect.left) + iScrollX,
		int(m_tRect.top) + iScrollY,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		m_tFrame.iMotion * 503,
		m_tFrame.iFrameStart * 334,
		503,
		334,
		RGB(0, 0, 0));
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CDash::Release(void)
{
}