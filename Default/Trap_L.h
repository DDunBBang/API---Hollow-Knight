#pragma once
#include "Obj.h"
class CTrap_L :
	public CObj
{
public:
	CTrap_L();
	virtual ~CTrap_L();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

