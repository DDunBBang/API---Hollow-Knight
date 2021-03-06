#pragma once
#include "Monster.h"
class CWarriorHusk :
	public CMonster
{
public:
	enum STATE { IDLE, ATTACK, DEAD, END };

public:
	CWarriorHusk();
	virtual ~CWarriorHusk();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

private:
	void	Motion_Change();
	void	Move();
	void	Attack();
	void	Dead();

private:
	bool	m_bTarget;
	bool	m_bAttack;

	STATE	m_eCurState;
	STATE	m_ePreState;

	DWORD	m_dwMoveTime;
	DWORD	m_dwAttackTime;
	DWORD	m_dwCoolTime;
	DWORD	m_dwDeadTime;
};

