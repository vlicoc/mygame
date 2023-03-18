#define BACK_WIDE 640
#define BACK_HIGH 480

void inisnake();

void draw_snake();

void move();

void dir();

void draw_food();

void eatfood();

void creat_food();

void over();

typedef struct coor
{
	int x;
	int y;
}coor;

struct snake
{
	coor xy[500];
	int num;
	char way;
	int flag1 = 0;
};

struct FOOD
{
	coor fdxy;
	int flag = 0;
};


enum dir
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
};
