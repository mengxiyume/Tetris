#define _CRT_SECURE_NO_WARNINGS

#include"Head.h"

#define BlockWidth 4
#define BlockHeight 4
#define BlockCount 4

Blocks* ReadBlocks(size_t ReadNumber)
{
	FILE* pFile = NULL;
	FILE* pTmp = fopen("./BlockMode.txt", "rt");
	assert(pTmp);
	pFile = pTmp;

	int Buffer = 0;

	int i = 0, j = 0, c = 0, n = 0;

	Blocks* pBlocks = NULL;
	Blocks* pTmpBlocks = NULL;
	Blocks* LastBlocks = NULL;

	for (i = 0; i < ReadNumber; i++)
	{
		pTmpBlocks = GetBlocks(LastBlocks, BlockCount, BlockHeight, BlockWidth);
		assert(pTmpBlocks);
		LastBlocks = pTmpBlocks;
		if (!i)
		{
			pBlocks = LastBlocks;
		}
	}


	pTmpBlocks = pBlocks;

	for (n = 0; n < ReadNumber; n++)
	{
		Block* pTmpLoopBlock = pTmpBlocks->loopblock;
		for (c = 0; c < BlockCount; c++)
		{
			Block_Rows* pTmpBlockRows = pTmpLoopBlock->rows;
			for (i = 0; i < BlockHeight; i++)
			{
				Block_Columns* pTmpBlockColumns = pTmpBlockRows->Columns;
				for (j = 0; j < BlockWidth; j++)
				{
					fscanf(pFile, "%d", &Buffer);
					pTmpBlockColumns->state = Buffer;
					pTmpBlockColumns = NEXT_LINKED(pTmpBlockColumns);
				}
				fscanf(pFile, "\n");
				pTmpBlockRows = NEXT_LINKED(pTmpBlockRows);
			}
			fscanf(pFile, "\n");
			pTmpLoopBlock = NEXT_LINKED(pTmpLoopBlock);
		}
		fscanf(pFile, "\n");
		pTmpBlocks = NEXT_LINKED(pTmpBlocks);
	}
	fclose(pFile);
	pFile = NULL;
	return pBlocks;
}