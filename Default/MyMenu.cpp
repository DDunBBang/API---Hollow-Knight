#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CSoundMgr::Get_Instance()->PlayBGM(L"menu_bgm.wav", 1);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");
}

int CMyMenu::Update(void)
{
	return 0;
}

void CMyMenu::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_FIELD);
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);
		return;
	}
}

void CMyMenu::Render(HDC hDC)
{
	HDC hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMenuDC, 0, 0, SRCCOPY);
}

void CMyMenu::Release(void)
{
}
