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

    printf("데이터 수 입력 : ");
    scanf("%d", &n);    // 배열의 크기를 입력받음
    int* sortlist = (int*)malloc(sizeof(int) * n);
    int* mergesort = (int*)malloc(sizeof(int) * n);
    int* copylist = (int*)malloc(sizeof(int) * n);

    if (!sortlist) {
        printf("Memory allocation failed.\n");
        return 1; // 메모리 할당 실패 시 프로그램 종료
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
        sortlist[i] = i + 1;    // 배열을 1부터 num 까지의 요소로 초기화
    }


    shuffle(sortlist, n);

    /*
    printf("셔플된 배열: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    
    memcpy(copylist, sortlist, sizeof(int) * n);

    
    printf("셔플된 배열: ");
    for (i = 0; i < n; i++) {
        printf("%d ", copylist[i]);
    }
    printf("\n\n");
    */

    printf("현재 피봇 : %d\n", sortlist[0]);
    clock_t quick_start = clock();
    quicksort_DC(sortlist, 0, n - 1, threshold);
    clock_t quick_end = clock();

    clock_t merge_start = clock();
    mergesort_DC(copylist, 0, n - 1, mergesort);
    clock_t merge_end = clock();

    printf("퀵 정렬 소요 시간: %lf\n", (double)(quick_end - quick_start) / CLOCKS_PER_SEC);

    printf("합병 정렬 소요 시간: %lf\n", (double)(merge_end - merge_start) / CLOCKS_PER_SEC);

    /*
    printf("퀵 정렬 완료된 배열: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");

    
    printf("합병 정렬 완료된 배열: ");
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

