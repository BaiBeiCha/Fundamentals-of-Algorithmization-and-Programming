#include <stdio.h>
#include <locale.h>

/*
5.В одномерном массиве, состоящем из п целых элементов, вычислить: 
- номер максимального элемента массива; 
- произведение элементов массива, расположенных между первым и вторым нулевыми элементами.

36.Дан массив G целых чисел, содержащий 20 элементов.
Вычислить и вывести количество и сумму тех элементов, которые делятся на 2 и не делятся на 5.
*/

void getArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Элемент No %d: ", i + 1);
        scanf_s("%d", &arr[i]);
    }

    printf("\n");
}

void ex1() 
{
    int n;
    int arr[100];

    printf("Введите количество элементов массива: \n");
    scanf_s("%d", &n);

    getArray(arr, n);

    int maxValue = arr[0], maxI = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > maxValue)
        {
            maxValue = arr[i];
            maxI = i;
        }
    }

    printf("Номер максимального элемента массива: %d\n\n", maxI + 1);


    int z1 = -1, z2 = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0) 
        {
            if (z1 == -1) 
            {
                z1 = i;
            }
            else
            {
                z2 = i;
                break;
            }
        }
    }

    if (z1 > 0 && z2 > 0)
    {
        int mult = 1;

        for (int i = z1 + 1; i < z2; i++)
        {
            mult *= arr[i];
        }

        printf("Произведение элементов массива, между первым и вторым нулевыми элементами равно: %d\n\n", mult);
    }
    else
    {
        printf("Нулевых элементов нет или их тольок 1\n");
    }
}

void ex2() {
    int n;
    int G[20], sum = 0, count = 0;

    printf("Введите количество элементов массива (не более 20): \n");
    scanf_s("%d", &n);

    getArray(G, n);

    for (int i = 0; i < n; i++)
    {
        if (G[i] % 2 == 0 && G[i] % 5 != 0)
        {
            sum += G[i];
            count++;
        }
    }

    if (count > 0) {
        printf("Количество элементов, которые делятся на 2 и не делятся на 5: %d\n", count);
        printf("Их сумма: %d", sum);
    }
    else
    {
        printf("Элементов, которые делятся на 2 и не делятся на 5, нет!");
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    ex1();
    printf("\n\n");
    ex2();
}

