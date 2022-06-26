#pragma once
#include "Monster.h"
class CFly :
	public CMonster
{
public:
	enum STATE {IDLE, DEAD, END};

public:
	CFly();
	virtual ~CFly();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

private:
	void	Motion_Change();

private:
	STATE	m_eCurState;
	STATE	m_ePreState;

	DWORD	m_dwDead;
};

