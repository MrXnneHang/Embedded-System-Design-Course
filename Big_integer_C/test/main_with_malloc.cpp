#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000
int a[SIZE], b[SIZE], c[SIZE];

// 返回两者较大值
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 将数组设置为0
void setZero(int* num, int len) {
    for (int i = 0; i < len; i++)
        num[i] = 0;
}

// 比较两个数组形式数字大小
int Compare(int* num1, int* num2) {
    int i, j;
    for (i = SIZE - 1; num1[i] == 0; i--);
    for (j = SIZE - 1; num2[j] == 0; j--);
    if (i < j) return -1;
    else if (i > j) return 1;
    else {
        for (; i >= 0; i--) {
            if (num1[i] > num2[i])
                return 1;
            else if (num1[i] < num2[i])
                return -1;
        }
        return 0;
    }
}
// 比较两个大数字符串的大小
int compare(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    return strcmp(str1, str2);
}


// 将一个数组赋给另一个数组
int copy(int* num1, int* num2) {
    int i, j;
    for (i = 0; i < SIZE; i++)
        num1[i] = 0;
    for (i = SIZE - 1; num2[i] == 0; i--);
    for (j = 0; j <= i; j++)
        num1[j] = num2[j];
    return i + 1;
}

// 大数加法
char* add(char* str1, char* str2) {
    setZero(a, SIZE);
    setZero(b, SIZE);
    setZero(c, SIZE);

    int i, carry = 0;
    int len1 = strlen(str1), len2 = strlen(str2), len = max(len1, len2);
    for (i = 0; i < len1; i++)
        a[i] = str1[len1 - 1 - i] - '0';
    for (i = 0; i < len2; i++)
        b[i] = str2[len2 - 1 - i] - '0';
    for (i = 0; i < len; i++) {
        c[i] = (a[i] + b[i] + carry) % 10;
        carry = (a[i] + b[i] + carry) / 10;
    }
    if (carry != 0)
        c[len++] = 1;

    char* result = (char*)malloc(SIZE + 1 * sizeof(char));
    for (i = len - 1; i >= 0; i--)
        result[len - 1 - i] = c[i] + '0';
    result[len] = '\0';

    return result;
}

// 大数减法
char* subtract(char* str1, char* str2) {
    setZero(a, SIZE);
    setZero(b, SIZE);
    setZero(c, SIZE);

    int i, borrow = 0;
    int len1 = strlen(str1), len2 = strlen(str2), len = max(len1, len2);
    for (i = 0; i < len1; i++)
        a[i] = str1[len1 - 1 - i] - '0';
    for (i = 0; i < len2; i++)
        b[i] = str2[len2 - 1 - i] - '0';

    // 初步根据位数判断两数大小	
    if (len2 > len1) {
        for (i = 0; i < len; i++) {
            c[i] = b[i] - a[i] - borrow;
            if (c[i] < 0) {
                borrow = 1;
                c[i] += 10;
            }
            else
                borrow = 0;
        }
    }
    else {
        for (i = 0; i < len; i++) {
            c[i] = a[i] - b[i] - borrow;
            if (c[i] < 0 && i + 1 < len) {
                borrow = 1;
                c[i] += 10;
            }
            else
                borrow = 0;
        }
    }

    // 如果发现被减数小于减数，则重新计算，用减数减去被减数，输出负号 
    if (c[len - 1] < 0) {
        for (i = 0; i < len; i++) {
            c[i] = b[i] - a[i] - borrow;
            if (c[i] < 0 && i + 1 < len) {
                borrow = 1;
                c[i] += 10;
            }
            else
                borrow = 0;
        }
    }

    while (c[len - 1] == 0 && len > 1)
        len--;

    char* result = (char*)malloc(SIZE + 1 * sizeof(char));
    for (i = len - 1; i >= 0; i--)
        result[len - 1 - i] = c[i] + '0';
    result[len] = '\0';

    return result;
}

// 大数乘法
char* multiply(char* str1, char* str2) {
    setZero(a, SIZE);
    setZero(b, SIZE);
    setZero(c, SIZE);

    int i, j, k, carry = 0, tmp;
    int len1 = strlen(str1), len2 = strlen(str2);
    for (i = 0; i < len1; i++)
        a[i] = str1[len1 - 1 - i] - '0';
    for (i = 0; i < len2; i++)
        b[i] = str2[len2 - 1 - i] - '0';

    for (i = 0; i < len1; i++) {
        for (k = i, j = 0; j < len2; j++, k++) {
            c[k] += a[i] * b[j];
        }
    }
    for (i = 0; i <= k; i++) {
        c[i] += carry;
        tmp = c[i];
        c[i] = tmp % 10;
        carry = tmp / 10;
    }

    for (i = k; c[i] == 0; i--);
    char* result = (char*)malloc(SIZE + 1 * sizeof(char));
    for (int j = 0; j <= i; j++)
        result[j] = c[i - j] + '0';
    result[i + 1] = '\0';

    return result;
}

// 大数除法
char* divide(char* str1, char* str2) {
    setZero(a, SIZE);
    setZero(b, SIZE);
    setZero(c, SIZE);

    int i, j, tmp, tmp2 = 0, borrow = 0, temp[SIZE] = { 0 }, temp2[SIZE] = { 0 };
    int len1 = strlen(str1), len2 = strlen(str2);
    for (i = 0; i < len1; i++)
        a[i] = str1[len1 - 1 - i] - '0';
    for (i = 0; i < len2; i++)
        b[i] = str2[len2 - 1 - i] - '0';

    if (Compare(a, b) < 0) {
        char* result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    while (Compare(a, b) >= 0) {
        tmp = len1 - len2;
        if (tmp == tmp2 && tmp > 0)
            tmp--;
        tmp2 = tmp;

        setZero(temp2, SIZE);
        for (i = len1 - 1; i >= tmp; i--)
            temp2[i] = b[i - tmp];
        copy(temp, a);

        if (Compare(temp, temp2) < 0)
            continue;
        for (j = 1;; j++) {
            borrow = 0;
            for (i = tmp; i < len1; i++) {
                temp[i] = a[i] - temp2[i] - borrow;
                if (temp[i] < 0) {
                    borrow = 1;
                    temp[i] += 10;
                }
                else
                    borrow = 0;
            }

            len1 = copy(a, temp);
            c[tmp] = j;
            if (Compare(temp, temp2) < 0)
                break;
        }
    }

    char* result = (char*)malloc(SIZE + 1 * sizeof(char));
    for (i = SIZE - 1; c[i] == 0; i--);
    for (j = 0; i >= 0; i--, j++)
        result[j] = c[i] + '0';
    result[j] = '\0';

    return result;
}

// 大数取模运算
char* mod(char* str1, char* str2) {
    setZero(a, SIZE);
    setZero(b, SIZE);
    setZero(c, SIZE);

    int i, j, tmp, tmp2 = 0, borrow = 0, temp[SIZE] = { 0 }, temp2[SIZE] = { 0 };
    int len1 = strlen(str1), len2 = strlen(str2);
    for (i = 0; i < len1; i++)
        a[i] = str1[len1 - 1 - i] - '0';
    for (i = 0; i < len2; i++)
        b[i] = str2[len2 - 1 - i] - '0';

    if (Compare(a, b) < 0) {
        char* result = (char*)malloc(SIZE + 1 * sizeof(char));
        for (i = len1 - 1; i >= 0; i--)
            result[len1 - 1 - i] = a[i] + '0';
        result[len1] = '\0';
        return result;
    }

    while (Compare(a, b) >= 0) {
        tmp = len1 - len2;
        if (tmp == tmp2 && tmp > 0)
            tmp--;
        tmp2 = tmp;

        setZero(temp2, SIZE);
        for (i = len1 - 1; i >= tmp; i--)
            temp2[i] = b[i - tmp];
        copy(temp, a);

        if (Compare(temp, temp2) < 0)
            continue;
        for (j = 1;; j++) {
            borrow = 0;
            for (i = tmp; i < len1; i++) {
                temp[i] = a[i] - temp2[i] - borrow;
                if (temp[i] < 0) {
                    borrow = 1;
                    temp[i] += 10;
                }
                else
                    borrow = 0;
            }

            len1 = copy(a, temp);
            if (Compare(temp, temp2) < 0)
                break;
        }
    }

    char* result = (char*)malloc(SIZE + 1 * sizeof(char));
    for (i = len1 - 1; i >= 0; i--)
        result[len1 - 1 - i] = a[i] + '0';
    result[len1] = '\0';

    return result;
}

// 大数幂运算
char* power(char* base, char* exp) {
    char* result = (char*)malloc(2 * sizeof(char));
    result[0] = '1';
    result[1] = '\0';

    char* one = (char*)malloc(2 * sizeof(char));
    one[0] = '1';
    one[1] = '\0';

    while (compare(exp, one) > 0) {
        result = multiply(result, base);
        exp = subtract(exp, one);
    }
    result = multiply(result, base);

    free(one);
    return result;
}




//辅助函数：将十进制字符串除以 2
void divideByTwo(char* num, char* result) {
    int len = strlen(num);
    int carry = 0;

    for (int i = 0; i < len; i++) {
        int currentDigit = num[i] - '0' + carry * 10;
        result[i] = (currentDigit / 2) + '0';
        carry = currentDigit % 2;
    }

    result[len] = '\0';

    //移除前导零
    int start = 0;
    while (result[start] == '0' && result[start + 1] != '\0') {
        start++;
    }
    memmove(result, result + start, len - start + 1);
}

//辅助函数：检查字符串是否为零
int isZero(const char* num) {
    while (*num) {
        if (*num != '0') {
            return 0;
        }
        num++;
    }
    return 1;
}
//十进制字符转换成二进制
static char* decimalToBinary(const char* num, int bits) {
    //分配足够大的空间来存储二进制字符串
    char* binaryString = (char*)malloc(bits + 1);
    if (binaryString == NULL) {
        return NULL; // 内存分配失败
    }
    binaryString[bits] = '\0'; // 字符串结尾符

    //复制输入字符串，因为我们会修改它
    char* tempNum = strdup(num);
    if (tempNum == NULL) {
        free(binaryString);
        return NULL; // 内存分配失败
    }

    //从最低位开始填充二进制字符串
    for (int i = bits - 1; i >= 0; i--) {
        if (isZero(tempNum)) {
            binaryString[i] = '0'; // 如果已经为零，填充剩余位
        }
        else {
            int lastDigit = (tempNum[strlen(tempNum) - 1] - '0') % 2;
            binaryString[i] = lastDigit ? '1' : '0'; // 获取最低位的二进制位

            //将十进制字符串除以 2
            char* dividedNum = (char*)malloc(strlen(tempNum) + 1);
            if (dividedNum == NULL) {
                free(binaryString);
                free(tempNum);
                return NULL; // 内存分配失败
            }
            divideByTwo(tempNum, dividedNum);
            free(tempNum);
            tempNum = dividedNum;
        }
    }

    free(tempNum);
    return binaryString;
}
char* fastpowermod(char* base, const char* binaryexp, char* m) {
    //初始化结果为 "1"
    char* result = (char*)malloc(2 * sizeof(char));
    result[0] = '1';
    result[1] = '\0';
    //复制 base 以便进行幂运算
    char* tempBase = strdup(base);
    int len = strlen(binaryexp);

    //遍历二进制指数的每一位
    for (int i = 0; i < len; i++) {
        //如果当前二进制位为 '1'，将结果乘以当前的 base
        if (binaryexp[len - 1 - i] == '1') {
            char* newResult = multiply(result, tempBase);
            newResult = mod(newResult, m);
            free(result);
            result = newResult;
        }
        //base 自身相乘
        char* newBase = multiply(tempBase, tempBase);
        newBase = mod(newBase, m);
        free(tempBase);
        tempBase = newBase;
    }

    //释放临时变量
    free(tempBase);
    return result;
}
char* removeLeadingZeros(const char* str) {
    while (*str == '0') {
        str++;
    }
    return (char*)str;
}
int main() {
    // 变量定义
    int bits;
    char num1[SIZE], num2[SIZE];
    char result[SIZE]; char binaryExp[SIZE]; char exp[SIZE]; char m[SIZE];
    // 加法测试
    strcpy(num1, "123456789123456789");
    strcpy(num2, "987654321987654321");
    strcpy(result, add(num1, num2));
    printf("Addition: %s + %s = %s\n", num1, num2, result);

    // 减法测试
    strcpy(num1, "987654321987654321");
    strcpy(num2, "123456789123456789");
    strcpy(result, subtract(num1, num2));
    printf("Subtraction: %s - %s = %s\n", num1, num2, result);

    // 乘法测试
    strcpy(num1, "260");
    strcpy(num2, "20000000");
    strcpy(result, multiply(num1, num2));
    printf("Multiplication: %s * %s = %s\n", num1, num2, result);

    // 除法测试
    strcpy(num1, "6000");
    strcpy(num2, "5");
    strcpy(result, divide(num1, num2));
    printf("Division: %s / %s = %s\n", num1, num2, result);

    // 取模测试
    strcpy(num1, "1661");
    strcpy(num2, "1000");
    strcpy(result, mod(num1, num2));
    printf("Modulo: %s %% %s = %s\n", num1, num2, result);

    // 快速幂模测试
    strcpy(num1, "2210613142");
    strcpy(num2, "45654");
    strcpy(m, "1000");
    bits = strlen(num2) * 4;
    strcpy(binaryExp, decimalToBinary(num2, bits));
    strcpy(binaryExp, removeLeadingZeros(binaryExp));
    printf("Binary:%s\n", binaryExp);
    strcpy(result, fastpowermod(num1, binaryExp, m));
    printf("Fast Power Modulo: %s^%s %% %s = %s\n", num1, num2, m, removeLeadingZeros(result));

    return 0;
}