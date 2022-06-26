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
	void		Hit(void);
	void		Offset(void);
	void		Motion_Change(void);

private:
	bool		m_bDash;
	bool		m_bHeal;
	bool		m_bHit;
	bool		m_bImu;
	bool		m_bDownAttack;
	bool		m_bUpAttack;
	bool		m_bInven;
	bool		m_bAttack;
	bool		m_bKey;

	float		m_fTime;
	float		m_fJumpHeight;

	DWORD		m_dwAttackTime;
	DWORD		m_dwDashTime;
	DWORD		m_dwHealTime;
	DWORD		m_dwHitTime;
	DWORD		m_dwImuTime;
	DWORD		m_dwDeadTime;
	DWORD		m_dwParryTime;

	STATE		m_ePreState;
	STATE		m_eCurState;
};

