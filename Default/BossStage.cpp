#include "stdafx.h"
#include "BossStage.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
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
#include "Boss_Door.h"
#include "Door.h"

CBossStage::CBossStage()
{
}


CBossStage::~CBossStage()
{
	Release();
}

void CBossStage::Initialize(void)
{
	CSoundMgr::Get_Instance()->PlayBGM(L"boss_bgm.wav", 1);
	CObjMgr::Get_Instance()->Release();
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFalseKnight>::Create());
	CScrollMgr::Get_Instance()->Reset_Scroll(0.f, -1400.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	//CUIMgr::Get_Instance()->Add_UI(UI_SOUL_BASE, CAbstractFactory<CSoul_Base>::Create_UI());
	//CUIMgr::Get_Instance()->Add_UI(UI_SOUL, CAbstractFactory<CSoul>::Create_UI());
	//for (size_t i = 0; i < 5; ++i)
	//{
	//	CUIMgr::Get_Instance()->Get_HP()->push_back(CAbstractFactory<CHP>::Create_UI(165.f + (i * 50), 15.f));
	//}
	Load_File();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/bg/Field.bmp", L"Field");
}

int CBossStage::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
	return 0;
}

void CBossStage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();
}

void CBossStage::Render(HDC hDC)
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

void CBossStage::Release(void)
{
}

void CBossStage::Load_File()
{
	HANDLE hFile;

	// 1. 파일 개방
	hFile = CreateFile(L"../Data/Field/Boss.dat",	// 파일 경로와 이름을 명시하는 매개변수
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
		}
	}

	CloseHandle(hFile);
}
