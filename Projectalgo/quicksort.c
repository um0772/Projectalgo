#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void quicksort_DC(int list[], int low, int high);
int partition(int list[], int low, int high);
void shuffle(int* arr, int num);

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
    if (!arr) {
        printf("Memory allocation failed.\n");
        return 1; // 메모리 할당 실패 시 프로그램 종료
    }
    for (int i = 0; i < num; i++) {
        arr[i] = i + 1;    // 배열을 1부터 num 까지의 요소로 초기화
    }
 
    shuffle(arr, num);

    clock_t start = clock();
    printf("현재 피봇 : %d\n", arr[0]);
    quicksort_DC(arr, 0, num - 1);
    clock_t end = clock();
    
    printf("소요 시간: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

   
    free(arr);
    return 0;
}
    

