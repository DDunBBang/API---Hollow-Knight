#include "stdafx.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};


	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}


}

void CCollisionMgr::Collision_Rect_Ex(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fWidth = 0.f;
			float	fHeight = 0.f;

			if (Check_Rect(Dest, Sour, &fWidth, &fHeight))
			{
				// ���� �浹
				if (fWidth > fHeight)
				{
					// �� �浹
					if (Dest->Get_Info().fY < Sour->Get_Info().fY)
					{
						Dest->Set_PosY(-fHeight);
					}
					// �� �浹
					else
					{
						Dest->Set_PosY(fHeight);
					}
				}

				// �¿� �浹
				else
				{
					// �� �浹
					if (Dest->Get_Info().fX < Sour->Get_Info().fX)
					{
						Dest->Set_PosX(-fWidth);
					}
					// �� �浹
					else
					{
						Dest->Set_PosX(fWidth);
					}
				}

			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	// abs : ���밪�� ������ִ� �Լ�
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : ��Ʈ�� �����ִ� �Լ�
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;	// �浹�� �� ���
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float* _pX, float* _pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fRadiusX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}
