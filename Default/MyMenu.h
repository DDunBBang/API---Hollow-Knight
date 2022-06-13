#pragma once
#include "Scene.h"
class CMyMenu :
	public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
};

