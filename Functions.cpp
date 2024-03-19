#define _CRT_SECURE_NO_WARNINGS

#include "Funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

// Проверка строки на числовое значение
int isNumber(char* num) 
{
    int flag = 1;
    int i = 0;

    if (num[0] == '-') 
    {
        if (num[1] == '\0')
        {
            flag = 0; // Строка содержит только минус, не число
        }
        i = 1;
    }

    for (; num[i] != '\0'; i++) 
    {
        if (num[i] < '0' || num[i] > '9') 
        {
            flag = 0; // Не число
        }
    }
    return flag; // Число
}

// Сумма
void addNumbers(char* num1, char* num2, char* result)
{
    memset(result, '0', MAX);
    result[MAX - 1] = '\0';

    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int size;

    int mas1[MAX] = { 0 }, mas2[MAX] = { 0 };

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

    for (int i = 0; i < len2; i++)
    {
        mas2[i] = num2[i] - '0';
    }

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
    while (result[first_digit_pos] == '0' && first_digit_pos < MAX - 2)
    {
        first_digit_pos++;
    }

    // Вывод результата без лишних нулей
    if (first_digit_pos == MAX - 1) // Все цифры нули
    {
        printf("Сумма: 0\n\n"); // Выводим один ноль
    }
    else
    {
        printf("Сумма: %s\n\n", result + first_digit_pos); // Вывод результата без лишних нулей
    }
}

// Вычитание
void subtract(char num1[], char num2[], char result[]) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int res[MAX] = { 0 };

    int negative = 0;
    if (len1 < len2 || (len1 == len2 && strcmp(num1, num2) < 0)) {
        subtract(num2, num1, result);
        negative = 1;
    }
    else {
        for (int i = 0; i < len1; i++) {
            res[i] = num1[len1 - i - 1] - '0';
        }

        for (int i = 0; i < len2; i++) {
            res[i] -= num2[len2 - i - 1] - '0';
        }

        for (int i = 0; i < MAX - 1; i++) {
            if (res[i] < 0) {
                res[i] += 10;
                res[i + 1]--;
            }
        }

        int index = MAX - 1;
        while (index >= 0 && res[index] == 0) {
            index--;
        }

        if (index == -1) {
            strcpy(result, "0");
        }
        else {
            for (int i = index; i >= 0; i--) {
                result[index - i] = res[i] + '0';
            }
            result[index + 1] = '\0';
        }
    }

    if (negative) {
        memmove(result + 1, result, strlen(result) + 1);
        result[0] = '-';
    }
}

// Переворачиваем строку
void reverseString(char* str) 
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) 
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Умножение
void multiply(char num1[], char num2[], char result[]) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int res[MAX] = { 0 };

    for (int i = 0; i < len1; i++) 
    {
        for (int j = 0; j < len2; j++) 
        {
            res[i + j] += (num1[len1 - i - 1] - '0') * (num2[len2 - j - 1] - '0');
        }
    }

    int carry = 0;
    for (int i = 0; i < MAX; i++) 
    {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }

    int index = MAX - 1;
    while (index >= 0 && res[index] == 0) 
    {
        index--;
    }

    if (index == -1) 
    {
        strcpy(result, "0");
    }
    else 
    {
        for (int i = index; i >= 0; i--) 
        {
            result[index - i] = res[i] + '0';
        }
        result[index + 1] = '\0';
    }
}