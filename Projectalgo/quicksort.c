#include "quicksort.h"

// 분할 정복을 사용하여 배열을 퀵 정렬하는 함수
void quicksort_DC(int list[], int low, int high, int threshold) {
    if (high - low + 1 <= threshold) { // 임계값 조건 체크
        insertion_sort(list, low, high); // 임계값 이하의 배열 크기에는 삽입 정렬을 수행
    }
    else if(low < high) { // 배열 크기가 1보다 큰 경우에만 정렬을 수행
        int pivot_pos = partition(list, low, high); // 배열을 분할하고 피봇의 위치를 찾음
        quicksort_DC(list, low, pivot_pos - 1, threshold); // 피봇을 기준으로 왼쪽 부분 배열을 정렬
        quicksort_DC(list, pivot_pos + 1, high, threshold); // 피봇을 기준으로 오른쪽 부분 배열을 정렬
    }
}

// 배열을 분할하고 피봇의 위치를 찾는 함수
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

    return j; // 피봇의 위치를 반환
}
