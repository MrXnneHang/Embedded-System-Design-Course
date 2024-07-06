#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000
int a[SIZE], b[SIZE], c[SIZE];

// �������߽ϴ�ֵ
int max(int a, int b) {
    return (a > b) ? a : b;
}

// ����������Ϊ0
void setZero(int* num, int len) {
    for (int i = 0; i < len; i++)
        num[i] = 0;
}

// �Ƚ�����������ʽ���ִ�С
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
// �Ƚ����������ַ����Ĵ�С
int compare(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    return strcmp(str1, str2);
}


// ��һ�����鸳����һ������
int copy(int* num1, int* num2) {
    int i, j;
    for (i = 0; i < SIZE; i++)
        num1[i] = 0;
    for (i = SIZE - 1; num2[i] == 0; i--);
    for (j = 0; j <= i; j++)
        num1[j] = num2[j];
    return i + 1;
}

// �����ӷ�
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

// ��������
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

    // ��������λ���ж�������С	
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

    // ������ֱ�����С�ڼ����������¼��㣬�ü�����ȥ��������������� 
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

// �����˷�
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

// ��������
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

// ����ȡģ����
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

// ����������
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




//������������ʮ�����ַ������� 2
void divideByTwo(char* num, char* result) {
    int len = strlen(num);
    int carry = 0;

    for (int i = 0; i < len; i++) {
        int currentDigit = num[i] - '0' + carry * 10;
        result[i] = (currentDigit / 2) + '0';
        carry = currentDigit % 2;
    }

    result[len] = '\0';

    //�Ƴ�ǰ����
    int start = 0;
    while (result[start] == '0' && result[start + 1] != '\0') {
        start++;
    }
    memmove(result, result + start, len - start + 1);
}

//��������������ַ����Ƿ�Ϊ��
int isZero(const char* num) {
    while (*num) {
        if (*num != '0') {
            return 0;
        }
        num++;
    }
    return 1;
}
//ʮ�����ַ�ת���ɶ�����
static char* decimalToBinary(const char* num, int bits) {
    //�����㹻��Ŀռ����洢�������ַ���
    char* binaryString = (char*)malloc(bits + 1);
    if (binaryString == NULL) {
        return NULL; // �ڴ����ʧ��
    }
    binaryString[bits] = '\0'; // �ַ�����β��

    //���������ַ�������Ϊ���ǻ��޸���
    char* tempNum = strdup(num);
    if (tempNum == NULL) {
        free(binaryString);
        return NULL; // �ڴ����ʧ��
    }

    //�����λ��ʼ���������ַ���
    for (int i = bits - 1; i >= 0; i--) {
        if (isZero(tempNum)) {
            binaryString[i] = '0'; // ����Ѿ�Ϊ�㣬���ʣ��λ
        }
        else {
            int lastDigit = (tempNum[strlen(tempNum) - 1] - '0') % 2;
            binaryString[i] = lastDigit ? '1' : '0'; // ��ȡ���λ�Ķ�����λ

            //��ʮ�����ַ������� 2
            char* dividedNum = (char*)malloc(strlen(tempNum) + 1);
            if (dividedNum == NULL) {
                free(binaryString);
                free(tempNum);
                return NULL; // �ڴ����ʧ��
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
    //��ʼ�����Ϊ "1"
    char* result = (char*)malloc(2 * sizeof(char));
    result[0] = '1';
    result[1] = '\0';
    //���� base �Ա����������
    char* tempBase = strdup(base);
    int len = strlen(binaryexp);

    //����������ָ����ÿһλ
    for (int i = 0; i < len; i++) {
        //�����ǰ������λΪ '1'����������Ե�ǰ�� base
        if (binaryexp[len - 1 - i] == '1') {
            char* newResult = multiply(result, tempBase);
            newResult = mod(newResult, m);
            free(result);
            result = newResult;
        }
        //base �������
        char* newBase = multiply(tempBase, tempBase);
        newBase = mod(newBase, m);
        free(tempBase);
        tempBase = newBase;
    }

    //�ͷ���ʱ����
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
    // ��������
    int bits;
    char num1[SIZE], num2[SIZE];
    char result[SIZE]; char binaryExp[SIZE]; char exp[SIZE]; char m[SIZE];
    // �ӷ�����
    strcpy(num1, "123456789123456789");
    strcpy(num2, "987654321987654321");
    strcpy(result, add(num1, num2));
    printf("Addition: %s + %s = %s\n", num1, num2, result);

    // ��������
    strcpy(num1, "987654321987654321");
    strcpy(num2, "123456789123456789");
    strcpy(result, subtract(num1, num2));
    printf("Subtraction: %s - %s = %s\n", num1, num2, result);

    // �˷�����
    strcpy(num1, "260");
    strcpy(num2, "20000000");
    strcpy(result, multiply(num1, num2));
    printf("Multiplication: %s * %s = %s\n", num1, num2, result);

    // ��������
    strcpy(num1, "6000");
    strcpy(num2, "5");
    strcpy(result, divide(num1, num2));
    printf("Division: %s / %s = %s\n", num1, num2, result);

    // ȡģ����
    strcpy(num1, "1661");
    strcpy(num2, "1000");
    strcpy(result, mod(num1, num2));
    printf("Modulo: %s %% %s = %s\n", num1, num2, result);

    // ������ģ����
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