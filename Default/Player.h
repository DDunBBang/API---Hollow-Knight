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
	void Set_Land(bool _bLand) { m_bLand = _bLand; }
	void Set_Jump(bool _bJump) { m_bJump = _bJump; }

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		Jumping(void);
	void		Dash(void);
	void		Heal(void);
	void		Offset(void);
	void		Motion_Change(void);

private:
	bool		m_bDash;
	bool		m_bHeal;

	float		m_fTime;
	DWORD		m_dwJumpTime;
	DWORD		m_dwAttackTime;
	DWORD		m_dwDashTime;
	DWORD		m_dwHealTime;

	STATE		m_ePreState;
	STATE		m_eCurState;
};

