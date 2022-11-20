#pragma once

typedef struct Drop
{
	
	bool state;
	int color;
	struct Drop* Last;
	struct Drop* Next;
}Drop;
//��ʾ����x
typedef struct TLine
{
	Drop* Arr;
	struct TLine* Last;
	struct TLine* Next;
}TLine;
//��ʾ����y

typedef struct BlockColumns
{
	bool state;
	struct BlockColumns* Last;
	struct BlockColumns* Next;
}Block_Columns;
//��x
typedef struct BlockRows
{
	BlockColumns* Columns;
	struct BlockRows* Last;
	struct BlockRows* Next;
}Block_Rows;
//��y
typedef struct Block
{
	BlockRows* rows;
	struct Block* Last;
	struct Block* Next;
}Block;
//������ѭ��
typedef struct Blocks
{
	Block* loopblock;
	struct Blocks* Last;
	struct Blocks* Next;
}Blocks;
//������ѭ������

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
//��ʾ��Ϣ