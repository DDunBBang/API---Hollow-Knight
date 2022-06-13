#pragma once

#include "Obj.h"

class CPlayer :	public CObj
{
public:
	enum STATE { IDLE, WALK, DASH, JUMP, DOWN, ATTACK, HIT, DEAD, FIRE, CHARGE, END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		Jumping(void);
	void		Offset(void);
	void		Motion_Change(void);

private:
	bool				m_bJump;
	bool				m_bLand;

	float				m_fJumpPower;
	float				m_fTime;
	DWORD				m_dwJumpTime;
	DWORD				m_dwAttackTime;

	STATE				m_ePreState;
	STATE				m_eCurState;
};

