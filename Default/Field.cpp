#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Field.h"


CField::CField()
{
}


CField::~CField()
{
	Release();
}

void CField::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Field.bmp", L"Field");
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

	BitBlt(hDC, 0, 0, 3900, 2000, hField, 4700, 2500, SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CField::Release(void)
{
}
