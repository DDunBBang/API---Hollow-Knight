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

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }


	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Dead(void) { m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void		Set_FrameKey(TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }

	bool		Get_Dead(void) { return m_bDead; }
	const float Get_Speed(void) const { return m_fSpeed; }

	const RECT&		Get_Rect(void) const { return m_tRect; }
	const INFO&		Get_Info(void) const { return m_tInfo; }

public:
	virtual		void	Initialize(void) PURE;
	virtual		int		Update(void)	PURE;
	virtual		void	Late_Update(void) PURE;
	virtual		void	Render(HDC hDC) PURE;
	virtual		void	Release(void) PURE;

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	FRAME		m_tFrame;

	float		m_fSpeed;
	float		m_fJumpPower;
	float		m_fAngle;
	float		m_fDistance;

	bool		m_bDead;
	bool		m_bLand;
	bool		m_bJump;

	TCHAR*		m_pFrameKey;
	CObj*		m_pTarget;

	BLENDFUNCTION m_bf;
};