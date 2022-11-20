#pragma once

typedef struct Drop
{
	
	bool state;
	int color;
	struct Drop* Last;
	struct Drop* Next;
}Drop;
//显示矩阵x
typedef struct TLine
{
	Drop* Arr;
	struct TLine* Last;
	struct TLine* Next;
}TLine;
//显示矩阵y

typedef struct BlockColumns
{
	bool state;
	struct BlockColumns* Last;
	struct BlockColumns* Next;
}Block_Columns;
//块x
typedef struct BlockRows
{
	BlockColumns* Columns;
	struct BlockRows* Last;
	struct BlockRows* Next;
}Block_Rows;
//块y
typedef struct Block
{
	BlockRows* rows;
	struct Block* Last;
	struct Block* Next;
}Block;
//块类型循环
typedef struct Blocks
{
	Block* loopblock;
	struct Blocks* Last;
	struct Blocks* Next;
}Blocks;
//块类型循环链接

typedef struct DissPlay
{

	bool GameOver;

	int dissx;
	int dissy;
	int Blockx;
	int Blocky;
	int Blockw;
	int Blockh;
	int RoundBlock;
	int BlockInterval = 9;

	int NextBlockx;
	int NextBlocky;

	int Score;
	int ScoreSize;
	int Scorex;
	int Scorey;

	int Level;
	int LevelSize;
	int Levelx;
	int Levely;

	int Width_Number;
	int Height_Number;
	TLine* DissArr;
	TLine* LifeArr;
	Block* CurrentBlock;
	Block* NextBlock;
}DP;
//显示信息