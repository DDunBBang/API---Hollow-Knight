#include "stdafx.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Monster.h"
#include "Bottom.h"
#include "Top.h"
#include "Wall_L.h"
#include "Wall_R.h"
#include "Trap.h"
#include "Trap_L.h"
#include "Trap_R.h"
#include "Spear.h"
#include "AbstractFactory.h"

CMyEdit::CMyEdit()
	:m_bTrue(false), m_etype(EDIT_END)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&rc, sizeof(RECT));
	ZeroMemory(&m_Mouse, sizeof(RECT));
	ZeroMemory(&pt, sizeof(POINT));
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/bg/Field.bmp", L"Field");
	CTileMgr::Get_Instance()->Initialize();

	for (int i = 0; i < 9; ++i)
	{
		m_tInfo.fX = 30;
		m_tInfo.fY = 50 * (i + 1);
		m_tInfo.fCX = 40;
		m_tInfo.fCY = 40;

		rc[i].left = int(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
		rc[i].right = int(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
		rc[i].top = int(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
		rc[i].bottom = int(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
	}
}

int CMyEdit::Update(void)
{
	CTileMgr::Get_Instance()->Update();

	Update_Mouse();
	Select();
	Key_Input();

	CObjMgr::Get_Instance()->Update();

	return 0;
}
void CMyEdit::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	HDC hField = CBmpMgr::Get_Instance()->Find_Image(L"Field");
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 6400, 1664, hField, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
	CTileMgr::Get_Instance()->Render(hDC);

	TCHAR szTitle[9][32];

	swprintf_s(szTitle[0], L"바닥");
	swprintf_s(szTitle[1], L"천장");
	swprintf_s(szTitle[2], L"왼벽");
	swprintf_s(szTitle[3], L"오른벽");
	swprintf_s(szTitle[4], L"가시");
	swprintf_s(szTitle[5], L"왼가시");
	swprintf_s(szTitle[6], L"오른가시");
	swprintf_s(szTitle[7], L"돌송곳");
	swprintf_s(szTitle[8], L"보스");

	if (m_etype != EDIT_END)
		DrawText(hDC, szTitle[m_etype], lstrlen(szTitle[m_etype]), &m_Mouse, DT_CENTER);
	for (int i = 0; i < 9; ++i)
	{
		Rectangle(hDC, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
		DrawText(hDC, szTitle[i], lstrlen(szTitle[i]), &rc[i], DT_CENTER);
	}

	CObjMgr::Get_Instance()->Render(hDC);

}

void CMyEdit::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
}

void CMyEdit::Select(void)
{
	RECT rcTrue{};
	if (!m_bTrue)
	{
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[0]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_BOTTOM;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[1]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_TOP;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[2]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_WALL_L;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[3]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_WALL_R;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[4]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_TRAP;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[5]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_TRAP_L;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[6]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_TRAP_R;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[7]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_SPEAR;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[8]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_BOSS;
			}
		}
	}
}

void CMyEdit::Save_File()
{
}

void CMyEdit::Update_Mouse()
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_Mouse.left = int(pt.x - 5) + iScrollX;
	m_Mouse.right = int(pt.x + 5) + iScrollX;
	m_Mouse.top = int(pt.y - 5) + iScrollY;
	m_Mouse.bottom = int(pt.y + 5) + iScrollY;
}

void CMyEdit::Key_Input(void)
{
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int	iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
	int	iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;

	if (m_bTrue)
	{
		m_Mouse.left = int(pt.x - 20) + iScrollX;
		m_Mouse.right = int(pt.x + 20) + iScrollX;
		m_Mouse.top = int(pt.y - 20) + iScrollY;
		m_Mouse.bottom = int(pt.y + 20) + iScrollY;
		switch (m_etype)
		{
		case CMyEdit::EDIT_BOTTOM:
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBottom>::Create((float)iX, (float)iY));
			break;
		case CMyEdit::EDIT_TOP:
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CTop>::Create((float)iX, (float)iY));
			break;
		case CMyEdit::EDIT_WALL_L:
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CWall_L>::Create((float)iX, (float)iY));
			break;
		case CMyEdit::EDIT_WALL_R:
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CWall_R>::Create((float)iX, (float)iY));
			break;
		case CMyEdit::EDIT_TRAP:
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CTrap>::Create((float)iX, (float)iY));
			break;
		case CMyEdit::EDIT_TRAP_L:
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CTrap_L>::Create((float)iX, (float)iY));
			break;
		case CMyEdit::EDIT_TRAP_R:
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CTrap_R>::Create((float)iX, (float)iY));
			break;
		case CMyEdit::EDIT_SPEAR:
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CSpear>::Create((float)iX, (float)iY));
			break;
		case CMyEdit::EDIT_BOSS:
			break;
		case CMyEdit::EDIT_END:
			break;
		default:
			break;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		CTileMgr::Get_Instance()->Picking_Tile(pt);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		m_etype = EDIT_END;
		m_bTrue = false;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CTileMgr::Get_Instance()->Save_Tile();
		Save_File();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		CTileMgr::Get_Instance()->Load_Tile();
	}

}
