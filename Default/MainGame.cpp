#include "stdafx.h"
#include "MainGame.h"
//#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
//#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"


CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	HDC hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	CSceneMgr::Get_Instance()->Render(hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
//	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
//	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
