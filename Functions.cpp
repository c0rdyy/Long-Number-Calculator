#define _CRT_SECURE_NO_WARNINGS

#include "Funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1024

// Проверка строки на число
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

bool isNegative(const char* num)
{
    return num[0] == '-';
}

// Сложение
void addPositiveNumbers(char* num1, char* num2, char* result)
{
    memset(result, '0', MAX);
    result[MAX - 1] = '\0';

    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int mas1[MAX] = { 0 }, mas2[MAX] = { 0 };

    // Переворачивание числа
    for (int i = 0; i < len1; i++) 
    {
        mas1[len1 - i - 1] = num1[i] - '0';
    }

    for (int i = 0; i < len2; i++) 
    {
        mas2[len2 - i - 1] = num2[i] - '0';
    }

    int carry = 0; // Перенос из предыдущего разряда
    int size;

    if (len1 > len2)
    {
        size = len1;
    }
    else
    {
        size = len2;
    }

    for (int i = 0; i < size; i++) 
    {
        int sum = carry + mas1[i] + mas2[i];
        result[MAX - i - 2] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry) 
    {
        result[MAX - size - 2] = carry + '0';
    }

    // Удаление лишних нулей
    int first_digit_pos = 0;
    while (result[first_digit_pos] == '0' && first_digit_pos < MAX - 1) 
    {
        first_digit_pos++;
    }

    // Сдвиг результата в начало массива
    if (first_digit_pos > 0) 
    {
        memmove(result, result + first_digit_pos, MAX - first_digit_pos);
    }
}

void addNumbers(char* num1, char* num2, char* result)
{
    bool isNum1Negative = isNegative(num1);
    bool isNum2Negative = isNegative(num2);

    char tempNum1[MAX + 1], tempNum2[MAX + 1];

    // Удаление минуса
    if (isNum1Negative)
    {
        strcpy(tempNum1, num1 + 1);
    }
    else
    {
        strcpy(tempNum1, num1);
    }

    if (isNum2Negative)
    {
        strcpy(tempNum2, num2 + 1);
    }
    else
    {
        strcpy(tempNum2, num2);
    }

    if (!isNum1Negative && !isNum2Negative) 
    {
        // Оба числа положительные
        addPositiveNumbers(tempNum1, tempNum2, result);
    }
    else if (isNum1Negative && isNum2Negative) 
    {
        // Оба числа отрицательные
        addPositiveNumbers(tempNum1, tempNum2, result);
        memmove(result + 1, result, strlen(result) + 1);
        result[0] = '-';
    }
    else 
    {
        // Числа имеют разные знаки
        int cmpResult = compare_strings(tempNum1, tempNum2);
        if ((cmpResult > 0 && !isNum1Negative) || (cmpResult < 0 && isNum1Negative)) 
        {
            subtract(tempNum1, tempNum2, result);
            if (isNum1Negative) 
            {
                memmove(result + 1, result, strlen(result) + 1);
                result[0] = '-';
            }
        }
        else {
            subtract(tempNum2, tempNum1, result);
            if (isNum2Negative) 
            {
                memmove(result + 1, result, strlen(result) + 1);
                result[0] = '-';
            }
        }
    }
}


// Функции для вычитания 
int compare_strings(const char* num1, const char* num2) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    if (len1 > len2)
    {
        return 1;
    }

    if (len1 < len2)
    {
        return -1;
    }

    for (int i = 0; i < len1; i++) 
    {
        if (num1[i] > num2[i])
        {
            return 1;
        }
        if (num1[i] < num2[i])
        {
            return -1;
        }
    }

    return 0;
}

void subtract_positive(const char* num1, const char* num2, char* result) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int diff = len1 - len2;
    memset(result, 0, MAX);  // Очистка результата

    int carry = 0;

    // Вычитание начинается с конца строк
    for (int i = len2 - 1; i >= 0; i--) 
    {
        int sub = ((num1[i + diff] - '0') - (num2[i] - '0') - carry);
        if (sub < 0) 
        {
            sub += 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
        result[i + diff] = sub + '0';
    }

    for (int i = diff - 1; i >= 0; i--) 
    {
        if (carry == 1 && num1[i] == '0') 
        {
            result[i] = '9';
        }
        else {
            int sub = (num1[i] - '0') - carry;
            result[i] = sub + '0';
            carry = 0;
        }
    }

    // Удаление нулей из результата
    int start = 0;
    while (start < len1 && result[start] == '0') 
    {
        start++;
    }

    if (start == len1) 
    { 
        // В случае, если результат равен 0
        strcpy(result, "0");
    }
    else 
    {
        if (start > 0) 
        {
            memmove(result, result + start, len1 - start + 1); // Сдвиг результата в начало
        }
    }
}

void subtract(const char* num1, const char* num2, char* result) 
{
    char tempNum1[MAX + 1], tempNum2[MAX + 1];

    bool isNum1Negative = isNegative(num1);
    bool isNum2Negative = isNegative(num2);

    // Удаление минуса
    if (isNum1Negative) 
    {
        strcpy(tempNum1, num1 + 1);
    }
    else 
    {
        strcpy(tempNum1, num1);
    }

    if (isNum2Negative)
    {
        strcpy(tempNum2, num2 + 1);
    }
    else
    {
        strcpy(tempNum2, num2);
    }

    int needSwap = compare_strings(tempNum1, tempNum2);

    if (!isNum1Negative && !isNum2Negative) 
    {
        if (needSwap < 0) 
        {
            subtract_positive(tempNum2, tempNum1, result);
            memmove(result + 1, result, strlen(result) + 1); // Сдвиг результата
            result[0] = '-';
        }
        else {
            subtract_positive(tempNum1, tempNum2, result);
        }
    }
    else if (isNum1Negative && isNum2Negative) 
    {
        if (needSwap < 0) 
        {
            subtract_positive(tempNum2, tempNum1, result);
        }
        else 
        {
            subtract_positive(tempNum1, tempNum2, result);
            memmove(result + 1, result, strlen(result) + 1); // Сдвиг результата
            result[0] = '-'; 
        }
    }
    else if (isNum1Negative && !isNum2Negative) 
    {
        addPositiveNumbers(tempNum1, tempNum2, result);
        memmove(result + 1, result, strlen(result) + 1);
        result[0] = '-';
    }
    else 
    {
        addPositiveNumbers(tempNum1, tempNum2, result);
    }

    // Проверка на -0
    if (strcmp(result, "-0") == 0) 
    {
        strcpy(result, "0");
    }
}

// Реверс строки
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
void multiply(char* num1, char* num2, char* result) 
{
    // Убираем минус
    int is_negative_flag = 0;
    if (num1[0] == '-') 
    {
        is_negative_flag ^= 1;
        num1++;
    }
    if (num2[0] == '-') 
    {
        is_negative_flag ^= 1;
        num2++;
    }

    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int resultArr[MAX] = { 0 };

    int i_n1 = 0; // Позиция для первого числа
    int i_n2 = 0; // Позиция для второго числа

    // Обход числа справа налево
    for (int i = len1 - 1; i >= 0; i--) 
    {
        int carry = 0;
        int n1 = num1[i] - '0';
        i_n2 = 0;

        // Перемножение n1 с каждой цифрой num2
        for (int j = len2 - 1; j >= 0; j--) 
        {
            int n2 = num2[j] - '0';
            int sum = n1 * n2 + resultArr[i_n1 + i_n2] + carry;
            carry = sum / 10;
            resultArr[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }

        if (carry > 0) 
        {
            resultArr[i_n1 + i_n2] += carry;
        }
        i_n1++;
    }

    // Пропуск нулей в начале
    int i = len1 + len2 - 1;
    while (i >= 0 && resultArr[i] == 0)
    {
        i--;
    }

    // Если результат равен 0
    if (i == -1) 
    {
        strcpy(result, "0");
        return;
    }

    // Записываем результат
    int index = 0;
    if (is_negative_flag) 
    {
        result[index++] = '-';
    }

    while (i >= 0) 
    {
        result[index++] = resultArr[i--] + '0';
    }
    result[index] = '\0';
}

// Деление
void divide(const char* num1, const char* num2, char* result, int decimaplaces)
{
    if (strcmp(num2, "0") == 0)
    {
        strcpy(result, "Ошибка! Деление на ноль!");
        return;
    }

    bool isNum1Negative = isNegative(num1);
    bool isNum2Negative = isNegative(num2);

    char tempNum1[MAX + 1], tempNum2[MAX + 1];
    char tempResult[MAX + 1];

    if (isNum1Negative)
    {
        strcpy(tempNum1, num1 + 1);
    }
    else
    {
        strcpy(tempNum1, num1);
    }

    if (isNum2Negative)
    {
        strcpy(tempNum2, num2 + 1);
    }
    else
    {
        strcpy(tempNum2, num2);
    }

    memset(result, 0, MAX);
    memset(tempResult, 0, MAX);

    int resultPos = 0;
    int tempNum1Pos = 0;
    bool decimalAdded = false; // Была ли добавлена десятичная точка

    while (tempNum1Pos < strlen(tempNum1) || decimaplaces > 0)
    {
        if (tempNum1Pos >= strlen(tempNum1))
        {
            // Если все цифры делимого были обработаны, добавляем ноль для продолжения деления после запятой
            if (!decimalAdded)
            {
                result[resultPos++] = '.';
                decimalAdded = true;
            }
            tempResult[strlen(tempResult)] = '0'; // Добавление нуля к остатку
            decimaplaces--;
        }
        else
        {
            // Добавляем следующую цифру к остатку
            size_t tempResultLen = strlen(tempResult);
            tempResult[tempResultLen] = tempNum1[tempNum1Pos++];
            tempResult[tempResultLen + 1] = '\0'; // Конец строки

            while (tempResult[0] == '0' && tempResult[1] != '\0')
            {
                memmove(tempResult, tempResult + 1, strlen(tempResult));
            }
        }

        if (compare_strings(tempResult, tempNum2) >= 0 || decimalAdded)
        {
            int count = 0;
            while (compare_strings(tempResult, tempNum2) >= 0)
            {
                subtract(tempResult, tempNum2, tempResult);
                count++;
            }
            result[resultPos++] = count + '0';
        }
        else if (resultPos > 0 || decimalAdded)
        {
            result[resultPos++] = '0';
        }
    }

    if (resultPos == 0)
    {
        strcpy(result, "0");
    }
    else
    {
        if (isNum1Negative != isNum2Negative) 
        {
            memmove(result + 1, result, resultPos + 1);
            result[0] = '-';
            resultPos++;
        }
        result[resultPos] = '\0';
    }
}
