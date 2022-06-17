#include "stdafx.h"
#include "FalseKnight.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CFalseKnight::CFalseKnight()
{
}


CFalseKnight::~CFalseKnight()
{
}

void CFalseKnight::Initialize(void)
{
	m_tInfo = { 700.f, 1000.f, 170.f, 200.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight.bmp", L"FalseKnight");

	m_pFrameKey = L"FalseKnight";
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iMotion = 1;

	m_fJumpPower = 15.f;
	m_fSpeed = 5.f;

	m_eDir = DIR_LEFT;
}

int CFalseKnight::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Jumping();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CFalseKnight::Late_Update(void)
{
	Move_Frame();
	Motion_Change();
}

void CFalseKnight::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX-325.f) + iScrollX,
		int(m_tInfo.fY-260.f) + iScrollY,
		650,
		390,
		hMemDC,
		m_tFrame.iFrameStart * 650,
		m_tFrame.iMotion * 390,
		650,
		390,
		RGB(47, 46, 39));
}

void CFalseKnight::Release(void)
{
}

void CFalseKnight::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CFalseKnight::IDLE:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 0;
			break;
		case CFalseKnight::JUMP:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 1;
			break;
		case CFalseKnight::JUMP_ATTACK:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 1;
			break;
		case CFalseKnight::WAVE:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 1;
			break;
		case CFalseKnight::NUCKBACK:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.iMotion = 1;
			break;
		}
	}
	m_ePreState = m_eCurState;
}

void CFalseKnight::Jumping()
{
	float fY = 0.f;

	bool bLineCol = CCollisionMgr::Collision_Line(this, CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLOCK), &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower;

	}
	else if (m_tRect.bottom < fY - 3 || !bLineCol)
	{
		m_tInfo.fY += m_fSpeed * 2;
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
		m_bLand = true;
	}
}

void CFalseKnight::Pattern()
{
}
