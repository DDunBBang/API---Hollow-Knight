#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr*		CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (WINCX - 6400 > m_fScrollX)
		m_fScrollX = WINCX - 6400;


	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCY - 1664 > m_fScrollY)
		m_fScrollY = WINCY - 1664;

}
