#pragma once

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;	// 가로 사이즈
	float	fCY;	// 세로 사이즈
}INFO;


typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;

	DWORD	dwFrameSpeed;
	DWORD	dwFrameTime;

}FRAME;