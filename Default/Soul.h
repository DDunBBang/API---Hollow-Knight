#pragma once
#include "UI.h"
class CSoul :
	public CUI
{
public:
	CSoul();
	virtual ~CSoul();

public:
	void Set_Gauge(int _iTemp) { m_iGauge += _iTemp; }
	const int* Get_Gauge() const { return &m_iGauge; }

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int m_iGauge;
};