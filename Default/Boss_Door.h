#pragma once
#include "Obj.h"
class CBoss_Door :
	public CObj
{
public:
	CBoss_Door();
	virtual ~CBoss_Door();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

