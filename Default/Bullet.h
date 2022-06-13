#pragma once
#include "Obj.h"
class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

