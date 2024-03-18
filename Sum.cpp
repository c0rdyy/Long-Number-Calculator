#include "Funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

void addNumbers(char* num1, char* num2, char* result)
{
    memset(result, '0', MAX);
    result[MAX - 1] = '\0';

    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int size;

    int mas1[MAX], mas2[MAX];

    if (len1 > len2)
    {
        size = len1;
    }
    else
    {
        size = len2;
    }

    for (int i = 0; i < len1; i++)
    {
        mas1[i] = num1[i] - '0';
    }

    mas1[len1] = '\0';

    for (int i = 0; i < len2; i++)
    {
        mas2[i] = num2[i] - '0';
    }

    mas2[len2] = '\0';

    for (int i = 0; i < size; i++)
    {
        if (i < len1)
        {
            result[MAX - i - 2] += mas1[len1 - i - 1];
        }
        if (i < len2)
        {
            result[MAX - i - 2] += mas2[len2 - i - 1];
        }
        result[MAX - i - 3] += (result[MAX - i - 2] - '0') / 10; // Учитываем перенос
        result[MAX - i - 2] = (result[MAX - i - 2] - '0') % 10 + '0'; // Записываем остаток
    }

    int first_digit_pos = 0;
    while (result[first_digit_pos] == '0') {
        first_digit_pos++;
    }

    // Вывод результата без лишних нулей
    printf("%s\n\n", result + first_digit_pos);
}