#pragma once

#include "Include.h"

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj*		Get_Target(OBJID eID, CObj* pObj);
	list<CObj*>* Get_ObjList(int _iID) { return &m_ObjList[_iID]; }

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Delete_ID(OBJID eID);

	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

private:
	list<CObj*>	m_ObjList[OBJ_END];

public:
	static		CObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

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
	static		CObjMgr*		m_pInstance;

};
