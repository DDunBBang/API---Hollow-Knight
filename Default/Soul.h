#pragma once
#include "UI.h"
class CSoul :
	public CUI
{
public:
	CSoul();
	virtual ~CSoul();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};