#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

//5.	В одномерном массиве, состоящем из n вещественных элементов, вычислить:
//-произведение элементов массива с четными номерами;
//-разность двух минимальных нечетных элементов массива.
//35.	Дана целочисленная прямоугольная матрица. Определить количество столбцов,
//содержащих хотя бы один нулевой элемент.

float* getArray(int length)
{
    float* array;

    if (!(array = (float*)malloc(length * sizeof(float))))
    {
        printf("Недостаточно памяти!");
        return 0;
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            printf("Элемент [%d]: ", i + 1);
            scanf_s("%f", (array + i));
        }

        return array;
    }
}

void printArray(float* array, int length) 
{
    for (int i = 0; i < length; i++)
    {
        printf("%f ", *(array + i));
    }
    printf("\n");
}

void ex5() {
    int length;
    float mult = 1, diff, *array, *min;

    printf("Введите размер массива: ");
    scanf_s("%d", &length);
    
    array = getArray(length);
    printf("\nМассив: \n");
    printArray(array, length);
    
    for (int i = 0; i < length; i++)
    {
        if ((i + 1) % 2 == 0) 
        {
            mult *= *(array + i);
        }
    }
    printf("\nПроизведение элементов массива с четными номерами: %f\n", mult);

    min = (float*)malloc(2 * sizeof(float));

    for (int i = 0; i < 2; i++)
    {
        *(min + i) = INFINITY;
    }

    for (int i = 0; i < length; i++)
    {
        if ((i + 1) % 2 != 0) 
        {
            if (*(min) > *(array + i))
            {
                *(min) = *(array + i);
            }

            if ((*(min + 1) > *(array + i)) && (*(array + i) > *(min)))
            {
                *(min + 1) = *(array + i);
            }
        }
    }
    printf("Минимальный нечетный элемент массива 1: %f\n", *(min));
    printf("Минимальный нечетный элемент массива 2: %f\n", *(min + 1));

    diff = *(min + 1) - *(min);
    free(min);
    free(array);

    printf("Разность двух минимальных нечетных элементов массива: %f", diff);
}

int** getMatrix(int n, int m)
{
    int** matrix;

    matrix = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
        *(matrix + i) = (int*)calloc(m, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        printf("Строка %d:\n", i + 1);
        for (int j = 0; j < m; j++)
        {
            printf("Элемент %d: ", j + 1);
            scanf_s("%d", *(matrix + i) + j);
        }
        printf("\n");
    }

    return matrix;
}

void printMatrix(int** matrix, int n, int m)
{
    printf("Матрица:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d\t", *(*(matrix + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

void ex35()
{
    int n, m, count = 0, **matrix;

    printf("Введите количество строк: ");
    scanf_s("%d", &n);
    printf("Введите количество столбцов: ");
    scanf_s("%d", &m);

    matrix = getMatrix(n, m);
    printMatrix(matrix, n, m);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++) 
        {
            if (*(*(matrix + j) + i) == 0) {
                count++;
                break;
            }
        }
    }

    free(matrix);
    printf("Количество столбцов, содержащих хотя бы один нулевой элемен: %d", count);
}

int main()
{
    setlocale(LC_ALL, "rus");

    ex5();
    printf("\n\n\n");
    ex35();
}
