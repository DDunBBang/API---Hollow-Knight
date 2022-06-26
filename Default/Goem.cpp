#include "stdafx.h"
#include "Goem.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CGoem::CGoem()
	: m_ePreState(END), m_eCurState(IDLE), m_dwChange(GetTickCount()), m_bStand(false)
{
}


CGoem::~CGoem()
{
}

void CGoem::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Goem/Idle.bmp", L"Goem_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Goem/Up.bmp", L"Goem_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Goem/Down.bmp", L"Goem_Down");

	m_eType = NOMAL;
	m_tInfo.eSave = EDIT_FLY;
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 0.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 125;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iMotion = 0;

	m_pFrameKey = L"Goem_Idle";
}

int CGoem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CGoem::Late_Update(void)
{
	if (m_dwChange + 1000 < GetTickCount())
	{
		if (m_ePreState == UP)
			m_eCurState = IDLE;
		else if (m_ePreState == DOWN)
			m_eCurState = IDLE;
		else if (m_ePreState == IDLE)
		{
			if (m_bStand)
			{
				m_eCurState = DOWN;
				m_bStand = false;
			}
			else
			{
				m_eCurState = UP;
				m_bStand = true;
			}
		}
		m_dwChange = GetTickCount();
	}
	Move_Frame();
	Motion_Change();
}

void CGoem::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tRect.left) + iScrollX,
		int(m_tRect.top) + iScrollY,
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		m_tFrame.iFrameStart * 200,
		0,
		200,
		512,
		RGB(255, 255, 255));
}

void CGoem::Release(void)
{
}

void CGoem::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CGoem::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 0;

			m_pFrameKey = L"Goem_Idle";
			break;
		case CGoem::UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 250;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 0;

			m_pFrameKey = L"Goem_Up";
			break;
		case CGoem::DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 250;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 0;

			m_pFrameKey = L"Goem_Down";
			break;
		}
	}
	m_ePreState = m_eCurState;
}
