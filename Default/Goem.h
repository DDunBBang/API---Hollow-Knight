#pragma once
#include "Monster.h"
class CGoem :
	public CMonster
{
public:
	enum STATE {IDLE, UP, DOWN, END};

public:
	CGoem();
	virtual ~CGoem();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

private:
	void	Motion_Change();

private:
	bool	m_bStand;

	STATE	m_eCurState;
	STATE	m_ePreState;

	DWORD	m_dwChange;
};

