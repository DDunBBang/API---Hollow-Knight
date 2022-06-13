#pragma once
#include "Scene.h"
class CEnding :
	public CScene
{
public:
	CEnding();
	virtual ~CEnding();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
};

