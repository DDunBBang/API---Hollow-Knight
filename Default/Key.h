#pragma once
#include "Obj.h"
class CKey :
	public CObj
{
public:
	CKey();
	virtual ~CKey();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
};

