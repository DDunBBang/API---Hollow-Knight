#pragma once
#include "Obj.h"
class CTrap_R :
	public CObj
{
public:
	CTrap_R();
	virtual ~CTrap_R();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

