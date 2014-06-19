#include <stdio.h>
#include <stdlib.h>

#define SIZEX 30// размеры массива для вывода на экран
#define SIZEY 20

int *FillArray(int, int, int**); // заполняет массив
int *ClearMemory(int, int, int**); // очищаем память

int main()
{

    // динамический массив
    int **dynWorld;
    int dynXM = 100; //30
	int dynYM = 20; //20
	// статический массив
	int stWorld[SIZEX][SIZEY];

	int sdvig=0;

	int i,j;
	// Выделяем память под адреса столбцов
	// важно сначала выделить под иксы, потом под игреки,
	// чтобы был вид [i][j], а не [j][i]
	dynWorld=(int **)malloc(sizeof(int *)*dynXM);
	// Выделяем память для iго столбца
	// пробегаемся по всем столбцам с нулевого до последнего
	// опираясь на кол-во элементов (y-ков)
	for(i=0;i<dynXM;i++)dynWorld[i]=(int *)malloc(sizeof(int)*dynYM);

	FillArray(dynXM, dynYM, dynWorld);

	// передаем часть динамического массива в статический
	// задаем сдвиг по X (можно поиграть с этим числом для наглядности)
	sdvig=4;

	for(j=0;j<dynYM;j++){
        for(i=sdvig;i<SIZEX+sdvig;i++){
            stWorld[i-sdvig][j]=dynWorld[i][j];
        }
	}

    // выводим на экран статический массив

	for(j=0;j<SIZEY;j++){
        for(i=0;i<SIZEX;i++){
            printf("%d ", stWorld[i][j]);
        }
        printf("\n");
	}

    // освобождаем память
    ClearMemory(dynXM, dynYM, dynWorld);

    return 0;
}

int *FillArray(int XM, int YM, int **dynWorld)
{
	int i,j;

	for(j=0;j<YM;j++){
        for(i=0;i<XM;i++){
            dynWorld[i][j]=0;
        }
	}
	// элемент X4 Y3 будет равен 5
	dynWorld[4][3]=5;

	return *dynWorld;
}

int *ClearMemory(int XM, int YM, int **dynWorld)
{
    int i;
    
    for(i=0;i<XM;i++)free(dynWorld[i]);
    free((void *)dynWorld);

    return 0;
}
