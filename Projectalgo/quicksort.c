#include "quicksort.h"

// ���� ������ ����Ͽ� �迭�� �� �����ϴ� �Լ�
void quicksort_DC(int list[], int low, int high, int threshold) {
    if (high - low + 1 <= threshold) { // �Ӱ谪 ���� üũ
        insertion_sort(list, low, high); // �Ӱ谪 ������ �迭 ũ�⿡�� ���� ������ ����
    }
    else if(low < high) { // �迭 ũ�Ⱑ 1���� ū ��쿡�� ������ ����
        int pivot_pos = partition(list, low, high); // �迭�� �����ϰ� �Ǻ��� ��ġ�� ã��
        quicksort_DC(list, low, pivot_pos - 1, threshold); // �Ǻ��� �������� ���� �κ� �迭�� ����
        quicksort_DC(list, pivot_pos + 1, high, threshold); // �Ǻ��� �������� ������ �κ� �迭�� ����
    }
}

// �迭�� �����ϰ� �Ǻ��� ��ġ�� ã�� �Լ�
int partition(int list[], int low, int high) {
    int i, j = low;
    for (i = low + 1; i <= high; i++) {
        if (list[i] < list[low]) {
            j++;
            // ���⿡�� list[i]�� list[j]�� ���� ��ȯ�մϴ�.
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    // ���������� list[low]�� list[j]�� ���� ��ȯ�մϴ�.
    int temp = list[low];
    list[low] = list[j];
    list[j] = temp;

    return j; // �Ǻ��� ��ġ�� ��ȯ
}
