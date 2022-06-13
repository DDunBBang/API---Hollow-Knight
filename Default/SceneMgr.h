#pragma once
#include "Scene.h"

class CSceneMgr
{
public:
	enum SCENEID {MENU, FIELD, ENDING, SCENE_END};

private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr* m_pInstance;
	CScene* m_pScene;

	SCENEID m_ePreScene;
	SCENEID m_eCurScene;

};

