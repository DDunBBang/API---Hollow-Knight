#include "stdafx.h"
#include "Wall_L.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CWall_L::CWall_L()
{
}


CWall_L::~CWall_L()
{
}

void CWall_L::Initialize(void)
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 128.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/wall_L.bmp", L"Wall_L");

	m_pFrameKey = L"Wall_L";
}

int CWall_L::Update(void)
{
	Update_Rect();
	return 0;
}

void CWall_L::Late_Update(void)
{
}

void CWall_L::Render(HDC hDC)
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
		202,
		313,
		RGB(255, 255, 255));
}

void CWall_L::Release(void)
{
}
