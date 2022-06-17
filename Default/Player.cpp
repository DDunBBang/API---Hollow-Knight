#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Blade.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Dash.h"
#include "Charge.h"
#include "CollisionMgr.h"
#include "HP.h"
#include "UIMgr.h"
#include "Soul.h"

CPlayer::CPlayer()
	: m_dwJumpTime(GetTickCount()), m_ePreState(END), m_eCurState(IDLE), m_dwHealTime(GetTickCount()),
	m_dwAttackTime(GetTickCount()), m_fTime(0.f), m_bDash(false), m_dwDashTime(GetTickCount()), m_bHeal(false)
{

}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 1000.f, 35.f, 75.f };
	m_fSpeed = 7.f;
	m_fJumpPower = 12.f;
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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/dash/Dash.bmp", L"Player_Dash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/Charge.bmp", L"Player_Charge");


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;

	m_pFrameKey = L"Player_IDLE";

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CPlayer::Update(void)
{
	Update_Rect();
	if (m_bDead)
		return OBJ_DEAD;
	Offset();
	if (m_bDash)
		Dash();
	else if (m_bHeal)
		Heal();
	else
	{
		Key_Input();
		Jumping();	
	}
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_dwJumpTime + 300 < GetTickCount())
		m_bJump = false;
	Motion_Change();
	Move_Frame();
}

void CPlayer::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX-90) + iScrollX,
		int(m_tInfo.fY-50) + iScrollY,
		180,
		90,
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
		if (3 <= *(dynamic_cast<CSoul*>(CUIMgr::Get_Instance()->Get_UIList(UI_SOUL)->front())->Get_Gauge())
			&& dynamic_cast<CHP*>(CUIMgr::Get_Instance()->Get_HP()->back())->Get_Destroy())
		{
			if (CKeyMgr::Get_Instance()->Key_Down('A'))
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_CHARGE, CAbstractFactory<CCharge>::Create(m_tInfo.fX, m_tInfo.fY - 12.f));
				m_dwHealTime = GetTickCount();
				m_bHeal = true;
			}
		}
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
				if(CKeyMgr::Get_Instance()->Key_Up('Z'))
					m_dwAttackTime = GetTickCount();
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
			if (CKeyMgr::Get_Instance()->Key_Up('Z'))
				m_dwAttackTime = GetTickCount();
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
				if (CKeyMgr::Get_Instance()->Key_Up('Z'))
					m_dwAttackTime = GetTickCount();
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
				if (CKeyMgr::Get_Instance()->Key_Up('Z'))
					m_dwAttackTime = GetTickCount();
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
			if (CKeyMgr::Get_Instance()->Key_Up('Z'))
				m_dwAttackTime = GetTickCount();
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LSHIFT))
	{
		m_bDash = true;
		CObjMgr::Get_Instance()->Add_Object(OBJ_DASH, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, m_eDir));
		m_dwDashTime = GetTickCount();
	}

}

void CPlayer::Jumping(void)
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
		if (0 == m_tFrame.iFrameStart)
		{
			m_eCurState = DOWN;
			m_pFrameKey = L"Player_DOWN";
		}
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
		m_bLand = true;
	}
}

void CPlayer::Dash(void)
{
	m_eCurState = DASH;
	m_pFrameKey = L"Player_Dash";
	if (DIR_LEFT == m_eDir)
		m_tInfo.fX -= m_fSpeed*4.f;
	if (DIR_RIGHT == m_eDir)
		m_tInfo.fX += m_fSpeed*4.f;
	if (m_dwDashTime + 150 < GetTickCount())
	{
		m_bDash = false;
		CObjMgr::Get_Instance()->Delete_ID(OBJ_DASH);
	}
}

void CPlayer::Heal(void)
{
	if (3 <= *(dynamic_cast<CSoul*>(CUIMgr::Get_Instance()->Get_UIList(UI_SOUL)->front())->Get_Gauge()))
	{

		if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		{
			m_eCurState = CHARGE;
			m_pFrameKey = L"Player_Charge";
			if (m_dwHealTime + 900 < GetTickCount())
			{
				for (auto& iter : *(CUIMgr::Get_Instance()->Get_HP()))
				{
					if (dynamic_cast<CHP*>(iter)->Get_Destroy())
					{
						dynamic_cast<CHP*>(iter)->Set_Destroy(false);
						dynamic_cast<CSoul*>(CUIMgr::Get_Instance()->Get_UIList(UI_SOUL)->front())->Set_Gauge(-3);
						break;
					}
				}
				m_dwHealTime = GetTickCount();
			}
		}
	}
	else
	{
		m_bHeal = false;
		CObjMgr::Get_Instance()->Delete_ID(OBJ_CHARGE);
	}
	if (CKeyMgr::Get_Instance()->Key_Up('A'))
	{
		m_bHeal = false;
		CObjMgr::Get_Instance()->Delete_ID(OBJ_CHARGE);
	}
}

void CPlayer::Offset(void)
{
	int iOffsetMinX = 465;
	int iOffsetMaxX = 485;

	int iOffsetMinY = 355;
	int iOffsetMaxY = 365;

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
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;

			m_tFrame.dwFrameSpeed = 0;
			m_tFrame.dwFrameTime = GetTickCount();
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
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;

			m_tFrame.dwFrameSpeed = 60;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::END:
			break;
		}

		m_ePreState = m_eCurState;
	}
}
