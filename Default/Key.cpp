#include "stdafx.h"
#include "Key.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CKey::CKey()
{
}


CKey::~CKey()
{
}

void CKey::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Key.bmp", L"Key");
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	m_iHP = 1;
	m_pFrameKey = L"Key";
}

int CKey::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CKey::Late_Update(void)
{
	if (0 >= m_iHP)
		m_bDead = true;
}

void CKey::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(hDC,
		int(m_tRect.left) + iScrollX,
		int(m_tRect.top) + iScrollY,
		64,
		64,
		hMemDC,
		0,
		0,
		64,
		64,
		RGB(255, 255, 255));
}

void CKey::Release(void)
{
}
