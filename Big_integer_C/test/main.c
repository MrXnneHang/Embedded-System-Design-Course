//#pragma once
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#define SIZE 100
//
//// 全局数组
//int a[SIZE], b[SIZE], c[SIZE];
//char result1[SIZE + 1], result2[SIZE + 1], result3[SIZE + 1];
//char tempNum[SIZE + 1], dividedNum[SIZE + 1];
//int temp2[SIZE + 1];
//char binaryString[SIZE + 1];
//char modBaseResult[SIZE + 1], modResult[SIZE + 1], newResult[SIZE + 1], newBase[SIZE + 1];
//char tempBase[SIZE + 1];
//
//char localResult1[SIZE + 1];
//char localModResult[SIZE + 1];
//char localNewResult[SIZE + 1];
//char localTempBase[SIZE + 1];
//char localModBaseResult[SIZE + 1];
//char localNewBase[SIZE + 1];
//
//
////E
//char binaryExp[SIZE + 1]; char D[SIZE + 1]; char result[SIZE + 1]; char m[SIZE + 1];
//
//
//
//
//// 将数组设置为0
//void setZero(int* num, int len) {
//    int i;
//    for (i = 0; i < len; i++)
//        num[i] = 0;
//}
//
//// 比较两个数组形式数字大小
//int Compare(int* num1, int* num2) {
//    int i, j;
//    for (i = SIZE - 1; num1[i] == 0; i--);
//    for (j = SIZE - 1; num2[j] == 0; j--);
//    if (i < j) return -1;
//    else if (i > j) return 1;
//    else {
//        for (; i >= 0; i--) {
//            if (num1[i] > num2[i])
//                return 1;
//            else if (num1[i] < num2[i])
//                return -1;
//        }
//        return 0;
//    }
//}
//
//// 将一个数组赋给另一个数组
//int copy(int* num1, int* num2) {
//    int i, j;
//    for (i = 0; i < SIZE; i++)
//        num1[i] = 0;
//    for (i = SIZE - 1; num2[i] == 0; i--);
//    for (j = 0; j <= i; j++)
//        num1[j] = num2[j];
//    return i + 1;
//}
//
//char* add(char* str1, char* str2) {
//    int carry, len1, len2, len;
//    int i;
//
//    setZero(a, SIZE);
//    setZero(b, SIZE);
//    setZero(c, SIZE);
//
//    carry = 0;
//    len1 = strlen(str1);
//    len2 = strlen(str2);
//    len = (len1 > len2) ? len1 : len2;
//
//    for (i = 0; i < len1; i++) {
//        a[i] = str1[len1 - 1 - i] - '0';
//    }
//    for (i = 0; i < len2; i++) {
//        b[i] = str2[len2 - 1 - i] - '0';
//    }
//    for (i = 0; i < len; i++) {
//        c[i] = (a[i] + b[i] + carry) % 10;
//        carry = (a[i] + b[i] + carry) / 10;
//    }
//    if (carry != 0) {
//        c[len++] = 1;
//    }
//
//    for (i = len - 1; i >= 0; i--) {
//        result1[len - 1 - i] = c[i] + '0';
//    }
//    result1[len] = '\0';
//
//    return result1;
//}
//
//char* subtract(char* str1, char* str2) {
//    int borrow, len1, len2, len;
//    int i;
//
//    setZero(a, SIZE);
//    setZero(b, SIZE);
//    setZero(c, SIZE);
//
//    borrow = 0;
//    len1 = strlen(str1);
//    len2 = strlen(str2);
//    len = (len1 > len2) ? len1 : len2;
//
//    for (i = 0; i < len1; i++) {
//        a[i] = str1[len1 - 1 - i] - '0';
//    }
//    for (i = 0; i < len2; i++) {
//        b[i] = str2[len2 - 1 - i] - '0';
//    }
//
//    for (i = 0; i < len; i++) {
//        c[i] = a[i] - b[i] - borrow;
//        if (c[i] < 0) {
//            borrow = 1;
//            c[i] += 10;
//        }
//        else {
//            borrow = 0;
//        }
//    }
//
//    while (c[len - 1] == 0 && len > 1) {
//        len--;
//    }
//
//    for (i = len - 1; i >= 0; i--) {
//        result2[len - 1 - i] = c[i] + '0';
//    }
//    result2[len] = '\0';
//
//    return result2;
//}
//
//char* multiply(char* str1, char* str2) {
//    int carry, tmp, len1, len2;
//    int i, j, k;
//
//    setZero(a, SIZE);
//    setZero(b, SIZE);
//    setZero(c, SIZE);
//
//    len1 = strlen(str1);
//    len2 = strlen(str2);
//
//    for (i = 0; i < len1; i++)
//        a[i] = str1[len1 - 1 - i] - '0';
//    for (i = 0; i < len2; i++)
//        b[i] = str2[len2 - 1 - i] - '0';
//
//    for (i = 0; i < len1; i++) {
//        for (k = i, j = 0; j < len2; j++, k++) {
//            c[k] += a[i] * b[j];
//        }
//    }
//
//    carry = 0;
//    for (i = 0; i < SIZE; i++) {
//        c[i] += carry;
//        tmp = c[i];
//        c[i] = tmp % 10;
//        carry = tmp / 10;
//    }
//
//    for (i = SIZE - 1; i >= 0 && c[i] == 0; i--);
//    if (i == -1) {
//        result3[0] = '0';
//        result3[1] = '\0';
//    }
//    else {
//        for (j = 0; j <= i; j++)
//            result3[j] = c[i - j] + '0';
//        result3[i + 1] = '\0';
//    }
//
//    return result3;
//}
//
//char* divide(char* str1, char* str2) {
//    static char result[SIZE + 1];
//    int i, j, tmp, tmp2 = 0, borrow = 0, temp[SIZE] = { 0 }, temp2[SIZE] = { 0 };
//    int len1, len2;
//
//    setZero(a, SIZE);
//    setZero(b, SIZE);
//    setZero(c, SIZE);
//
//    len1 = strlen(str1);
//    len2 = strlen(str2);
//
//    for (i = 0; i < len1; i++)
//        a[i] = str1[len1 - 1 - i] - '0';
//    for (i = 0; i < len2; i++)
//        b[i] = str2[len2 - 1 - i] - '0';
//
//    if (Compare(a, b) < 0) {
//        result[0] = '0';
//        result[1] = '\0';
//        return result;
//    }
//
//    while (Compare(a, b) >= 0) {
//        tmp = len1 - len2;
//        if (tmp == tmp2 && tmp > 0)
//            tmp--;
//        tmp2 = tmp;
//
//        setZero(temp2, SIZE);
//        for (i = len1 - 1; i >= tmp; i--)
//            temp2[i] = b[i - tmp];
//        copy(temp, a);
//
//        if (Compare(temp, temp2) < 0)
//            continue;
//        for (j = 1;; j++) {
//            borrow = 0;
//            for (i = tmp; i < len1; i++) {
//                temp[i] = a[i] - temp2[i] - borrow;
//                if (temp[i] < 0) {
//                    borrow = 1;
//                    temp[i] += 10;
//                }
//                else
//                    borrow = 0;
//            }
//
//            len1 = copy(a, temp);
//            c[tmp] = j;
//            if (Compare(temp, temp2) < 0)
//                break;
//        }
//    }
//
//    for (i = SIZE - 1; c[i] == 0 && i >= 0; i--);
//    for (j = 0; i >= 0; i--, j++)
//        result[j] = c[i] + '0';
//    result[j] = '\0';
//
//    return result;
//}
//
//char* mod(char* str1, char* str2, char* result) {
//    int i, j, tmp, tmp2 = 0, borrow = 0, len1, len2;
//    int nonZeroFound;
//
//    setZero(a, SIZE);
//    setZero(b, SIZE);
//    setZero(c, SIZE);
//
//    len1 = strlen(str1);
//    len2 = strlen(str2);
//
//    for (i = 0; i < len1; i++)
//        a[i] = str1[len1 - 1 - i] - '0';
//    for (i = 0; i < len2; i++)
//        b[i] = str2[len2 - 1 - i] - '0';
//
//    if (Compare(a, b) < 0) {
//        for (i = len1 - 1; i >= 0; i--)
//            result[len1 - 1 - i] = a[i] + '0';
//        result[len1] = '\0';
//        return result;
//    }
//
//    while (Compare(a, b) >= 0) {
//        tmp = len1 - len2;
//        if (tmp == tmp2 && tmp > 0)
//            tmp--;
//        tmp2 = tmp;
//
//        setZero(temp2, SIZE);
//        for (i = len1 - 1; i >= tmp; i--)
//            temp2[i] = b[i - tmp];
//        copy(c, a);
//
//        if (Compare(c, temp2) < 0)
//            continue;
//        for (j = 1;; j++) {
//            borrow = 0;
//            for (i = tmp; i < len1; i++) {
//                c[i] = a[i] - temp2[i] - borrow;
//                if (c[i] < 0) {
//                    borrow = 1;
//                    c[i] += 10;
//                }
//                else
//                    borrow = 0;
//            }
//
//            len1 = copy(a, c);
//            if (Compare(c, temp2) < 0)
//                break;
//        }
//    }
//
//    nonZeroFound = 0;
//    for (i = len1 - 1; i >= 0; i--) {
//        result[len1 - 1 - i] = a[i] + '0';
//        if (a[i] != 0) {
//            nonZeroFound = 1;
//        }
//    }
//    result[len1] = '\0';
//
//    if (!nonZeroFound) {
//        result[0] = '0';
//        result[1] = '\0';
//    }
//
//    return result;
//}
//
//char* processed_mod(char* base, char* m, char* result) {
//    return mod(base, m, result);
//}
//
//
//void divideByTwo(const char* num, char* result) {
//    int len;
//    int carry;
//    int i;
//    int start;
//    carry = 0;
//    len = strlen(num);
//    start = 0;
//    for (i = 0; i < len; i++) {
//        int currentDigit = num[i] - '0' + carry * 10;
//        result[i] = (currentDigit / 2) + '0';
//        carry = currentDigit % 2;
//    }
//
//    result[len] = '\0';
//
//    while (result[start] == '0' && result[start + 1] != '\0') {
//        start++;
//    }
//    memmove(result, result + start, len - start + 1);
//}
//
//int isZero(const char* num) {
//    while (*num) {
//        if (*num != '0') {
//            return 0;
//        }
//        num++;
//    }
//    return 1;
//}
//
//char* decimalToBinary(const char* num, int bits) {
//    int i;
//    strcpy(tempNum, num);
//
//    for (i = bits - 1; i >= 0; i--) {
//        if (isZero(tempNum)) {
//            binaryString[i] = '0';
//        }
//        else {
//            int lastDigit = (tempNum[strlen(tempNum) - 1] - '0') % 2;
//            binaryString[i] = lastDigit ? '1' : '0';
//
//            divideByTwo(tempNum, dividedNum);
//            strcpy(tempNum, dividedNum);
//        }
//    }
//
//    return binaryString;
//}
//void my_strcpy(char* dest, const char* src) {
//    while (*src) {
//        *dest++ = *src++;
//    }
//    *dest = '\0'; // 确保字符串以空字符结尾
//}
//
//char* fastpowermod(const char* base, const char* binaryexp, const char* m) {
//    int i; int len;
//    my_strcpy(localResult1, "1");
//    my_strcpy(localTempBase, base);
//
//    len = strlen(binaryexp);
//
//    for ( i = 0; i < len; i++) {
//        if (binaryexp[len - 1 - i] == '1') {
//
//            my_strcpy(localNewResult, multiply(localResult1, localTempBase));
//
//            my_strcpy(localModResult, processed_mod(localNewResult, (char*)m, localModResult));
//
//            my_strcpy(localResult1, localModResult);
//
//        }
//
//        my_strcpy(localNewBase, multiply(localTempBase, localTempBase));
//        my_strcpy(localModBaseResult, processed_mod(localNewBase, (char*)m, localModBaseResult));
//        my_strcpy(localTempBase, localModBaseResult);
//    }
//
//    my_strcpy(result1, localResult1);
//    return result1;
//}
//
//char* removeLeadingZeros(const char* str) {
//    while (*str == '0') {
//        str++;
//    }
//    return (char*)str;
//}
//
//
//
//int main() {
//    // 变量定义
//    int bits;
//    char num1[SIZE], num2[SIZE]; 
//
//    // 加法测试
//    strcpy(num1, "123456789123456789");
//    strcpy(num2, "987654321987654321");
//    strcpy(result, add(num1, num2));
//    printf("Addition: %s + %s = %s\n", num1, num2, result);
//
//    // 减法测试
//    strcpy(num1, "987654321987654321");
//    strcpy(num2, "123456789123456789");
//    strcpy(result, subtract(num1, num2));
//    printf("Subtraction: %s - %s = %s\n", num1, num2, result);
//
//    // 乘法测试
//    strcpy(num1, "260");
//    strcpy(num2, "20000000");
//    strcpy(result, multiply(num1, num2));
//    printf("Multiplication: %s * %s = %s\n", num1, num2, result);
//
//    // 除法测试
//    strcpy(num1, "6000");
//    strcpy(num2, "5");
//    strcpy(result, divide(num1, num2));
//    printf("Division: %s / %s = %s\n", num1, num2, result);
//
//    // 取模测试
//    strcpy(num1, "1661");
//    strcpy(num2, "1000");
//    strcpy(result, mod(num1, num2, result));
//    printf("Modulo: %s %% %s = %s\n", num1, num2, result);
//
//    // 快速幂模测试
//    strcpy(num1, "2210613142");
//    strcpy(num2, "45654");
//    strcpy(m, "1000");
//    bits = strlen(num2) * 4;
//    strcpy(binaryExp,decimalToBinary(num2, bits));
//    strcpy(binaryExp,removeLeadingZeros(binaryExp));
//    printf("Binary:%s\n", binaryExp);
//    strcpy(result, fastpowermod(num1, binaryExp, m));
//    printf("Fast Power Modulo: %s^%s %% %s = %s\n", num1, num2, m, removeLeadingZeros(result));
//
//    return 0;
//}
