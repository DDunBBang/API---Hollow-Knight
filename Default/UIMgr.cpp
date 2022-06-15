#include "stdafx.h"
#include "UIMgr.h"
#include "UI.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}


CUIMgr::~CUIMgr()
{
}

void CUIMgr::Add_UI(UIID eID, CUI * pUI)
{
	if (eID >= UI_END || nullptr == pUI)
		return;

	m_UIList[eID].push_back(pUI);
}

void CUIMgr::Delete_ID(UIID eID)
{
	for (auto& iter : m_UIList[eID])
		Safe_Delete(iter);

	m_UIList[eID].clear();
}

int CUIMgr::Update(void)
{
	int	iEvent = 0;
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_UIList[i].begin();
			iter != m_UIList[i].end();)
		{
			iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CUI*>(*iter);
				iter = m_UIList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return iEvent;
}

void CUIMgr::Late_Update(void)
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UIList[i])
		{
			iter->Late_Update();
			if (m_UIList[i].empty())
				break;
		}
	}
}

void CUIMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UIList[i])
			iter->Render(hDC);
	}
}

void CUIMgr::Release(void)
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UIList[i])
			Safe_Delete<CUI*>(iter);

		m_UIList[i].clear();
	}
}
