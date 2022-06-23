#include "stdafx.h"
#include "WarriorHusk.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Attack.h"
#include "AbstractFactory.h"

CWarriorHusk::CWarriorHusk()
	:m_bTarget(false), m_ePreState(END), m_eCurState(IDLE), m_dwMoveTime(GetTickCount()), m_dwAttackTime(GetTickCount()),
	m_dwCoolTime(GetTickCount()), m_dwDeadTime(GetTickCount()), m_bAttack(true)
{
}


CWarriorHusk::~CWarriorHusk()
{
}

void CWarriorHusk::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskWarrior/Idle.bmp", L"HuskWarrior_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskWarrior/Attack.bmp", L"HuskWarrior_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/HuskWarrior/Dead.bmp", L"HuskWarrior_Dead");

	m_fSpeed = 1.f;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 100.f;
	m_iHP = 3;

	m_eType = RARE;

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;

	m_eCurState = IDLE;
	m_pFrameKey = L"HuskWarrior_Idle";
}

int CWarriorHusk::Update(void)
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
			m_tInfo.fCX = 100.f;
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
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
	}

	if (0 == m_tFrame.iMotion)
	{
		m_eDir = DIR_LEFT;
	}
	else
	{
		m_eDir = DIR_RIGHT;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CWarriorHusk::Late_Update(void)
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
		if (m_bTarget)
			Attack();
		else
			Move();
	}
	else
		Dead();
}

void CWarriorHusk::Render(HDC hDC)
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
		m_tFrame.iFrameStart * 260,
		m_tFrame.iMotion * 200,
		260,
		200,
		RGB(128, 128, 128));
}

void CWarriorHusk::Release(void)
{
}

void CWarriorHusk::Motion_Change()
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
		case CWarriorHusk::IDLE:
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_pFrameKey = L"HuskWarrior_Idle";
			break;
		case CWarriorHusk::ATTACK:
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_pFrameKey = L"HuskWarrior_Attack";
			m_dwAttackTime = GetTickCount();
			break;
		case CWarriorHusk::DEAD:
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_pFrameKey = L"HuskWarrior_Dead";
			m_dwDeadTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CWarriorHusk::Move()
{

	if (m_dwMoveTime + 2400 < GetTickCount())
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

void CWarriorHusk::Attack()
{
	m_bParry = true;
	if (3 == m_tFrame.iFrameStart && m_bAttack)
	{
		if (0 == m_tFrame.iMotion)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MATTACK, CAbstractFactory<CAttack>::Create(m_tInfo.fX-30.f, m_tInfo.fY));
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MATTACK, CAbstractFactory<CAttack>::Create(m_tInfo.fX + 30.f, m_tInfo.fY));
		}
		m_bAttack = false;
	}
	if (9 == m_tFrame.iFrameStart && !m_bAttack)
	{
		m_bParry = true;
		if (0 == m_tFrame.iMotion)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MATTACK, CAbstractFactory<CAttack>::Create(m_tInfo.fX - 30.f, m_tInfo.fY));
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MATTACK, CAbstractFactory<CAttack>::Create(m_tInfo.fX + 30.f, m_tInfo.fY));
		}
		m_bAttack = true;
	}
	if (0 == m_tFrame.iMotion)
	{
		m_tInfo.fX -= m_fSpeed*4.f;
	}
	else
	{
		m_tInfo.fX += m_fSpeed*4.f;
	}
	if (m_dwAttackTime + 1050 < GetTickCount())
	{
		m_bTarget = false;
		m_eCurState = IDLE;
		m_dwCoolTime = GetTickCount();
		m_tInfo.fCX = 50.f;
		m_bAttack = true;
		m_bParry = false;
	}
}

void CWarriorHusk::Dead()
{
	if (m_dwDeadTime + 10000 < GetTickCount())
		m_bDead = true;

	if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		m_tFrame.dwFrameTime = GetTickCount();
}
