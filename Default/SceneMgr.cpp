#include "stdafx.h"
#include "SceneMgr.h"
#include "MyMenu.h"
#include "Field.h"
#include "Ending.h"
#include "MyEdit.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene(SC_END), m_eCurScene(SC_MENU)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene)
{
	m_eCurScene = eScene;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);		

		switch (m_eCurScene)
		{
		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_FIELD:
			m_pScene = new CField;
			break;

		case SC_ENDING:
			m_pScene = new CEnding;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;

		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete<CScene*>(m_pScene);
}