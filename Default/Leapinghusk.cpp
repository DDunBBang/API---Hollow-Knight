#include "stdafx.h"
#include "Leapinghusk.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"


CLeapinghusk::CLeapinghusk()
	:m_bTarget(false), m_ePreState(END), m_eCurState(IDLE), m_dwMoveTime(GetTickCount()), m_dwAttackTime(GetTickCount()),
	m_dwCoolTime(GetTickCount()), m_dwDeadTime(GetTickCount())
{
}


CLeapinghusk::~CLeapinghusk()
{
}

void CLeapinghusk::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskLeap/Idle.bmp", L"LeapingHusk_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskLeap/Attack.bmp", L"LeapingHusk_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskLeap/Dead.bmp", L"LeapingHusk_Dead");

	m_fSpeed = 1.f;
	m_tInfo.fCX = 55.f;
	m_tInfo.fCY = 120.f;
	m_iHP = 3;
	m_fJumpPower = 12.f;
	m_fJumpHeight = 0.f;

	m_eType = NOMAL;

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;

	m_eCurState = IDLE;
	m_pFrameKey = L"LeapingHusk_Idle";
}

int CLeapinghusk::Update(void)
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
		}
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CLeapinghusk::Late_Update(void)
{
	if (0 >= m_iHP)
	{
		m_tInfo.fCX = 0.f;
		m_tInfo.fCY = 0.f;
		m_eCurState = DEAD;
	}

	Motion_Change();
	Move_Frame();

	if (m_eCurState != DEAD)
	{

		float fY = 0.f;

		bool bLineCol = CCollisionMgr::Collision_Line(this, CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLOCK), &fY);

		if (m_bTarget)
			Attack();
		else if ((m_tRect.bottom < fY - 3 || !bLineCol))
		{
			if (0 == m_tFrame.iMotion)
				m_tInfo.fX -= m_fSpeed*3.f;
			else
				m_tInfo.fX += m_fSpeed*3.f;
			m_tInfo.fY += m_fJumpPower;
		}
		else if (bLineCol)
		{
			m_eCurState = IDLE;
			Move();
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
		}
	}
	else
		Dead();
}

void CLeapinghusk::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX - 65.f) + iScrollX,
		int(m_tInfo.fY - 100.f) + iScrollY,
		130,
		180,
		hMemDC,
		m_tFrame.iFrameStart * 200,
		m_tFrame.iMotion * 250,
		200,
		250,
		RGB(255, 255, 255));
}

void CLeapinghusk::Release(void)
{
}

void CLeapinghusk::Motion_Change()
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
		case CLeapinghusk::IDLE:
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_pFrameKey = L"LeapingHusk_Idle";
			break;
		case CLeapinghusk::ATTACK:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_pFrameKey = L"LeapingHusk_Attack";
			m_dwAttackTime = GetTickCount();
			break;
		case CLeapinghusk::DEAD:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_pFrameKey = L"LeapingHusk_Dead";
			m_dwDeadTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CLeapinghusk::Move()
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

void CLeapinghusk::Attack()
{
	if (0 == m_tFrame.iMotion)
	{
		m_tInfo.fX -= m_fSpeed*3.f;
	}
	else
	{
		m_tInfo.fX += m_fSpeed*3.f;
	}
	m_fJumpHeight += m_fJumpPower;
	m_tInfo.fY -= m_fJumpPower;
	if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		m_tFrame.dwFrameTime = GetTickCount();

	if (200 <= m_fJumpHeight)
	{
		m_tFrame.iFrameStart = 0;
		m_bTarget = false;
		m_tInfo.fCX = 50.f;
		m_fJumpHeight = 0.f;
		m_dwCoolTime = GetTickCount();
	}
}

void CLeapinghusk::Dead()
{
	if (m_dwDeadTime + 10000 < GetTickCount())
		m_bDead = true;

	if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		m_tFrame.dwFrameTime = GetTickCount();
}
