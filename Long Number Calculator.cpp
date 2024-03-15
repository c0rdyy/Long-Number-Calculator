#include <stdio.h>
#include <locale.h>
#include "Funcs.h"

int main()
{
	setlocale(LC_ALL, "Ru");

	int t, task;

	printf("<=================================================>\n\n");
	printf("|  Добро пожаловать в калькулятор длинных чисел!  |\n\n");
	printf("<=================================================>\n\n");

	do
	{
		printf("<< Запустить калькулятор? >>\n 1 - Да\n 2 - Нет\n>> ");
		scanf_s("%d", &t);

		if (t != 2 && t != 1)
		{
			printf("Ошибка ввода!\n");
		}

		switch (t)
		{
		case 1:

			printf("\n<< Меню выбора операций >>\n 1 - Сложение\n 2 - Вычитание\n 3 - Умножение\n 4 - Деление\n");

			do
			{
				printf(">> ");
				scanf_s("%d", &task);

				if (task < 1 || task > 4)
				{
					printf("Ошибка ввода!\n");
				}

				switch (task)
				{
				case 1:
					break;
				default:
					break;
				}

			} while (task < 1 || task > 4);

			break;
		case 2:
			printf("Завершение программы!\n");
			break;
		default:
			printf("Ошибка!\n");
			break;
		}

	} while (t != 2);
	
	return 0;
}
