#pragma once

#include "Obj.h"
#include "UI.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create(void)
	{
		CObj*		pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}

	static CObj*		Create(float _fX, float _fY, DIRECTION eDir = DIR_END)
	{
		CObj*		pInstance = new T;
		pInstance->Set_Pos(_fX, _fY);
		if (DIR_END != eDir)
			pInstance->Set_Dir(eDir);
		pInstance->Initialize();

		return pInstance;
	}

	static CUI*		Create_UI(void)
	{
		CUI*		pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}

	static CUI*		Create_UI(float _fX, float _fY, DIRECTION eDir = DIR_END)
	{
		CUI*		pInstance = new T;
		pInstance->Set_Pos(_fX, _fY);
		if (DIR_END != eDir)
			pInstance->Set_Dir(eDir);
		pInstance->Initialize();

		return pInstance;
	}

public:
	CAbstractFactory() {}
	~CAbstractFactory() { }
};

