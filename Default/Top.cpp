#include "stdafx.h"
#include "Top.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CTop::CTop()
{
}


CTop::~CTop()
{
}

void CTop::Initialize(void)
{
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 64.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Top.bmp", L"Top");

	m_pFrameKey = L"Top";
}

int CTop::Update(void)
{
	Update_Rect();
	return 0;
}

void CTop::Late_Update(void)
{
}

void CTop::Render(HDC hDC)
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
		313,
		202,
		RGB(255, 255, 255));
}

void CTop::Release(void)
{
}
