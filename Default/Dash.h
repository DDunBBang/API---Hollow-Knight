#pragma once
#include "Obj.h"
class CDash :
	public CObj
{
public:
	CDash();
	virtual ~CDash();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

