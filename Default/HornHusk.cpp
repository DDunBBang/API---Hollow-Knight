#include "stdafx.h"
#include "HornHusk.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"


CHornHusk::CHornHusk()
	:m_bTarget(false), m_ePreState(END), m_eCurState(IDLE), m_dwMoveTime(GetTickCount()), m_dwAttackTime(GetTickCount()),
	m_dwCoolTime(GetTickCount())
{
}


CHornHusk::~CHornHusk()
{
}

void CHornHusk::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskHornHead/Idle.bmp", L"HornHusk_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskHornHead/Attack.bmp", L"HornHusk_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskHornHead/Dead.bmp", L"HornHusk_Dead");

	m_fSpeed = 1.f;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 100.f;
	m_iHP = 3;

	m_eType = NOMAL;

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;

	m_eCurState = IDLE;
	m_pFrameKey = L"HornHusk_Idle";
}

int CHornHusk::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	float	fWidth = fabs(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - m_tInfo.fX);
	float	fHeight = fabs(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - m_tInfo.fY);
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	if (200 > fDiagonal)
	{
		if (m_dwCoolTime + 1000 < GetTickCount())
		{
			m_bTarget = true;
			m_eCurState = ATTACK;
			m_tInfo.fCX = 80.f;
		}
	}

	float fY = 0.f;

	bool bLineCol = CCollisionMgr::Collision_Line(this, CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLOCK), &fY);

	if (m_tRect.bottom < fY - 3 || !bLineCol)
	{
		if (1 == m_tFrame.iMotion)
			m_tInfo.fX -= m_fSpeed;
		else
			m_tInfo.fX += m_fSpeed;
		m_tInfo.fY += m_fSpeed * 2;

		if (1 == m_tFrame.iFrameStart)
			m_tFrame.dwFrameTime = GetTickCount();
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CHornHusk::Late_Update(void)
{
	Motion_Change();
	Move_Frame();

	if (m_bTarget)
		Attack();
	else
		Move();
}

void CHornHusk::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX - 65.f) + iScrollX,
		int(m_tInfo.fY - 95.f) + iScrollY,
		130,
		150,
		hMemDC,
		m_tFrame.iFrameStart * 230,
		m_tFrame.iMotion * 200,
		230,
		200,
		RGB(255, 255, 255));
}

void CHornHusk::Release(void)
{
}

void CHornHusk::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX < m_tInfo.fX)
		{
			m_tFrame.iMotion = 0;
		}
		else
		{
			m_tFrame.iMotion = 1;
		}
		switch (m_eCurState)
		{
		case CHornHusk::IDLE:
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_pFrameKey = L"HornHusk_Idle";
			break;
		case CHornHusk::ATTACK:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_pFrameKey = L"HornHusk_Attack";
			m_dwAttackTime = GetTickCount();
			break;
		case CHornHusk::DEAD:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_pFrameKey = L"HornHusk_Dead";
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CHornHusk::Move()
{
	if (m_dwMoveTime + 2000 < GetTickCount())
	{
		if (0 == m_tFrame.iMotion)
		{
			m_tFrame.iMotion = 1;
		}
		else
		{
			m_tFrame.iMotion = 0;
		}
		m_dwMoveTime = GetTickCount();
	}
	if (0 == m_tFrame.iMotion)
	{
		m_tInfo.fX -= m_fSpeed;
	}
	else
	{
		m_tInfo.fX += m_fSpeed;
	}
}

void CHornHusk::Attack()
{
	if (0 == m_tFrame.iMotion)
	{
		m_tInfo.fX -= m_fSpeed*3.f;
	}
	else
	{
		m_tInfo.fX += m_fSpeed*3.f;
	}
	if (m_dwAttackTime + 2000 < GetTickCount())
	{
		m_bTarget = false;
		m_eCurState = IDLE;
		m_tInfo.fCX = 50.f;
		m_dwCoolTime = GetTickCount();
	}
}

void CHornHusk::Dead()
{
}
