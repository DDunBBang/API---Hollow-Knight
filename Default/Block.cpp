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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/block.bmp", L"Block");

	m_pFrameKey = L"Block";
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
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY),
		hMemDC,
		m_tFrame.iMotion * 256,
		m_tFrame.iFrameStart * 128,
		256,
		128,
		RGB(255, 0, 0));
}

void CBlock::Release(void)
{
}
