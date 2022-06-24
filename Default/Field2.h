#pragma once
#include "Scene.h"
class CField2 :
	public CScene
{
public:
	CField2();
	virtual ~CField2();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

private:
	void Load_File();
};

