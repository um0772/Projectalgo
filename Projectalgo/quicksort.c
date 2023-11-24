#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void quicksort_DC(int list[], int low, int high);
int partition(int list[], int low, int high);
void shuffle(int* arr, int num);
void mergesort_DC(int list[], int low, int high, int* sorted);
void merge(int list[], int low, int mid, int high, int* sorted);

void quicksort_DC(int list[], int low, int high) {
    int pivot_pos;
    if (low < high) {
        pivot_pos = partition(list, low, high);
        //quicksort_DC(list, low, pivot_pos - 1);
        //quicksort_DC(list, pivot_pos + 1, high);
    }
}

int partition(int list[], int low, int high) {
    int i, j = low;
    for (i = low + 1; i <= high; i++) {
        if (list[i] < list[low]) {
            j++;
            // 여기에서 list[i]와 list[j]의 값을 교환합니다.
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    // 마지막으로 list[low]와 list[j]의 값을 교환합니다.
    int temp = list[low];
    list[low] = list[j];
    list[j] = temp;

    return j;
}

void mergesort_DC(int list[], int low, int high, int* sorted) {
    int middle;
    if (low < high) {
        middle = (low + high) / 2;
        mergesort_DC(list, low, middle, sorted);
        mergesort_DC(list, middle + 1, high, sorted);
        merge(list, low, middle, high, sorted);
    }
}

void merge(int list[], int low, int mid, int high, int* sorted) {
    int i;
    
    int n1 = low, n2 = mid + 1, s = low;
    while (n1 <= mid && n2 <= high) {
        if (list[n1] <= list[n2]) sorted[s++] = list[n1++];
        else sorted[s++] = list[n2++];
    }

    if (n1 > mid) {
        while (n2 <= high) sorted[s++] = list[n2++];
    }
    else {
        while (n1 <= mid) sorted[s++] = list[n1++];
    }

    for (i = low; i <= high; i++) list[i] = sorted[i];

}
void shuffle(int* arr, int num)
{
    
    int temp;
    int rn;
    for (int i = 0; i < num - 1; i++)
    {
        rn = rand() % (num - i) + i;    // i 부터 num-1 사이에 임의의 정수 생성
        temp = arr[i];
        arr[i] = arr[rn];
        arr[rn] = temp;
    }
}

int main() {
    srand((unsigned int)time(NULL));
    
    int num;
    printf("데이터 수 입력 : ");
    scanf("%d", &num);    // 배열의 크기를 입력받음
    int* arr = (int*)malloc(sizeof(int) * num);
    int* sorted = (int*)malloc(sizeof(int) * num);

    if (!arr) {
        printf("Memory allocation failed.\n");
        return 1; // 메모리 할당 실패 시 프로그램 종료
    }

    if (!sorted) {
        printf("Memory allocation merge failed. \n");
        return 1;
    }

    for (int i = 0; i < num; i++) {
        arr[i] = i + 1;    // 배열을 1부터 num 까지의 요소로 초기화
    }
 
    shuffle(arr, num);

    clock_t quick_start = clock();
    printf("현재 피봇 : %d\n", arr[0]);
    quicksort_DC(arr, 0, num - 1);
    clock_t quick_end = clock();

    printf("퀵 정렬 완료된 배열: ");
    for (int i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    clock_t merge_start = clock();
    mergesort_DC(arr, 0, num - 1, sorted);
    clock_t merge_end = clock();

    printf("합병 정렬 완료된 배열: ");
    for (int i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

 
    
    printf("퀵 정렬 소요 시간: %lf\n", (double)(quick_end - quick_start) / CLOCKS_PER_SEC);

    printf("합병 정렬 소요 시간: %lf\n", (double)(merge_end - merge_start) / CLOCKS_PER_SEC);

    free(arr);
    free(sorted);

    return 0;
}
    

