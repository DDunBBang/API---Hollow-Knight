#pragma once
#include "UI.h"
class CInven :
	public CUI
{
public:
	CInven();
	virtual ~CInven();

public:
	void Set_On(bool _bOn) { m_bOn = _bOn; }

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool	m_bOn;

	vector<CUI*> m_vecInven[4];
};

