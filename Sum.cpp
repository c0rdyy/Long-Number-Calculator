#define _CRT_SECURE_NO_WARNINGS

#include "Funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

// �����
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
        result[MAX - i - 3] += (result[MAX - i - 2] - '0') / 10; // ��������� �������
        result[MAX - i - 2] = (result[MAX - i - 2] - '0') % 10 + '0'; // ���������� �������
    }

    int first_digit_pos = 0;
    while (result[first_digit_pos] == '0' && first_digit_pos < MAX - 2)
    {
        first_digit_pos++;
    }

    // ����� ���������� ��� ������ �����
    if (first_digit_pos == MAX - 1) // ��� ����� ����
    {
        printf("�����: 0\n\n"); // ������� ���� ����
    }
    else
    {
        printf("�����: %s\n\n", result + first_digit_pos); // ����� ���������� ��� ������ �����
    }
}

// ���������
void subtract(const char* num1, const char* num2, char* result) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxlen;
    int negative = 0;

    if (len1 > len2)
    {
        maxlen = len1;
    }
    else
    {
        maxlen = len2;
    }

    if (len1 < len2) 
    {
        const char* temp = num1;
        num1 = num2;
        num2 = temp;
        int tempLen = len1;
        len1 = len2;
        len2 = tempLen;
        negative = 1;
    }

    int i, carry = 0;
    for (i = 0; i < maxlen; i++) 
    {
        int digit1;
        int digit2;

        if (i < len1)
        {
            digit1 = num1[len1 - 1 - i] - '0';
        }
        else
        {
            digit1 = 0;
        }

        if (i < len2)
        {
            digit2 = num2[len2 - 1 - i] - '0';
        }
        else
        {
            digit2 = 0;
        }

        int diff = digit1 - digit2 - carry;
        if (diff < 0) 
        {
            diff += 10;
            carry = 1;
        }
        else 
        {
            carry = 0;
        }

        result[i] = diff + '0';
    }

    // ���������� ����������� �������� � ������ �������������
    if (carry == 1) 
    {
        result[i++] = '1';
    }

    // ������������� ���������
    if (negative) 
    {
        result[i++] = '-';
    }

    // �������� ����������
    for (int j = 0; j < i / 2; j++) 
    {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }

    // �������� ������� �����
    int j = 0;
    while (result[j] == '0' && j < i - 1) 
    {
        j++;
    }

    // ����� ����������, ���� ���� ������� ����
    if (j > 0) 
    {
        for (int k = 0; k < i - j; k++) 
        {
            result[k] = result[k + j];
        }
        i -= j;
    }

    result[i] = '\0'; // ���������� �������� ������� � ����� ������

    printf("��������� ���������: %s\n\n", result);
}

