#pragma once

#include"Head.h"

void ReadToBlock(int x, TLine* destination, Block_Rows* sourse, int color);
bool LifeLoop(bool Life);
void PutTetris();
int IfEliminate();
int Tetris();
void GetRandBlock(bool once);
bool LifeToBack();
void InitTetris();