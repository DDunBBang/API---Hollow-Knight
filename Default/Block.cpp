#include "stdafx.h"
#include "Block.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Tile.bmp", L"Tile");

	m_pFrameKey = L"Tile";
}

int CBlock::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlock::Late_Update(void)
{
}

void CBlock::Render(HDC hDC)
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
		100,
		100,
		RGB(255, 255, 255));
}

void CBlock::Release(void)
{
}
