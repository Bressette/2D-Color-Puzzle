#pragma once

const int sizeX = 10;
const int sizeY = 10;
void initBoard(float board[sizeY][sizeX][3], float color1[3], float color2[3], float color3[3], float color4[3]);
void scrambleBoard(float board[sizeY][sizeX][3], int steps);
void lerpColorF(float nextColor[3], float color1[3], float color2[3], int currentStep, int totalSteps);
void makeVerticalMove(int x, int dir, float board[sizeY][sizeX][3]);
void makeHorizontalMove(int y, int dir, float board[sizeY][sizeX][3]);
int checkBoard(float board[sizeY][sizeX][3], float boardSolved[sizeY][sizeX][3]);
