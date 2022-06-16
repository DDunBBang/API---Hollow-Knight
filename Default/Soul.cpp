#include "stdafx.h"
#include "Soul.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CSoul::CSoul()
	: m_iGauge(0)
{
}


CSoul::~CSoul()
{
}

void CSoul::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Gauge/Soul.bmp", L"Soul");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Gauge/Soul_Full.bmp", L"Soul_Full");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Gauge/Soul_Empty.bmp", L"Soul_Empty");

	m_tInfo.fCX = 90.f;
	m_tInfo.fCY = 90.f;

	m_tInfo.fX = 68.f;
	m_tInfo.fY = 60.f;

	m_pFrameKey = L"Soul_Empty";
	m_tFrame.iFrameStart = 0;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CSoul::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (0 >= m_iGauge)
	{
		m_iGauge = 0;
		m_pFrameKey = L"Soul_Empty";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
	}
	else if (9 <= m_iGauge)
	{
		m_iGauge = 9;
		m_pFrameKey = L"Soul_Full";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
	}
	else
	{
		m_pFrameKey = L"Soul";
		m_tFrame.iFrameEnd = 3;
		m_tFrame.dwFrameSpeed = 120;
		m_tFrame.iMotion = m_iGauge - 1;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CSoul::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		++m_iGauge;
	else if (CKeyMgr::Get_Instance()->Key_Down('W'))
		--m_iGauge;

	Move_Frame();
}

void CSoul::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX),
		int(m_tInfo.fY),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		m_tFrame.iMotion * 120,
		m_tFrame.iFrameStart * 120,
		120,
		120,
		RGB(255, 0, 0));
}

void CSoul::Release(void)
{
}
