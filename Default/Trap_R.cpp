#include "stdafx.h"
#include "Trap_R.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CTrap_R::CTrap_R()
{
}


CTrap_R::~CTrap_R()
{
}

void CTrap_R::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/trap/trap_R.bmp", L"Trap_R");
	m_pFrameKey = L"Trap_R";
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	m_tInfo.eSave = EDIT_TRAP_R;
}

int CTrap_R::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CTrap_R::Late_Update(void)
{
}

void CTrap_R::Render(HDC hDC)
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
		0,
		0,
		150,
		150,
		RGB(255, 255, 255));
}

void CTrap_R::Release(void)
{
}
