#pragma once
#include "Obj.h"
class CHit :
	public CObj
{
public:
	CHit();
	virtual ~CHit();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

