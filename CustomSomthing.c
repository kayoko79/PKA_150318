#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define NONE -1

typedef enum {SC_NONE=0, SC_INTRO=100, SC_LOBBY=200, SC_INGAME=300, SC_RESULT=400} SCENE;
typedef enum {NOCURSOR, SOLIDCURSOR, NORMALCURSOR} CURSORTYPE;
typedef enum {BOX_W_40=40, BOX_W_30=30, BOX_W_20=20, BOX_H_10=10, BOX_H_20=20, BOX_H_30=30} BOXSIZE;

typedef struct { SCENE code; int sub_code; } SceneInfo;
typedef struct { BOXSIZE box_width; BOXSIZE box_height; } ViewerSize;

void gotoxy(short x, short y) 
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setCursorType(CURSORTYPE type)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 0;
	cursorInfo.bVisible = FALSE;
	switch (type)
	{
	case NOCURSOR:
		cursorInfo.dwSize = 1;
		cursorInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		cursorInfo.dwSize = 20;
		cursorInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void checkSceneCode(SceneInfo *info, SCENE code);
void drawBax(BOXSIZE w, BOXSIZE h);

int main(void)
{
	SCENE changeScene = SC_NONE;
	SceneInfo scInfo;
	scInfo.code = changeScene;
	scInfo.sub_code = 0;

	while (TRUE)
	{
		switch (checkKeyEvent())
		{
		case LEFT:	changeScene = SC_INTRO;		break;
		case RIGHT:	changeScene = SC_LOBBY;		break;
		case UP:	changeScene = SC_INGAME;	break;
		case DOWN:	changeScene = SC_RESULT;	break;
		case ESC:	changeScene = SC_NONE;		break;
		}
		checkSceneCode(&scInfo, changeScene);
	}
}


int checkKeyEvent(void)
{
	int key;
	switch (key = _getch())
	{
	case LEFT:
	case RIGHT:
	case UP:
	case DOWN:
	case ENTER:
		return key;
	}
	return NONE;
}

void checkSceneCode(SceneInfo *info, SCENE code)
{
	if (info->code == code)
		return;

	info->code = code;

	switch (info->code)
	{
	case SC_INTRO:
		drawBax(BOX_W_40, BOX_H_20);
		break;
	case SC_LOBBY:
		drawBax(BOX_W_20, BOX_H_20);
		break;
	case SC_INGAME:
		drawBax(BOX_W_30, BOX_H_10);
		break;
	case SC_RESULT:
		drawBax(BOX_W_20, BOX_H_30);
		break;
	case SC_NONE:
		drawBax(0, 0);
		break;
	}
}

void drawBax(BOXSIZE w, BOXSIZE h)
{
	gotoxy(0, 0);
	for (int i = 0; i < h; i++)
	{
		
		for (int j = 0; j < w; j++)
		{
			if (i == 0 || i == (h - 1))
				printf("-");
			else
			{
				if (j == 0 || j == (w - 1))
					printf("|");
				else
					printf(" ");
			}
		}
		printf("\n");
	}
}

