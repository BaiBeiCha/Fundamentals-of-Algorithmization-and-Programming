#include <stdio.h>
#include <string.h>
#include <locale.h>

//Разработать программу, которая выполняет действия из задания 1 (работа с матрицами) и задания 2 (работа со строками).
//В программе должно быть реализовано меню, каждое действие должно быть реализовано в отдельной функции.
//    Содержание меню :
//        1 – Выполнить задание 1;
//        2 – Выполнить задание 2;
//        3 – Выход.

//1.	Определить среднее арифметическое значение элементов матрицы А(8х8), лежащих на главной диагонали.
//2.	Написать программу, которая вводит строки текста в массив символов s[100], используя функцию gets.
//Выведите строки в верхнем и нижнем регистрах.



const int N = 8;
const int length = 100;

void getArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
    {
        printf("Элемент %d: ", i + 1);
        scanf_s("%d", &arr[i]);
    }

    printf("\n");
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void getMatrix(int arr[N][N], int n) {
    for (int i = 0; i < n; i++) {
        printf("Строка %d: \n", i + 1);
        getArray(arr[i], n);
    }
}

void printMatrix(int arr[N][N], int n) {
    printf("Массив: \n");
    for (int i = 0; i < n; i++) {
        printArray(arr[i], n);
    }
    printf("\n\n");
}

float arifmet(int arr[N][N], int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += arr[i][i];
    }

    return sum / n;
}

void ex1()
{
    int n, matrix[N][N];

    printf("Введите размерность квадратной матрицы n (не более 8 * 8!): ");
    scanf_s("%d", &n);

    getMatrix(matrix, n);
    printMatrix(matrix, n);

    printf("Среднее арифметическое элементов матрицы на главной диагонвли: %.2f\n\n", arifmet(matrix, n));
}

void ex2()
{
    printf("Введите текст (не более 99 символов!):\n");

    char s[length];
    gets_s(s, length);

    printf("Строка в верхнем регистре:\n");
    _strupr_s(s);
    puts(s);
    printf("Строка в нижнем регистре:\n");
    _strlwr_s(s);
    puts(s);
}

int main()
{
    int command;

    setlocale(LC_ALL, "rus");

    while (true) 
    {
        printf("Меню\n");
        printf("Список команд: \n1 – Выполнить задание 1;\n2 – Выполнить задание 2;\n3 – Выход.\n");
        printf("Введите команду: ");
        scanf_s("%d", &command);
        printf("\n");

        switch (command)
        {   
        case 1:
            ex1();
            printf("\n");
            break;

        case 2:
            char err[1];
            gets_s(err, 1);
            ex2();
            printf("\n");
            break;

        case 3:
            return 0;

        default:
            printf("Введена неверная команда!\n");
            break;
        }
    }
}
