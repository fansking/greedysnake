#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#define Height 600
#define Width 800
using namespace std;
int foox = (rand() % 23 + 1)*2;
int fooy = (rand() % 23 + 1) * 2;
int food_x, food_y;
int direction=4;
IMAGE img_1,img_2;

struct snake {
	int position_x;
	int position_y;
	struct snake* next;
}; typedef struct snake SNA;
SNA* CreatLinker(int len)
{
	SNA *pH = new SNA();
	pH->next = NULL;
	SNA *pT = pH;
	for (int i = 0; i < len; i++)
	{
		SNA *pX = new SNA();
		pX->position_x = 300- i * 20;
		pX->position_y = 300 ;
		pT->next = pX;
		pT = pT->next;
		pT->next = NULL;
	}
	return pH;
}
void DeleteLinker(SNA *pH)
{
	while (NULL != pH->next)
	{
		SNA *pT = pH;
		pH = pH->next;
		delete pT;
	}
}

void Grow(SNA *pH)
{
	SNA *pT = pH->next;
	int m, n;
	while (NULL != pT->next)
	{
		pT = pT->next;
		m = pT->position_x + 20;
		n = pT->position_y + 20;
	}
	SNA* pX = new SNA();
	pX->position_x = m;
	pX->position_y = n;
	pT->next = pX;
	pX->next = NULL;
}
int LenOfSnake(SNA *pH)
{
	SNA *pT = pH->next;
	int len=0;
	while (NULL != pT)
	{
		++len;
		pT = pT->next;
	}
	return len;
}
int checkbump(SNA *pH)
{
	SNA *pT = pH->next;
	int m = LenOfSnake(pH);
	int x = pT->position_x;
	int y = pT->position_y;
	if ((x <=20) || (x>=580) || (y<=20) || (y >=580))
		return 1;
	for (int i = 0; i < m-1; i++)
	{
		pT = pT->next;
		if (x == pT->position_x && y == pT->position_y)
			return 1;
	}
	return 0;
}
int checkeat(SNA *pH)
{
	SNA *pT = pH->next;
	int x = pT->position_x;
	int y = pT->position_y;
	float distance = (x - food_x)*(x - food_x) + (y - food_y)*(y - food_y);
	if (distance<400)
		return 1;
	return 0;
}
void PrintSnake(SNA *pH)
{
	SNA *pT = pH->next;
	setcolor(BLACK);
	setfillcolor(BLACK);
	for (int i = 0; i < LenOfSnake(pH); i++)
	{
		fillcircle(pT->position_x, pT->position_y, 10);
		pT = pT->next;
	}
}
void PrintFood()
{
	setcolor(RED);
	setfillcolor(RED);
	fillcircle(food_x, food_y,10);
}
void move(SNA *pH)
{
	SNA *pB = pH;
	SNA *pT = pH->next;
	int num = LenOfSnake(pH);
	for (int i = 0; i < num-1; i++)
	{
		pB = pH;
		pT = pH->next;
		for (int j = 0; j < num - i-1; j++)
		{
			pB = pB->next;
			pT = pT->next;
		}
		pT->position_x = pB->position_x;
		pT->position_y = pB->position_y;
	}
	pT = pH->next;
	switch (direction)
	{
	case 1:pT->position_y = pT->position_y - 20; break;
	case 2:pT->position_y = pT->position_y + 20; break;
	case 3:pT->position_x = pT->position_x - 20; break;
	case 4:pT->position_x = pT->position_x + 20; break;
	}

}
void show()
{
	setbkcolor(WHITE);
	cleardevice();
	loadimage(&img_1, "F:\\¼¼ÄÜ\\1.jpg",600,600);
	putimage(0, 0, &img_1);
	setlinestyle(PS_SOLID, 2);
	setcolor(BLACK);
	line(10, 10, 10, 590);
	line(10, 10, 590, 10);
	line(10, 590, 590, 590);
	line(590, 10, 590, 590);
}
void updatewithoutinput(SNA *pH)
{
	SNA *pT = pH->next;
	PrintFood();
	move(pH);
	PrintSnake(pH);
	food_x = 10 * foox;
	food_y = 10 * fooy;
	if (checkeat(pH))
	{
		foox = (rand() % 23 + 1) * 2;
		fooy = (rand() % 23 + 1) * 2;
		Grow(pH);
	}
	if (checkbump(pH))
	{
		outtextxy(700, 300, "ÓÎÏ·Ê§°Ü");
		FlushBatchDraw();
		_getch();
		
	}
	Sleep(225);

}
void updatewithinput(SNA *pH)
{
	char input;
	SNA *pT = pH->next;
	if (_kbhit())
	{
		input = _getch();
		if (input == 'w')
			direction = 1;
		else if (input == 's')
			direction = 2;
		else if (input == 'a')
			direction = 3;
		else if (input == 'd')
			direction = 4;
	}
	
}
int main()
{
	initgraph(Width, Height);
	SNA *pH = CreatLinker(3);
	BeginBatchDraw();
	while (1)
	{
		show();
		updatewithoutinput(pH);
		updatewithinput(pH);
		FlushBatchDraw();
	}
	EndBatchDraw();
	DeleteLinker(pH);
	return 0;
}