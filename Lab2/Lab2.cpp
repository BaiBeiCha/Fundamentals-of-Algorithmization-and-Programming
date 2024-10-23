#include<stdio.h>
#include<locale.h>

/*1. Определить, является ли треугольник со сторонами a, b и c равносторонним
  2. По номеру месяца напечатать его название.
  определить вид треугольника*/

void ex1() 
{
    float a, b, c;

    printf("Введите стороны треугольника:\n");
    scanf_s("%f%f%f", &a, &b, &c);

    if (a > b + c || b > a + c || c > a + b) 
    {
        printf("Треугольник не существует");
    }
    else 
    {
        printf("Треугольник - ");

        if (a == b && a == c) 
        {
            printf("равносторонний ");
        }
    else if((a == b && a != c) || (a == c && a != b) || (b == c && b != a))
        {
            printf("равнобедренный ");
        }

        float cos;

        if (a > b && a > c) 
        {
            cos = (b * b + c * c - a * a) / 2 * b * c;
        }
        else if (b > c && b > a) 
        {
            cos = (a * a + c * c - b * b) / 2 * a * c;
        }
        else if (c > a && c > b) {
            cos = (a * a + b * b - c * c) / 2 * a * b;
        }
        else if (a == b && a > c) 
        {
            cos = (b * b + c * c - a * a) / 2 * b * c;
        }
        else if (b == c && b > a) 
        {
            cos = (a * a + c * c - b * b) / 2 * a * c;
        }
        else if (c == a && c > b) 
        {
            cos = (a * a + b * b - c * c) / 2 * a * b;
        }
        else if (a == b && b == c) 
        {
            cos = 1;
        }

        if (cos == 0) 
        {
            printf("прямоугольный");
        }
        else if (cos < 0) 
        {
            printf("тупоугольный");
        }
        else 
        {
            printf("остроугольный");
        }
    }    
}

void ex2() 
{
    int num;

    printf("Введите номер месяца: ");
    scanf_s("%d", &num);

    switch (num)
    {
    default:
        printf("Неверный номер месяца!");
        break;

    case 1:
        printf("Январь");
        break;

    case 2:
        printf("Февраль");
        break;

    case 3:
        printf("Март");
        break;

    case 4:
        printf("Апрель!");
        break;

    case 5:
        printf("Май");
        break;

    case 6:
        printf("Июнь");
        break;

    case 7:
        printf("Июль");
        break;

    case 8:
        printf("Август");
        break;

    case 9:
        printf("Сентябрь");
        break;

    case 10:
        printf("Октябрь");
        break;

    case 11:
        printf("Ноябрь");
        break;

    case 12:
        printf("Декабрь");
        break;
    }
}

int main()
{
    setlocale(LC_CTYPE, "");

    ex1();
    printf("\n");
    ex2();
}