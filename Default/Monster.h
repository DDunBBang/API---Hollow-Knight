#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	enum Type { NOMAL, RARE, BOSS, END };
public:
	CMonster();
	virtual ~CMonster();

public:
	Type		Get_Type() { return m_eType; }

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

protected:
	Type m_eType;
};

