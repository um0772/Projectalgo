#include "shuffle.h"

// �迭�� �������� ���� �Լ�
void shuffle(int* list, int n) {
    int i;
    int temp;
    int rn;

    for (i = 0; i < n - 1; i++) {
        // �迭�� ���� ��ġ(i)���� ������ �߿��� �������� �ϳ��� ��ġ(rn)�� ����
        rn = rand() % (n - i) + i;

        // �迭�� ���� ��ġ(i)�� ������ ��ġ(rn)�� �ִ� ��� ���� ��ȯ
        temp = list[i];
        list[i] = list[rn];
        list[rn] = temp;
    }
}
