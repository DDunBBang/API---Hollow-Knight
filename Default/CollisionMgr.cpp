#include "stdafx.h"
#include "CollisionMgr.h"
#include "Monster.h"
#include "SoundMgr.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};


	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				return true;
			}
		}
	}
	return false;

}

bool CCollisionMgr::Collision_Broken(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};


	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Sour->Set_HP(1);
				return true;
			}
		}
	}
	return false;

}

int CCollisionMgr::Collision_Rect_Ex(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fWidth = 0.f;
			float	fHeight = 0.f;

			if (Check_Rect(Dest, Sour, &fWidth, &fHeight))
			{
				// 상하 충돌
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (Dest->Get_Info().fY < Sour->Get_Info().fY)
					{
						//Dest->Set_PosY(-fHeight);
						return 1;
					}
					// 하 충돌
					else
					{
						Dest->Set_PosY(fHeight);
						return 2;
					}
				}

				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_Info().fX < Sour->Get_Info().fX)
					{
						Dest->Set_PosX(-fWidth);
						return 3;
					}
					// 우 충돌
					else
					{
						Dest->Set_PosX(fWidth);
						return 4;
					}
				}

			}
		}
	}
	return 0;
}

bool CCollisionMgr::Collision_Attack_Monster(CObj* _Temp, list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				if (CMonster::RARE == dynamic_cast<CMonster*>(Sour)->Get_Type())
				{
					if (Sour->Get_Parry())
					{
						if (_Temp->Get_Info().fX < Sour->Get_Info().fX)
						{
							if (Sour->Get_Dir() == DIR_LEFT)
							{
								_Temp->Set_Parry(true);
								CSoundMgr::Get_Instance()->PlaySound(L"hero_parry.wav", SOUND_EFFECT, 1);
								Sleep(300);
							}
							else
							{
								CSoundMgr::Get_Instance()->PlaySound(L"enemy_damage.wav", SOUND_EFFECT, 1);
								Sour->Set_HP(1);
							}
						}
						else
						{
							if (Sour->Get_Dir() == DIR_RIGHT)
							{
								_Temp->Set_Parry(true);
								CSoundMgr::Get_Instance()->PlaySound(L"hero_parry.wav", SOUND_EFFECT, 1);
								Sleep(300);
							}
							else
							{
								CSoundMgr::Get_Instance()->PlaySound(L"enemy_damage.wav", SOUND_EFFECT, 1);
								Sour->Set_HP(1);
							}
						}
					}
					else
					{
						CSoundMgr::Get_Instance()->PlaySound(L"enemy_damage.wav", SOUND_EFFECT, 1);
						if (_Temp->Get_Info().fX < Sour->Get_Info().fX)
							Sour->Set_PosX(50.f);
						else
							Sour->Set_PosX(-50.f);
						Sour->Set_HP(1);
					}
				}
				if (CMonster::NOMAL == dynamic_cast<CMonster*>(Sour)->Get_Type())
				{
					CSoundMgr::Get_Instance()->PlaySound(L"enemy_damage.wav", SOUND_EFFECT, 1);
					if (_Temp->Get_Info().fX < Sour->Get_Info().fX)
						Sour->Set_PosX(50.f);
					else
						Sour->Set_PosX(-50.f);
					Sour->Set_HP(1);
				}
				if (CMonster::FLY == dynamic_cast<CMonster*>(Sour)->Get_Type())
				{
					CSoundMgr::Get_Instance()->PlaySound(L"enemy_damage.wav", SOUND_EFFECT, 1);
					Sour->Set_HP(1);
				}
				if (CMonster::BOSS == dynamic_cast<CMonster*>(Sour)->Get_Type())
				{
					CSoundMgr::Get_Instance()->PlaySound(L"false_knight_damage_armour.wav", SOUND_EFFECT, 1);
					Sour->Set_HP(1);
				}
				return true;
			}
		}
	}
	return false;
}

bool CCollisionMgr::Collision_Line(CObj* _pObj, list<CObj*>* _Sour, float* _pY)
{

	CObj* pTarget = nullptr;

	float fMin = 3000.f;

	for (auto& iter : *_Sour)
	{
		if (_pObj->Get_Rect().right > iter->Get_Rect().left &&
			_pObj->Get_Rect().left < iter->Get_Rect().right &&
			_pObj->Get_Rect().bottom <= iter->Get_Rect().top + 20.f)
		{
			if ((iter->Get_Rect().top) - (_pObj->Get_Rect().bottom) < fMin)
			{
				pTarget = iter;
				fMin = (iter->Get_Rect().top) - (_pObj->Get_Rect().bottom);
			}
		}
	}

	if (!pTarget)
		return false;

	*_pY = pTarget->Get_Rect().top;

	return true;
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

void CCollisionMgr::Collision_Erase(RECT _Dest, list<CObj*> _Sour)
{
	RECT rc{};
	for (auto& Sour : _Sour)
	{
		if (IntersectRect(&rc, &_Dest, &(Sour->Get_Rect())))
		{
			Sour->Set_Dead();
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	// abs : 절대값을 만들어주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;	// 충돌을 한 경우
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
