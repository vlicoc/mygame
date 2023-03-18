#include<graphics.h>
#include<conio.h>
#include<vector>
#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<cmath>
void draw_back();

void map();

void move();

bool ifgameover();

void input_picture();
//
const int w = 50;
//宽
const int WIDE=1000;
//高
const int HIGH = 800;

struct player//玩家
{
	int px=2*w;
	int py=w;
};
player play;

IMAGE img1;
IMAGE img2;
using namespace std;
int flag;
int BACK[WIDE/w+1][HIGH/ w+1] = { 0 };//0为墙，1为路
int main()
{	
	srand((unsigned)time(NULL));
	for(int i=0;i<WIDE;i+=w)//数组初始化
	for (int j = 0;j < HIGH;j+=w)
	{
		BACK[i / w][j / w] = 0;
	}
	initgraph(WIDE,HIGH);
	setbkcolor(WHITE);
	map();
	draw_back();
	input_picture();//导入图片
	while (1)
	{
		if (_kbhit())//输入键，对player进行移动。
		{
			clearrectangle(play.px, play.py, play.px + w, play.py + w);
			move();
		}

		if (ifgameover())//如果到达终点
		{
			putimage(0, 0, &img2);
			break;
		}
		else
			putimage(play.px, play.py, &img1);
	}
	_getch();
	closegraph();
	return 0;
}
//画地图
void draw_back()
{   
	for(int i=0;i<WIDE;i+=w)
	for (int j = 0;j < HIGH;j+=w)
	{
		if (BACK[i/w][j/w] == 0)
		{
			setfillcolor(BLACK);
			fillrectangle(i, j, i + w, j + w);
		}
		else{
			setfillcolor(WHITE);
			fillrectangle(i, j, i + w, j + w);
		}			
	}
}
//生成随机地图
void map()
{
	srand((unsigned)time(NULL));
	for (int i = 0;i < WIDE / w;i++)
		for (int j = 0;j < HIGH / w;j++)
		{
			BACK[i][0] = 1;
			BACK[0][j] = 1;
			BACK[WIDE / w - 1][j] = 1;
			BACK[i][HIGH / w - 1] = 1;
		}
	vector<int>X;
	vector<int>Y;

	X.push_back(2);
	Y.push_back(2);

	while (X.size())
	{
		int r = rand() % X.size();
		int x = X[r];
		int y = Y[r];

		int count = 0;
		for (int i = x - 1;i < x + 2;i++)
			for (int j = y - 1;j < y + 2;j++)
				if (abs(x - i) + abs(y - j) == 1 && BACK[i][j] > 0) {
					++count;
				}
		if (count <= 1) {
			BACK[x][y] = 1;
			for (int i = x - 1;i < x + 2;i++)
				for (int j = y - 1;j < y + 2;j++)
					if (abs(x - i) + abs(y - j) == 1 && BACK[i][j] == 0) {
						X.push_back(i);
						Y.push_back(j);
					}
		}

		X.erase(X.begin() + r);
		Y.erase(Y.begin() + r);
	}
	BACK[2][1] = 1;

	for (int i = WIDE / w - 3;i >= 0;i--)
		if (BACK[i][HIGH / w - 3] == 1) {
			BACK[i][HIGH / w - 2] = 1;
			break;
		}
}
//移动方向
void move()
{
	char a = 0;
	a = _getch();
	switch (a)
	{
	case 80:if (BACK[play.px / w][play.py / w + 1] == 1)//下
		play.py += w;break;
	case 72:if (BACK[play.px / w][play.py / w - 1] == 1)//上
		play.py -= w;break;
	case 77:if (BACK[play.px / w + 1][play.py / w] == 1)//右
		play.px += w;break;
	case 75:if (BACK[play.px / w - 1][play.py / w ] == 1)//左
		play.px -= w;break;
	}
}
//是否到达终点
bool ifgameover()
{
	if (play.py >= HIGH - w)
	{
		play.px =WIDE;
		play.py = HIGH;
		return true;
	}
	else
		return false;
}
//从文件中导入图片资源
void input_picture()
{
	loadimage(&img1, L"C:\\Users\\云深不知处\\Pictures\\player.jpg",w,w);
	loadimage(&img2, L"C:\\Users\\云深不知处\\Pictures\\reward.jpg", WIDE, HIGH);	
}
