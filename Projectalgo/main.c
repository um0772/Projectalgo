#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "quicksort.h"
#include "mergesort.h"
#include "insertionsort.h"
#include "shuffle.h"



int main() {
    srand((unsigned int)time(NULL));
    int threshold = 0;
    int n;
    int i;

    printf("������ �� �Է� : ");
    scanf("%d", &n);    // �迭�� ũ�⸦ �Է¹���
    int* sortlist = (int*)malloc(sizeof(int) * n);
    int* mergesort = (int*)malloc(sizeof(int) * n);
    int* copylist = (int*)malloc(sizeof(int) * n);

    if (!sortlist) {
        printf("Memory allocation failed.\n");
        return 1; // �޸� �Ҵ� ���� �� ���α׷� ����
    }

    if (!mergesort) {
        printf("Memory allocation merge failed. \n");
        return 1;
    }
    if (!copylist) {
        printf("Memory allocation merge failed. \n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        sortlist[i] = i + 1;    // �迭�� 1���� num ������ ��ҷ� �ʱ�ȭ
    }


    shuffle(sortlist, n);

    /*
    printf("���õ� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    
    memcpy(copylist, sortlist, sizeof(int) * n);

    
    printf("���õ� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", copylist[i]);
    }
    printf("\n\n");
    */

    printf("���� �Ǻ� : %d\n", sortlist[0]);
    clock_t quick_start = clock();
    quicksort_DC(sortlist, 0, n - 1, threshold);
    clock_t quick_end = clock();

    clock_t merge_start = clock();
    mergesort_DC(copylist, 0, n - 1, mergesort);
    clock_t merge_end = clock();

    printf("�� ���� �ҿ� �ð�: %lf\n", (double)(quick_end - quick_start) / CLOCKS_PER_SEC);

    printf("�պ� ���� �ҿ� �ð�: %lf\n", (double)(merge_end - merge_start) / CLOCKS_PER_SEC);

    /*
    printf("�� ���� �Ϸ�� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");

    
    printf("�պ� ���� �Ϸ�� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    */

    free(sortlist);
    free(mergesort);
    free(copylist);

    return 0;
} 

