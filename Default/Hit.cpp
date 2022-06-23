#include "stdafx.h"
#include "Hit.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CHit::CHit()
	:m_bSound(true)
{
}


CHit::~CHit()
{
}

void CHit::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Character/Effect/DamageEffect.bmp", L"Damage");

	m_tInfo.fCX = 500.f;
	m_tInfo.fCY = 300.f;
	m_pFrameKey = L"Damage";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	if (m_eDir == DIR_LEFT)
		m_tFrame.iMotion = 1;
	else
		m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CHit::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	if (m_bSound)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"hero_damage.wav", SOUND_EFFECT, 1);
		m_bSound = false;
	}
	return OBJ_NOEVENT;
}

void CHit::Late_Update(void)
{
	if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		m_bDead = true;
	Move_Frame();
}

void CHit::Render(HDC hDC)
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
		m_tFrame.iFrameStart * 800,
		m_tFrame.iMotion * 300,
		800,
		300,
		RGB(0, 0, 0));
}

void CHit::Release(void)
{
}
