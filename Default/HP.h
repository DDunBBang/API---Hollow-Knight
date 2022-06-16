#pragma once
#include "UI.h"

class CHP :
	public CUI
{
public:
	CHP();
	virtual ~CHP();

public:
	enum STATE {HP_CREAT, HP_DESTROY, HP_END};

public:
	void Set_Destroy(bool _bDestroy) { m_bDestroy = _bDestroy; }
	bool Get_Destroy() { return m_bDestroy; }

	void Motion_Change();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bDestroy;

	STATE m_eCurState;
	STATE m_ePreState;
};

