#include <stdio.h>
#include <locale.h>
#include "Funcs.h"
#include <stdlib.h>
#include <string.h>

#define MAX 1000
int main()
{
	setlocale(LC_ALL, "Ru");

	int t, task;

	char num1[MAX], num2[MAX];
	char result[MAX];

	printf("***************************************************\n");
	printf("*                                                 *\n");
	printf("*  Добро пожаловать в калькулятор длинных чисел!  *\n");
	printf("*                                                 *\n");
	printf("***************************************************\n\n\n");

	do
	{
		printf("**************************\n");
		printf("*                        *\n");
		printf("* Запустить калькулятор? *\n");
		printf("*                        *\n");
		printf("**************************\n");
		printf("*                        *\n");
		printf("*  1 - Да                *\n");
		printf("*  2 - Нет               *\n");
		printf("*                        *\n");
		printf("**************************\n");

		printf("\n>> ");
		scanf_s("%d", &t);
		while (getchar() != '\n'); // Очистка буфера

		printf("\n\n");

		if (t != 2 && t != 1)
		{
			printf("Ошибка ввода!\n");
		}

		switch (t)
		{
		case 1:
			
			printf("\n**************************");
			printf("\n*                        *");
			printf("\n*  Меню выбора операций  *");
			printf("\n*                        *");
			printf("\n**************************\n");
			printf("*                        *\n");
			printf("*  1 - Сложение          *\n");
			printf("*  2 - Вычитание         *\n");
			printf("*  3 - Умножение         *\n");
			printf("*  4 - Деление           *\n");
			printf("*                        *\n");
			printf("**************************\n");

			do
			{
				printf("\n>> ");
				scanf_s("%d", &task);
				while (getchar() != '\n');
				printf("\n\n");

				if (task < 1 || task > 4)
				{
					printf("Ошибка ввода!\n");
				}

				switch (task)
				{
				case 1:
					printf("Введите первое число: ");
					fgets(num1, sizeof(num1), stdin);
					num1[strcspn(num1, "\n")] = '\0'; // Удаление символа новой строки

					while (!isNumber(num1)) 
					{
						printf("Ошибка! Введите корректное число!\n");
						printf("Введите первое число: ");
						fgets(num1, sizeof(num1), stdin);
						num1[strcspn(num1, "\n")] = '\0'; 
					}

					printf("Введите второе число: ");
					fgets(num2, sizeof(num2), stdin);
					num2[strcspn(num2, "\n")] = '\0';

					while (!isNumber(num2))
					{
						printf("Ошибка! Введите корректное число!\n");
						printf("Введите второе число: ");
						fgets(num2, sizeof(num2), stdin);
						num2[strcspn(num2, "\n")] = '\0';
					}

					addNumbers(num1, num2, result);
					break;
				case 2:
					printf("Введите первое число: ");
					fgets(num1, sizeof(num1), stdin);
					num1[strcspn(num1, "\n")] = '\0'; 

					while (!isNumber(num1))
					{
						printf("Ошибка! Введите корректное число!\n");
						printf("Введите первое число: ");
						fgets(num1, sizeof(num1), stdin);
						num1[strcspn(num1, "\n")] = '\0';
					}

					printf("Введите второе число: ");
					fgets(num2, sizeof(num2), stdin);
					num2[strcspn(num2, "\n")] = '\0';

					while (!isNumber(num2))
					{
						printf("Ошибка! Введите корректное число!\n");
						printf("Введите второе число: ");
						fgets(num2, sizeof(num2), stdin);
						num2[strcspn(num2, "\n")] = '\0';
					}

					subtract(num1, num2, result);
					printf("Результат: %s\n\n", result);
					break;
				case 3:
					printf("Введите первое число: ");
					fgets(num1, sizeof(num1), stdin);
					num1[strcspn(num1, "\n")] = '\0';

					while (!isNumber(num1))
					{
						printf("Ошибка! Введите корректное число!\n");
						printf("Введите первое число: ");
						fgets(num1, sizeof(num1), stdin);
						num1[strcspn(num1, "\n")] = '\0';
					}

					printf("Введите второе число: ");
					fgets(num2, sizeof(num2), stdin);
					num2[strcspn(num2, "\n")] = '\0';

					while (!isNumber(num2))
					{
						printf("Ошибка! Введите корректное число!\n");
						printf("Введите второе число: ");
						fgets(num2, sizeof(num2), stdin);
						num2[strcspn(num2, "\n")] = '\0';
					}

					multiply(num1, num2, result);
					printf("Результат: %s\n\n", result);
					break;
				case 4:
					printf("Введите первое число: ");
					fgets(num1, sizeof(num1), stdin);
					num1[strcspn(num1, "\n")] = '\0';

					while (!isNumber(num1))
					{
						printf("Ошибка! Введите корректное число!\n");
						printf("Введите первое число: ");
						fgets(num1, sizeof(num1), stdin);
						num1[strcspn(num1, "\n")] = '\0';
					}

					printf("Введите второе число: ");
					fgets(num2, sizeof(num2), stdin);
					num2[strcspn(num2, "\n")] = '\0';

					while (!isNumber(num2))
					{
						printf("Ошибка! Введите корректное число!\n");
						printf("Введите второе число: ");
						fgets(num2, sizeof(num2), stdin);
						num2[strcspn(num2, "\n")] = '\0';
					}
				
					printf("Результат: %s\n\n", result);
					break;
				default:
					printf("Ошибка!\n");
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
