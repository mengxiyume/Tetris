#define _CRT_SECURE_NO_WARNINGS

#include"News.h"

bool LeftNews(DP* diss)
{
	TLine* TmpLifeTLine = diss->LifeArr;
	TLine* TmpTLine = diss->DissArr;
	int i = 0;

	for (i = 0; i < 4; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
	while (TmpLifeTLine)
	{
		//最左边的一列有活动块则不能继续向左移动
		if (TmpLifeTLine->Arr->state)
		{
			return false;
		}
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
	//整张二维链表向左旋转
	//能否左旋判定
	TmpLifeTLine = diss->LifeArr;
	for (i = 0; i < 8; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
	while (TmpTLine)
	{

		Drop* TmpLifeDrop = TmpLifeTLine->Arr->Next;
		Drop* TmpDrop = TmpTLine->Arr;

		while (TmpLifeDrop)
		{
			int IfMove = 0;

			if (TmpLifeDrop->state)
			{
				IfMove++;
			}
			if (TmpDrop->state)
			{
				IfMove++;
			}

			if (IfMove > 1)
			{
				return false;
			}
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
			TmpDrop = NEXT_LINKED(TmpDrop);
		}


		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
		TmpTLine = NEXT_LINKED(TmpTLine);
	}


	//左旋
	TmpLifeTLine = diss->LifeArr;
	for (i = 0; i < 4; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
	while (TmpLifeTLine)
	{
		Drop* TmpLastBeginLifeDrop = TmpLifeTLine->Arr;
		Drop* TmpNextBeginLifeDrop = TmpLifeTLine->Arr->Next;
		Drop* TmpEndLifeDrop = NULL;
		Drop* TmpDrop = TmpLifeTLine->Arr;
		while (TmpDrop->Next)
		{
			TmpDrop = NEXT_LINKED(TmpDrop);
		}
		TmpDrop->Next = TmpLastBeginLifeDrop;
		TmpLastBeginLifeDrop->Last = TmpDrop;
		TmpLastBeginLifeDrop->Next = NULL;

		TmpNextBeginLifeDrop->Last = NULL;
		TmpLifeTLine->Arr = TmpNextBeginLifeDrop;

		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}

	return true;
}

bool RightNews(DP* diss)
{
	TLine* TmpLifeTLine = diss->LifeArr;
	TLine* TmpTLine = diss->DissArr;
	int i = 0;

	for (i = 0; i < 4; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}

	while (TmpLifeTLine)
	{
		//最右边的一列有活动块则不能继续向右移动
		Drop* TmpDrop = TmpLifeTLine->Arr;
		while (TmpDrop->Next)
		{
			TmpDrop = NEXT_LINKED(TmpDrop);
		}
		if (TmpDrop->state)
		{
			return false;
		}
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}

	//整张二维链表向右旋转
	//能否右旋判定
	TmpLifeTLine = diss->LifeArr;
	TmpTLine = diss->DissArr;
	for (i = 0; i < 8; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
	while (TmpTLine)
	{

		Drop* TmpLifeDrop = TmpLifeTLine->Arr;
		Drop* TmpDrop = TmpTLine->Arr->Next;

		while (TmpDrop)
		{
			int IfMove = 0;

			if (TmpLifeDrop->state)
			{
				IfMove++;
			}
			if (TmpDrop->state)
			{
				IfMove++;
			}

			if (IfMove > 1)
			{
				return false;
			}
			TmpLifeDrop = NEXT_LINKED(TmpLifeDrop);
			TmpDrop = NEXT_LINKED(TmpDrop);
		}
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
		TmpTLine = NEXT_LINKED(TmpTLine);
	}

	//右旋
	TmpLifeTLine = diss->LifeArr;
	for (i = 0; i < 4; i++)
	{
		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}
	while (TmpLifeTLine)
	{
		//将链表最后一位移动到最前
		Drop* TmpBeginLifeDrop = TmpLifeTLine->Arr;
		Drop* TmpDrop = TmpLifeTLine->Arr;

		Drop* TmpLastEndLifeDrop = NULL;
		Drop* TmpNextEndLifeDrop = NULL;
		while (TmpDrop->Next)
		{
			TmpDrop = NEXT_LINKED(TmpDrop);
		}

		TmpNextEndLifeDrop = TmpDrop->Last;
		TmpLastEndLifeDrop = TmpDrop;
		TmpLastEndLifeDrop->Last = NULL;
		TmpLastEndLifeDrop->Next = TmpBeginLifeDrop;
		TmpBeginLifeDrop->Last = TmpLastEndLifeDrop;
		TmpNextEndLifeDrop->Next = NULL;
		TmpLifeTLine->Arr = TmpLastEndLifeDrop;

		TmpLifeTLine = NEXT_LINKED(TmpLifeTLine);
	}

	return true;
}

bool IfRotate(int* x, int y, Block_Rows* sourse, DP* diss)
{
	//如果已经在最右边，变换空间不足则向左移动
	int Tmpx = *x;
	int i = 0;
	int color = NULL;
	size_t SourseWidth = 0;
	Block_Rows* TmpBlockRows = sourse;

	//需重构
	//*************************
	int Begin = 0;
	int End = 0;
	while (TmpBlockRows)
	{
		Block_Columns* TmpBlockColumns = TmpBlockRows->Columns;
		int i = 0;
		while (TmpBlockColumns)
		{
			i++;
			if (TmpBlockColumns->state)
			{
				if (i < Begin)
				{
					Begin = i;
				}
				else if(i > End)
				{
					End = i;
				}
			}
			TmpBlockColumns = NEXT_LINKED(TmpBlockColumns);
		}
		TmpBlockRows = NEXT_LINKED(TmpBlockRows);
	}
	SourseWidth = End - Begin;
	printf("%d", SourseWidth);
	if (Tmpx + SourseWidth > diss->Width_Number)
	{
		Tmpx = diss->Width_Number - SourseWidth;
	}
	//*************************

	//判断变换后是否重合
	//获取一个空间存储变换之后的块
	TLine* TmpTransFrom = NULL;
	TLine* TmpTLine = NULL;
	TLine* Last = NULL;
	for (i = 0; i < diss->Height_Number + 4; i++)
	{
		Last = GetTLine(Last, diss->Width_Number);
		if (!i)
		{
			TmpTransFrom = Last;
		}
	}
	TmpTLine = TmpTransFrom;
	for (i = 0; i < y; i++)
	{
		assert(TmpTLine);
		TmpTLine = NEXT_LINKED(TmpTLine);
	}
	ReadToBlock(Tmpx, TmpTLine, sourse, color);
	TmpTLine = TmpTransFrom;
	TLine* TmpBackTLine = diss->DissArr;

	for (i = 0; i < 4; i++)
	{
		assert(TmpTLine);
		TmpTLine = NEXT_LINKED(TmpTLine);
	}
	while (TmpBackTLine)
	{
		Drop* TmpDrop = TmpTLine->Arr;
		Drop* TmpBackDrop = TmpBackTLine->Arr;
		while (TmpBackDrop)
		{
			int ifrotate = 0;

			if (TmpBackDrop->state)
			{
				ifrotate++;
			}
			if (TmpDrop->state)
			{
				ifrotate++;
			}

			if (ifrotate > 1)
			{
				CloseTLine(&TmpTransFrom);
				return false;
			}

			TmpBackDrop = NEXT_LINKED(TmpBackDrop);
			TmpDrop = NEXT_LINKED(TmpDrop);
		}

		TmpBackTLine = NEXT_LINKED(TmpBackTLine);
		TmpTLine = NEXT_LINKED(TmpTLine);
	}


	CloseTLine(&TmpTransFrom);

	if (*x != Tmpx)
	{
		*x = Tmpx;
	}
	//未重合返回true
	//如Tmpx改变且未重合，返回true且改变x

	return true;
}

void UpNews(DP* diss)
{
	TLine* TmpBottom = NULL;
	int x = 0;
	int y = 0;
	bool _0State = false;
	int LeftNumber = 0;
	int BottomNumber = 0;
	TLine* TmpTLine = diss->LifeArr;
	int i = 0;
	int color = NULL;

	for (i = 0; i < 4; i++)
	{
		TmpTLine = NEXT_LINKED(TmpTLine);
	}
	while (TmpTLine)
	{
		Drop* TmpDrop = TmpTLine->Arr;
		x = 0;
		while (TmpDrop)
		{
			if (TmpDrop->state)
			{
				//拿到最左边和最底部
				TmpBottom = TmpTLine;
				BottomNumber = y;
				if (x == 0)
				{
					_0State = true;
				}
				break;
			}
			x++;
			TmpDrop = NEXT_LINKED(TmpDrop);
		}
		if (LeftNumber > x || !LeftNumber)
		{
			LeftNumber = x;
		}
		if (_0State)
		{
			LeftNumber = 0;
		}
		y++;
		TmpTLine = NEXT_LINKED(TmpTLine);
	}
	for (i = 0; i < 3; i++)
	{
		BottomNumber--;
		TmpBottom = LAST_LINKED(TmpBottom);
	}

	//拿到颜色
	TmpTLine = diss->LifeArr;
	for (i = 0; i < 4; i++)
	{
		TmpTLine = NEXT_LINKED (TmpTLine);
	}
	while (TmpTLine)
	{
		bool IfGet = false;
		Drop* TmpDrop = TmpTLine->Arr;
		while (TmpDrop)
		{
			if (TmpDrop->state)
			{
				color = TmpDrop->color;
				IfGet = true;
				break;
			}
			TmpDrop = NEXT_LINKED(TmpDrop);
		}

		if (IfGet)
		{
			break;
		}
		TmpTLine = NEXT_LINKED(TmpTLine);
	}

	//逆时针旋转

	//判断能否旋转
	if (IfRotate(&LeftNumber, BottomNumber, diss->CurrentBlock->Next->rows,diss))
	{
		//旋转
		diss->CurrentBlock = diss->CurrentBlock->Next;
		ReadToBlock(LeftNumber, TmpBottom, diss->CurrentBlock->rows, color);
	}

}

void DownNews()
{
	LifeLoop(true);
}

//消息处理
int	NewsHandle(int News, DP* diss)
{
	if (!News)
	{
		return 0;
	}

	switch (News)
	{
	case VK_LEFT:
		//左移一位
		LeftNews(diss);
		PutTetris();
		break;
	case VK_RIGHT:
		//右移一位
		RightNews(diss);
		PutTetris();
		break;
	case VK_UP:
		//变换形态
		UpNews(diss);
		PutTetris();
		break;
	case VK_DOWN:
		//下一一位
		DownNews();
		PutTetris();
		break;
	default:
		break;
	}
	return true;
}

//变换
void IfTramsForm(DP* diss)
{
	int News = 0;
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (News)
		{
			News = NULL;
		}
		News = VK_LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if (News)
		{
			News = NULL;
		}
		News = VK_RIGHT;
	}
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState('W'))
	{
		if (News)
		{
			News = NULL;
		}
		News = VK_UP;
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (News)
		{
			News = NULL;
		}
		News = VK_DOWN;
	}
	NewsHandle(News,diss);
}