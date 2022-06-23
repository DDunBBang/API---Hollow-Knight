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
#include "Hit.h"
#include "CollisionMgr.h"
#include "HP.h"
#include "UIMgr.h"
#include "Soul.h"
#include "Inven.h"
#include "FalseKnight.h"
#include "AttackEffect.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
	: m_ePreState(END), m_eCurState(IDLE), m_dwHealTime(GetTickCount()),
	m_dwAttackTime(GetTickCount()), m_fTime(0.f), m_bDash(false), m_dwDashTime(GetTickCount()), m_bHeal(false),
	m_bHit(false), m_dwHitTime(GetTickCount()), m_bImu(false), m_dwImuTime(GetTickCount()), m_bDownAttack(false),
	m_bUpAttack(false), m_bInven(false), m_bAttack(false), m_fJumpHeight(0), m_dwParryTime(GetTickCount())
{

}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 1500.f, 35.f, 75.f };
	m_fSpeed = 8.f;
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
	//블럭충돌
	if (2 == CCollisionMgr::Collision_Rect_Ex(*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)), *(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLOCK))))
	{
		m_bJump = false;
		m_fJumpHeight = 0.f;
	}

	//대못공격판정
	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE)->begin() != CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE)->end())
	{
		if (dynamic_cast<CBlade*>((*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE))).back())->Get_Attack())
		{
			if (CCollisionMgr::Collision_Attack_Monster(this, *(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE)), *(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER))))
			{
				if (m_bDownAttack)
				{
					m_bJump = true;
					m_fJumpHeight = 50.f;
				}
				else if (!m_bUpAttack)
				{
					if (DIR_RIGHT == m_eDir)
						m_tInfo.fX -= 40;
					else
						m_tInfo.fX += 40;
				}
				float fX = dynamic_cast<CBlade*>((*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE))).back())->Get_Info().fX;
				float fY = dynamic_cast<CBlade*>((*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE))).back())->Get_Info().fY;
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CAttackEffect>::Create(fX, fY, m_eDir));
				dynamic_cast<CSoul*>((*(CUIMgr::Get_Instance()->Get_UIList(UI_SOUL))).front())->Set_Gauge(1);
				dynamic_cast<CBlade*>((*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE))).front())->Set_Attack(false);
			}
			if (CCollisionMgr::Collision_Rect(*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE)), *(CObjMgr::Get_Instance()->Get_ObjList(OBJ_TRAP))))
			{
				CSoundMgr::Get_Instance()->PlaySound(L"sword_hit_reject.wav", SOUND_EFFECT, 1);
				if (m_bDownAttack)
				{
					m_bJump = true;
					m_fJumpHeight = 50.f;
				}
				else if (!m_bUpAttack)
				{
					if (DIR_RIGHT == m_eDir)
						m_tInfo.fX -= 40;
					else
						m_tInfo.fX += 40;
				}
				float fX = dynamic_cast<CBlade*>((*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE))).back())->Get_Info().fX;
				float fY = dynamic_cast<CBlade*>((*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE))).back())->Get_Info().fY;
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CAttackEffect>::Create(fX, fY, m_eDir));
				dynamic_cast<CBlade*>((*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLADE))).front())->Set_Attack(false);
			}
			m_bDownAttack = false;
			m_bUpAttack = false;

			if (m_bParry)
				m_dwParryTime = GetTickCount();
		}
	}

	//히트판정
	if (!m_bHit && !m_bImu && !m_bParry)
	{
		if (CCollisionMgr::Collision_Rect(*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)), *(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER))) ||
			CCollisionMgr::Collision_Rect(*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)), *(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MATTACK))) ||
			CCollisionMgr::Collision_Rect(*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)), *(CObjMgr::Get_Instance()->Get_ObjList(OBJ_TRAP))))
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CHit>::Create(m_tInfo.fX, m_tInfo.fY, m_eDir));
			m_eCurState = HIT;
			m_pFrameKey = L"Player_HIT";
			m_bHit = true;
			m_dwHitTime = GetTickCount();
			for (int i = 4; i >= 0; --i)
			{
				if (!dynamic_cast<CHP*>((*(CUIMgr::Get_Instance()->Get_HP()))[i])->Get_Destroy())
				{
					dynamic_cast<CHP*>((*(CUIMgr::Get_Instance()->Get_HP()))[i])->Set_Destroy(true);
					break;
				}
				if (0 == i)
				{
					m_eCurState = DEAD;
					m_pFrameKey = L"Player_DEAD";
					m_bImu = true;
				}
			}
		}
	}
	if (m_bHit && m_dwHitTime + 1000 < GetTickCount())
	{

		m_bHit = false;
	}
	if (m_dwParryTime + 500 < GetTickCount())
		m_bParry = false;

	Update_Rect();
	if (m_bDead)
		return OBJ_DEAD;
	Offset();


	if (m_eCurState != DEAD)
	{
		if (m_bHit && m_dwHitTime + 300 > GetTickCount())
			Hit();
		else if (m_bDash)
			Dash();
		else if (m_bHeal)
			Heal();
		else
		{
			Key_Input();
			Jumping();
		}
	}
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_fJumpHeight > 270.f)
	{
		m_bJump = false;
		m_fJumpHeight = 0.f;
	}

	if (!m_bAttack)
	{
		Motion_Change();
	}
	Move_Frame();

	if (m_ePreState == ATTACK && m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
	{
		m_bAttack = false;
		m_dwAttackTime = GetTickCount();
	}

	if (m_ePreState == DEAD)
	{
		if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		{
			CScrollMgr::Get_Instance()->Reset_Scroll(0.f, -1400.f);
			Set_Pos(400.f, 1500.f);
			m_eCurState = IDLE;
			m_pFrameKey = L"Player_IDLE";
			m_bImu = false;
		}
	}
}

void CPlayer::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX - 90) + iScrollX,
		int(m_tInfo.fY - 50) + iScrollY,
		180,
		90,
		hMemDC,
		m_tFrame.iMotion * 256,
		m_tFrame.iFrameStart * 128,
		256,
		128,
		RGB(255, 0, 0));
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
				CSoundMgr::Get_Instance()->PlaySound(L"charge.wav", SOUND_EFFECT, 1);
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
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			m_eCurState = WALK;
			m_eDir = DIR_LEFT;
		}
		else
		{
			m_eCurState = IDLE;
		}
		if (CKeyMgr::Get_Instance()->Key_Down('X'))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"hero_jump.wav", SOUND_EFFECT, 1);
			m_bJump = true;
			m_bLand = false;
			m_eCurState = JUMP;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			if (m_dwAttackTime + 100 < GetTickCount())
			{
				if (CKeyMgr::Get_Instance()->Key_Down('Z'))
				{
					m_bUpAttack = true;
					if (DIR_LEFT == m_eDir)
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY - 80, DIR_LT));
					else
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY - 80, DIR_RT));
					m_eCurState = ATTACK;
					m_pFrameKey = L"Player_ATTACK_TOP";
				}
			}
		}
		else if (m_dwAttackTime + 100 < GetTickCount())
		{
			if (CKeyMgr::Get_Instance()->Key_Down('Z'))
			{
				if (DIR_LEFT == m_eDir)
					CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX - 80, m_tInfo.fY, m_eDir));
				else
					CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX + 80, m_tInfo.fY, m_eDir));
				m_eCurState = ATTACK;
				m_pFrameKey = L"Player_ATTACK1";
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
			if (m_dwAttackTime + 100 < GetTickCount())
			{
				if (CKeyMgr::Get_Instance()->Key_Down('Z'))
				{
					m_bDownAttack = true;
					if (DIR_LEFT == m_eDir)
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY + 80, DIR_LD));
					else
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY + 80, DIR_RD));
					m_eCurState = ATTACK;
					m_pFrameKey = L"Player_ATTACK_DOWN";
				}
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			if (m_dwAttackTime + 100 < GetTickCount())
			{
				if (CKeyMgr::Get_Instance()->Key_Down('Z'))
				{
					m_bUpAttack = true;
					if (DIR_LEFT == m_eDir)
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY - 80, DIR_LT));
					else
						CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX, m_tInfo.fY - 80, DIR_RT));
					m_eCurState = ATTACK;
					m_pFrameKey = L"Player_ATTACK_TOP";
				}
			}
		}
		else if (m_dwAttackTime + 100 < GetTickCount())
		{
			if (CKeyMgr::Get_Instance()->Key_Down('Z'))
			{
				if (DIR_LEFT == m_eDir)
					CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX - 80, m_tInfo.fY, m_eDir));
				else
					CObjMgr::Get_Instance()->Add_Object(OBJ_BLADE, CAbstractFactory<CBlade>::Create(m_tInfo.fX + 80, m_tInfo.fY, m_eDir));
				m_eCurState = ATTACK;
				m_pFrameKey = L"Player_ATTACK1";
			}
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LSHIFT))
	{
		m_dwImuTime = GetTickCount();
		m_bDash = true;
		CObjMgr::Get_Instance()->Add_Object(OBJ_DASH, CAbstractFactory<CDash>::Create(m_tInfo.fX, m_tInfo.fY, m_eDir));
		m_dwDashTime = GetTickCount();
	}
	if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		if (m_bInven)
			m_bInven = false;
		else
			m_bInven = true;
		dynamic_cast<CInven*>(CUIMgr::Get_Instance()->Get_UIList(UI_INVEN)->front())->Set_On(m_bInven);
	}
}

void CPlayer::Jumping(void)
{
	float fY = 0.f;

	bool bLineCol = CCollisionMgr::Collision_Line(this, CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLOCK), &fY);

	if (m_bJump)
	{
		m_fJumpHeight += m_fJumpPower;
		m_tInfo.fY -= m_fJumpPower;

	}
	else if (m_tRect.bottom < fY - 3 || !bLineCol)
	{
		m_tInfo.fY += m_fSpeed * 2.f;
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed*2.f);
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
	m_bImu = true;
	m_eCurState = DASH;
	m_pFrameKey = L"Player_Dash";
	if (DIR_LEFT == m_eDir)
	{
		m_tInfo.fX -= m_fSpeed*4.f;
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed*4.f);
	}
	if (DIR_RIGHT == m_eDir)
	{
		m_tInfo.fX += m_fSpeed*4.f;
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed*4.f);
	}
	if (m_dwDashTime + 200 < GetTickCount())
	{
		m_bImu = false;
		m_bDash = false;
		m_bJump = false;
		m_fJumpHeight = 0.f;
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
				CSoundMgr::Get_Instance()->PlaySound(L"charge_complete.wav", SOUND_EFFECT, 1);
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

void CPlayer::Hit(void)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	switch (m_tFrame.iFrameStart)
	{
	case 0:
		CScrollMgr::Get_Instance()->Set_ScrollX(8);
		CScrollMgr::Get_Instance()->Set_ScrollY(8);
		break;
	case 1:
		CScrollMgr::Get_Instance()->Set_ScrollX(-8);
		CScrollMgr::Get_Instance()->Set_ScrollY(-8);
		break;
	case 2:
		CScrollMgr::Get_Instance()->Set_ScrollX(-8);
		break;
	case 3:
		CScrollMgr::Get_Instance()->Set_ScrollX(8);
		break;
	case 4:
		CScrollMgr::Get_Instance()->Set_ScrollY(8);
		break;
	case 5:
		CScrollMgr::Get_Instance()->Set_ScrollY(-8);
		break;
	}
	if (DIR_LEFT == m_eDir)
		m_tInfo.fX += m_fSpeed;
	else
		m_tInfo.fX -= m_fSpeed;
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
			m_pFrameKey = L"Player_IDLE";
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_pFrameKey = L"Player_MOVE";
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
			m_pFrameKey = L"Player_JUMP";
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

			m_tFrame.dwFrameSpeed = 20;
			m_tFrame.dwFrameTime = GetTickCount();
			m_bAttack = true;
			break;
		case CPlayer::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;

			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
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
