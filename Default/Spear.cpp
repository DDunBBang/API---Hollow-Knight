#include "stdafx.h"
#include "Spear.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CSpear::CSpear()
	:m_bHit(false)
{
}


CSpear::~CSpear()
{
}

void CSpear::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/trap/spear.bmp", L"Spear");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/trap/spear_LD.bmp", L"Spear_LD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/trap/spear_RD.bmp", L"Spear_RD");

	m_pFrameKey = L"Spear";

	m_tInfo.fCX = 39.f;
	m_tInfo.fCY = 105.f;
}

int CSpear::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CSpear::Late_Update(void)
{
	if (m_bHit)
	{
		if (DIR_LEFT == m_eDir)
			m_pFrameKey = L"Spear_LD";
		else if (DIR_RIGHT == m_eDir)
			m_pFrameKey = L"Spear_RD";
	}
}

void CSpear::Render(HDC hDC)
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
		39,
		105,
		RGB(255, 255, 255));
}

void CSpear::Release(void)
{
}
