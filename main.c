#include <stdio.h>
#include <stdlib.h>

// размеры массива для вывода на экран
#define SIZEX 25
#define SIZEY 20

int *FillArray(int, int, int**); // заполняет массив
int DynamicToStatic(int stWorld[][SIZEY], int, int, int**);
int PrintArray(int stWorld[][SIZEY]);
int *ClearMemory(int, int, int**); // очищаем память

// ============================= MAIN ================================
int main()
{
    // динамический массив
    int **dynWorld;
    int dynXM = 100;
    int dynYM = 20;
    // статический массив
    int stWorld[SIZEX][SIZEY];
    // задаем сдвиг по X (можно поиграть с этим числом для наглядности)
    int sdvig=70;
    int i;
    // инициализируем динамический массив
    dynWorld=(int **)malloc(sizeof(int *)*dynXM);
    for(i=0;i<dynXM;i++)dynWorld[i]=(int *)malloc(sizeof(int)*dynYM);
    // заполняем массив
    FillArray(dynXM, dynYM, dynWorld);
    // передаем часть динамического массива в статический
    DynamicToStatic(stWorld, sdvig, dynYM, dynWorld);
    // выводим на экран статический массив
    PrintArray(stWorld);
    // освобождаем память
    ClearMemory(dynXM, dynYM, dynWorld);
    return 0;
}

// ============================= OTHER ================================
int *FillArray(int XM, int YM, int **dynWorld)
{
    int i,j;

    for(j=0;j<YM;j++){
        for(i=0;i<XM;i++){
            dynWorld[i][j]=i;
        }
    }
    // элемент X4 Y3 будет равен 5
    dynWorld[4][3]=5;

    return *dynWorld;
}

int DynamicToStatic(int stWorld[][SIZEY], int sdvig, int YM, int **dynWorld)
{
    int i,j;

    for(j=0;j<YM;j++){
        for(i=sdvig;i<SIZEX+sdvig;i++){
            stWorld[i-sdvig][j]=dynWorld[i][j];
        }
    }
}

int PrintArray(int stWorld[][SIZEY])
{
    int i,j;
    for(j=0;j<SIZEY;j++){
            for(i=0;i<SIZEX;i++){
                printf("%d ", stWorld[i][j]);
            }
            printf("\n");
    }
}

int *ClearMemory(int XM, int YM, int **dynWorld)
{
    int i;

    for(i=0;i<XM;i++)free(dynWorld[i]);
    free((void *)dynWorld);

    return *dynWorld;
}
