#include "stdafx.h"
#include "Blade.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CBlade::CBlade()
{
}


CBlade::~CBlade()
{
}

void CBlade::Initialize(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/Effect/RL_Attack.bmp", L"RL_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/Effect/U_Attack.bmp", L"U_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/Effect/D_Attack.bmp", L"D_Attack");

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_pFrameKey = L"RL_Attack";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = 0;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tInfo.fCX = 256.f;
		m_tInfo.fCY = 128.f;
		break;
	case DIR_RIGHT:
		m_pFrameKey = L"RL_Attack";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = 1;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tInfo.fCX = 256.f;
		m_tInfo.fCY = 128.f;
		break;
	case DIR_LT:
		m_pFrameKey = L"U_Attack";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = 0;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tInfo.fCX = 256.f;
		m_tInfo.fCY = 256.f;
		break;
	case DIR_RT:
		m_pFrameKey = L"U_Attack";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = 1;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tInfo.fCX = 256.f;
		m_tInfo.fCY = 256.f;
		break;
	case DIR_LD:
		m_pFrameKey = L"D_Attack";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = 0;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tInfo.fCX = 256.f;
		m_tInfo.fCY = 256.f;
		break;
	case DIR_RD:
		m_pFrameKey = L"D_Attack";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 1;
		m_tFrame.iMotion = 1;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		m_tInfo.fCX = 256.f;
		m_tInfo.fCY = 256.f;
		break;
	}
}

int CBlade::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlade::Late_Update(void)
{
	Move_Frame();
	if (m_tFrame.iFrameStart == 0)
		m_bDead = true;
}

void CBlade::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (!lstrcmp(m_pFrameKey, L"RL_Attack"))
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left) + iScrollX,
			int(m_tRect.top) + iScrollY,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC,
			m_tFrame.iMotion * 256,
			m_tFrame.iFrameStart * 128,
			256,
			128,
			RGB(0, 0, 0));
	}
	else
	{
		GdiTransparentBlt(hDC,
			int(m_tRect.left) + iScrollX,
			int(m_tRect.top) + iScrollY,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			hMemDC,
			m_tFrame.iMotion * 256,
			m_tFrame.iFrameStart * 256,
			256,
			256,
			RGB(0, 0, 0));
	}
}

void CBlade::Release(void)
{
}
