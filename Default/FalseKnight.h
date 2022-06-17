#pragma once
#include "Obj.h"
class CFalseKnight :
	public CObj
{
public:
	enum STATE {IDLE, JUMP, JUMP_ATTACK, WAVE, NUCKBACK, STATE_END };
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
	void Pattern();

private:
	STATE m_eCurState;
	STATE m_ePreState;
};

