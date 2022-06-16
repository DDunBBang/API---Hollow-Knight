#include "stdafx.h"
#include "UIMgr.h"
#include "UI.h"
#include "KeyMgr.h"
#include "HP.h"

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
	for (auto& iter : m_vecHP)
	{
		iter->Update();
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
	for (auto& iter : m_vecHP)
	{
		iter->Late_Update();
	}
	if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		for (int i = 4; i >= 0; --i)
		{
			if (!dynamic_cast<CHP*>(m_vecHP[i])->Get_Destroy())
			{
				dynamic_cast<CHP*>(m_vecHP[i])->Set_Destroy(true);
				break;
			}

		}
	}
	/*if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		for (int i = 0; i < 5; ++i)
		{
			if (dynamic_cast<CHP*>(m_vecHP[i])->Get_Destroy())
			{
				dynamic_cast<CHP*>(m_vecHP[i])->Set_Destroy(false);
				break;
			}
		}
	}*/
}

void CUIMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UIList[i])
			iter->Render(hDC);
	}

	for (auto& iter : m_vecHP)
	{
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
	for_each(m_vecHP.begin(), m_vecHP.end(), CDeleteObj());
	m_vecHP.clear();
}
