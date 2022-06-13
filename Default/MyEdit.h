#pragma once
#include "Scene.h"
class CMyEdit :
	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
};

