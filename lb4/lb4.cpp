// lb4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#define LETTER 1
#define NOT_THE_LETTER 0
#define MAXLEN 1000
#define MAXLEN2 100
char list_id[MAXLEN2][MAXLEN] = { "\0" }; //список идентификаторов
int dlina_slova = 0;
int proverka(char* ptr, int i) //проверяю на слова int float ...
{
	char type_name[4][MAXLEN] = { "int ","float ","double ","char " };
	char* ptr_const = type_name[i];
	while (*ptr_const != '\0') { // Проверяем, переменная ли это?
		if (*ptr != *ptr_const)
			return 0;
		ptr++; ptr_const++;
	}
	return 1;
}
int search_name(char* ptr) //проверяю была ли такая переменная
{
	int i = 0;
	int k = 0, k2 = 0; //счетчик пройденных букв в слове
	char* ptr_var = list_id[i];
	char name1[MAXLEN2];
	for (i = 0; i < MAXLEN2; i++)
		name1[i] = '\0';
	i = 0;
	while (*ptr != '\0') //записываем слово
	{
		if (*ptr == ' ' || *ptr == ',' || *ptr == '.' || *ptr == '\n' || *ptr == '(' ||
			*ptr == '[' || *ptr == ';' || *ptr == '=' || *ptr == '*' || *ptr == ')')
			break;
		name1[i++] = *ptr++;
		k++; //сколько надо будет пропустить
	}
	for (i = 0; i < MAXLEN; i++)
	{
		if (list_id[i][0] == '\0')
			break;
		if (strcmp(name1, list_id[i]) == 0) //проверка слова
		{
			return k;
		}
	}
	return -1;
}
int main(void)
{
	setlocale(LC_ALL, "RUS");
	HANDLE hStdout; // дескриптор консольного. HANDLE - это индекс, который	указывает на конкретный ресурс.
		// окна
		FILE* fp; // входной файл
	char line[MAXLEN]; // строчка из файла
	char word[MAXLEN]; // слово
	int flag_type = 0; //указан ли тип
	int pervaia_stroka = 1;
	int k = 0, k2 = 0;
	int flag_nom_var = -1; //буду проверять дошли до существующей	переменной или нет
		int flag; // флаг слово/разделитель
	int prev_flag; // предыдущее значение флага
	char* ptr; // указатель на строчку
	int crutch1 = 0;
	WORD foregroundColor0; // цвет слов
	WORD foregroundColor1; // цвет разделителей
	WORD foregroundColor2;
	WORD foregroundColor; // цвет символа
	WORD backgroundColor; // цвет фона
	WORD textAttribute; // атрибут текста - цвет
	// символа и фона
	// Получить стандартный дескриптор
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	// определить цвета символов, разделителей и фона
	foregroundColor0 = FOREGROUND_INTENSITY |
		FOREGROUND_RED;
	foregroundColor2 = FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN;
	foregroundColor1 = FOREGROUND_INTENSITY |
		FOREGROUND_BLUE;
	backgroundColor = 0 | 0 | 0 | 0;
	SetConsoleTextAttribute(hStdout, foregroundColor1 | backgroundColor);
	// открыть файл для чтения
	fp = fopen("t3.txt", "rt");
	if (fp == NULL)
		return 0; // ошибка при открытии файла
	while (!feof(fp))
	{
		ptr = fgets(line, MAXLEN, fp);
		if (ptr == NULL)
			break;
		flag = NOT_THE_LETTER;
		word[0] = '\0';
		if (pervaia_stroka == 0)
			flag_nom_var = search_name(ptr);
		pervaia_stroka = 0;
		while (*ptr != 0)
		{
			if (crutch1 == 1) //пишем разделитель. проходим итерацию до				конца.выводим что надо и потом проверяем новую букву.
				flag_nom_var = search_name(ptr);
			crutch1 = 0;
			if (*ptr == ' ' || *ptr == ',' || *ptr == '.' || *ptr == '\n' || *ptr == '(' ||
				*ptr == '[' || *ptr == ';' || *ptr == '=' || *ptr == '*' || *ptr == ')' || *ptr ==
				'\t')
			{
				flag = NOT_THE_LETTER;
				crutch1 = 1;
			}
			if (flag_nom_var > 0)
			{
				flag == LETTER;
				foregroundColor = foregroundColor0;
				textAttribute = foregroundColor | backgroundColor;
				SetConsoleTextAttribute(hStdout, textAttribute);
				printf("%c", *ptr++);
				flag_nom_var--;
			}
			else
			{
				if (flag == NOT_THE_LETTER)
				{
					if (list_id[k][0] != '\0')
						k++;
					k2 = 0;
					if (*ptr == 'i')
						if (proverka(ptr, 0) == 1)
						{
							k2 = 0;
							flag = LETTER;
							foregroundColor = foregroundColor2;
							textAttribute = foregroundColor |
								backgroundColor;
							SetConsoleTextAttribute(hStdout,
								textAttribute);
							printf("int ");
							ptr += 4;
						}
					if (*ptr == 'f')
						if (proverka(ptr, 1) == 1)
						{
							k2 = 0;
							flag = LETTER;
							foregroundColor = foregroundColor2;
							textAttribute = foregroundColor |
								backgroundColor;
							SetConsoleTextAttribute(hStdout,
								textAttribute);
							printf("float ");
							ptr += 6;
						}
					if (*ptr == 'd')
						if (proverka(ptr, 2) == 1)
						{
							k2 = 0;
							flag = LETTER;
							foregroundColor = foregroundColor2;
							textAttribute = foregroundColor |
								backgroundColor;
							SetConsoleTextAttribute(hStdout,
								textAttribute);
							printf("double ");
							ptr += 7;
						}
					if (*ptr == 'c')
						if (proverka(ptr, 3) == 1)
						{
							k2 = 0;
							flag = LETTER;
							foregroundColor = foregroundColor2;
							textAttribute = foregroundColor |
								backgroundColor;
							SetConsoleTextAttribute(hStdout,
								textAttribute);
							printf("char ");
							ptr += 5;
						}
						else
							flag = NOT_THE_LETTER;
				}
				if (flag == LETTER) //запоминаю переменные
					list_id[k][k2++] = *ptr;
				if (flag == LETTER)
				{
					foregroundColor = foregroundColor0;
					textAttribute = foregroundColor | backgroundColor;
					SetConsoleTextAttribute(hStdout, textAttribute);
					printf("%c", *ptr++); // вывести слово
				}
				if (flag == NOT_THE_LETTER)
				{
					foregroundColor = foregroundColor1;
					textAttribute = foregroundColor | backgroundColor;
					SetConsoleTextAttribute(hStdout, textAttribute);
					printf("%c", *ptr++); // вывести слово
				}
			}
		}
	}
	return 0;
}