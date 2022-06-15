#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Field.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "Bottom.h"
#include "Wall_L.h"
#include "Wall_R.h"
#include "Top.h"
#include "Trap.h"
#include "Trap_L.h"
#include "Trap_R.h"
#include "Spear.h"
#include "TileMgr.h"


CField::CField()
{
}


CField::~CField()
{
	Release();
}

void CField::Initialize(void)
{
	CTileMgr::Get_Instance()->Load_Tile();
	Load_File();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/bg/Field.bmp", L"Field");
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
}

int CField::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CField::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CField::Render(HDC hDC)
{
	HDC hField = CBmpMgr::Get_Instance()->Find_Image(L"Field");
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, 6400, 1664, hField, 0, 0, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CField::Release(void)
{
}

void CField::Load_File()
{
	HANDLE hFile;

	// 1. ���� ����
	hFile = CreateFile(L"../Data/Field/Field.dat",	// ���� ��ο� �̸��� ����ϴ� �Ű�����
		GENERIC_READ,		// ��� ����, GENERIC_WRITE(����), GENERIC_READ(�б�)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ���ΰ�, NULL�� ���� �� �������� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ������ ����
		OPEN_EXISTING,		// ���� ���� ���, �ش� ������ ��� �۾��� ������ �ƴϸ� ���� ���� ������ ���� CREATE_ALWAYS(���� ����) : ������ ���ٸ� ����, ������ �����,  OPEN_EXISTING(�б� ����) : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ� ����, FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� �Ϲ����� ���� ����
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	// 2. ���� ����

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
		case EDIT_BOSS:
			break;
		}
	}

	CloseHandle(hFile);
}
