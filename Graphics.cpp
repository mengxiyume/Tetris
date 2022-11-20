#define _CRT_SECURE_NO_WARNINGS

#include"Graphics.h"

IMAGE BK;

#define BlockWidth 4

void InitGraphicsMode(int Window_Width, int Window_Height, DP* diss)
{
	setbkcolor(RGB(255, 249, 239));
	settextcolor(RGB(112, 112, 112));
	setbkmode(TRANSPARENT);
	setlinestyle(PS_NULL);

	LOGFONT f;
	gettextstyle(&f);											// 获取当前字体设置
	f.lfHeight = 30;											// 设置字体高度为 30
	_tcscpy(f.lfFaceName, _T("Segoe UI Semilight Italic"));		// 设置字体为“Segoe UI Semilight Italic”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;							// 设置输出效果为抗锯齿  
	settextstyle(&f);											// 设置字体样式

	mciSendString("open ./Music/BK.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);

	loadimage(&BK, "./UI/BK.png");

	diss->Blockx = 110;
	diss->Blocky = 30;
	diss->Blockw = 30;
	diss->Blockh = 30;
	diss->RoundBlock = 8;
	diss->BlockInterval = 9;

	diss->NextBlockx = 527;
	diss->NextBlocky = 188;

	diss->ScoreSize = 25;
	diss->Scorex = 583;
	diss->Scorey = 121;

	diss->LevelSize = 25;
	diss->Levelx = 609;
	diss->Levely = 46;
	diss->Level = 1;

	cleardevice();
	BeginBatchDraw();
}

void DissPlayGame(DP* diss)
{
	cleardevice();
	putimage(0, 0, &BK);

	char Buffer[1024];

	settextcolor(RGB(112, 112, 112));
	LOGFONT f;
	gettextstyle(&f);											// 获取当前字体设置
	f.lfHeight = 30;											// 设置字体高度为 30
	_tcscpy(f.lfFaceName, _T("Segoe UI Semilight Italic"));		// 设置字体为“Segoe UI Semilight Italic”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;							// 设置输出效果为抗锯齿  
	settextstyle(&f);											// 设置字体样式

	//关卡
	sprintf(Buffer, "%03d", diss->Level);
	outtextxy(diss->Levelx, diss->Levely, Buffer);

	//分数
	sprintf(Buffer, "%07d", diss->Score);
	outtextxy(diss->Scorex, diss->Scorey, Buffer);

	if (diss->GameOver)
	{
		LOGFONT f;
		gettextstyle(&f);											// 获取当前字体设置
		f.lfHeight = 200;											// 设置字体高度为 30
		_tcscpy(f.lfFaceName, _T("Segoe UI Semilight Italic"));		// 设置字体为“Segoe UI Semilight Italic”(高版本 VC 推荐使用 _tcscpy_s 函数)
		f.lfQuality = ANTIALIASED_QUALITY;							// 设置输出效果为抗锯齿  
		settextstyle(&f);											// 设置字体样式
		settextcolor(RGB(117, 138, 109));

		outtextxy(520, 363, "菜");
	}

	int TmpX = diss->Blockx;
	int TmpY = diss->Blocky;
	int TmpW = diss->Blockw;
	int TmpH = diss->Blockh;
	int Round = diss->RoundBlock;
	int Interval = diss->BlockInterval;

	int i = 0, j = 0;

	TLine* TmpLifeTLine = diss->LifeArr;
	TLine* TmpTLine = diss->DissArr;

	TmpX = diss->NextBlockx;
	TmpY = diss->NextBlocky;
	for (i = 0; i < 4; i++)
	{
		Drop* TmpLifeDrop = TmpLifeTLine->Arr;
		for (j = 0; j < diss->Width_Number / 2 - BlockWidth / 2; j++)
		{
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
		}
		for (j = 0; j < 4; j++)
		{
			if (diss->GameOver)
			{
				setfillcolor(RGB(222, 140, 140));
				fillroundrect(TmpX, TmpY, TmpX + TmpW, TmpY + TmpH, Round, Round);
			}
			if (TmpLifeDrop->state)
			{
				setfillcolor(TmpLifeDrop->color);
				fillroundrect(TmpX, TmpY, TmpX + TmpW, TmpY + TmpH, Round, Round);
			}
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
			TmpX += TmpW + Interval;
		}
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
		TmpY += TmpH + Interval;
		TmpX = diss->NextBlockx;
	}

	for (i = 0; i < 4; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}

	TmpX = diss->Blockx;
	TmpY = diss->Blocky;

	while (TmpLifeTLine)
	{
		Drop* TmpLifeDrop = TmpLifeTLine->Arr;
		Drop* TmpDrop = TmpTLine->Arr;
		while (TmpLifeDrop)
		{
			if (diss->GameOver)
			{
				setfillcolor(RGB(222, 140, 140));
				fillroundrect(TmpX, TmpY, TmpX + TmpW, TmpY + TmpH, Round, Round);
			}
			if (TmpDrop->state)
			{
				setfillcolor(TmpDrop->color);
				fillroundrect(TmpX, TmpY, TmpX + TmpW, TmpY + TmpH, Round, Round);
			}
			if (TmpLifeDrop->state)
			{
				setfillcolor(TmpLifeDrop->color);
				fillroundrect(TmpX, TmpY, TmpX + TmpW, TmpY + TmpH, Round, Round);
			}
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
			TmpDrop = NEXT_LINKED(TmpDrop);
			TmpX += TmpW + Interval;
		}

		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
		TmpTLine = NEXT_LINKED(TmpTLine);
		TmpY += TmpH + Interval;
		TmpX = diss->Blockx;
	}
	

	FlushBatchDraw();
}