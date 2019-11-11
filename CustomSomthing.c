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
typedef enum {STORY_PROLOGUE=1000, STORY_SCENE_001=1001, STORY_SCENE_002 = 1002} STORYTYPE;

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

int checkKeyEvent(void);
void readHeroStory(STORYTYPE type);

void checkSceneCode(SceneInfo *info, SCENE code);
void drawBax(BOXSIZE w, BOXSIZE h);
SCENE checkSceneChange(int key, SCENE curScene);

int main(void)
{
	system("mode con cols=41 lines=32");
	setCursorType(NOCURSOR);
	srand((int)time(NULL));

	SCENE changeScene = SC_NONE;
	SceneInfo scInfo;
	scInfo.code = changeScene;
	scInfo.sub_code = 0;
	// set first view page
	changeScene = SC_INTRO;

	while (TRUE)
	{
		checkSceneCode(&scInfo, changeScene);
		changeScene = checkSceneChange(checkKeyEvent(), scInfo.code);
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

SCENE checkSceneChange(int key, SCENE curScene)
{
	switch (curScene)
	{
	case SC_INTRO:
		if (key > 0) return SC_LOBBY;
	case SC_LOBBY:
	case SC_INGAME:
	case SC_RESULT:
		break;
	}
	return curScene;
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
		gotoxy(12, 5);
		printf(".용사여 일어나라.");
		gotoxy(8, 15);
		printf("PRESS ANY KEY TO CONTINUE");
		break;
	case SC_LOBBY:
		drawBax(BOX_W_40, BOX_H_30);
		readHeroStory(STORY_PROLOGUE);
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

void readHeroStory(STORYTYPE type)
{
	switch (type)
	{
	case STORY_PROLOGUE:
		gotoxy(3, 3);
		Sleep(1000);
		printf("아주 먼 옛날...");
		gotoxy(3, 4);
		Sleep(1000);
		printf("한 마을에 용사가 살았습니다.");
		gotoxy(3, 5);
		Sleep(1000);
		printf("하지만 그는 스스로를 잘 몰랐죠...");
		gotoxy(3, 6);
		Sleep(1000);
		printf("스스로를 그저 그런 나무꾼으로만");
		gotoxy(3, 7);
		Sleep(1000);
		printf("생각했습니다.");
		break;
	case STORY_SCENE_001:
	case STORY_SCENE_002:
		break;
	}
}

void drawBax(BOXSIZE w, BOXSIZE h)
{
	system("cls");
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

