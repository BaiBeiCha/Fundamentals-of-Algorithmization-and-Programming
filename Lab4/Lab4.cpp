#include <stdio.h>
#include <locale.h>

/*1.Ввести массив вещественных чисел размером n, n вводиться с клавиатуры.
    Найти его наибольший и наименьший элементы и поменять их местами.
    Найти сумму и произведение всех элементов массива.
  2.В одномерном массиве, состоящем из n вещественных элементов, вычислить:
    - сумму отрицательных элементов массива;
    - произведение элементов массива, расположенных между максимальным и минимальным элементами.*/

float min, max;
int n, minI, maxI;

void getArray(float arr[])
{
    printf("Введите количество элементов массива: ");
    scanf_s("%d", &n);

    for (int i = 0; i < n; i++)                                  
    {
        printf("элемент No %d: ", i + 1);
        scanf_s("%f", &arr[i]);
    }

    printf("\n");
}

void printArray(float arr[])
{
    printf("массив: ");
    for (int i = 0; i < n; i++) 
    {
        printf("%.2f ", arr[i]);
    }
    printf("\n\n");
}

void getMinMax(float arr[])
{
    min = arr[0];
    minI = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min) {
            min = arr[i];
            minI = i;
        }
    }
    printf("Минимальный элемент массива = %.2f, его номер = %d\n", min, minI + 1);

    max = arr[0];
    maxI = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max) {
            max = arr[i];
            maxI = i;
        }
    }
    printf("Максимальный элемент массива = %.2f, его номер = %d\n\n", max, maxI + 1);
}

void ex1(float arr[])
{
    float sum = 0;
    float mult = 1;

    arr[minI] = max;
    arr[maxI] = min;

    printf("Новый ");
    printArray(arr);

    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    printf("Сумма всех элементов массива: %.2f\n", sum);

    for (int i = 0; i < n; i++)
    {
        mult *= arr[i];
    }
    printf("Произведение всех элементов массива: %.2f\n", mult);
}

void ex2(float arr[])
{
    float sum = 0;
    float mult = 1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            sum += arr[i];
        }
    }
    printf("Сумма всех отрицательных значений массива: %.2f\n", sum);

    if (minI > maxI) 
    {
        for (int i = maxI + 1; i < minI; i++)
        {
            mult *= arr[i];
        }
    } 
    else if (maxI > minI) 
    {
        for (int i = maxI + 1; i < minI; i++)
        {
            mult *= arr[i];
        }
    } 
    else 
    {
        printf("Все элементы массива = %.2f\n", arr[0]);
        mult = 0;
    }
    printf("Произведение элемнентов массива между максимальным и минимальным его элементами: %.2f\n", mult);
}

void main()
{
    setlocale(LC_ALL, "rus");

    float arr[100];
    getArray(arr);
    printArray(arr);

    getMinMax(arr);

    ex1(arr);
    printf("\n");
    ex2(arr);
}
