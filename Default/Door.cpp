#include "stdafx.h"
#include "Door.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CDoor::CDoor()
{
}


CDoor::~CDoor()
{
}

void CDoor::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/door/door.bmp", L"Door");
	
	m_tInfo.fCX = 160.f;
	m_tInfo.fCY = 650.f;
	m_tInfo.eSave = EDIT_DOOR;

	m_pFrameKey = L"Door";
	m_tFrame.iMotion = 0;

	m_iHP = 9;
}

int CDoor::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CDoor::Late_Update(void)
{
	if (6 >= m_iHP && 4 <= m_iHP)
	{
		m_tFrame.iMotion = 1;
	}
	else if (3 >= m_iHP && 1 <= m_iHP)
	{
		m_tFrame.iMotion = 2;
	}
	else if (0 >= m_iHP)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_FIELD2);
		m_bDead = true;
	}
}

void CDoor::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	GdiTransparentBlt(hDC,
		int(m_tInfo.fX - 150.f) + iScrollX,
		int(m_tInfo.fY - 325.f) + iScrollY,
		300,
		650,
		hMemDC,
		m_tFrame.iMotion * 553,
		0,
		553,
		962,
		RGB(255, 255, 255));
}

void CDoor::Release(void)
{
}
