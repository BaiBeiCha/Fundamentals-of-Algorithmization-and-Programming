#include<stdio.h>
#include<locale.h> 

/*������ ������ � ������ ��������. 
����� ������� ������� �����������, ������� ������ ����������� � ����� ��������.
��������� ������� � ��������� �� ���� ������ ����� �������.*/

void main()
{
	setlocale(LC_CTYPE, "");

	float h, r, sideS, fullS, V;
	
	printf("������� ������ ��������: ");
	scanf_s("%f", &h);

	printf("������� ������ ��������: ");
	scanf_s("%f", &r);

	sideS = 2 * r * h * 3.14;
	fullS = sideS + 2 * 3.14 * r * r;
	V = 3.14 * r * r * h;

	printf("\n");
	printf("������� ������� ����������� �������� �����: %.2f\n", sideS);
	printf("������� ������ ����������� �������� �����: %.2f\n", fullS);
	printf("����� �������� �����: %.2f\n", V);
}
