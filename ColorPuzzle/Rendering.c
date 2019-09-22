#include <GL/glut.h>
#include "Rendering.h"
#include "game.h"
#include <math.h>

void displayBoard(float board[sizeY][sizeX][3])
{
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			float color[3];
			color[0] = board[y][x][0];
			color[1] = board[y][x][1];
			color[2] = board[y][x][2];
			float width = (float) XRES / sizeX;
			float height = (float)YRES / sizeY;
			displayRect(x*width, y*height, width, height, color[0], color[1], color[2]);
		}
	}
}

void displayRect(float x, float y, float w, float h, float red, float green, float blue)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glColor3f(red, green, blue);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(w, 0);
	glVertex2f(w, h);
	glVertex2f(0, h);
	glEnd();
	glPopMatrix();
}

void drawCursor(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * (float) i / (float)(num_segments);//get the current angle

		float x = r * cos(theta);//calculate the x component
		float y = r * sin(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
}