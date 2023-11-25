#include "shuffle.h"

// 배열을 무작위로 섞는 함수
void shuffle(int* list, int n) {
    int i;
    int temp;
    int rn;

    for (i = 0; i < n - 1; i++) {
        // 배열의 현재 위치(i)부터 끝까지 중에서 무작위로 하나의 위치(rn)를 선택
        rn = rand() % (n - i) + i;

        // 배열의 현재 위치(i)와 무작위 위치(rn)에 있는 요소 값을 교환
        temp = list[i];
        list[i] = list[rn];
        list[rn] = temp;
    }
}
