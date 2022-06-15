#pragma once
#include "UI.h"
class CSoul_Base :
	public CUI
{
public:
	CSoul_Base();
	virtual ~CSoul_Base();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

