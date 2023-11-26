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
    srand((unsigned int)time(NULL));  // 무작위 수 생성을 위한 난수 초기화
    int threshold = 14;               // 삽입 정렬을 위한 임계값
    int n;                           // 배열의 크기
    int i;

    printf("데이터 수 입력 : ");
    scanf("%d", &n);                // 사용자로부터 배열의 크기를 입력받음
    int* sortlist = (int*)malloc(sizeof(int) * n);   // 정렬할 배열을 동적으로 할당
    int* mergesort = (int*)malloc(sizeof(int) * n);  // 합병 정렬을 위한 배열 할당
    int* copylist = (int*)malloc(sizeof(int) * n);    // 복사할 배열 할당

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
        sortlist[i] = i + 1;    // 배열을 1부터 n까지의 요소로 초기화
    }

    shuffle(sortlist, n);  // 배열을 무작위로 섞음

    /*
    printf("sortlist 배열 셔플: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    */

    memcpy(copylist, sortlist, sizeof(int) * n);  // 정렬 결과를 비교하기 위해 복사

    /*
    printf("sortlist 배열 복사: ");
    for (i = 0; i < n; i++) {
        printf("%d ", copylist[i]);
    }
    printf("\n\n");
    */
    
    printf("현재 피봇 : %d\n", sortlist[0]);
    
    
    clock_t quick_start = clock();  // 퀵 정렬 시작 시간 측정
    quicksort_DC(sortlist, 0, n - 1, threshold);  // 퀵 정렬 수행
    clock_t quick_end = clock();    // 퀵 정렬 종료 시간 측정

    clock_t merge_start = clock();  // 합병 정렬 시작 시간 측정
    mergesort_DC(copylist, 0, n - 1, mergesort);  // 합병 정렬 수행
    clock_t merge_end = clock();    // 합병 정렬 종료 시간 측정
    
    printf("퀵 정렬 소요 시간: %lf\n", (double)(quick_end - quick_start) / CLOCKS_PER_SEC);  // 소요 시간 출력

    printf("합병 정렬 소요 시간: %lf\n", (double)(merge_end - merge_start) / CLOCKS_PER_SEC);  // 소요 시간 출력
    
    /*
    printf("퀵 정렬 완료된 배열: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    
    
    printf("합병 정렬 완료된 배열: ");
    for (i = 0; i < n; i++) {
        printf("%d ", copylist[i]);
    }
    printf("\n\n");
    */

    free(sortlist);     // 동적으로 할당한 메모리 해제
    free(mergesort);    // 동적으로 할당한 메모리 해제
    free(copylist);     // 동적으로 할당한 메모리 해제

    return 0;
} 

