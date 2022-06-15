#pragma once
#include "Obj.h"
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static int	Collision_Rect_Ex(list<CObj*> _Dest, list<CObj*> _Sour);

	static bool Collision_Line(CObj * _pObj, list<CObj*>* _Sour, float * _pY);

	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);
	static void Collision_Erase(RECT _Dest, list<CObj*> _Sour);
	static bool Check_Sphere(CObj* pDest, CObj* pSour);
	static bool Check_Rect(CObj* pDest, CObj* pSour, float* _pX, float* _pY);
};

