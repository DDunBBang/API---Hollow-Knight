#pragma once
#include "Obj.h"
class CFalseKnight :
	public CObj
{
public:
	enum STATE {IDLE, JUMP, JUMP_ATTACK, WAVE, SWING, GROGGY, STAND, DEAD, STATE_END };
public:
	CFalseKnight();
	virtual ~CFalseKnight();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

private:
	void Motion_Change();
	void Jumping();
	void SellectPattern();
	void Jump_Attack();
	void Wave();
	void Swing();

private:
	STATE	m_eCurState;
	STATE	m_ePreState;

	int		m_iPattern;

	bool	m_bPattern;

	DWORD	m_dwJumpTime;
	DWORD	m_dwPatternTime;
};

