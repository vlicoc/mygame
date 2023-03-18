#include"snake.h"
#include<graphics.h>
#include<iostream>
#include<cstring>
#include<conio.h>
#include<ctime>

struct snake sn;
struct FOOD food;


int main()
{
	int a = 0;
	srand((unsigned int)time(NULL));
	inisnake();
	while (1)
	{	
		if (sn.flag1)
		{settextstyle(80, 10, _T("宋体"));
		outtextxy(BACK_WIDE, BACK_HIGH, _T("gameover"));
		Sleep(1000);
		break;
		}
		cleardevice();

		draw_snake();
		eatfood();
		if (!food.flag)
		{
			creat_food();
		}
		draw_food();
		move();
		Sleep(250);
		if (_kbhit())
		{
			dir();
		}
		over();
	}
	_getch();
	closegraph();
	return 0;
}

void inisnake()
{
	initgraph(BACK_WIDE, BACK_HIGH);

	setbkcolor(RGB(0, 155, 155));
	sn.xy[2].x = 0;
	sn.xy[2].y = 0;
	sn.xy[1].x = 10;
	sn.xy[1].y = 0;
	sn.xy[0].x = 20;
	sn.xy[0].y = 0;
	sn.num = 3;
	sn.way = right;
}

void draw_snake()
{
	for (int i = 0;i < sn.num;i++)
	{
		setlinecolor(BLUE);
		setfillcolor(YELLOW);
		fillrectangle(sn.xy[i].x, sn.xy[i].y, sn.xy[i].x + 10, sn.xy[i].y + 10);
	}
}

void move()
{
	for (int i = sn.num - 1;i > 0;i--)
	{
		sn.xy[i].x = sn.xy[i - 1].x;
		sn.xy[i].y = sn.xy[i - 1].y;
	}

	switch (sn.way)
	{
	case right:
		sn.xy[0].x += 10;break;
	case left:
		sn.xy[0].x -= 10;break;
	case up:
		sn.xy[0].y -= 10;break;
	case down:
		sn.xy[0].y += 10;break;
	default:
		break;
	}
}

void dir()
{
	char ch = 0;
	ch = _getch();
	switch (ch)
	{
	case 72:if (sn.way != down)
		sn.way = up;break;
	case 80:if (sn.way != up)
		sn.way = down;break;
	case 75:if (sn.way != right)
		sn.way = left;break;
	case 77:if (sn.way != left)
		sn.way = right;break;
	default:
		break;
	}
}

void creat_food()
{
	while (1)
	{
		int a = 0;
		food.fdxy.x = rand() % BACK_WIDE / 10 * 10;
		food.fdxy.y = rand() % BACK_HIGH / 10 * 10;
		for (int i = 0;i < sn.num;i++)
		{
			if ((food.fdxy.x == sn.xy[i].x) && (food.fdxy.y == sn.xy[i].y))
				a = 1;
		}
		if (!a)
			break;
	}
	food.flag = 1;
}

void draw_food()
{
	setlinecolor(WHITE);
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
}

void eatfood()
{
	if ((food.fdxy.x == sn.xy[0].x) && (food.fdxy.y == sn.xy[0].y))
	{
		food.flag = 0;
		sn.num++;
	}
}


void over()
{
	for (int i = 1;i < sn.num;i++)
	{
		if ((sn.xy[0].x == sn.xy[i].x) && (sn.xy[0].y == sn.xy[i].y))
		{
			sn.flag1 = 1;
		}
	}
	if ((sn.xy[0].y > BACK_HIGH) || (sn.xy[0].x > BACK_WIDE) ||(sn.xy[0].x < 0) || (sn.xy[0].y < 0))
	{
		sn.flag1 = 1;
	}
}