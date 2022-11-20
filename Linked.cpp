#define _CRT_SECURE_NO_WARNINGS 1

#include"Linked.h"
#include"Head.h"

Drop* GetDrop(Drop* last)
{
	Drop* Tmp = (Drop*)calloc(1, sizeof(Drop));
	assert(Tmp);
	Drop* ret = Tmp;
	if (last)
	{
		last->Next = ret;
	}
	ret->Last = last;
	return ret;
}

TLine* GetTLine(TLine* last, size_t DropNumber)
{
	TLine* Tmp = (TLine*)calloc(1, sizeof(TLine));
	assert(Tmp);
	TLine* ret = Tmp;
	if (last)
	{
		last->Next = ret;
	}
	ret->Last = last;
	int i = 0;
	Drop* Last = NULL;
	for (i = 0; i < DropNumber; i++)
	{
		Last = GetDrop(Last);
		if (!i)
		{
			ret->Arr = Last;
		}
	}
	return ret;
}

Block_Columns* GetBlockColumns(Block_Columns* last)
{
	Block_Columns* Tmp = (Block_Columns*)calloc(1, sizeof(Block_Columns));
	assert(Tmp);
	Block_Columns* ret = Tmp;
	if (last)
	{
		last->Next = ret;
	}
	ret->Last = last;
	return ret;
}

Block_Rows* GetBlockRows(Block_Rows* last, size_t ColumnsNumber)
{
	assert(ColumnsNumber);
	Block_Rows* Tmp = (Block_Rows*)calloc(1, sizeof(Block_Rows));
	assert(Tmp);
	Block_Rows* ret = Tmp;
	if (last)
	{
		last->Next = ret;
	}
	ret->Last = last;
	int i = 0;
	Block_Columns* Last = NULL;
	for (i = 0; i < ColumnsNumber; i++)
	{
		Last = GetBlockColumns(Last);
		if (!i)
		{
			ret->Columns = Last;
		}
	}
	return ret;
}

Block* GetBlock(Block* last, size_t RowsNumber, size_t ColumnsNumber)
{
	assert(RowsNumber && ColumnsNumber);
	Block* Tmp = (Block*)calloc(1, sizeof(Block));
	assert(Tmp);
	Block* ret = Tmp;
	if (last)
	{
		last->Next = Tmp;
	}
	ret->Last = last;
	int i = 0;
	Block_Rows* Last = NULL;
	for (i = 0; i < RowsNumber; i++)
	{
		Last = GetBlockRows(Last, ColumnsNumber);
		if (!i)
		{
			ret->rows = Last;
		}
	}
	return ret;
}

Block* GetLoopBlock(size_t LoopNumber, size_t RowsNumber, size_t ColumnsNumber)
{
	assert(LoopNumber && RowsNumber && ColumnsNumber);
	Block* Begin = NULL;
	Block* Tmp = NULL;
	Block* Last = NULL;
	int i = 0;
	for (i = 0; i < LoopNumber; i++)
	{
		Tmp = GetBlock(Last, RowsNumber, ColumnsNumber);
		assert(Tmp);
		Last = Tmp;
		if (!i)
		{
			Begin = Last;
		}
	}
	Begin->Last = Last;
	Last->Next = Begin;
	return Begin;
}

Blocks* GetBlocks(Blocks* last, size_t LoopNumber, size_t RowsNumber, size_t ColumnsNumber)
{
	assert(LoopNumber && RowsNumber && ColumnsNumber);
	Blocks* Tmp = (Blocks*)calloc(1, sizeof(Blocks));
	assert(Tmp);
	Blocks* ret = Tmp;
	if (last)
	{
		last->Next = ret;
	}
	ret->Last = last;
	ret->loopblock = GetLoopBlock(LoopNumber, RowsNumber, ColumnsNumber);
	return ret;
}


void CloseDrop(Drop** dest)
{
	assert(dest);
	assert(*dest);
	free(*dest);
	*dest = NULL;
}

void CloseTLine(TLine** dest)
{
	assert(dest);
	assert(*dest);

	int i = 0;
	Drop* Tmp = (*dest)->Arr;
	Drop* Next = Tmp;

	while (true)
	{
		Next = Tmp->Next;
		CloseDrop(&Tmp);
		if (!Next)
		{
			break;
		}
		Tmp = Next;
	}
	free(*dest);
	*dest = NULL;
}

void CloseBlockColumns(Block_Columns** dest)
{
	assert(dest);
	assert(*dest);
	free(*dest);
	*dest = NULL;
}

void CloseBlockRows(Block_Rows** dest)
{
	assert(dest);
	assert(*dest);

	int i = 0;
	Block_Columns* Tmp = (*dest)->Columns;
	Block_Columns* Next = Tmp;

	while (true)
	{
		Next = Tmp->Next;
		CloseBlockColumns(&Tmp);
		if (!Next)
		{
			break;
		}
		Tmp = Next;
	}
	free(*dest);
	*dest = NULL;
}

void CloseBlock(Block** dest)
{
	assert(dest);
	assert(*dest);

	CloseBlockRows(&(*dest)->rows);
	free(*dest);
	*dest = NULL;
}

void CloseLoopBlock(Block** dest)
{
	assert(dest);
	assert(*dest);

	Block* Begin = *dest;
	Block* Tmp = *dest;
	Block* Next = Tmp;

	while (true)
	{
		Next = Tmp->Next;
		CloseBlock(&Tmp);
		if (Begin == Next->Next)
		{
			//循环链表的最后一个元素的下一个元素为第一个元素
			//满足头尾衔接点时即可关闭循环链表
			break;
		}
		Tmp = Next;
	}
	*dest = NULL;
}

void CloseBlocks(Blocks** dest)
{
	assert(dest);
	assert(*dest);

	Blocks* NextBlocks = NULL;
	Blocks* TmpBlocks = *dest;

	while (true)
	{
		NextBlocks = TmpBlocks->Next;
		CloseLoopBlock(&TmpBlocks->loopblock);
		if (!NextBlocks)
		{
			break;
		}
		TmpBlocks = NextBlocks;
	}
	free(*dest);
	*dest = NULL;
}