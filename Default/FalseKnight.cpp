#include "stdafx.h"
#include "FalseKnight.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Wave.h"
#include "Attack.h"
#include "SoundMgr.h"

CFalseKnight::CFalseKnight()
	:m_iPattern(0), m_dwJumpTime(GetTickCount()), m_dwPatternTime(GetTickCount()), m_bLoop(false), m_dwSelectPattern(GetTickCount()), m_bTarget(false),
	m_bJumpAttack(false), m_bWave(false), m_iWave(1), m_bSwing(false), m_iSwingL(1), m_iSwingR(1), m_iLoop(0), m_bPattern(false), m_bGroggy(false)
{
}


CFalseKnight::~CFalseKnight()
{
}

void CFalseKnight::Initialize(void)
{
	m_tInfo = { 6000.f, 450.f, 160.f, 300.f };
	m_tInfo.fCX = 160.f;
	m_tInfo.fCY = 300.f;
	m_iHP = 15;
	m_bLand = true;
	m_eType = BOSS;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Idle.bmp", L"FalseKnight_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Jump.bmp", L"FalseKnight_Jump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Jump_Attack.bmp", L"FalseKnight_Jump_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Wave.bmp", L"FalseKnight_Wave");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Swing.bmp", L"FalseKnight_Swing");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Groggy.bmp", L"FalseKnight_Groggy");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Stand.bmp", L"FalseKnight_Stand");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/Dead.bmp", L"FalseKnight_Dead");

	m_pFrameKey = L"FalseKnight_Idle";
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
	float	fWidth = fabs(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - m_tInfo.fX);
	float	fHeight = fabs(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - m_tInfo.fY);
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	if (300 > fDiagonal)
	{
		if(!m_bTarget)
		{ 
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			CSoundMgr::Get_Instance()->PlayBGM(L"boss_bgm.wav", 1);
		}
		m_bTarget = true;
	}
	CCollisionMgr::Collision_Rect_Ex(*(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER)), *(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BLOCK)));
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bGroggy)
	{
		if (m_bJumpAttack)
			Jump_Attack();
		else if (m_bSwing)
			Swing();
		else if (m_bWave)
			Wave();
		else
			Jumping();
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CFalseKnight::Late_Update(void)
{
	if (0 == m_iHP)
	{
		m_eCurState = GROGGY;
		m_pFrameKey = L"FalseKnight_Groggy";
		m_tInfo.fCX = 0.f;
		m_tInfo.fCY = 0.f;
	}
	if (m_dwJumpTime + 400 < GetTickCount())
		m_bJump = false;
	if (m_bTarget)
	{
		if (m_dwSelectPattern + 1500 < GetTickCount() && !m_bPattern)
			SelectPattern();
	}
	Move_Frame();
	Motion_Change();
	if(m_bGroggy)
	{
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_tFrame.dwFrameTime = GetTickCount();
		}
		else
		{
			if (1 == m_tFrame.iMotion)
			{
				m_tInfo.fX -= 5;
			}
			else
			{
				m_tInfo.fX += 5;
			}
		}
	}
}

void CFalseKnight::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX-325.f) + iScrollX,
		int(m_tInfo.fY-400.f) + iScrollY,
		650,
		600,
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
			m_bLand = false;
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
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tInfo.fY += 70.f;
			if (1 == m_tFrame.iMotion)
				m_tFrame.iMotion = 0;
			else
				m_tFrame.iMotion = 1;
			m_bGroggy = true;
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
		if (1 == m_tFrame.iMotion)
			m_tInfo.fX -= m_fSpeed;
		else
			m_tInfo.fX += m_fSpeed;
		m_tInfo.fY -= m_fJumpPower;

		if (1 == m_tFrame.iFrameStart)
			m_tFrame.dwFrameTime = GetTickCount();
	}
	else if (m_tRect.bottom < fY - 3 || !bLineCol)
	{
		if (1 == m_tFrame.iMotion)
			m_tInfo.fX -= m_fSpeed;
		else
			m_tInfo.fX += m_fSpeed;
		m_tInfo.fY += m_fSpeed * 2;
		m_bPattern = false;
		m_dwSelectPattern = GetTickCount();

		if (1 == m_tFrame.iFrameStart)
			m_tFrame.dwFrameTime = GetTickCount();
	}
	else if (bLineCol)
	{
		if (!m_bLand)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"false_knight_land.wav", SOUND_EFFECT, 1);
			m_bLand = true;
		}
		m_eCurState = IDLE;
		m_pFrameKey = L"FalseKnight_Idle";
		m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
	}
}

void CFalseKnight::SelectPattern()
{
	m_iPattern = rand() % 12 + 1;
	//m_iPattern = 12;
	if (4 >= m_iPattern)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"false_knight_jump.wav", SOUND_EFFECT, 1);
		m_eCurState = JUMP;
		m_pFrameKey = L"FalseKnight_Jump";
	}
	else if (7 >= m_iPattern)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"false_knight_wave.wav", SOUND_EFFECT, 1);
		m_eCurState = WAVE;
		m_pFrameKey = L"FalseKnight_Wave";
	}
	else if (10 >= m_iPattern)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"false_knight_wave.wav", SOUND_EFFECT, 1);
		m_eCurState = WAVE;
		m_pFrameKey = L"FalseKnight_Wave";
	}
	else
	{
		CSoundMgr::Get_Instance()->PlaySound(L"false_knight_wave.wav", SOUND_EFFECT, 1);
		m_eCurState = SWING;
		m_pFrameKey = L"FalseKnight_Swing";
	}
	m_iLoop = 0;
	m_bPattern = true;
	m_dwSelectPattern = GetTickCount();
}

void CFalseKnight::Jump_Attack()
{
}

void CFalseKnight::Wave()
{
	if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
	{
		m_bLoop = true;
	}
	if (0 == m_tFrame.iFrameStart && m_bLoop)
	{
		m_eCurState = IDLE;
		m_pFrameKey = L"FalseKnight_Idle";
		m_dwSelectPattern = GetTickCount();
		m_bWave = false;
		m_bLoop = false;
		m_bPattern = false;
		m_iWave = 1;
	}
	if (1 == m_iWave && 4 == m_tFrame.iFrameStart)
	{
		--m_iWave;
		if (1 == m_tFrame.iMotion)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"false_knight_strike_ground.wav", SOUND_EFFECT, 1);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MATTACK, CAbstractFactory<CWave>::Create(m_tInfo.fX - 130.f, m_tInfo.fY + 120, DIR_LEFT));
		}
		else
		{
			CSoundMgr::Get_Instance()->PlaySound(L"false_knight_strike_ground.wav", SOUND_EFFECT, 1);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MATTACK, CAbstractFactory<CWave>::Create(m_tInfo.fX + 130.f, m_tInfo.fY + 120, DIR_RIGHT));
		}
	}
}

void CFalseKnight::Swing()
{
	if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
	{
		m_bLoop = true;
	}
	if (0 == m_tFrame.iFrameStart && m_bLoop)
	{
		++m_iLoop;
		m_bLoop = false;
	}
	if (4 == m_iLoop)
	{
		m_eCurState = IDLE;
		m_pFrameKey = L"FalseKnight_Idle";
		m_dwSelectPattern = GetTickCount();
		m_bSwing = false;
		m_bPattern = false;
	}
	if (1 == m_iSwingL && 3 == m_tFrame.iFrameStart)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"false_knight_strike_ground.wav", SOUND_EFFECT, 1);
		--m_iSwingL;
		m_iSwingR = 1;
		CObjMgr::Get_Instance()->Add_Object(OBJ_MATTACK, CAbstractFactory<CAttack>::Create(m_tInfo.fX - 170.f, m_tInfo.fY + 120));
	}
	if (1 == m_iSwingR && 8 == m_tFrame.iFrameStart)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"false_knight_strike_ground.wav", SOUND_EFFECT, 1);
		--m_iSwingR;
		m_iSwingL = 1;
		CObjMgr::Get_Instance()->Add_Object(OBJ_MATTACK, CAbstractFactory<CAttack>::Create(m_tInfo.fX + 170.f, m_tInfo.fY + 120));
	}
}

