#include "stdafx.h"
#include "Attack.h"
#include "ScrollMgr.h"

CAttack::CAttack()
	:m_dwDeleteTime(GetTickCount())
{
}


CAttack::~CAttack()
{
}

void CAttack::Initialize(void)
{
	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 120.f;
}

int CAttack::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CAttack::Late_Update(void)
{
	if (m_dwDeleteTime + 90 < GetTickCount())
		m_bDead = true;
}

void CAttack::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CAttack::Release(void)
{
}
