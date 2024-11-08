#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

/*	Задание 1
Разработать программу с использованием файлов в соответствии с вариантом.
5.	Создать текстовый файл F1 не менее, чем из 10 строк и записать в него информацию.
Скопировать в файл F2 только четные строки из F1. 

	Задание 2
Сформировать бинарный файл из элементов, заданной в варианте структуры, 
распечатать его содержимое, выполнить добавление элементов в соответствии 
со своим вариантом и поиск по одному из параметров (например, по фамилии, 
по государственному номеру, по году рождения и т.д.). Формирование, печать, 
добавление, поиск элементов и выбор желаемого действия оформить в виде функций. 
Предусмотреть сообщения об ошибках при открытии файла и выполнении 
операций ввода/вывода.
5.	Структура «Читатель»: фамилия, имя, отчество; номер читательского билета; название книги; срок возврата.*/

//Структура «Читатель»: фамилия, имя, отчество; номер читательского билета; название книги; срок возврата.
const int nameLength = 50;
const int maxBooksAmount = 10;
const int maxReadersAmount = 50;
int currentReadersAmount = 0;
int currentReader = -1;

const char readersFilePath[] = "data\\readers.dat";

struct Date
{
	int day;
	int month;
	int year;
};

struct Book
{
	char bookTitle[nameLength];
	Date returnDate;
};

struct Reader
{
	int ID;
	char surname[nameLength];
	char name[nameLength];
	char patronymic[nameLength];
	int currentBooksAmount = 0;
	Book books[maxBooksAmount];
};

Reader readers[maxReadersAmount];

void passNullChar()
{
	char* nullChar = (char*)malloc(sizeof(char));
	gets_s(nullChar, 1);
	free(nullChar);
}

void printBookInfo(Book book)
{
	printf("Название: %s\nДата возврата: %d:%d:%d\n\n",
		book.bookTitle, book.returnDate.day, book.returnDate.month, book.returnDate.year);
}

void printReaderInfo(int i)
{
	printf("Читатель ID: %d\nФИО: %s %s %s\nКниги:\n",
		readers[i].ID, readers[i].surname, readers[i].name, readers[i].patronymic);
	for (int j = 0; j < readers[i].currentBooksAmount; j++)
	{
		printf("Книга No%d:\n", (j + 1));
		printBookInfo(readers[i].books[j]);
	}
}

void printReaders()
{
	printf("Читатели:\n");
	for (int i = 0; i < currentReadersAmount; i++)
	{
		printReaderInfo(i);

		if (i < currentReadersAmount - 1)
			printf("\n");
	}
}

void readReaders()
{
	FILE* file;
	if (fopen_s(&file, readersFilePath, "rb") != 0) {
		printf("Ошибка открытия файла\n");
		return;
	}

	fread(&currentReadersAmount, sizeof(int), 1, file);
	if (currentReadersAmount > maxReadersAmount) {
		printf("Ошибка: количество читателей превышает максимум!\n");
		fclose(file);
		return;
	}

	fread(readers, sizeof(Reader), currentReadersAmount, file);
	fclose(file);

	printf("Успешно считано!\n");
}

bool save()
{
	FILE* file;
	if (fopen_s(&file, readersFilePath, "wb") != 0) {
		printf("Ошибка открытия файла\n");
		return false;
	}

	fwrite(&currentReadersAmount, sizeof(int), 1, file);
	fwrite(readers, sizeof(Reader), currentReadersAmount, file);
	fclose(file);

	fclose(file);
	return true;
}

void setField(char* field, char* newfield)
{
	strcpy_s(field, strlen(newfield) + 1, newfield);
}

void getField(const char* message, char* buf, int length)
{
	printf("%s", message);
	fgets(buf, length, stdin);
	buf[strcspn(buf, "\n")] = 0;
}

Book getBook()
{
	Book newBook = {};

	getField("Введите название книги: ", newBook.bookTitle, nameLength);

	int d, m, y;
	printf("Введите дату в формате:\nдень месяц год:\n");
	scanf_s("%d%d%d", &newBook.returnDate.day,
		&newBook.returnDate.month,
		&newBook.returnDate.year);
	printf("\n");

	return newBook;
}

Reader getReader(int i)
{
	Reader reader;

	passNullChar();
	getField("Введите фамилию: ", reader.surname, nameLength);
	getField("Введите имя: ", reader.name, nameLength);
	getField("Введите отчество: ", reader.patronymic, nameLength);

	printf("Введите количество книг: ");
	scanf_s("%d", &reader.currentBooksAmount);

	while (reader.currentBooksAmount > maxBooksAmount)
	{
		printf("Количество книг превышает максимально возможное!\nВведите количество книг: ");
		scanf_s("%d", &reader.currentBooksAmount);
	}

	for (int i = 0; i < reader.currentBooksAmount; i++)
	{
		passNullChar();
		printf("Книга No%d\n", (i + 1));
		reader.books[i] = getBook();
		printf("\n");
	}

	reader.ID = i;
	return reader;
}

void getReadersArray()
{
	int amount;
	printf("Введите количество читателей: ");
	scanf_s("%d", &amount);

	if (amount < 1)
	{
		printf("Слишком мало читателей!\n");
		return;
	}
	if (amount <= maxReadersAmount)
	{
		for (int i = 0; i < amount; i++)
		{
			printf("Введите данные читателя %d:\n", i + 1);
			readers[i] = getReader(i + 1);
		}

		currentReadersAmount = amount;
	}
	else
	{
		printf("Слишком много читателей!\n");
	}

	save();
}

void addReadersArray()
{
	int amount;
	printf("Введите количество читателей: ");
	scanf_s("%d", &amount);

	if (amount + currentReadersAmount <= maxReadersAmount)
	{
		for (int i = currentReadersAmount; i < currentReadersAmount + amount; i++)
		{
			printf("Введите данные читателя %d:\n", i + 1);
			readers[i] = getReader(i + 1);
		}

		currentReadersAmount += amount;

		save();
	}
	else
	{
		printf("Слишком много читателей!\n");
	}
}

void sortReadersBySurname()
{
	for (int i = 0; i < currentReadersAmount - 1; i++) {
		for (int j = i + 1; j < currentReadersAmount; j++) {
			if ((strcoll(readers[i].surname, readers[j].surname) > 0)) {
				Reader temp = readers[i];
				readers[i] = readers[j];
				readers[j] = temp;
			}
		}
	}

	save();
}

void sortReadersByID()
{
	for (int i = 0; i < currentReadersAmount - 1; i++) {
		for (int j = i + 1; j < currentReadersAmount; j++) {
			if (readers[i].ID > readers[j].ID) {
				Reader temp = readers[i];
				readers[i] = readers[j];
				readers[j] = temp;
			}
		}
	}

	save();
}

int find(char* par)
{
	for (int i = 0; i < currentReadersAmount; i++)
	{
		if (strcmp(par, readers[i].name) == 0 ||
			strcmp(par, readers[i].surname) == 0 ||
			strcmp(par, readers[i].patronymic) == 0)
		{
			return i;
		}
	}

	return -1;
}

int find(int id)
{
	for (int i = 0; i < currentReadersAmount; i++)
	{
		if (readers[i].ID == id)
		{
			return i;
		}
	}

	return -1;
}

void editReader()
{
	int choice;
	printf("Выберите, что хотите изменить:\n");
	printf("1 - Изменение фамилии;\n");
	printf("2 - Изменение имени;\n");
	printf("3 - Изменение отчества;\n");
	printf("4 - Изменение книги;\n");
	printf("5 - Добавить книгу;");
	printf("6 - Отмена.\n");
	scanf_s("%d", &choice);
	passNullChar();

	switch (choice)
	{
	case 1:
		getField("Введите новую фамилию: ", readers[currentReader].surname, nameLength);
		break;
	case 2:
		getField("Введите новое имя: ", readers[currentReader].name, nameLength);
		break;
	case 3:
		getField("Введите новое отчество: ", readers[currentReader].patronymic, nameLength);
		break;
	case 4:
		int num;
		printf("Введите номер книги, которую хотите изменить: ");
		scanf_s("%d", &num);

		while (num > readers[currentReader].currentBooksAmount || num < 1)
		{
			printf("Такой книги не существует!\nВведите номер книги, которую хотите изменить: ");
			scanf_s("%d", &num);
		}
		num--;
		
		printf("Введите новые данные книги:\n");
		readers[currentReader].books[num] = getBook();
		break;
	case 5:
		if (readers[currentReader].currentBooksAmount < maxBooksAmount)
		{
			printf("Книга No%d:\n", (readers[currentReader].currentBooksAmount + 1));
			readers[currentReader].books[readers[currentReader].currentBooksAmount] = getBook();

			readers[currentReader].currentBooksAmount++;
		} 
		else
		{
			printf("Невозможно добавить книгу! Количество книг будет превышает максимально возможное!\n");
		}
		break;
	case 6:
		return;
	default:
		printf("Неверная команда!\n");
		break;
	}

	save();
}

void deleteReader()
{
	for (int i = currentReader; i < currentReadersAmount - 1; i++) {
		readers[i] = readers[i + 1];
	}

	currentReadersAmount--;
	save();
}

bool editMenu()
{
	printf("Текущий читатель:\n");
	printReaderInfo(currentReader);
	printf("\n");
	int choice;
	printf("Выберете действие: \n");
	printf("1 - Изменение заданной структуры;\n");
	printf("2 - Удаление структуры из массива;\n");
	printf("3 - Выход.\n");
	scanf_s("%d", &choice);

	switch (choice)
	{
	case 1:
		editReader();
		break;
	case 2:
		deleteReader();
		break;
	case 3:
		return false;
	default:
		printf("Неверная команда!\n");
		break;
	}
}

void editReaders()
{
	printf("Выберите параметр поиска:\n");
	printf("1 - Фамилия/имя/отчество/название книги\n");
	printf("2 - ID читателя\n");
	int command;
	scanf_s("%d", &command);
	passNullChar();

	switch (command)
	{
	case 1:
		char name[nameLength];
		getField("Введите фамилию/имя/отчество/название книги: ", name, nameLength);
		currentReader = find(name);
		break;
	case 2:
		printf("Введите ID читателя: ");
		int id;
		scanf_s("%d", &id);
		passNullChar();
		currentReader = find(id);
		break;
	default:
		printf("Неверная команда!\n");
		break;
	}

	if (currentReader == -1)
	{
		printf("Читатель не найден!\n");
		return;
	}

	while (true)
	{
		if (editMenu())
		{
			return;
		}

		printf("\n");
	}
}

/*Сформировать бинарный файл из элементов, заданной в варианте структуры, 
распечатать его содержимое, выполнить добавление элементов в соответствии 
со своим вариантом и поиск по одному из параметров (например, по фамилии, 
по государственному номеру, по году рождения и т.д.). Формирование, печать, 
добавление, поиск элементов и выбор желаемого действия оформить в виде функций. 
Предусмотреть сообщения об ошибках при открытии файла и выполнении 
операций ввода/вывода.*/
bool ex2Menu()
{
	int command;
	printf("Выберете действие: \n");
	printf("1 - Ввод массива структур;\n");
	printf("2 - Cортировка массива структур;\n");
	printf("3 - Поиск в массиве структур по заданному параметру;\n");
	printf("4 - Вывод на экран массива структур;\n");
	printf("5 - Сохранить;\n");
	printf("6 - Выход.\n");
	scanf_s("%d", &command);

	switch (command)
	{
	case 1:
		int choice;
		printf("Выберете действие: \n");
		printf("1 - Ввод массива структур;\n");
		printf("2 - Добавить массив структур.\n");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			int cm;
			printf("Выберете действие: \n");
			printf("1 - Ввод массива структур из консоли;\n");
			printf("2 - Ввод массива структур из файла.\n");
			scanf_s("%d", &cm);

			switch (cm) {
			case 1:
				getReadersArray();
				break;
			case 2:
				readReaders();
				printReaders();
				break;
			default:
				printf("Неверная команда!\n");
				break;
			}
			break;

		case 2:
			addReadersArray();
			break;

		default:
			printf("Неверная команда!\n");
			break;
		}
		break;
	case 2:
		int sortType;
		printf("Выберете тип сортировки:\n");
		printf("1 - Сортировка по ID;\n");
		printf("2 - Сортировка по фамилии.\n");
		scanf_s("%d", &sortType);

		switch (sortType) {
		case 1:
			sortReadersByID();
			break;
		case 2:
			sortReadersBySurname();
			printReaders();
			break;
		default:
			printf("Неверная команда!\n");
			break;
		}
		printReaders();
		break;
	case 3:
		editReaders();
		break;
	case 4:
		printReaders();
		break;
	case 5:
		if (save())
		{
			printf("Успешно сохранено!\n");
		}
		else
		{
			printf("Сохранить не удалось!\n");
		}
		break;
	case 6:
		return true;
	default:
		printf("Неверная комманда!\n");
	}

	return false;
}

/*Создать текстовый файл F1 не менее, чем из 10 строк и записать в него информацию.
Скопировать в файл F2 только четные строки из F1.*/
void ex1()
{
	const int lines = 20;
	const int lineLength = 100;

	FILE *f1, *f2;
	if ((fopen_s(&f1, "data\\f1.txt", "w+t") != 0) || (fopen_s(&f2, "data\\f2.txt", "w+t") != 0))
	{
		printf("Невозможно открыть файл \n");  
		return;
	}

	for (int i = 1; i <= lines; i++)
	{
		fprintf(f1, "Строка No%d\n", i);
	}

	rewind(f1);

	for (int i = 1; i <= lines; i ++)
	{
		char* line;

		if (!(line = (char*)malloc(lineLength * sizeof(char))))
		{
			printf("Недостаточно памяти!");
			return;
		}

		fgets(line, lineLength, f1);
		if (i % 2 == 0)
		{
			fprintf(f2, line);
		}

		free(line);
	}

	fclose(f1);
	fclose(f2);
}

bool mainMenu()
{
	int command;
	printf("Выберете действие: \n");
	printf("1 - Задание 1;\n");
	printf("2 - Задание 2;\n");
	printf("3 - Выход.\n");
	scanf_s("%d", &command);

	switch (command)
	{
	case 1:
		ex1();
		break;
	case 2:
		while (true)
		{
			if (ex2Menu())
			{
				return false;
			}

			printf("\n");
		}
		break;
	case 3:
		return true;
	default:
		printf("Неверная команда!\n");
		break;
	}
	return false;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true)
	{
		if (mainMenu())
		{
			return 0;
		}
	
		printf("\n");
	}
}