// OpenGLSquares.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "Rendering.h"
#include "game.h"



void display();
void keyboard(unsigned char key, int x, int y);
void click(int button, int state, int x, int y);
void assignColors(float color1[3], float color2[3], float color3[3], float color4[3]);
void createGame(float board[sizeY][sizeX][3], float boardSolved[sizeY][sizeX][3], float color1[3], float color2[3], float color3[3], float color4[3]);
void createGLUTWindow(int argc, char **argv);
void displayInstructions();

float board[sizeY][sizeX][3] = { 0 };
float boardSolved[sizeY][sizeX][3] = { 0 };

int scrambleSteps = 25 * (sizeX*sizeY);
float color1[3] = { 0 }; //bottom left
float color2[3] = { 0 }; //botom right
float color3[3] = { 0 }; //top left
float color4[3] = { 0 }; //top right
int selectedX = 1;
int selectedY = 1;
int moves = 0;


int main(int argc, char **argv)
{
	displayInstructions();
	srand(time(0));
	createGLUTWindow(argc, argv);
	createGame(board, boardSolved, color1, color2, color3, color4);
	display(board);
	printf("Press enter to scramble board...");
	getchar();
	scrambleBoard(board, scrambleSteps);
	glutMainLoop();

	return 1;
}

void createGLUTWindow(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(XRES, YRES);
	glutCreateWindow("Color Puzzle");

	glClearColor(0.0, 0.0, 0.0, 0.0);         // black background 
	glMatrixMode(GL_PROJECTION);              // setup viewing projection 
	glLoadIdentity();                           // start with identity matrix 
	gluOrtho2D(0.0, XRES, 0.0, YRES, -1, 1);   // setup a sizexsizex2 viewing world
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMouseFunc(click);
}

void game()
{
	displayBoard(board);
}

void display()
{
	game();
	//drawCursor(1, 1, 1, 10);

	glFlush();
}

int selectMode = 0; //0 is none, 1 is x mode, 2 is y mode
void keyboard(unsigned char key, int x, int y)
{
	moves++;

	if (selectedY == sizeY - 1)
	{
		selectedY = 1;
	}
	if (selectedY == 0)
	{
		selectedY = sizeY - 2;
	}
	if (selectedX == sizeX - 1)
	{
		selectedX = 1;
	}
	if (selectedX == 0)
	{
		selectedX = sizeX - 2;
	}
	switch (key)
	{
	case 'w':
		makeVerticalMove(selectedX, 1, board);
		selectedY++;
		break;
	case 's':
		makeVerticalMove(selectedX, -1, board);
		selectedY--;
		break;
	case 'a':
		makeHorizontalMove(selectedY, -1, board);
		selectedX--;
		break;
	case 'd':
		makeHorizontalMove(selectedY, 1, board);
		selectedX++;
		break;
	case 'r':
		createGame(board, boardSolved, color1, color2, color3, color4);
		break;
	default:
		break;
	}
	if (checkBoard(board, boardSolved))
	{
		printf("You win!\nYou took %d moves.", moves);
	}
	glutPostRedisplay(); /* this redraws the scene without
							waiting for the display callback
							so that any changes appear instantly */

}

void click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		selectedY = sizeY - 1 - (y * sizeY / glutGet(GLUT_WINDOW_HEIGHT));
		selectedX = x * sizeX / glutGet(GLUT_WINDOW_WIDTH);
	}
}

void assignColors(float color1[3], float color2[3], float color3[3], float color4[3])
{

	color1[0] = rand() % 2;
	color1[1] = rand() % 2;
	color1[2] = rand() % 2;
	color2[0] = rand() % 2;
	color2[1] = rand() % 2;
	color2[2] = rand() % 2;
	color3[0] = rand() % 2;
	color3[1] = rand() % 2;
	color3[2] = rand() % 2;
	color4[0] = rand() % 2;
	color4[1] = rand() % 2;
	color4[2] = rand() % 2;

	if (compareColors(color1, color2) || compareColors(color1, color3) || compareColors(color1, color4))
	{
		assignColors(color1, color2, color3, color4);
	}
	if (compareColors(color2, color3) || compareColors(color2, color4))
	{
		assignColors(color1, color2, color3, color4);
	}
	if (compareColors(color3, color4))
	{
		assignColors(color1, color2, color3, color4);
	}

}

void createGame(float board[sizeY][sizeX][3], float boardSolved[sizeY][sizeX][3], float color1[3], float color2[3], float color3[3], float color4[3])
{
	assignColors(color1, color2, color3, color4);

	initBoard(board, color1, color2, color3, color4);
	initBoard(boardSolved, color1, color2, color3, color4);
}

int compareColors(float color1[3], float color2[3])
{
	if (color1[0] == color2[0] && color1[1] == color2[1] && color1[2] == color2[2])
		return 1;
	return 0;
}

void displayInstructions()
{
	printf("Hello, welcome to Color Puzzle. This is a 2D rubik's cube-esque puzzle game based on organizing colors.\n");
	printf("After these instructions, you will be prompted to scramble the board.\n");
	printf("The goal of the game is to unscramble the colors by organizing them into the correct location.\n");
	printf("The controls are:\n");
	printf("Click a colored tile to control it.\n");
	printf("Use WASD to make it move up, left, down, and right\n");
	printf("Press 'r' to restart with a new board.\n");
	printf("The colors will wrap around to the other side of the board. However, the edge colors stay in place for reference.\n");
	printf("The game will end when you completely organize all the colors.");
	printf("The console will say when you have won.\n");
}