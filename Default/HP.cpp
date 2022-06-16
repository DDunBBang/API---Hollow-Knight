#include "stdafx.h"
#include "HP.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

CHP::CHP()
	:m_bDestroy(false), m_eCurState(HP_END), m_ePreState(HP_END)
{
}


CHP::~CHP()
{
}

void CHP::Initialize(void)
{
	//m_tInfo.fX = 165.f;
	//m_tInfo.fY = 12.f;
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 130.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HP_DESTROY.bmp", L"Destroy");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HP_INTRO.bmp", L"Creat");

	m_pFrameKey = L"Creat";
	
	m_tFrame.dwFrameSpeed = 40;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CHP::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	if (m_bDestroy)
	{
		m_eCurState = HP_DESTROY;
	}
	else
	{
		m_eCurState = HP_CREAT;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CHP::Late_Update(void)
{
	Motion_Change();
	if ((4 >= m_tFrame.iFrameStart && !lstrcmp(m_pFrameKey, L"Creat"))
		|| (5 >= m_tFrame.iFrameStart && !lstrcmp(m_pFrameKey, L"Destroy")))
		Move_Frame();
}

void CHP::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX),
		int(m_tInfo.fY),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		0,
		m_tFrame.iFrameStart * 256,
		128,
		256,
		RGB(255, 0, 0));
}

void CHP::Release(void)
{
}

void CHP::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CHP::HP_CREAT:
			m_pFrameKey = L"Creat";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CHP::HP_DESTROY:
			m_pFrameKey = L"Destroy";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}