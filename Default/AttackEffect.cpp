#include "stdafx.h"
#include "AttackEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CAttackEffect::CAttackEffect()
{
}


CAttackEffect::~CAttackEffect()
{
}

void CAttackEffect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/Effect/Attack_Effect.bmp", L"Attack_Effect");

	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 150.f;
	m_pFrameKey = L"Attack_Effect";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	if (m_eDir == DIR_LEFT)
		m_tFrame.iMotion = 1;
	else
		m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 30;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CAttackEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CAttackEffect::Late_Update(void)
{
	if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		m_bDead = true;
	Move_Frame();
}

void CAttackEffect::Render(HDC hDC)
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
		m_tFrame.iFrameStart * 280,
		m_tFrame.iMotion * 200,
		280,
		200,
		RGB(23, 23, 21));
}

void CAttackEffect::Release(void)
{
}
