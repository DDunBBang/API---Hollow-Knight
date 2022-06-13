#pragma once
#include "Obj.h"
class CBlock :
	public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
};

