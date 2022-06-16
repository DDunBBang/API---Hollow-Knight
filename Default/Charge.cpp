#include "stdafx.h"
#include "Charge.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CCharge::CCharge()
{
}


CCharge::~CCharge()
{
}

void CCharge::Initialize(void)
{
	m_tInfo.fCX = 180.f;
	m_tInfo.fCY = 180.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/Effect/Charge_Effect.bmp", L"Charge_Effect");

	m_pFrameKey = L"Charge_Effect";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CCharge::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CCharge::Late_Update(void)
{
	Move_Frame();
}

void CCharge::Render(HDC hDC)
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
		m_tFrame.iFrameStart * 172,
		0,
		172,
		170,
		RGB(255, 0, 0));
}

void CCharge::Release(void)
{
}
