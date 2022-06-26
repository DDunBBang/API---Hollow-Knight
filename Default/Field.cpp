#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
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
#include "Soul_Base.h"
#include "Soul.h"
#include "HP.h"
#include "FalseKnight.h"
#include "Inven.h"
#include "Plat.h"
#include "HornHusk.h"
#include "Leapinghusk.h"
#include "WarriorHusk.h"
#include "SoundMgr.h"
#include "Door.h"
#include "Boss_Door.h"


CField::CField()
{
}


CField::~CField()
{
	Release();
}

void CField::Initialize(void)
{
	CObjMgr::Get_Instance()->Release();

	CSoundMgr::Get_Instance()->PlayBGM(L"field_bgm.wav", 1);
	Load_File();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/bg/Field.bmp", L"Field");

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CScrollMgr::Get_Instance()->Reset_Scroll((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX), -(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CHornHusk>::Create(900.f, 1500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CHornHusk>::Create(900.f, 50.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CHornHusk>::Create(900.f, 900.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CHornHusk>::Create(3500.f, 1500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CLeapinghusk>::Create(400.f, 900.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CLeapinghusk>::Create(4500.f, 900.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CLeapinghusk>::Create(4000.f, 1500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CWarriorHusk>::Create(3000.f, 1500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CWarriorHusk>::Create(5500.f, 900.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CWarriorHusk>::Create(6000.f, 450.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CWarriorHusk>::Create(5800.f, 450.f));
	CUIMgr::Get_Instance()->Add_UI(UI_SOUL_BASE, CAbstractFactory<CSoul_Base>::Create_UI());
	CUIMgr::Get_Instance()->Add_UI(UI_SOUL, CAbstractFactory<CSoul>::Create_UI());

	for (size_t i = 0; i < 5; ++i)
	{
		CUIMgr::Get_Instance()->Get_HP()->push_back(CAbstractFactory<CHP>::Create_UI(165.f + (i * 50), 15.f));
	}
}

int CField::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
	return 0;
}

void CField::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();
}

void CField::Render(HDC hDC)
{
	HDC hField = CBmpMgr::Get_Instance()->Find_Image(L"Field");
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int iCullCX = iMoveX + WINCX + 2;
	int iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, iCullCX, iCullCY, hField, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
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
		case EDIT_PLAT:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CPlat>::Create(tInfo.fX, tInfo.fY));
			break;
		case EDIT_DOOR:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BROKEN, CAbstractFactory<CDoor>::Create(tInfo.fX, tInfo.fY));
			break;
		}
	}

	CloseHandle(hFile);
}
