#pragma once
#include "Obj.h"
class CBlade :
	public CObj
{
public:
	CBlade();
	virtual ~CBlade();

public:
	void Set_Attack(bool _bAttack) { m_bAttack = _bAttack; }

	bool	Get_Attack() { return m_bAttack; }

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

private:
	bool		m_bAttack;
	bool		m_bSound;
};

