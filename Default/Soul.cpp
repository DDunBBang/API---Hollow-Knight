#include "stdafx.h"
#include "Soul.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CSoul::CSoul()
{
}


CSoul::~CSoul()
{
}

void CSoul::Initialize(void)
{
}

int CSoul::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CSoul::Late_Update(void)
{
}

void CSoul::Render(HDC hDC)
{
}

void CSoul::Release(void)
{
}
