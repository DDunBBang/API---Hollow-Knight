#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release(void)
{
}
