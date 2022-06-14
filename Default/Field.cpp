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
#include "Block.h"
#include "Bottom.h"
#include "Wall_L.h"
#include "Wall_R.h"
#include "Top.h"


CField::CField()
{
}


CField::~CField()
{
	Release();
}

void CField::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/bg/Field.bmp", L"Field");
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(400.f, 650.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBottom>::Create(464.f, 650.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CTop>::Create(528.f, 650.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CWall_L>::Create(592.f, 650.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CWall_R>::Create(656.f, 650.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(729.f, 650.f));
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
