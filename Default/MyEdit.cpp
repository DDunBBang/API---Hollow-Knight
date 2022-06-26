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
#include "CollisionMgr.h"
#include "Plat.h"
#include "Door.h"
#include "Fly.h"
#include "Boss_Door.h"

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

	for (int i = 0; i < 12; ++i)
	{
		m_tInfo.fX = 30.f;
		m_tInfo.fY = float(50 * (i + 1));
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 40.f;

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

	CObjMgr::Get_Instance()->Render(hDC);

	TCHAR szTitle[12][32];

	swprintf_s(szTitle[0], L"바닥");
	swprintf_s(szTitle[1], L"천장");
	swprintf_s(szTitle[2], L"왼벽");
	swprintf_s(szTitle[3], L"오른벽");
	swprintf_s(szTitle[4], L"가시");
	swprintf_s(szTitle[5], L"왼가시");
	swprintf_s(szTitle[6], L"오른가시");
	swprintf_s(szTitle[7], L"돌송곳");
	swprintf_s(szTitle[8], L"플랫");
	swprintf_s(szTitle[9], L"돌문");
	swprintf_s(szTitle[10], L"보스문");
	swprintf_s(szTitle[11], L"파리");

	if (m_etype != EDIT_END)
		DrawText(hDC, szTitle[m_etype], lstrlen(szTitle[m_etype]), &m_Mouse, DT_CENTER);
	for (int i = 0; i < 12; ++i)
	{
		Rectangle(hDC, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
		DrawText(hDC, szTitle[i], lstrlen(szTitle[i]), &rc[i], DT_CENTER);
	}

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
				m_etype = EDIT_PLAT;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[9]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_DOOR;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[10]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_FLY;
			}
		}
		if (IntersectRect(&rcTrue, &m_Mouse, &rc[11]))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
			{
				m_bTrue = true;
				m_etype = EDIT_BOSS_DOOR;
			}
		}
	}
}

void CMyEdit::Save_File()
{
	HANDLE	hFile = CreateFile(L"../Data/Edit/Editer.dat",	// 파일 경로와 이름을 명시하는 매개변수
		GENERIC_WRITE,		// 모드 지정, GENERIC_WRITE(쓰기), GENERIC_READ(읽기)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈할 때 허용을 할 것인가, NULL로 지정 시 공유하지 않음
		NULL,				// 보안 속성, NULL인 경우 기본 값으로 설정
		CREATE_ALWAYS,		// 파일 생성 방식, 해당 파일을 열어서 작업할 것인지 아니면 새로 만들 것인지 설정 CREATE_ALWAYS(쓰기 전용) : 파일이 없다면 생성, 있으면 덮어쓰기,  OPEN_EXISTING(읽기 전용) : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL, // 파일 속성 지정, FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 일반적인 파일 생성
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 우린 안 쓰니 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save File", L"Error", MB_OK);
		return;
	}

	DWORD dwByte = 0;
	for (size_t i=0; i < OBJ_END; ++i)
	{
		for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(i)))
		{
			WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		}
	}

	CloseHandle(hFile);
}

void CMyEdit::Load_File()
{
	HANDLE hFile;

	// 1. 파일 개방
	hFile = CreateFile(L"../Data/Edit/Editer.dat",	// 파일 경로와 이름을 명시하는 매개변수
		GENERIC_READ,		// 모드 지정, GENERIC_WRITE(쓰기), GENERIC_READ(읽기)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈할 때 허용을 할 것인가, NULL로 지정 시 공유하지 않음
		NULL,				// 보안 속성, NULL인 경우 기본 값으로 설정
		OPEN_EXISTING,		// 파일 생성 방식, 해당 파일을 열어서 작업할 것인지 아니면 새로 만들 것인지 설정 CREATE_ALWAYS(쓰기 전용) : 파일이 없다면 생성, 있으면 덮어쓰기,  OPEN_EXISTING(읽기 전용) : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL, // 파일 속성 지정, FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 일반적인 파일 생성
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	// 2. 파일 쓰기

	DWORD	dwByte = 0;

	INFO tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		switch (tInfo.eSave)
		{
		case EDIT_BOTTOM:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBottom>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_TOP:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CTop>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_WALL_L:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CWall_L>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_WALL_R:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CWall_R>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_TRAP:
			CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CTrap>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_TRAP_L:
			CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CTrap_L>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_TRAP_R:
			CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CTrap_R>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_SPEAR:
			CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CSpear>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_PLAT:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CPlat>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_DOOR:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BROKEN, CAbstractFactory<CDoor>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_FLY:
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFly>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_BOSS_DOOR:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BROKEN, CAbstractFactory<CBoss_Door>::Create(tInfo.fX, tInfo.fY));
			break;
		}
	}

	CloseHandle(hFile);
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

	if (m_bTrue)
	{
		m_Mouse.left = int(pt.x - 20) + iScrollX;
		m_Mouse.right = int(pt.x + 20) + iScrollX;
		m_Mouse.top = int(pt.y - 20) + iScrollY;
		m_Mouse.bottom = int(pt.y + 20) + iScrollY;
		int iX;
		int iY;
		switch (m_etype)
		{
		case EDIT_BOTTOM:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBottom>::Create((float)iX, (float)iY));
			break;
		case EDIT_TOP:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CTop>::Create((float)iX, (float)iY));
			break;
		case EDIT_WALL_L:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CWall_L>::Create((float)iX, (float)iY));
			break;
		case EDIT_WALL_R:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CWall_R>::Create((float)iX, (float)iY));
			break;
		case EDIT_TRAP:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CTrap>::Create((float)iX, (float)iY));
			break;
		case EDIT_TRAP_L:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CTrap_L>::Create((float)iX, (float)iY));
			break;
		case EDIT_TRAP_R:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CTrap_R>::Create((float)iX, (float)iY));
			break;
		case EDIT_SPEAR:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CSpear>::Create((float)iX, (float)iY));
			break;
		case EDIT_PLAT:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CPlat>::Create((float)iX, (float)iY));
			break;
		case EDIT_DOOR:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BROKEN, CAbstractFactory<CDoor>::Create((float)iX, (float)iY));
			break;
		case EDIT_FLY:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFly>::Create((float)iX, (float)iY));
			break;
		case EDIT_BOSS_DOOR:
			iX = pt.x - (pt.x%TILECX) + TILECX * 0.5;
			iY = pt.y - (pt.y%TILECY) + TILECY * 0.5;
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				CObjMgr::Get_Instance()->Add_Object(OBJ_BROKEN, CAbstractFactory<CBoss_Door>::Create((float)iX, (float)iY));
			break;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(15.f);
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-15.f);
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(15.f);
	}


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-15.f);
	}

	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		CTileMgr::Get_Instance()->Picking_Tile(pt);
	}*/

	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		m_etype = EDIT_END;
		m_bTrue = false;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		for (size_t i = 0; i < OBJ_END; ++i)
		{
			CCollisionMgr::Collision_Erase(m_Mouse, *(CObjMgr::Get_Instance()->Get_ObjList(i)));
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CTileMgr::Get_Instance()->Save_Tile();
		Save_File();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		CTileMgr::Get_Instance()->Load_Tile();
		Load_File();
	}

}
