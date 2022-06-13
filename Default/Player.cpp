#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Blade.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CPlayer::CPlayer()
	: m_bJump(false), m_dwJumpTime(GetTickCount()), m_ePreState(END), m_eCurState(IDLE), m_bLand(false),
	m_dwAttackTime(GetTickCount()), m_fJumpPower(0.f), m_fTime(0.f)
{

}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 600.f, 180.f, 90.f };
	m_fSpeed = 7.f;
	m_fJumpPower = 10.f;
	m_eDir = DIR_RIGHT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/Player.bmp", L"Player");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/idle.bmp", L"Player_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/move.bmp", L"Player_MOVE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/attack_down.bmp", L"Player_ATTACK_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/attack_top.bmp", L"Player_ATTACK_TOP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/attack1.bmp", L"Player_ATTACK1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/attack2.bmp", L"Player_ATTACK2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/dead.bmp", L"Player_DEAD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/hit.bmp", L"Player_HIT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/jump_down.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/jump_land.bmp", L"Player_LAND");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/jump_start.bmp", L"Player_JUMP");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;

	m_pFrameKey = L"Player_IDLE";

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	Key_Input();
	Offset();
	Jumping();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_tInfo.fY >= 680)
	{
		m_bLand = true;
		m_tInfo.fY = 680.f;
	}
	if (m_dwJumpTime + 300 < GetTickCount())
		m_bJump = false;
	Motion_Change();
	Move_Frame();
}

void CPlayer::Render(HDC hDC)
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
		m_tFrame.iMotion * 256,
		m_tFrame.iFrameStart * 128,
		256,
		128,
		RGB(255,0,0));
}

void CPlayer::Release(void)
{	
}

void CPlayer::Key_Input(void)
{
	if (m_bLand)
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			m_eCurState = WALK;
			m_eDir = DIR_RIGHT;
			m_pFrameKey = L"Player_MOVE";
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			m_pFrameKey = L"Player_MOVE";
			m_eCurState = WALK;
			m_eDir = DIR_LEFT;
		}
		else
		{
			m_eCurState = IDLE;
			m_pFrameKey = L"Player_IDLE";
		}
		if (CKeyMgr::Get_Instance()->Key_Down('X'))
		{
			m_dwJumpTime = GetTickCount();
			m_bJump = true;
			m_bLand = false;
			m_eCurState = JUMP;
			m_pFrameKey = L"Player_JUMP";
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			if (m_dwAttackTime + 150 < GetTickCount())
			{
				if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))
				{
					if(DIR_LEFT == m_eDir)
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY - 80, DIR_LT));
					else
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY - 80, DIR_RT));
					m_eCurState = ATTACK;
					m_pFrameKey = L"Player_ATTACK_TOP";
					if (4 == m_tFrame.iFrameStart)
						m_dwAttackTime = GetTickCount();
				}
			}
		}
		else if (m_dwAttackTime + 200 < GetTickCount())
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))
			{
				if (DIR_LEFT == m_eDir)
					CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX - 80, m_tInfo.fY, m_eDir));
				else
					CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX + 80, m_tInfo.fY, m_eDir));
				m_eCurState = ATTACK;
				m_pFrameKey = L"Player_ATTACK1";
				if (4 == m_tFrame.iFrameStart)
					m_dwAttackTime = GetTickCount();
			}
		}
	}
	else
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			m_eDir = DIR_RIGHT;
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			m_eDir = DIR_LEFT;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			if (m_dwAttackTime + 150 < GetTickCount())
			{
				if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))
				{
					if(DIR_LEFT == m_eDir)
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY + 80, DIR_LD));
					else
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY + 80, DIR_RD));
					m_eCurState = ATTACK;
					m_pFrameKey = L"Player_ATTACK_DOWN";
					if (4 == m_tFrame.iFrameStart)
						m_dwAttackTime = GetTickCount();
				}
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			if (m_dwAttackTime + 150 < GetTickCount())
			{
				if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))
				{
					if (DIR_LEFT == m_eDir)
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY - 80, DIR_LT));
					else
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY - 80, DIR_RT));
					m_eCurState = ATTACK;
					m_pFrameKey = L"Player_ATTACK_TOP";
					if (4 == m_tFrame.iFrameStart)
						m_dwAttackTime = GetTickCount();
				}
			}
		}
		else if (m_dwAttackTime + 150 < GetTickCount())
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))
			{
				if (DIR_LEFT == m_eDir)
					CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX - 80, m_tInfo.fY, m_eDir));
				else
					CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX + 80, m_tInfo.fY, m_eDir));
				m_eCurState = ATTACK;
				m_pFrameKey = L"Player_ATTACK1";
				if (4 == m_tFrame.iFrameStart)
					m_dwAttackTime = GetTickCount();
			}
		}
	}

}

void CPlayer::Jumping(void)
{
	if (m_bJump)
		m_tInfo.fY -= m_fJumpPower;
	else
		m_tInfo.fY += m_fJumpPower*1.2;
}

void CPlayer::Offset(void)
{
	int iOffsetMinX = 100.f;
	int iOffsetMaxX = 860.f;

	int iOffsetMinY = 100.f;
	int iOffsetMaxY = 620.f;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffsetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffsetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffsetMinY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffsetMaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayer::Motion_Change(void)
{
	if (DIR_LEFT == m_eDir)
		m_tFrame.iMotion = 0;
	else if (DIR_RIGHT == m_eDir)
		m_tFrame.iMotion = 1;
	if (m_ePreState != m_eCurState)
	{		
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::DASH:
			break;
		case CPlayer::JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;

			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;

			m_tFrame.dwFrameSpeed = 65;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;

			m_tFrame.dwFrameSpeed = 30;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::HIT:
			break;
		case CPlayer::DEAD:
			break;
		case CPlayer::FIRE:
			break;
		case CPlayer::CHARGE:
			break;
		case CPlayer::END:
			break;
		}

		m_ePreState = m_eCurState;
	}
}
