#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "Tile.h"
#include "ScrollMgr.h"

CTileMgr*	CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize(void)
{
	//for (int i = 0; i < TILEY; ++i)
	//{
	//	for (int j = 0; j < TILEX; ++j)
	//	{
	//		float	fX = (float)(TILECX * j) + (TILECX >> 1);
	//		float	fY = (float)(TILECY * i) + (TILECY >> 1);

	//		CObj* pTile = CAbstractFactory<CTile>::Create(fX, fY);
	//		m_vecTile.push_back(pTile);
	//	}
	//}
}

void CTileMgr::Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY());

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	for (auto& iter : m_vecTile)
	{
		iter->Render(hDC);
	}
}

void CTileMgr::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}

void CTileMgr::Picking_Tile(POINT& _pt)
{
	int	iX = _pt.x - (_pt.x%TILECX) + TILECX * 0.5;
	int	iY = _pt.y - (_pt.y%TILECY) + TILECY * 0.5;

	CObj* pTile = CAbstractFactory<CTile>::Create((float)iX, (float)iY);
	m_vecTile.push_back(pTile);
}

void CTileMgr::Save_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Edit/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}

	CloseHandle(hFile);

}

void CTileMgr::Load_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Edit/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	INFO	tInfo{};
	DWORD	dwByte = 0;

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		if (0 == dwByte)
			break;

		CObj*	pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);

		m_vecTile.push_back(pTile);
	}
	CloseHandle(hFile);


}
