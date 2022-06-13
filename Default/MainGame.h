#pragma once

#include "Define.h"
#include "Player.h"
#include "Bullet.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

 public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_hDC;
};