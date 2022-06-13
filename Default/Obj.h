#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY) 
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

public:
	virtual		void	Initialize(void)	PURE;
	virtual		void	Update(void)		PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	float		m_fSpeed;
};

