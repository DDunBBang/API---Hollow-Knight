#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 300.f, 100.f, 100.f };
	m_fSpeed = 10.f;
}

void CPlayer::Update(void)
{
	Key_Input();
	Update_Rect();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, 
		m_tRect.left, 
		m_tRect.top, 
		m_tRect.right, 
		m_tRect.bottom);
}

void CPlayer::Release(void)
{	
}

void CPlayer::Key_Input(void)
{
	// GetKeyState()
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;
}