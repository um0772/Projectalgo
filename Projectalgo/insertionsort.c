#include "insertionsort.h"

// 삽입 정렬 알고리즘을 사용하여 배열의 일부를 정렬하는 함수
void insertion_sort(int list[], int low, int high) {
    int i, j, next; // 반복문 변수와 다음 값을 임시로 저장할 변수 선언
    for (i = low + 1; i <= high; i++) { // 배열의 일부를 순회하며 삽입 정렬 수행
        next = list[i]; // 다음 값을 임시 변수에 저장
        j = i - 1; // 현재 위치의 이전 위치를 가리키는 변수 설정

        // 'low' 인덱스를 기준으로 하여, 'high' 인덱스까지 삽입 정렬 실행
        while (j >= low && list[j] > next) { // 현재 위치보다 큰 값을 찾을 때까지 반복
            list[j + 1] = list[j]; // 큰 값을 현재 위치로 이동
            j--; // 이전 위치로 이동
        }

        list[j + 1] = next; // 찾은 적절한 위치에 다음 값을 삽입
    }
} // 삽입 정렬 함수 종료
