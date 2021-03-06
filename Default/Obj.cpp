#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fAngle(0.f), m_fDistance(0.f), m_bLand(false),
	m_pTarget(nullptr), m_pFrameKey(L""), m_fJumpPower(0.f), m_bJump(false), m_iHP(0), m_bParry(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	m_bf.BlendOp = AC_SRC_OVER;
	m_bf.AlphaFormat = 0;
	m_bf.BlendFlags = 0;
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left = int(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = int(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = int(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = int(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwFrameTime = GetTickCount();
	}
}
