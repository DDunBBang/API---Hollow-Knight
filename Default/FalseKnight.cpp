#include "stdafx.h"
#include "FalseKnight.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CFalseKnight::CFalseKnight()
	:m_iPattern(0), m_dwJumpTime(GetTickCount()), m_dwPatternTime(GetTickCount()), m_bPattern(false), m_dwSelectPattern(GetTickCount()),
	m_bJumpAttack(false), m_bWave(false), m_bSwing(false)
{
}


CFalseKnight::~CFalseKnight()
{
}

void CFalseKnight::Initialize(void)
{
	m_tInfo = { 700.f, 1000.f, 170.f, 200.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Idle.bmp", L"Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Jump.bmp", L"Jump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Jump_Attack.bmp", L"Jump_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Wave.bmp", L"Wave");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Swing.bmp", L"Swing");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Groggy.bmp", L"Groggy");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Stand.bmp", L"Stand");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Dead.bmp", L"Dead");

	m_pFrameKey = L"Idle";
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iMotion = 1;

	m_fJumpPower = 20.f;
	m_fSpeed = 5.f;

	m_eDir = DIR_LEFT;
}

int CFalseKnight::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bJumpAttack)
		Jump_Attack();
	else if (m_bSwing)
		Swing();
	else if (m_bWave)
		Wave();
	else
		Jumping();
	
	Update_Rect();
	return OBJ_NOEVENT;
}

void CFalseKnight::Late_Update(void)
{
	if (m_dwJumpTime + 400 < GetTickCount())
		m_bJump = false;
	if(m_dwSelectPattern + 2000 < GetTickCount())
		SelectPattern();
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
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX < m_tInfo.fX)
		{
			m_tFrame.iMotion = 1;
		}
		else
		{
			m_tFrame.iMotion = 0;
		}
		switch (m_eCurState)
		{
		case CFalseKnight::IDLE:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CFalseKnight::JUMP:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwFrameTime = GetTickCount();
			m_bJump = true;
			m_dwJumpTime = GetTickCount();
			break;
		case CFalseKnight::JUMP_ATTACK:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameTime = GetTickCount();
			m_bJumpAttack = true;
			break;
		case CFalseKnight::WAVE:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameTime = GetTickCount();
			m_bWave = true;
			break;
		case CFalseKnight::SWING:
			m_tFrame.dwFrameSpeed = 90;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_bSwing = true;
			break;
		case CFalseKnight::GROGGY:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CFalseKnight::STAND:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CFalseKnight::DEAD:
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFrameTime = GetTickCount();
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

void CFalseKnight::SelectPattern()
{
	m_iPattern = rand() % 11 + 1;
	if (4 >= m_iPattern)
	{
		m_eCurState = JUMP;
		m_pFrameKey = L"Jump";
	}
	else if (7 >= m_iPattern)
	{
		m_eCurState = WAVE;
		m_pFrameKey = L"Wave";
	}
	else if (10 >= m_iPattern)
	{
		m_eCurState = WAVE;
		m_pFrameKey = L"Wave";
	}
	else
	{
		m_eCurState = SWING;
		m_pFrameKey = L"Swing";
	}
	m_dwSelectPattern = GetTickCount();
}

void CFalseKnight::Jump_Attack()
{
}

void CFalseKnight::Wave()
{
}

void CFalseKnight::Swing()
{
}

