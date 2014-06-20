#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

// размеры экрана
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500

// размеры массива для вывода на экран
#define SIZEX 25
#define SIZEY 20

// размер блока
#define BLOCKSIZE 30

int FillArray(int, int, int**); // заполняем массив
int DynamicToStatic(int stWorld[][SIZEY], int, int, int**);
int DrawScreen(int stWorld[][SIZEY]);
int DrawMap(int stWorld[][SIZEY]);
int DrawBlock(int, int, int, int, int);
int PrintArray(int stWorld[][SIZEY]);
int ClearMemory(int, int, int**); // очищаем память

// ============================= MAIN ================================
int main()
{
    initwindow(SCREEN_WIDTH,SCREEN_HEIGHT);
	// динамический массив
	int **dynWorld;
	int dynXM = 100;
	int dynYM = 20;
	// статический массив
	int stWorld[SIZEX][SIZEY];
	// задаем сдвиг по X (можно поиграть с этим числом для наглядности)
	int sdvig = 0;
	char chKey;
	int i;
	// инициализируем динамический массив
	dynWorld = (int **)malloc(sizeof(int *)*dynXM);
	for (i = 0; i<dynXM; i++)dynWorld[i] = (int *)malloc(sizeof(int)*dynYM);

	do{
        // заполняем массив
        FillArray(dynXM, dynYM, dynWorld);
        // передаем часть динамического массива в статический
        DynamicToStatic(stWorld, sdvig, dynYM, dynWorld);
        // выводим на экран статический массив
        DrawScreen(stWorld);
        PrintArray(stWorld);
        chKey = getch();
	}while(chKey!='q');

	// освобождаем память
	ClearMemory(dynXM, dynYM, dynWorld);
    closegraph();
	return 0;
}

// ============================= OTHER ================================

// заполняем массив
int FillArray(int XM, int YM, int **dynWorld)
{
	int i, j;

	for (j = 0; j<YM; j++){
		for (i = 0; i<XM; i++){
			dynWorld[i][j] = 1; // белые
		}
	}
	// элемент X4 Y3 будет равен 5
	dynWorld[4][3] = 0; // черный
	dynWorld[5][3] = 2; // зеленый

	//return *dynWorld;
	return 0;
}

// преобразуем динамический массив в статический
int DynamicToStatic(int stWorld[][SIZEY], int sdvig, int YM, int **dynWorld)
{
	int i, j;

	for (j = 0; j<YM; j++){
		for (i = sdvig; i<SIZEX + sdvig; i++){
			stWorld[i - sdvig][j] = dynWorld[i][j];
		}
	}

	return 0;
}

// выводим изображение на экран
int DrawScreen(int stWorld[][SIZEY])
{
    // обнуляем бэкграунд
    setfillstyle(1,BLACK);
    bar(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

    // рисуем верхнее меню
    /*
    setfillstyle(1,WHITE);
    outtext("INVENTORY: 0");
    moveto(0,15);
    outtext("MODE: WALK");
    */

    // рисуем карту
    DrawMap(stWorld);
    // рисуем человечка
    //DrawMan();


    // рисуем нижнее меню
    /*
    moveto(0,MAP_Y+MAP_HEIGHT+2);
    setfillstyle(1,WHITE);
    outtext("BOTTOM MENU");
    */

    return 0;
}

int DrawMap(int stWorld[][SIZEY])
{
	int i, j;
	int x1,y1,x2,y2;

	// выводим в цикле (работает, иногда глючит вывод - косяк graphics.h)
	for (j = 0; j<SIZEY; j++){
        y1=j*BLOCKSIZE;
        y2=y1+BLOCKSIZE;
		for (i = 0; i<SIZEX; i++){
            x1=i*BLOCKSIZE;
            x2=x1+BLOCKSIZE;
			DrawBlock(stWorld[i][j], x1,y1,x2,y2);
		}
	}

	return 0;
}

int DrawBlock(int blockType, int x1, int y1, int x2, int y2)
{
    if(blockType==0){
        setfillstyle(1,BLACK);
        bar(x1,y1,x2,y2);
    }else if(blockType==1){
        setfillstyle(1,WHITE);
        bar(x1,y1,x2,y2);
    }else if(blockType==2){
        setfillstyle(1,GREEN);
        bar(x1,y1,x2,y2);
    }

    return 0;
}

// печатаем массив
int PrintArray(int stWorld[][SIZEY])
{
	int i, j;
	for (j = 0; j<SIZEY; j++){
		for (i = 0; i<SIZEX; i++){
			printf("%d ", stWorld[i][j]);
		}
		printf("\n");
	}

	return 0;
}

// чистим память
int ClearMemory(int XM, int YM, int **dynWorld)
{
	int i;

	for (i = 0; i<XM; i++)free(dynWorld[i]);
	free((void *)dynWorld);

	return 0;
}
