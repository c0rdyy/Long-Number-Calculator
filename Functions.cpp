#define _CRT_SECURE_NO_WARNINGS

#include "Funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

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
    strcpy(tempNum1, isNum1Negative ? num1 + 1 : num1);
    strcpy(tempNum2, isNum2Negative ? num2 + 1 : num2);

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


//Вычитание 
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

bool isNegative(const char* num) 
{
    return num[0] == '-';
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
        // В случае, если результат равен 0.
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
    strcpy(tempNum1, isNum1Negative ? num1 + 1 : num1);
    strcpy(tempNum2, isNum2Negative ? num2 + 1 : num2);

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