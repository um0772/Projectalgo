#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "quicksort.h"
#include "mergesort.h"
#include "insertionsort.h"
#include "shuffle.h"



int main() {
    srand((unsigned int)time(NULL));  // ������ �� ������ ���� ���� �ʱ�ȭ
    int threshold = 14;               // ���� ������ ���� �Ӱ谪
    int n;                           // �迭�� ũ��
    int i;

    printf("������ �� �Է� : ");
    scanf("%d", &n);                // ����ڷκ��� �迭�� ũ�⸦ �Է¹���
    int* sortlist = (int*)malloc(sizeof(int) * n);   // ������ �迭�� �������� �Ҵ�
    int* mergesort = (int*)malloc(sizeof(int) * n);  // �պ� ������ ���� �迭 �Ҵ�
    int* copylist = (int*)malloc(sizeof(int) * n);    // ������ �迭 �Ҵ�

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
        sortlist[i] = i + 1;    // �迭�� 1���� n������ ��ҷ� �ʱ�ȭ
    }

    shuffle(sortlist, n);  // �迭�� �������� ����

    /*
    printf("sortlist �迭 ����: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    */

    memcpy(copylist, sortlist, sizeof(int) * n);  // ���� ����� ���ϱ� ���� ����

    /*
    printf("sortlist �迭 ����: ");
    for (i = 0; i < n; i++) {
        printf("%d ", copylist[i]);
    }
    printf("\n\n");
    */
    
    printf("���� �Ǻ� : %d\n", sortlist[0]);
    
    
    clock_t quick_start = clock();  // �� ���� ���� �ð� ����
    quicksort_DC(sortlist, 0, n - 1, threshold);  // �� ���� ����
    clock_t quick_end = clock();    // �� ���� ���� �ð� ����

    clock_t merge_start = clock();  // �պ� ���� ���� �ð� ����
    mergesort_DC(copylist, 0, n - 1, mergesort);  // �պ� ���� ����
    clock_t merge_end = clock();    // �պ� ���� ���� �ð� ����
    
    printf("�� ���� �ҿ� �ð�: %lf\n", (double)(quick_end - quick_start) / CLOCKS_PER_SEC);  // �ҿ� �ð� ���

    printf("�պ� ���� �ҿ� �ð�: %lf\n", (double)(merge_end - merge_start) / CLOCKS_PER_SEC);  // �ҿ� �ð� ���
    
    /*
    printf("�� ���� �Ϸ�� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    
    
    printf("�պ� ���� �Ϸ�� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", copylist[i]);
    }
    printf("\n\n");
    */

    free(sortlist);     // �������� �Ҵ��� �޸� ����
    free(mergesort);    // �������� �Ҵ��� �޸� ����
    free(copylist);     // �������� �Ҵ��� �޸� ����

    return 0;
} 

