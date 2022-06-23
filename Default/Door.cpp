#include "stdafx.h"
#include "Door.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CDoor::CDoor()
{
}


CDoor::~CDoor()
{
}

void CDoor::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/door/door.bmp", L"Door");
	
	m_tInfo.fCX = 300.f;
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
}

void CDoor::Render(HDC hDC)
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
		m_tFrame.iMotion * 553,
		962,
		553,
		962,
		RGB(255, 255, 255));
}

void CDoor::Release(void)
{
}
