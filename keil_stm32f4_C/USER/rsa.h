#include "malloc.h"
#include <string.h>

#define SIZE 500  // Reduce array size to 500

void setZero(int* array, int size) {
    int i;
    for (i = 0; i < size; i++) {
        array[i] = 0;
    }
}
// ????????????
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
// ????????????
int copy(int* num1, int* num2) {
    int i, j;
    for (i = 0; i < SIZE; i++)
        num1[i] = 0;
    for (i = SIZE - 1; num2[i] == 0; i--);
    for (j = 0; j <= i; j++)
        num1[j] = num2[j];
    return i + 1;
}


char* add(char* str1, char* str2) {
    int* a;
    int* b;
    int* c;
    char* result;
    int i;
    int carry;
    int len1;
    int len2;
    int len;

    a = (int*)my_malloc(SIZE * sizeof(int));
    b = (int*)my_malloc(SIZE * sizeof(int));
    c = (int*)my_malloc(SIZE * sizeof(int));
    result = (char*)my_malloc((SIZE + 1) * sizeof(char));

    setZero(a, SIZE);
    setZero(b, SIZE);
    setZero(c, SIZE);

    carry = 0;
    len1 = strlen(str1);
    len2 = strlen(str2);
    len = (len1 > len2) ? len1 : len2;

    for (i = 0; i < len1; i++) {
        a[i] = str1[len1 - 1 - i] - '0';
    }
    for (i = 0; i < len2; i++) {
        b[i] = str2[len2 - 1 - i] - '0';
    }
    for (i = 0; i < len; i++) {
        c[i] = (a[i] + b[i] + carry) % 10;
        carry = (a[i] + b[i] + carry) / 10;
    }
    if (carry != 0) {
        c[len++] = 1;
    }

    for (i = len - 1; i >= 0; i--) {
        result[len - 1 - i] = c[i] + '0';
    }
    result[len] = '\0';

    //my_free(a);
    //my_free(b);
    //my_free(c);

    return result;
}

char* subtract(char* str1, char* str2) {
    int* a;
    int* b;
    int* c;
    char* result;
    int i;
    int borrow;
    int len1;
    int len2;
    int len;

    a = (int*)my_malloc(SIZE * sizeof(int));
    b = (int*)my_malloc(SIZE * sizeof(int));
    c = (int*)my_malloc(SIZE * sizeof(int));
    result = (char*)my_malloc((SIZE + 1) * sizeof(char));

    setZero(a, SIZE);
    setZero(b, SIZE);
    setZero(c, SIZE);

    borrow = 0;
    len1 = strlen(str1);
    len2 = strlen(str2);
    len = (len1 > len2) ? len1 : len2;

    for (i = 0; i < len1; i++) {
        a[i] = str1[len1 - 1 - i] - '0';
    }
    for (i = 0; i < len2; i++) {
        b[i] = str2[len2 - 1 - i] - '0';
    }

    if (len2 > len1) {
        for (i = 0; i < len; i++) {
            c[i] = b[i] - a[i] - borrow;
            if (c[i] < 0) {
                borrow = 1;
                c[i] += 10;
            } else {
                borrow = 0;
            }
        }
    } else {
        for (i = 0; i < len; i++) {
            c[i] = a[i] - b[i] - borrow;
            if (c[i] < 0 && i + 1 < len) {
                borrow = 1;
                c[i] += 10;
            } else {
                borrow = 0;
            }
        }
    }

    if (c[len - 1] < 0) {
        borrow = 0;
        for (i = 0; i < len; i++) {
            c[i] = b[i] - a[i] - borrow;
            if (c[i] < 0 && i + 1 < len) {
                borrow = 1;
                c[i] += 10;
            } else {
                borrow = 0;
            }
        }
    }

    while (c[len - 1] == 0 && len > 1) {
        len--;
    }

    for (i = len - 1; i >= 0; i--) {
        result[len - 1 - i] = c[i] + '0';
    }
    result[len] = '\0';

    //my_free(a);
    //my_free(b);
    //my_free(c);

    return result;
}


char* multiply(char* str1, char* str2) {
    int* a;
    int* b;
    int* c;
    char* result;
    int i, j, k, carry, tmp, len1, len2;

    a = (int*)my_malloc(SIZE * sizeof(int));
    b = (int*)my_malloc(SIZE * sizeof(int));
    c = (int*)my_malloc(SIZE * sizeof(int));
    result = (char*)my_malloc((SIZE + 1) * sizeof(char));

    setZero(a, SIZE);
    setZero(b, SIZE);
    setZero(c, SIZE);

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 > SIZE || len2 > SIZE) {
        result[0] = '\0';
        return result;
    }

    for (i = 0; i < len1; i++)
        a[i] = str1[len1 - 1 - i] - '0';
    for (i = 0; i < len2; i++)
        b[i] = str2[len2 - 1 - i] - '0';

    for (i = 0; i < len1; i++) {
        for (k = i, j = 0; j < len2; j++, k++) {
            c[k] += a[i] * b[j];
        }
    }

    carry = 0;
    for (i = 0; i < SIZE; i++) {
        c[i] += carry;
        tmp = c[i];
        c[i] = tmp % 10;
        carry = tmp / 10;
    }

    for (i = SIZE - 1; i >= 0 && c[i] == 0; i--);
    if (i == -1) {
        result[0] = '0';
        result[1] = '\0';
    }
    else {
        for (j = 0; j <= i; j++)
            result[j] = c[i - j] + '0';
        result[i + 1] = '\0';
    }
    printf("开始释放内存\n");

    my_free(a);
    my_free(b);
    my_free(c);
    printf("释放成功\n");

    return result;
}

char* mod(char* str1, char* str2) {
    int* a;
    int* b;
    int* c;
    int* temp;
    int* temp2;
    char* result;
	  int nonZeroFound;
    int i, j, tmp, tmp2 = 0, borrow = 0, len1, len2;

    a = (int*)my_malloc(SIZE * sizeof(int));
    b = (int*)my_malloc(SIZE * sizeof(int));
    c = (int*)my_malloc(SIZE * sizeof(int));
    temp = (int*)my_malloc(SIZE * sizeof(int));
    temp2 = (int*)my_malloc(SIZE * sizeof(int));
    result = (char*)my_malloc((SIZE + 1) * sizeof(char));

    setZero(a, SIZE);
    setZero(b, SIZE);
    setZero(c, SIZE);

    len1 = strlen(str1);
    len2 = strlen(str2);

    for (i = 0; i < len1; i++)
        a[i] = str1[len1 - 1 - i] - '0';
    for (i = 0; i < len2; i++)
        b[i] = str2[len2 - 1 - i] - '0';

    if (Compare(a, b) < 0) {
        for (i = len1 - 1; i >= 0; i--)
            result[len1 - 1 - i] = a[i] + '0';
        result[len1] = '\0';

        ////my_free(a);
        ////my_free(b);
        ////my_free(c);
        ////my_free(temp);
        ////my_free(temp2);

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

    // Handle the case where the result is 0
    nonZeroFound = 0;
    for (i = len1 - 1; i >= 0; i--) {
        result[len1 - 1 - i] = a[i] + '0';
        if (a[i] != 0) {
            nonZeroFound = 1;
        }
    }
    result[len1] = '\0';

    if (!nonZeroFound) {
        result[0] = '0';
        result[1] = '\0';
    }

    //my_free(a);
    //my_free(b);
    //my_free(c);
    //my_free(temp);
    //my_free(temp2);

    return result;
}

char* processed_mod(char* base,char* m)
{
    char* result;
    result = mod(base, m);
    if (strlen(result) == 0)
    {
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    else
    {
        return result;
    }
}

// ????:????????? 2
void divideByTwo(const char* num, char* result) {
    int len;
    int carry;
    int i;
	  int start;
    int currentDigit;
    carry = 0;
    len = strlen(num);

    for (i = 0; i < len; i++) {

        currentDigit = num[i] - '0' + carry * 10;
        
        result[i] = (currentDigit / 2) + '0';
        carry = currentDigit % 2;
    }

    result[len] = '\0';

    // ?????
     start = 0;
    while (result[start] == '0' && result[start + 1] != '\0') {
        start++;
    }
    memmove(result, result + start, len - start + 1);
}
// ????:?????????
int isZero(const char* num) {
    while (*num) {
        if (*num != '0') {
            return 0;
        }
        num++;
    }
    return 1;
}

// ???????????
char* decimalToBinary(const char* num, int bits) {
    // ?????????????????
    int i;
    char* binaryString;
    char* tempNum;
    char* dividedNum;
    int lastDigit;


    binaryString = (char*)my_malloc(bits + 1);
    if (binaryString == NULL) {
        return NULL; // ??????
    }
    binaryString[bits] = '\0'; // ??????

    // ???????,????????
    tempNum = (char*)my_malloc((strlen(num) + 1) * sizeof(char));
    if (tempNum == NULL) {
        ////my_free(binaryString);
        return NULL; // ??????
    }
    strcpy(tempNum, num);

    // ??????????????

    for (i = bits - 1; i >= 0; i--) {
        
        
        printf("if (isZero(tempNum)) {\n");
        if (isZero(tempNum)) {
            printf("isZero\n");
            binaryString[i] = '0'; // ??????,?????
        }
        else {
            printf("lastDigit = (tempNum[strlen(tempNum) - 1] - '0') % 2;\n");
            lastDigit = (tempNum[strlen(tempNum) - 1] - '0') % 2;
            printf("binaryString[i] = lastDigit ? '1' : '0';\n");
            binaryString[i] = lastDigit ? '1' : '0'; // ??????????

            // ????????? 2
            printf("dividedNum = (char*)my_malloc((strlen(tempNum) + 1) * sizeof(char));\n");
            dividedNum = (char*)my_malloc((strlen(tempNum) + 1) * sizeof(char));
            printf(" if (dividedNum == NULL) {\n");
            if (dividedNum == NULL) {
                ////my_free(binaryString);
                ////my_free(tempNum);
                return NULL; // ??????
            }
            printf("divideByTwo(tempNum, dividedNum);\n");
            divideByTwo(tempNum, dividedNum);
            printf(" //my_free(tempNum)\n");
            ////my_free(tempNum);
            printf("tempNum = dividedNum;;\n");
            tempNum = dividedNum;
        }
    }
    printf("Go out and free {\n");
    ////my_free(tempNum);
     printf("return {\n");
    return binaryString;
}


char* fastpowermod(const char* base, const char* binaryexp, const char* m) {
    // ?????? "1"
    char* result;
    char* tempBase;
    int len;
    char* newBase;
    char* modBase;
    char* modResult;
    char* newResult;
	    int i;

    result = (char*)my_malloc(2 * sizeof(char));
    if (!result) {
        return NULL; // ??????
    }
    result[0] = '1';
    result[1] = '\0';

    // ?? base ???????
    tempBase = (char*)my_malloc((strlen(base) + 1) * sizeof(char));
    if (!tempBase) {
        ////my_free(result);
        return NULL; // ??????
    }
    strcpy(tempBase, base);

    len = strlen(binaryexp);

    // ???????????

    for (i = 0; i < len; i++) {
        // ????????? '1',???????? base
        if (binaryexp[len - 1 - i] == '1') {
           newResult = multiply(result, tempBase);
            if (!newResult) {
                ////my_free(result);
                ////my_free(tempBase);
                return NULL; // ??????
            }
            modResult = processed_mod(newResult,(char*)m);
            ////my_free(newResult);
            ////my_free(result);
            result = modResult;
            if (!result) {
                ////my_free(tempBase);
                return NULL; // ??????
            }
        }

        // base ????
        newBase = multiply(tempBase, tempBase);
        if (!newBase) {
            ////my_free(result);
            ////my_free(tempBase);
            return NULL; // ??????
        }
        modBase = processed_mod(newBase, (char*)m);
        ////my_free(newBase);
        ////my_free(tempBase);
        tempBase = modBase;
        if (!tempBase) {
            ////my_free(result);
            return NULL; // ??????
        }
    }

    // ??????
    ////my_free(tempBase);
    return result;
}