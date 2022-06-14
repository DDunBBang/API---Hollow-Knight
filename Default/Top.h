#pragma once
#include "Obj.h"
class CTop :
	public CObj
{
public:
	CTop();
	virtual ~CTop();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

