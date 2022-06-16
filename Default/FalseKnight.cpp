#include "stdafx.h"
#include "FalseKnight.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CFalseKnight::CFalseKnight()
{
}


CFalseKnight::~CFalseKnight()
{
}

void CFalseKnight::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight.bmp", L"FalseKnigt");

	m_pFrameKey = L"FalseKnight";
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iMotion = 0;
}

int CFalseKnight::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CFalseKnight::Late_Update(void)
{
}

void CFalseKnight::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX) + iScrollX,
		int(m_tInfo.fY) + iScrollY,
		180,
		90,
		hMemDC,
		m_tFrame.iFrameStart * 650,
		m_tFrame.iMotion * 390,
		650,
		390,
		RGB(255, 0, 0));
}

void CFalseKnight::Release(void)
{
}
