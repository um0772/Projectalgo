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
        rn = rand() % (num - i) + i;    // i ���� num-1 ���̿� ������ ���� ����
        temp = arr[i];
        arr[i] = arr[rn];
        arr[rn] = temp;
    }
}

int main() {
    srand((unsigned int)time(NULL));
    
    int num;
    printf("������ �� �Է� : ");
    scanf("%d", &num);    // �迭�� ũ�⸦ �Է¹���
    int* arr = (int*)malloc(sizeof(int) * num);
    int* sorted = (int*)malloc(sizeof(int) * num);

    if (!arr) {
        printf("Memory allocation failed.\n");
        return 1; // �޸� �Ҵ� ���� �� ���α׷� ����
    }

    if (!sorted) {
        printf("Memory allocation merge failed. \n");
        return 1;
    }

    for (int i = 0; i < num; i++) {
        arr[i] = i + 1;    // �迭�� 1���� num ������ ��ҷ� �ʱ�ȭ
    }
 
    shuffle(arr, num);

    clock_t quick_start = clock();
    printf("���� �Ǻ� : %d\n", arr[0]);
    quicksort_DC(arr, 0, num - 1);
    clock_t quick_end = clock();

    printf("�� ���� �Ϸ�� �迭: ");
    for (int i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    clock_t merge_start = clock();
    mergesort_DC(arr, 0, num - 1, sorted);
    clock_t merge_end = clock();

    printf("�պ� ���� �Ϸ�� �迭: ");
    for (int i = 0; i < num; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

 
    
    printf("�� ���� �ҿ� �ð�: %lf\n", (double)(quick_end - quick_start) / CLOCKS_PER_SEC);

    printf("�պ� ���� �ҿ� �ð�: %lf\n", (double)(merge_end - merge_start) / CLOCKS_PER_SEC);

    free(arr);
    free(sorted);

    return 0;
}
    

