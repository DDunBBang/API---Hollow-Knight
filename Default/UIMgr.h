#pragma once

#include "Include.h"

class CUI;
class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	list<CUI*>* Get_UIList(int _iID) { return &m_UIList[_iID]; }
	vector<CUI*>* Get_HP() { return &m_vecHP; }

public:
	void		Add_UI(UIID eID, CUI* pUI);
	void		Delete_ID(UIID eID);

	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);	

public:
	static		CUIMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CUIMgr;

		return m_pInstance;
	}

	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static		CUIMgr*	m_pInstance;
	list<CUI*>	m_UIList[UI_END];

	vector<CUI*> m_vecHP;
};

