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
    if (!arr) {
        printf("Memory allocation failed.\n");
        return 1; // �޸� �Ҵ� ���� �� ���α׷� ����
    }
    for (int i = 0; i < num; i++) {
        arr[i] = i + 1;    // �迭�� 1���� num ������ ��ҷ� �ʱ�ȭ
    }
 
    shuffle(arr, num);

    clock_t start = clock();
    printf("���� �Ǻ� : %d\n", arr[0]);
    quicksort_DC(arr, 0, num - 1);
    clock_t end = clock();
    
    printf("�ҿ� �ð�: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

   
    free(arr);
    return 0;
}
    

