#include <stdio.h>
#include <locale.h>
#include <math.h>

//5.Дана целочисленная прямоугольная матрица.
// Определить количество строк, не содержащих ни одного нулевого элемента;
// максимальное из чисел, встречающихся в заданной матрице более одного раза.
//35.В матрице 6х8 заданной с клавиатуры пользователем,
// определить элементы (их позицию), которые являются одновременно минимальными в строке и столбце.
// Вывести координаты данных значений.

const int N = 20;

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

void getArrayD(int arr[N][N], int n, int m) {
	for (int i = 0; i < n; i++) {
		printf("Строка %d: \n", i + 1);
		getArray(arr[i], m);
	}
}

void printArrayD(int arr[N][N], int n, int m) {
	printf("Массив: \n");
	for (int i = 0; i < n; i++) {
		printArray(arr[i], m);
	}
	printf("\n\n");
}

int find(int arr[], int n, int a) {
	int count = 0;

	for (int i = 0; i < n; i++) {
		if (arr[i] == a) {
			count++;
		}
	}

	return count;
}

int findMax(int arr[N][N], int n, int m) {
	int max = arr[0][0];
	int count = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] > max) {
				max = arr[i][j];
				count = 1;
			}
			else if (arr[i][j] == max) {
				count++;
			}
		}
	}

	if (count > 1) {
		return max;
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (arr[i][j] == max) {
					arr[i][j] = -INFINITY; 
				}
			}
		}

		return findMax(arr, n, m);
	}
}

void ex5() {
	int n = 6, m = 8;
	printf("Введите размерность массива m * n: \n");
	printf("Количество строк: ");
	scanf_s("%d", &n);
	printf("Количество столбцов: ");
	scanf_s("%d", &m);

	int arr[N][N];
		/*= {
		{9,		19,		11,		-19,	17,		-6,		4,		-11},
		{12,	0,		18,		-5,		-3,		-19,	7,		-1},
		{15,	3,		18,		-2,		13,		-8,		14,		5},
		{12,	2,		3,		3,		-5,		0,		7,		-14},
		{-12,	-19,	-20,	12,		18,		12,		20,		1},
		{-13,	-18,	1,		6,		15,		3,		-10,	4}
		};*/
	getArrayD(arr, n, m);
	printf("\n");
	printArrayD(arr, n, m);

	//1
	int countNull = 0;
	for (int i = 0; i < n; i++) {
		if (find(arr[i], m, 0) == 0) {
			countNull++;
		}
	}
	printf("Количество строк, не содержащих ни одного нулевого элемента: %d\n", countNull);

	//2
	printf("Максимальное из чисел, встречающихся в заданной матрице более одного раза: %d\n", findMax(arr, n, m));
}

int findMin(int arr[], int n) {
	int min = arr[0];

	for (int i = 1; i < n; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}

	return min;
}

void ex35() {
	const int n = 6, m = 8;
	int arr[N][N];
	printf("Введите массив размерностью 6х8: \n");
	getArrayD(arr, n, m);
	printf("\n");
	printArrayD(arr, n, m);

	/*int arr[6][8]
		= {
		{9,		19,		11,		-19,	17,		-6,		4,		-11},
		{12,	0,		18,		-5,		-3,		-19,	7,		-1},
		{15,	3,		18,		-2,		13,		-8,		14,		5},
		{12,	2,		3,		3,		-5,		0,		7,		-14},
		{-12,	-19,	-20,	12,		18,		12,		20,		1},
		{-13,	-18,	1,		6,		15,		3,		-10,	4}
		};*/

	//1
	int minInStr[n], minInStb[m];

	for (int i = 0; i < n; i++) {
		minInStr[i] = findMin(arr[i], m);
	}

	for (int i = 0; i < m; i++) {
		int stb[n];
		for (int j = 0; j < n; j++) {
			stb[j] = arr[j][i];
		}

		minInStb[i] = findMin(stb, n);
	}

	printf("Элементы, которые являются минимальными одновременно в строке и столбце:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == minInStr[i] && arr[i][j] == minInStb[j]) {
				printf("Элемент %d на позиции [%d, %d]\n", arr[i][j], i+1, j+1);
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "rus");

	ex5();
	printf("\n\n");
	ex35();
}