#pragma once
#include "Obj.h"
class CAttackEffect :
	public CObj
{
public:
	CAttackEffect();
	virtual ~CAttackEffect();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

