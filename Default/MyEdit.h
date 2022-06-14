#pragma once
#include "Scene.h"
class CMyEdit :
	public CScene
{
public:
	enum EDIT {EDIT_BOTTOM, EDIT_TOP, EDIT_WALL_L, EDIT_WALL_R, EDIT_TRAP, EDIT_TRAP_L, EDIT_TRAP_R, EDIT_SPEAR, EDIT_BOSS, EDIT_END};
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Key_Input(void);
	void	Select(void);
	void	Save_File();
	void    Update_Mouse();

private:
	INFO m_tInfo;
	RECT rc[15];
	RECT m_Mouse;
	POINT pt;
	bool m_bTrue;
	EDIT m_etype;

};

