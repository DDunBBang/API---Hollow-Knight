#include "stdafx.h"
#include "Inven.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

CInven::CInven()
	: m_bOn(false)
{
}


CInven::~CInven()
{
}

void CInven::Initialize(void)
{
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = WINCY >> 1;

	m_bf.SourceConstantAlpha = 240;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inven/Inven_Base.bmp", L"Base");
	m_pFrameKey = L"Base";
}

int CInven::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CInven::Late_Update(void)
{
}

void CInven::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (m_bOn)
	{
		//BitBlt(hDC, 0, 0, m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0, SRCCOPY);
		GdiAlphaBlend(hDC,
			0,
			0,
			WINCX,
			WINCY,
			hMemDC,
			0,
			0,
			960,
			720,
			m_bf);
	}
	Rectangle(hMemDC, 100, 100, 100, 100);
}

void CInven::Release(void)
{
}
