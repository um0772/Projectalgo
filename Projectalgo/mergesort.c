#include "mergesort.h"

// 분할 정복을 사용하여 배열을 합병 정렬하는 함수
void mergesort_DC(int list[], int low, int high, int* sorted) {
    int middle;
    if (low < high) { // 배열 크기가 1보다 큰 경우에만 재귀적으로 정렬 수행
        middle = (low + high) / 2; // 중간 지점을 계산
        mergesort_DC(list, low, middle, sorted); // 왼쪽 부분 배열을 정렬
        mergesort_DC(list, middle + 1, high, sorted); // 오른쪽 부분 배열을 정렬
        merge(list, low, middle, high, sorted); // 정렬된 부분 배열을 병합
    }
}

// 두 개의 정렬된 배열을 합병하는 함수
void merge(int list[], int low, int mid, int high, int* sorted) {
    int i;

    int n1 = low, n2 = mid + 1, s = low; // 두 개의 부분 배열 및 임시 배열의 인덱스 초기화
    while (n1 <= mid && n2 <= high) {
        if (list[n1] <= list[n2]) sorted[s++] = list[n1++]; // 두 부분 배열 중 작은 값을 임시 배열에 복사
        else sorted[s++] = list[n2++];
    }

    if (n1 > mid) { // 왼쪽 부분 배열의 모든 요소가 처리되었을 경우
        while (n2 <= high) sorted[s++] = list[n2++]; // 오른쪽 부분 배열의 나머지 요소를 복사
    }
    else { // 오른쪽 부분 배열의 모든 요소가 처리되었을 경우
        while (n1 <= mid) sorted[s++] = list[n1++]; // 왼쪽 부분 배열의 나머지 요소를 복사
    }

    for (i = low; i <= high; i++) list[i] = sorted[i]; // 병합된 결과를 원래 배열에 복사
} // merge 함수 종료
