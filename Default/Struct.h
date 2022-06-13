#pragma once

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;	// ���� ������
	float	fCY;	// ���� ������
}INFO;


typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;

	DWORD	dwFrameSpeed;
	DWORD	dwFrameTime;

}FRAME;