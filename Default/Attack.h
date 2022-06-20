#pragma once
#include "Obj.h"
class CAttack :
	public CObj
{
public:
	CAttack();
	virtual ~CAttack();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

private:
	DWORD	m_dwDeleteTime;
};

