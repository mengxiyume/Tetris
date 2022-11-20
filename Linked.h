#pragma once

#include"Structur.h"

#define LAST_LINKED(NAME) ((NAME)->Last)
#define NEXT_LINKED(NAME) ((NAME)->Next)

TLine* GetTLine(TLine* last, size_t DropNumber);
Drop* GetDrop(Drop* last);


Block_Columns* GetBlockColumns(Block_Columns* last);
Block_Rows* GetBlockRows(Block_Rows* last, size_t ColumnsNumber);

Block* GetBlock(Block* last, size_t RowsNumber, size_t ColumnsNumber);
Block* GetLoopBlock(size_t LoopNumber, size_t RowsNumber, size_t ColumnsNumber);
Blocks* GetBlocks(Blocks* last, size_t LoopNumber, size_t RowsNumber, size_t ColumnsNumber);

void CloseDrop(Drop** dest);
void CloseTLine(TLine** dest);

void CloseBlockColumns(Block_Columns** dest);
void CloseBlockRows(Block_Rows** dest);
void CloseBlock(Block** dest);
void CloseLoopBlock(Block** dest);
void CloseBlocks(Blocks** dest);