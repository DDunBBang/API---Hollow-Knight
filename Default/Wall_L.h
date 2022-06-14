#pragma once
#include "Obj.h"
class CWall_L :
	public CObj
{
public:
	CWall_L();
	virtual ~CWall_L();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

