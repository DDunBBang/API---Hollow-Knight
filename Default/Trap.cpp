#include "stdafx.h"
#include "Trap.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CTrap::CTrap()
{
}


CTrap::~CTrap()
{
}

void CTrap::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/trap/trap.bmp", L"Trap");
	m_pFrameKey = L"Trap";

	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
}

int CTrap::Update(void)
{
	Update_Rect();
	return 0;
}

void CTrap::Late_Update(void)
{
}

void CTrap::Render(HDC hDC)
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

void CTrap::Release(void)
{
}
