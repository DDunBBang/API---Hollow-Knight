#include "stdafx.h"
#include "Fly.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CFly::CFly()
	: m_ePreState(END), m_eCurState(IDLE), m_dwDead(GetTickCount())
{
}


CFly::~CFly()
{
}

void CFly::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Fly/Idle.bmp", L"Fly_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Fly/Dead.bmp", L"Fly_Dead");

	m_eType = FLY;
	m_tInfo.eSave = EDIT_FLY;
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	m_iHP = 1;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iMotion = 0;

	m_pFrameKey = L"Fly_Idle";
}

int CFly::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CFly::Late_Update(void)
{
	if (0 >= m_iHP)
	{
		m_eCurState = DEAD;
		m_tInfo.fCY = 0.f;
		m_tInfo.fCX = 0.f;
		if (!m_bDead)
		{
			m_dwDead = GetTickCount();
			m_bDead = true;
		}
	}

	Move_Frame();
	Motion_Change();
	if (m_dwDead + 1500 < GetTickCount())
	{
		m_tInfo.fCX = 64.f;
		m_tInfo.fCY = 64.f;
		m_eCurState = IDLE;
		m_iHP = 1;
		m_dwDead = GetTickCount();
		m_bDead = false;
	}
}

void CFly::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX - 100.f) + iScrollX,
		int(m_tInfo.fY - 100.f) + iScrollY,
		200,
		200,
		hMemDC,
		0,
		m_tFrame.iFrameStart * 256,
		256,
		256,
		RGB(255, 255, 255));
}

void CFly::Release(void)
{
}

void CFly::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CFly::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 0;

			m_pFrameKey = L"Fly_Idle";
			break;
		case CFly::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameSpeed = 250;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 0;

			m_pFrameKey = L"Fly_Dead";
			break;
		}
	}
	m_ePreState = m_eCurState;
}
