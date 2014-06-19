#include <stdio.h>
#include <stdlib.h>

int *massiv(int, int, int**);

int main()
{
    // инициализируем массив
    int **dynWorld;
    int dynXM = 10; //50
	int dynYM = 5; //20
	int i,j;
	// Выделяем память под адреса столбцов
	// важно сначала выделить под иксы, потом под игреки,
	// чтобы был вид [i][j], а не [j][i]
	dynWorld=(int **)malloc(sizeof(int *)*dynXM);
	// Выделяем память для iго столбца
	// пробегаемся по всем столбцам с нулевого до последнего
	// опираясь на кол-во элементов (y-ков)
	for(i=0;i<dynXM;i++)dynWorld[i]=(int *)malloc(sizeof(int)*dynYM);

	massiv(dynXM, dynYM, dynWorld);

    // выводим на экран
	for(j=0;j<dynYM;j++){
        for(i=0;i<dynXM;i++){
            printf("%d ", dynWorld[i][j]);
        }
        printf("\n");
	}

    // освобождаем память
    for(i=0;i<dynXM;i++)free(dynWorld[i]);
    free((void *)dynWorld);

    return 0;
}

int *massiv(int XM, int YM, int **dynWorld){

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
