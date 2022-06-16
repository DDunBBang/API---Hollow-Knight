#include "stdafx.h"
#include "Soul_Base.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CSoul_Base::CSoul_Base()
{
}


CSoul_Base::~CSoul_Base()
{
}

void CSoul_Base::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Soul_Base.bmp", L"Soul_Base");
	m_pFrameKey = L"Soul_Base";
	
	m_tInfo.fX = 50.f;
	m_tInfo.fY = 30.f;
	m_tInfo.fCX = 210.f;
	m_tInfo.fCY = 130.f;
}

int CSoul_Base::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CSoul_Base::Late_Update(void)
{
}

void CSoul_Base::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX),
		int(m_tInfo.fY ),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		0,
		0,
		116,
		76,
		RGB(255, 0, 0));
}

void CSoul_Base::Release(void)
{
}
