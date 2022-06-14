#pragma once
#include "Obj.h"
class CSpear :
	public CObj
{
public:
	CSpear();
	virtual ~CSpear();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bHit;
};

