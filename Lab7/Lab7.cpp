#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>

//Разработать программу, которая выполняет действия из задания 1 (работа с матрицами) и задания 2 (работа со строками).
//В программе должно быть реализовано меню, каждое действие должно быть реализовано в отдельной функции.
//    Содержание меню :
//        1 – Выполнить задание 1;
//        2 – Выполнить задание 2;
//        3 – Выход.

//1.	Определить среднее арифметическое значение элементов матрицы А(8х8), лежащих на главной диагонали.
//2.	Написать программу, которая вводит строки текста в массив символов s[100], используя функцию gets.
//Выведите строки в верхнем и нижнем регистрах.

//Найти слова которые начинаются на букву с клавиатуры



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
    printf("Матрица: \n");
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

    printf("Среднее арифметическое элементов матрицы на главной диагонали: %.2f\n\n", arifmet(matrix, n));
}

void ex2()
{
    printf("Введите текст (не более 99 символов!):\n");

    char s[length];
    gets_s(s, length);

    printf("Строка в верхнем регистре:\n");
    _strupr_s(s, length);
    puts(s);
    printf("Строка в нижнем регистре:\n");
    _strlwr_s(s, length);
    puts(s);
}

void dop()
{
    const char* d = " ,.!?;:\n\t";

    printf("Введите текст: ");
    char s[length];
    gets_s(s, length);
    _strlwr_s(s, length);

    printf("Введите букву: ");
    char c;
    scanf_s("%c", &c, 1);

    char buffer[length];
    strncpy(buffer, s, length);
    buffer[length - 1] = '\0';

    int count = 0;
    char* word = strtok(buffer, d);
    printf("Слова, начинающиеся на букву %c:\n", c);
    while (word != NULL) {
        if (tolower(word[0]) == c) {
            count++;
            printf("%d) %s\n", count, word);
        }
        word = strtok(NULL, d);
    }

    if (count == 0)
    {
        printf("Слов, начинающихся на букву %c - нет!", c);
    }
}

int main()
{
    int command;

    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (true) 
    {
        printf("Меню\n");
        printf("Список команд: \n1 – Выполнить задание 1;\n2 – Выполнить задание 2;\n3 - доп\n4 – Выход.\n");
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
            char err1[1];
            gets_s(err1, 1);
            ex2();
            printf("\n");
            break;

        case 3:
            char err2[1];
            gets_s(err2, 1);
            dop();
            printf("\n");
            break;

        case 4:
            return 0;

        default:
            printf("Введена неверная команда!\n");
            break;
        }
    }
}
