#pragma once
#include "Enum.h"

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;	// ���� ������
	float	fCY;	// ���� ������
	EDIT	eSave;
}INFO;


typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;

	DWORD	dwFrameSpeed;
	DWORD	dwFrameTime;

}FRAME;