#pragma once

int isNumber(char* str); // Ввод
void addNumbers(char* num1, char* num2, char *result); // Сложение
void addPositiveNumbers(char* num1, char* num2, char* result);
void reverseString(char* str); // Переворачивание
void subtract(const char* num1, const char* num2, char* result); // Вычитание
void subtract_positive(const char* num1, const char* num2, char* result); // Вычитание
int compare_strings(const char* num1, const char* num2); // Сравнение
bool isNegative(const char* num); // Минус
void multiply(char* num1, char* num2, char* result); // Умножение
void divide(const char* num1, const char* num2, char* result, int decimaplaces); // Деление