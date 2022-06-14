#pragma once
#include "Obj.h"
class CBlade :
	public CObj
{
public:
	CBlade();
	virtual ~CBlade();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
};

