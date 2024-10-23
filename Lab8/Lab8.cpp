/*Ввести массив структур в соответствии с вариантом.
Рассортировать массив в алфавитном порядке по первому полю, входящему в структуру.

В программе реализовать меню :
1)	Ввод массива структур;
2)	Сортировка массива структур;
3)	Поиск в массиве структур по заданному параметру;
4)	Изменение заданной структуры;
5)	Удаление структуры из массива;
6)	Вывод на экран массива структур;
7)	Выход.

5.	Структура «Читатель»: фамилия, имя, отчество; номер читательского билета; название книги; срок возврата.*/

#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

const int nameLength = 30;
const int maxReadersAmount = 50;
int currentReadersAmount = 0;
int currentReader = -1;

void passNullChar()
{
	char* nullChar = (char*)malloc(sizeof(char));
	gets_s(nullChar, 1);
	free(nullChar);
}

struct Date
{
	int day, month, year;

	void setDate(int d, int m, int y) {
		day = d;
		month = m;
		year = y;
	}

	void print() {
		printf("%d.%d.%d", day, month, year);
	}
};

Date getDate() 
{
	Date date;
	int d, m, y;

	printf("Введите дату в формате:\nдень месяц год:\n");
	scanf_s("%d%d%d", &d, &m, &y);

	date.setDate(d, m, y);

	return date;
}

struct Book
{
	char name[nameLength];
	struct Date returnDate;

	void setName(char bookName[nameLength])
	{
		strcpy_s(name, bookName);
	}

	void print()
	{
		printf("Название книги: %s\nсрок возврата: ", name);
		returnDate.print();
		printf("\n");
	}
};

Book getBook()
{
	Book book;

	char bookName[nameLength];
	printf("Введите имя книги: ");
	fgets(bookName, nameLength, stdin);
	bookName[strcspn(bookName, "\n")] = 0;
	book.setName(bookName);

	printf("Введите дату возврата книги:\n");
	Date date = getDate();
	book.returnDate = date;

	return book;
}

struct Reader
{
	char surname[nameLength], name[nameLength], pantronymic[nameLength];
	int ID;
	struct Book book;

	void setSurname(char sn[nameLength])
	{
		strcpy_s(surname, sn);
	}

	void setName(char n[nameLength])
	{
		strcpy_s(name, n);
	}

	void setPantronymic(char p[nameLength])
	{
		strcpy_s(pantronymic, p);
	}

	void print()
	{
		printf("ФИО: %s %s %s\n ID: %d\n", surname, name, pantronymic, ID);
		book.print();
	}

	void print(int i)
	{
		printf("Читатель %d:\n", i);
		print();
	}
};

Reader readers[maxReadersAmount];

char* getSurname() 
{
	char surname[nameLength];
	printf("Введите фамилию: ");
	fgets(surname, nameLength, stdin);
	surname[strcspn(surname, "\n")] = 0;
	return surname;
}

char* getName() 
{
	char name[nameLength];
	printf("Введите имя: ");
	fgets(name, nameLength, stdin);
	name[strcspn(name, "\n")] = 0;
	return name;
}

char* getPantronymic()
{
	char pantronymic[nameLength];
	printf("Введите отчество: ");
	fgets(pantronymic, nameLength, stdin);
	pantronymic[strcspn(pantronymic, "\n")] = 0;
	return pantronymic;
}

bool checkID(int id)
{
	for (int i = 0; i < currentReadersAmount; i++)
	{
		if (readers[i].ID == id)
		{
			return true;
		}
	}

	return false;
}

Reader getReader(int i)
{
	Reader reader;

	passNullChar();
	reader.setSurname(getSurname());
	reader.setName(getName());
	reader.setPantronymic(getPantronymic());
	reader.ID = i;

	Book readingBook = getBook();
	reader.book = readingBook;

	return reader;
}

void getReadersArray()
{
	int amount;
	printf("Введите количество читателей: ");
	scanf_s("%d", &amount);

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
	}
	else
	{
		printf("Слишком много читателей!\n");
	}
}

void sortReaders()
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
}

void printReaders()
{
	printf("Читатели:\n");
	for (int i = 0; i < currentReadersAmount; i++)
	{
		readers[i].print(i + 1);
	}
	printf("\n\n");
}

int find(char par[nameLength])
{
	for (int i = 0; i < currentReadersAmount; i++)
	{
		if (strcmp(par, readers[i].name) == 0 ||
			strcmp(par, readers[i].surname) == 0 ||
			strcmp(par, readers[i].pantronymic) == 0 ||
			strcmp(par, readers[i].book.name) == 0)
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

int find(Date date)
{
	for (int i = 0; i < currentReadersAmount; i++)
	{
		if (readers[i].book.returnDate.day == date.day &&
			readers[i].book.returnDate.month == date.month &&
			readers[i].book.returnDate.year == date.year)
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
	printf("4 - Изменение ID читателя;\n");
	printf("5 - Изменение названия книги;\n");
	printf("6 - Изменение срока возврата книги;\n");
	printf("7 - Отмена;\n");
	scanf_s("%d", &choice);
	passNullChar();

	switch (choice)
	{
	case 1:
		printf("Введите новую фамилию: ");
		char newSurname[nameLength];
		fgets(newSurname, nameLength, stdin);
		newSurname[strcspn(newSurname, "\n")] = 0;
		readers[currentReader].setSurname(newSurname);
		break;
	case 2:
		printf("Введите новое имя: ");
		char newName[nameLength];
		fgets(newName, nameLength, stdin);
		newName[strcspn(newName, "\n")] = 0;
		readers[currentReader].setName(newName);
		break;
	case 3:
		printf("Введите новое отчество: ");
		char newPant[nameLength];
		fgets(newPant, nameLength, stdin);
		newPant[strcspn(newPant, "\n")] = 0;
		readers[currentReader].setPantronymic(newPant);
		break;
	case 4:
		printf("Введите новое ID читателя: ");
		int id;
		scanf_s("%d", &id);
		readers[currentReader].ID = id;
		break;
	case 5:
		printf("Введите новое название книги: ");
		char newBookName[nameLength];
		fgets(newBookName, nameLength, stdin);
		newBookName[strcspn(newBookName, "\n")] = 0;
		readers[currentReader].book.setName(newBookName);
		break;
	case 6:
		readers[currentReader].book.returnDate = getDate();
		break;
	case 7:
		return;
	default:
		printf("Неверная команда!\n");
		break;
	}
}

void deleteReader()
{
	for (int i = currentReader; i < currentReadersAmount - 1; i++) {
		readers[i] = readers[i + 1];
	}

	currentReadersAmount--;
}

bool editMenu()
{
	printf("Текущий читатель:\n");
	readers[currentReader].print();
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
	printf("3 - Срок возврата\n");
	int command;
	scanf_s("%d", &command);
	passNullChar();

	switch (command)
	{
	case 1:
		printf("Введите фамилию/имя/отчество/название книги: ");
		char name[nameLength];
		fgets(name, nameLength, stdin);
		name[strcspn(name, "\n")] = 0;
		currentReader = find(name);
		break;
	case 2:
		printf("Введите ID читателя: ");
		int id;
		scanf_s("%d", &id);
		passNullChar();
		currentReader = find(id);
		break;
	case 3:
		currentReader = find(getDate());
		break;
	default:
		printf("Неверная команда!\n");
		break;
	}

	if (currentReader == -1)
	{
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

bool mainMenu()
{
	int command;
	printf("Выберете действие: \n");
	printf("1 - Ввод массива структур;\n");
	printf("2 - Cортировка массива структур;\n");
	printf("3 - Поиск в массиве структур по заданному параметру;\n");
	printf("4 - Вывод на экран массива структур;\n");
	printf("5 - Выход.\n");
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
			getReadersArray();
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
		sortReaders();
		printReaders();
		break;
	case 3:
		editReaders();
		break;
	case 4:
		printReaders();
		break;
	case 5:
		return true;
	default:
		printf("Неверная комманда!\n");
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