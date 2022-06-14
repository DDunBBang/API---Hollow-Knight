#include "stdafx.h"
#include "Trap_L.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CTrap_L::CTrap_L()
{
}


CTrap_L::~CTrap_L()
{
}

void CTrap_L::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/trap/trap_L.bmp", L"Trap_L");
	m_pFrameKey = L"Trap_L";
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
}

int CTrap_L::Update(void)
{
	Update_Rect();
	return 0;
}

void CTrap_L::Late_Update(void)
{
}

void CTrap_L::Render(HDC hDC)
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
		0,
		0,
		150,
		150,
		RGB(255, 255, 255));
}

void CTrap_L::Release(void)
{
}
