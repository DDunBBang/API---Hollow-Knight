#pragma once
#include "Obj.h"

class CWall_R :
	public CObj
{
public:
	CWall_R();
	virtual ~CWall_R();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

