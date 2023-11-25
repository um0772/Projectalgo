#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

void quicksort_DC(int list[], int low, int high, int threshold);
int partition(int list[], int low, int high);
void shuffle(int* arr, int num);
void insertion_sort(int list[], int low, int high);
void mergesort_DC(int list[], int low, int high, int* sorted);
void merge(int list[], int low, int mid, int high, int* sorted);


void quicksort_DC(int list[], int low, int high, int threshold) {
    if (high - low + 1 <= threshold) { // �Ӱ谪 ���� üũ
        insertion_sort(list, low, high);
    }
    else {
        int pivot_pos = partition(list, low, high);
        quicksort_DC(list, low, pivot_pos - 1, threshold);
        quicksort_DC(list, pivot_pos + 1, high, threshold);
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

void insertion_sort(int list[], int low, int high) {
    int i, j, next;
    for (i = low + 1; i <= high; i++) {
        next = list[i];
        j = i - 1;
        // 'low' �ε����� �������� �Ͽ�, 'high' �ε������� ���� ���� ����
        while (j >= low && list[j] > next) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = next;
    }
}

void shuffle(int* list, int n)
{
    int i;
    int temp;
    int rn;
    for (i = 0; i < n - 1; i++)
    {
        rn = rand() % (n - i) + i; 
        temp = list[i];
        list[i] = list[rn];
        list[rn] = temp;
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int threshold = 10000;
    int n;
    int i;

    printf("������ �� �Է� : ");
    scanf("%d", &n);    // �迭�� ũ�⸦ �Է¹���
    int* sortlist = (int*)malloc(sizeof(int) * n);
    int* mergesort = (int*)malloc(sizeof(int) * n);
    int* sortlistCopy = (int*)malloc(sizeof(int) * n);

    if (!sortlist) {
        printf("Memory allocation failed.\n");
        return 1; // �޸� �Ҵ� ���� �� ���α׷� ����
    }
    
    if (!mergesort) {
        printf("Memory allocation merge failed. \n");
        return 1;
    }
    if (!sortlistCopy) {
        printf("Memory allocation merge failed. \n");
        return 1;
    }
    
    for (i = 0; i < n; i++) {
        sortlist[i] = i + 1;    // �迭�� 1���� num ������ ��ҷ� �ʱ�ȭ
    }
    
    /*
    for (i = 0; i < n; i++) {
        sortlist[i] = rand() % 1000000 + 1; // 1���� 100 ������ ���� �Ҵ�
    }
    */

    shuffle(sortlist, n);
    /*
    printf("���õ� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    */
    memcpy(sortlistCopy, sortlist, sizeof(int) * n);

    /*
    printf("���õ� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlistCopy[i]);
    }
    printf("\n\n");
    */

    printf("���� �Ǻ� : %d\n", sortlist[0]);
    clock_t quick_start = clock();
    quicksort_DC(sortlist, 0, n - 1, threshold);
    clock_t quick_end = clock();
    
    clock_t merge_start = clock();
    mergesort_DC(sortlistCopy, 0, n - 1, mergesort);
    clock_t merge_end = clock();
   
  
    


    printf("�� ���� �ҿ� �ð�: %lf\n", (double)(quick_end - quick_start) / CLOCKS_PER_SEC);
    
    printf("�պ� ���� �ҿ� �ð�: %lf\n", (double)(merge_end - merge_start) / CLOCKS_PER_SEC);

    /*
    printf("�� ���� �Ϸ�� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    */
    /*
    printf("�պ� ���� �Ϸ�� �迭: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sortlist[i]);
    }
    printf("\n\n");
    */

    free(sortlist);
    free(mergesort);
    free(sortlistCopy);

    return 0;
}


