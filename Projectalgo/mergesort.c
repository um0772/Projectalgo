#include "mergesort.h"

// ���� ������ ����Ͽ� �迭�� �պ� �����ϴ� �Լ�
void mergesort_DC(int list[], int low, int high, int* sorted) {
    int middle;
    if (low < high) { // �迭 ũ�Ⱑ 1���� ū ��쿡�� ��������� ���� ����
        middle = (low + high) / 2; // �߰� ������ ���
        mergesort_DC(list, low, middle, sorted); // ���� �κ� �迭�� ����
        mergesort_DC(list, middle + 1, high, sorted); // ������ �κ� �迭�� ����
        merge(list, low, middle, high, sorted); // ���ĵ� �κ� �迭�� ����
    }
}

// �� ���� ���ĵ� �迭�� �պ��ϴ� �Լ�
void merge(int list[], int low, int mid, int high, int* sorted) {
    int i;

    int n1 = low, n2 = mid + 1, s = low; // �� ���� �κ� �迭 �� �ӽ� �迭�� �ε��� �ʱ�ȭ
    while (n1 <= mid && n2 <= high) {
        if (list[n1] <= list[n2]) sorted[s++] = list[n1++]; // �� �κ� �迭 �� ���� ���� �ӽ� �迭�� ����
        else sorted[s++] = list[n2++];
    }

    if (n1 > mid) { // ���� �κ� �迭�� ��� ��Ұ� ó���Ǿ��� ���
        while (n2 <= high) sorted[s++] = list[n2++]; // ������ �κ� �迭�� ������ ��Ҹ� ����
    }
    else { // ������ �κ� �迭�� ��� ��Ұ� ó���Ǿ��� ���
        while (n1 <= mid) sorted[s++] = list[n1++]; // ���� �κ� �迭�� ������ ��Ҹ� ����
    }

    for (i = low; i <= high; i++) list[i] = sorted[i]; // ���յ� ����� ���� �迭�� ����
} // merge �Լ� ����
