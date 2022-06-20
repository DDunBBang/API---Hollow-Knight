#include "stdafx.h"
#include "Wave.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CWave::CWave()
	:m_dwDeleteTime(GetTickCount())
{
}


CWave::~CWave()
{
}

void CWave::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/FalseKnight/WaveEffect.bmp", L"WaveEffect");

	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 150.f;
	m_fSpeed = 5.f;

	if (DIR_LEFT == m_eDir)
		m_tFrame.iMotion = 1;
	else
		m_tFrame.iMotion = 0;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
	m_pFrameKey = L"WaveEffect";
}

int CWave::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (DIR_LEFT == m_eDir)
		m_tInfo.fX -= m_fSpeed;
	else
		m_tInfo.fX += m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CWave::Late_Update(void)
{
	Move_Frame();
	m_fSpeed += 0.25f;
	m_tInfo.fCX += 4.f;
	if (4 == m_tFrame.iFrameStart)
		m_tFrame.dwFrameTime = GetTickCount();

	if (m_dwDeleteTime + 1500 < GetTickCount())
		m_bDead = true;
}

void CWave::Render(HDC hDC)
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
		m_tFrame.iFrameStart * 520,
		m_tFrame.iMotion * 300,
		520,
		300,
		RGB(47, 46, 39));
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CWave::Release(void)
{
}
