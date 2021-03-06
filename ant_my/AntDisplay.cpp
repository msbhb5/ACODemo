#include "StdAfx.h"
#include "AntDisplay.h"
#include <stdio.h>	
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include <GL/glaux.h>
#include <iostream>
using namespace std;


/*
void keys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			xAnt = xAnt - 0.05;
			break;
		case GLUT_KEY_RIGHT:
			xAnt = xAnt + 0.05;
			break;
		case GLUT_KEY_UP:
			yAnt = yAnt + 0.05;
			break;
		case GLUT_KEY_DOWN:	
			yAnt = yAnt - 0.05;
			break;
	}
	glutPostRedisplay();
}*/
void CAntDisplay::DisplayInit(void)
{
	xAnt = -0.85;
	yAnt = 0.85;
}
void CAntDisplay::GetMovePath(int thread_seq)
{
	//int thread_seq = (int)thread;
	ant[thread_seq].Init();
	ant[thread_seq].AntInit();
	
	int i = 2000;
	while(i)
	{
	
		ant[thread_seq].AntSearchPath(thread_seq,ant[thread_seq].flag);		//蚂蚁探索路径
		ant[thread_seq].AntMove(ant[thread_seq].flag);				//蚂蚁一次移动

		/*x_queue.push(ant.x_temp);
		y_queue.push(ant.y_temp);*/
	
		i--;
	}
}
void CAntDisplay::Thread(void)
{ 
	//pthread_t ant_a, ant_b;

	//pthread_create(&ant_a, NULL, &GetMovePath, (void *)0);
	//pthread_create(&ant_b, NULL, &GetMovePath, (void *)0);
}

void CAntDisplay::DisplayAnt(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);

	DisplayMaze();
	glPointSize(5.0);
	glBegin(GL_POINTS);
		glColor3f(0.5,0.5,0.5 );
		glVertex2f(xAnt,yAnt);
	glEnd();
	glFlush();
	//glutPostRedisplay();
}

void CAntDisplay::DisplayMove(int thread_seq)
{
	//cout<<ant.move_path_x.front()<<" "<<ant.move_path_y.front()<<endl;

	DisplayAnt();										//迷宫中绘制一次蚂蚁

	//此处缺队列空的判定，暂时不用加，以后补上

	x = ant[thread_seq].move_path_x.front();
	y = ant[thread_seq].move_path_y.front();

	xAnt = -1 + (2 * y + 1) * MAZE_EACH/2;
	yAnt =  1 - (2 * x + 1) * MAZE_EACH/2;			//根据矩阵坐标计算蚂蚁的坐标

	//cout<<xAnt<<" "<<yAnt<<endl;

	ant[thread_seq].move_path_x.pop();
	ant[thread_seq].move_path_y.pop();	
	
	x_temp = ant[thread_seq].move_path_x.front();
	y_temp = ant[thread_seq].move_path_y.front();		//

	if(y_temp == y+1)				
	{
		xAnt = xAnt + 0.1f;
	}
	else if(y_temp == y-1)
	{
		xAnt = xAnt - 0.1f;
	}
	else if(x_temp == x+1)
	{
		yAnt = yAnt - 0.1f;
	}
	else if(x_temp == x-1)
	{
		yAnt = yAnt + 0.1f;
	}

	int n;
	n = 100 + rand()%600;
	Sleep(n);
			
}



