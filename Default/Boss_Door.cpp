#include "stdafx.h"
#include "Boss_Door.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CBoss_Door::CBoss_Door()
{
}


CBoss_Door::~CBoss_Door()
{
}

void CBoss_Door::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/door/boss_door.bmp", L"Boss_Door");

	m_tInfo.fCX = 170.f;
	m_tInfo.fCY = 200.f;
	m_tInfo.eSave = EDIT_BOSS_DOOR;

	m_iHP = 1;

	m_pFrameKey = L"Boss_Door";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iMotion = 0;
}

int CBoss_Door::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBoss_Door::Late_Update(void)
{
	if (0 >= m_iHP)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_BOSS);
		m_bDead = true;
	}
	Move_Frame();
}

void CBoss_Door::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	GdiTransparentBlt(hDC,
		int(m_tRect.left) + iScrollX,
		int(m_tRect.top) + iScrollY,
		170,
		200,
		hMemDC,
		m_tFrame.iFrameStart * 170,
		0,
		170,
		200,
		RGB(255, 255, 255));
}

void CBoss_Door::Release(void)
{
}
