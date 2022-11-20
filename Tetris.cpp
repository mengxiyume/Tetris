#define _CRT_SECURE_NO_WARNINGS 1

#include"Head.h"

#define BlockNumber 7
#define BlockWidth 4
#define BlockHeight 4
#define BlockCount 4

int Window_Width = 800;
int Window_Height = 1000;

int Width_Number = 10;
int Height_Number = 20;

DP diss{ 0 };

Blocks* pBlocks = NULL;

void InitTetris()
{
	InitGraphicsMode(Window_Width, Window_Height, &diss);

	diss.Width_Number = Width_Number;
	diss.Height_Number = Height_Number;
	int i = 0;
	TLine* Last = NULL;
	for (i = 0; i < Height_Number; i++)
	{
		Last = GetTLine(Last, Width_Number);
		if (!i)
		{
			diss.DissArr = Last;
		}
	}
	Last = NULL;
	for (i = 0; i < Height_Number + 8; i++)
	{
		Last = GetTLine(Last, Width_Number);
		if (!i)
		{
			diss.LifeArr = Last;
		}
	}
	pBlocks = ReadBlocks(BlockNumber);
}

void PutTetris()
{
	int i = 0, j = 0;
	assert(diss.DissArr);
	assert(diss.LifeArr);
	TLine* TmpTLine = diss.DissArr;
	TLine* TmpLifeTLine = diss.LifeArr;

	DissPlayGame(&diss);

	system("cls");

	printf("NEXT:\n");
	for (j = 0; j < 4; j++)
	{
		printf("|---");
	}
	printf("|\n");
	for (i = 0; i < 4; i++)
	{
		assert(TmpTLine->Arr);
		assert(TmpLifeTLine->Arr);
		Drop* TmpLifeDrop = TmpLifeTLine->Arr;
		for (j = 0; j < Width_Number / 2 - BlockWidth / 2; j++)
		{
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
		}
		for (j = 0; j < 4; j++)
		{
			if (TmpLifeDrop->state)
			{
				printf("| $ ");
			}
			else
			{
				printf("|   ");
			}
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
		}
		printf("|\n");
		for (j = 0; j < 4; j++)
		{
			printf("|---");
		}
		printf("|\n");
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}


	for (i = 0; i < 4; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}

	printf("\n\n");

	for (j = 0; j < Width_Number; j++)
	{
		printf("|---");
	}
	printf("|\n");


	for (i = 0; i < Height_Number; i++)
	{
		assert(TmpTLine);
		assert(TmpTLine->Arr);
		assert(TmpLifeTLine->Arr);
		Drop* TmpDrop = TmpTLine->Arr;
		Drop* TmpLifeDrop = TmpLifeTLine->Arr;
		for (j = 0; j < Width_Number; j++)
		{
			if (TmpLifeDrop->state)
			{
				printf("| * ");
			}
			else if (TmpDrop->state)
			{
				printf("| # ");
			}
			else
			{
				printf("|   ");
			}
			TmpDrop = NEXT_LINKED(TmpDrop);
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
		}
		printf("|\n");
		for (j = 0; j < Width_Number; j++)
		{
			printf("|---");
		}
		printf("|\n");
		TmpTLine = NEXT_LINKED(TmpTLine);
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
}

//活动块的运动
bool LifeLoop(bool Life)
{
	if (!Life)
	{
		return false;
	}
	TLine* TmpTLine = diss.DissArr;
	TLine* TmpLifeTLine = diss.LifeArr;
	int i = 0;

	//判断是否能够向下移动
	for (i = 0; i < 8; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
	//移动到活动块
	TLine* TmpEndLifeTLine = NULL;
	TLine* TmpEndTLine = NULL;
	TmpTLine = NEXT_LINKED(TmpTLine);
	while (TmpLifeTLine)
	{
		Drop* TmpLifeDrop = TmpLifeTLine->Arr;
		while (TmpLifeDrop)
		{
			if (TmpLifeDrop->state)
			{
				TmpEndLifeTLine = TmpLifeTLine;
				TmpEndTLine = TmpTLine;
				break;
			}
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
		}
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
		if (TmpTLine)
		{
			TmpTLine = NEXT_LINKED(TmpTLine);
		}
	}
	//到底后返回false
	if (TmpEndLifeTLine && !TmpEndLifeTLine->Next)
	{
		return false;
	}
	//碰撞判定
	TmpTLine = TmpEndTLine;
	TmpLifeTLine = TmpEndLifeTLine;
	for (i = 0; i < 4; i++)
	{
		if (!TmpTLine)
		{
			break;
		}
		//逐行向上判定
		Drop* TmpDrop = TmpTLine->Arr;
		Drop* TmpLifeDrop = TmpLifeTLine->Arr;

		while (TmpDrop)
		{
			int IfOverlap = 0;
			if (TmpDrop->state)
			{
				IfOverlap++;
			}
			if (TmpLifeDrop->state)
			{
				IfOverlap++;
			}
			if (IfOverlap > 1)
			{
				return false;
			}

			TmpDrop = NEXT_LINKED(TmpDrop);
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
		}


		TmpTLine = LAST_LINKED(TmpTLine);
		TmpLifeTLine = LAST_LINKED(TmpLifeTLine);
	}


	//向下移动
	TmpLifeTLine = diss.LifeArr;
	for (i = 0; i < 3; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
	TLine* LoopBegin = TmpLifeTLine;

	while (true)
	{
		if (!TmpLifeTLine->Next)
		{
			break;
		}
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
	TLine* LoopEnd = TmpLifeTLine->Last;
	LoopEnd->Next = NULL;

	//将链表尾摘除到中间某段
	TmpLifeTLine->Last = LoopBegin;
	TmpLifeTLine->Next = LoopBegin->Next;
	//头尾链接
	LoopBegin->Next->Last = TmpLifeTLine;
	LoopBegin->Next = TmpLifeTLine;

	return true;
}

bool LifeToBack()
{
	TLine* TmpLifeTLine = diss.LifeArr;
	TLine* TmpTLine = diss.DissArr;
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		if (i >= 4)
		{
			Drop* TmpLifeDrop = TmpLifeTLine->Arr;
			while (TmpLifeDrop)
			{
				if (TmpLifeDrop->state)
				{
					return true;
				}
				TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
			}
		}
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}

	while (true)
	{
		if (!TmpTLine)
		{
			break;
		}
		Drop* TmpLifeDrop = TmpLifeTLine->Arr;
		Drop* TmpDrop = TmpTLine->Arr;
		while (true)
		{
			if (!TmpDrop)
			{
				break;
			}
			//同位移动，尾位跳到下一行
			if (TmpLifeDrop->state)
			{
				TmpLifeDrop->state = false;
				TmpDrop->state = true;

				TmpDrop->color = TmpLifeDrop->color;
			}
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
			TmpDrop = NEXT_LINKED(TmpDrop);
		}

		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
		TmpTLine = NEXT_LINKED(TmpTLine);
	}
	return false;
}

void ReadToBlock(int x, TLine* destination, Block_Rows* sourse, int color)
{
	assert(destination && sourse);
	int i = 0, j = 0;
	for (i = 0; i < 4; i++)
	{
		Drop* TmpLifeDrop = destination->Arr;
		Block_Columns* BufferColumns = sourse->Columns;

		for (j = 0; j < Width_Number; j++)
		{
			if (j >= x && j < x + 4)
			{
				//	在(0`3)区间copy
				TmpLifeDrop->state = BufferColumns->state;
				TmpLifeDrop->color = color;
				BufferColumns = NEXT_LINKED(BufferColumns);
			}
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
		}
		destination = NEXT_LINKED(destination);
		sourse = NEXT_LINKED(sourse);
	}
}

void GetRandBlock(bool once)
{
	Blocks* BufferBlock = NULL;

	TLine* TmpLifeTLine = diss.LifeArr;
	Block* Buffer = NULL;
	Block_Rows* BufferRows = NULL;

	int Color = NULL;
	static bool Once = false;

	if (once)
	{
		Once = false;
	}

	int i = 0, j = 0;

	if (!Once)
	{
		//第一次调用
		//在预备区和活动区各生成一个块
		Once = true;
		for (int Count = 0; Count < 2; Count++)
		{
			BufferBlock = pBlocks;
			srand((unsigned int)time(NULL));
			Color = rand() % 0xFFFFFF + 1;
			int RandNumber = rand() % (BlockNumber - 1 + Count);
			for (i = 0;i<RandNumber;i++)
			{
				BufferBlock = NEXT_LINKED(BufferBlock);
			}
			Buffer = BufferBlock->loopblock;
			RandNumber = rand() % (BlockNumber * BlockNumber);
			for (i = 0; i < RandNumber; i++)
			{
				Buffer = NEXT_LINKED(Buffer);
			}
			BufferRows = Buffer->rows;

			ReadToBlock(Width_Number / 2 - BlockWidth / 2, TmpLifeTLine, BufferRows, Color);

			for (i = 0; i < 4; i++)
			{
				TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
			}
			if (Count == 0)
			{
				diss.NextBlock = Buffer;
			}
			else if (Count == 1)
			{
				diss.CurrentBlock = Buffer;
			}
		}
	}
	else
	{
		//将预备区的块移动到活动区
		//再生成一个块在预备区
		TLine* LastBegin = TmpLifeTLine;
		TLine* LastEnd = NULL;

		TLine* NextBegin = NULL;
		TLine* NextEnd = NULL;

		//将预备区移动到活动区
		for (i = 0; i < 4; i++)
		{
			TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
		}
		NextBegin = TmpLifeTLine;
		LastEnd = NextBegin->Last;
		for (i = 0; i < 4; i++)
		{
			TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
		}
		NextEnd = TmpLifeTLine->Last;

		//尾部链接
		TmpLifeTLine->Last = LastEnd;
		LastEnd->Next = TmpLifeTLine;
		//中间链接
		LastBegin->Last = NextEnd;
		NextEnd->Next = LastBegin;
		//头部链接
		NextBegin->Last = NULL;
		diss.LifeArr = NextBegin;

		//在预备区生成新的块
		TmpLifeTLine = diss.LifeArr;
		BufferBlock = pBlocks;
		srand((unsigned int)time(NULL));
		Color = rand() % 0xFFFFFF + 1;
		int RandNumber = rand() % BlockNumber;
		for (i = 0; i < RandNumber; i++)
		{
			BufferBlock = NEXT_LINKED(BufferBlock);
		}
		Buffer = BufferBlock->loopblock;
		RandNumber = rand() % (BlockNumber * BlockNumber);
		for (i = 0; i < RandNumber; i++)
		{
			Buffer = NEXT_LINKED(Buffer);
		}
		BufferRows = Buffer->rows;

		ReadToBlock(Width_Number / 2 - BlockWidth / 2, TmpLifeTLine, BufferRows, Color);
		diss.CurrentBlock = diss.NextBlock;
		diss.NextBlock = Buffer;
	}
	LifeLoop(true);
}

int IfEliminate()
{
	int TrueNumber = 0;
	TLine* TmpTLine = diss.DissArr;
	TLine* TmpUpTLine = TmpTLine;
	while (TmpTLine)
	{
		bool ifEliminate = false;
		Drop* TmpDrop = TmpTLine->Arr;
		while (TmpDrop)
		{
			ifEliminate = true;
			if (!TmpDrop->state)
			{
				ifEliminate = false;
				break;
			}
			TmpDrop = NEXT_LINKED(TmpDrop);
		}

		if (ifEliminate)
		{
			//将当前层清除并移动到顶端

			//清除当前层
			Drop* TmpDrop = TmpTLine->Arr;
			while (TmpDrop)
			{
				TmpDrop->state = false;
				TmpDrop->color = NULL;
				TmpDrop = NEXT_LINKED(TmpDrop);
			}

			//移动当前层
			TLine* NextTLine = TmpTLine->Next;
			TLine* LastTLine = TmpTLine->Last;

			TmpUpTLine->Last = TmpTLine;
			TmpTLine->Next = TmpUpTLine;
			TmpTLine->Last = NULL;
			diss.DissArr = TmpTLine;
			
			if (!NextTLine)
			{
				LastTLine->Next = NULL;
			}
			else
			{
				LastTLine->Next = NextTLine;
				NextTLine->Last = LastTLine;
			}
			TrueNumber++;
			TrueNumber += IfEliminate();
			break;
		}
		else 
		{
			TmpTLine = NEXT_LINKED(TmpTLine);
		}
	}
	return TrueNumber;
}

int Tetris()
{
	initgraph(Window_Width, Window_Height
#ifdef DEBUG
		, SHOWCONSOLE
#endif
	);
	do {
		//初始化
		InitTetris();
		bool Life = true;
		//预备区产生块
		GetRandBlock(true);
		diss.GameOver = false;
		PutTetris();
		while (true)
		{

			Life = LifeLoop(Life);

			for (int i = 0; i < 10; i++)
			{
				IfTramsForm(&diss);
				Sleep(60);
			}

			if (!Life)
			{
				for (int i = 0; i < 5; i++)
				{
					IfTramsForm(&diss);
					Sleep(60);
				}
				Life = LifeLoop(true);
				if (Life)
				{
					continue;
				}
				PutTetris();
				if (LifeToBack())
				{
					system("cls");
					printf("菜\n");

					diss.GameOver = true;
					DissPlayGame(&diss);

					system("pause");
					CloseTLine(&diss.DissArr);
					CloseTLine(&diss.LifeArr);
					CloseBlocks(&pBlocks);
					break;
				}
				int Eliminata = IfEliminate();
				diss.Score += Eliminata * Eliminata * 100;
				diss.Level = (diss.Score / 2000) + 1;

				Life = true;
				GetRandBlock(false);
			}
			PutTetris();
		}
	} while (true);
	return 0;
}