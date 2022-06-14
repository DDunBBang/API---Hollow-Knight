#include "stdafx.h"
#include "Bottom.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBottom::CBottom()
{
}


CBottom::~CBottom()
{
}

void CBottom::Initialize(void)
{
	m_tInfo.fCX = 128.f;
	m_tInfo.fCY = 64.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/bottom.bmp", L"Bottom");

	m_pFrameKey = L"Bottom";
}

int CBottom::Update(void)
{

	Update_Rect();
	return 0;
}

void CBottom::Late_Update(void)
{
}

void CBottom::Render(HDC hDC)
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
		313,
		202,
		RGB(255, 255, 255));
}

void CBottom::Release(void)
{
}
