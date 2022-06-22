#include "stdafx.h"
#include "Plat.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CPlat::CPlat()
{
}


CPlat::~CPlat()
{
}

void CPlat::Initialize(void)
{
	m_tInfo.fCX = 192.f;
	m_tInfo.fCY = 64.f;
	m_tInfo.eSave = EDIT_PLAT;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/plat.bmp", L"Plat");

	m_pFrameKey = L"Plat";
}

int CPlat::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPlat::Late_Update(void)
{
}

void CPlat::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX - 133.f) + iScrollX,
		int(m_tInfo.fY - 70.f) + iScrollY,
		266,
		180,
		hMemDC,
		0,
		0,
		266,
		231,
		RGB(255, 255, 255));

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlat::Release(void)
{
}
