#pragma once
#include "Scene.h"
class CBossStage :
	public CScene
{
public:
	CBossStage();
	virtual ~CBossStage();

public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

private:
	void Load_File();
};

