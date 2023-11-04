#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 9 // �ִ� ������ ���� 9�� �����մϴ�.
#define MAX_SIZE 100 // �ִ� �� ũ�⸦ 100���� �����մϴ�.
#define INF 999999 // ���Ѵ븦 ��Ÿ���� ������ 999999�� ����մϴ�.

typedef struct Graph {
    int V; // ������ ��Ÿ���ϴ�.
    int W; // �ش� ������ ����ġ�� ��Ÿ���ϴ�.
    struct Graph* link; // ���� ���� ������ ����Ű�� �������Դϴ�.

}Graph;

typedef struct inputGraph {
    int a; // �׷����� �� ���� ���� ��Ÿ���ϴ�.
    Graph* adjList[MAX_VERTICES]; // ���� ����Ʈ �Դϴ�.

}inputGraph;

typedef struct Heap {
    int heap; // ���� ����� ���� ����� ���Դϴ�.
    int size[MAX_SIZE]; // ���� ũ�⸦ �����ϴ� �迭�Դϴ�.
    int distance[MAX_SIZE]; // �� ���������� �Ÿ��� �����ϴ� �迭�Դϴ�.

}Heap;

Heap* init_Heap() {
    int i;
    Heap* h = (Heap*)malloc(sizeof(Heap)); // ���� ���� �Ҵ��մϴ�.
    if (h == NULL) {
        // �޸� �Ҵ翡 ������ ��� ���α׷��� �����մϴ�.
        exit(1);
    }
    h->heap = 0; // ���� �ʱ� ��� ���� 0���� �����մϴ�.
    for (i = 0; i < MAX_SIZE; i++) {
        h->distance[i] = INF; // �Ÿ� �迭�� ���Ѵ�� �ʱ�ȭ�մϴ�.
    }
    return h; // �ʱ�ȭ�� ���� ��ȯ�մϴ�.
}

void add_heap(Heap* h, int size, int dist) {
    h->heap += 1; // ���� ��Ҹ� �ϳ� �߰��մϴ�.
    h->size[h->heap] = size; // ���� ������ ��ġ�� �� ��Ҹ� �߰��մϴ�.
    h->distance[size] = dist; // �ش� ����� �Ÿ� ���� ������Ʈ�մϴ�.

    int child = h->heap; // �߰��� ����� ��ġ�Դϴ�.
    int parent = child / 2; // �θ� ����� ��ġ�Դϴ�.

    while (parent) {
        // �ڽ��� �θ𺸴� ������ �����մϴ�.
        if (h->distance[h->size[parent]] > h->distance[h->size[child]]) {
            int n = h->size[parent];
            h->size[parent] = h->size[child];
            h->size[child] = n;
            child = parent;
            parent = child / 2;
        }
        else
            break; // �θ� �ڽĺ��� �۰ų� ������ �ݺ��� �ߴ��մϴ�.
    }
}

int empty(Heap* h) {
    // ���� ��������� 1��, �׷��� ������ 0�� ��ȯ�մϴ�.
    return (h->heap ? 0 : 1);
}

int delete_min_heap(Heap* h) {
    if (h->heap == 0) {
        // ���� ��������� ���� �޽����� ����ϰ� -1�� ��ȯ�մϴ�.
        printf("heap empty\n");
        return -1;
    }
    int root = h->size[1]; // ���� ��Ʈ ���(���� ���� ��)�� �����ɴϴ�.
    h->size[1] = h->size[h->heap]; // ���� ������ ��Ҹ� ��Ʈ�� �̵��մϴ�.

    h->heap--; // �� ũ�⸦ 1 ���ҽ�ŵ�ϴ�.

    int parent = 1; // ��Ʈ���� �����մϴ�.
    int child = 2 * parent; // ��Ʈ�� �ڽ� ��ġ�Դϴ�.

    while (child <= h->heap) {
        // ������ �ڽ��� �ְ�, ���� �ڽĺ��� ������ ������ �ڽ��� �����մϴ�.
        if (child + 1 <= h->heap && h->distance[h->size[child]] > h->distance[h->size[child + 1]]) {
            child++;
        }
        // �θ𺸴� ���� �ڽ��� �θ�� ��ȯ�մϴ�.
        if (h->distance[h->size[parent]] > h->distance[h->size[child]]) {
            int temp = h->size[parent];
            h->size[parent] = h->size[child];
            h->size[child] = temp;

            parent = child;
            child = 2 * parent;
        }
        else {
            break; // �θ� �ڽĺ��� �۰ų� ������ �ݺ��� �ߴ��մϴ�.
        }
    }
    return root; // ���ŵ� ��Ʈ ��Ҹ� ��ȯ�մϴ�.
}

void init_adjList(inputGraph* g) {
    int i;
    g->a = 0; // �׷����� ���� ���� 0���� �ʱ�ȭ�մϴ�.
    for (i = 0; i < MAX_VERTICES; i++) {
        g->adjList[i] = NULL; // ���� ����Ʈ�� NULL�� �ʱ�ȭ�մϴ�.
    }
}
void add_vertex(inputGraph* g, int v) {
    if ((g->a) >= MAX_VERTICES) {
        // ������ ���� �ִ� ���� ���� �ʰ��ϸ� ���� �޽����� ����ϰ� �Լ��� �����մϴ�.
        fprintf(stderr, "���� ���� �ʰ�");
        return;
    }
    g->a++; // �׷����� ���� ���� 1 ������ŵ�ϴ�.
}


void add_edge(inputGraph* g, int u, int v, int w) {
    if (u >= MAX_VERTICES || v >= MAX_VERTICES) {
        fprintf(stderr, "���� ����"); // u �Ǵ� v�� �ִ� ���� ���� �ʰ��ϸ� ���� �޽����� ����մϴ�.
        return;
    }
    Graph* n1 = (Graph*)malloc(sizeof(Graph)); // u���� v�� ���� ������ ���� �޸𸮸� �Ҵ��մϴ�.
    Graph* n2 = (Graph*)malloc(sizeof(Graph)); // v���� u�� ���� ������ ���� �޸𸮸� �Ҵ��մϴ�.
    if (n1 == NULL || n2 == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����"); // �޸� �Ҵ翡 �����ϸ� ���� �޽����� ����ϰ� ���α׷��� �����մϴ�.
        exit(1);
    }
    // u���� v���� ���� �߰�
    n1->V = v;
    n1->W = w;
    n1->link = g->adjList[u];
    g->adjList[u] = n1;

    // v���� u���� ���� �߰�, ������ �׷����̱� ������ �������� �߰����ݴϴ�.
    n2->V = u;
    n2->W = w;
    n2->link = g->adjList[v];
    g->adjList[v] = n2;
}

void print_adjList(inputGraph* g) {
    int i;
    printf("-------���� ����Ʈ�� ����� �׷��� ���---------\n\n");
    for (i = 0; i < g->a; i++) {
        Graph* pg = g->adjList[i];
        printf("���� %d: ", i);
        while (pg != NULL) {
            if (i < pg->V) {
                // ������ ����ġ�� ����մϴ�.
                printf("%d -> %d (����ġ: %d) \t", i, pg->V, pg->W);
            }
            pg = pg->link;
        }
        printf("\n");
    }
    printf("\n");
    printf("----------------- key �� ��� ------------------\n\n");
}

void decrease_key(Heap* h, int v, int* distance) {
    int i;
    int prevDistance = h->distance[v]; // ���� ���� �Ÿ� ���� �����մϴ�.

    h->distance[v] = distance[v];  // ���� �Ÿ� ���� �����մϴ�.
    for (i = 1; i <= h->heap; i++) {
        if (h->size[i] == v) {
            int child = i;
            int parent = i / 2;
            // �θ�� �ڽ��� �Ÿ� ���� ���Ͽ�, �ʿ��� ��� ��ġ�� ��ȯ�մϴ�.
            while (parent) {
                if (h->distance[h->size[parent]] > h->distance[h->size[child]]) {
                    int n = h->size[parent];
                    h->size[parent] = h->size[child];
                    h->size[child] = n;
                    child = parent;
                    parent = child / 2;
                }
                else {
                    break;
                }
            }
            // �Ÿ� ���� ����Ǿ�����, ����� �Ÿ� ���� ����մϴ�.
            if (prevDistance != h->distance[v]) {
                printf("���� %d�� ����ġ�� %d���� %d�� ����Ǿ����ϴ�.\n", v, prevDistance, h->distance[v]);
            }
            break;
        }
    }
}

// ���� �˰��� ����
void Prim(inputGraph* g, Heap *heap, int root) {
    int distance[MAX_VERTICES]; // �� ���������� �Ÿ��� �����ϴ� �迭
    int nearest[MAX_VERTICES]; // ���� ����� ������ �����ϴ� �迭
    int MST[MAX_VERTICES] = { 0, }; // �ּ� ���� Ʈ���� ���Ե� ������ ǥ���ϴ� �迭
    int Weight = 0; // �ּ� ���� Ʈ���� �� ����ġ
    int i;

    // ��� ������ ���� �Ÿ��� ���Ѵ�� �ʱ�ȭ�ϰ�, �ּ� ���� �߰��մϴ�.
    for (i = 0; i < g->a; i++) {
        distance[i] = INF;
        nearest[i] = root;
        add_heap(heap, i, distance[i]);
    }
    // ���� ������ �Ÿ��� 0���� �����ϰ� Ű ���� ���ҽ�ŵ�ϴ�.
    distance[root] = 0;
    decrease_key(heap, root, distance);

    // ��� ������ ��ȸ�ϸ� �ּ� ���� Ʈ���� �����մϴ�.
    for (i = 0; i <= g->a - 2; i++) {
        int u = delete_min_heap(heap); // �ּ� ������ �ּ� �Ÿ� ������ �����մϴ�.
        MST[u] = 1; // ����� ������ �ּ� ���� Ʈ���� ���Խ�ŵ�ϴ�.

        // ����� ������ ������ �����鿡 ���� �Ÿ��� �����մϴ�.
        for (Graph* v = g->adjList[u]; v != NULL; v = v->link) {
            int w = v->V;
            if (!MST[w] && v->W < distance[w]) {
                distance[w] = v->W;
                nearest[w] = u;
                decrease_key(heap, w, distance);
            }
        }
    }

    // �ּ� ���� Ʈ���� ����� ����մϴ�.
    printf("\n");
    printf("----------------���� ����ġ ���----------------\n\n");
    printf("���� ������ %d\n", root);
    for (i = 0; i < g->a; i++) {
        if (i != root && distance[i] != INF) {
            printf("���� %d���� %d | ����ġ: %d\n", nearest[i], i, distance[i]);
            Weight += distance[i]; // �� ����ġ�� ����մϴ�.
        }
    }
    printf("\n");
    printf("�ּ� ����ġ ���� %d�̴�.\n", Weight);  // �� ����ġ�� ����մϴ�.
}

//main �Լ�
int main() {
    inputGraph* g;
    g = (inputGraph*)malloc(sizeof(inputGraph)); // �׷����� ���� �޸� �Ҵ�

    Heap* h = init_Heap(); // �� �ʱ�ȭ
    init_adjList(g); // ���� ����Ʈ �ʱ�ȭ
    int i;
    // �׷����� �������� �߰��մϴ�.
    for (i = 0; i < 9; i++) {
        add_vertex(g, i);
    }
    // �׷����� �������� �߰��մϴ�. �� ������ �� ������ ����ġ�� �����ϴ�.
    add_edge(g, 0, 1, 4);
    add_edge(g, 0, 7, 8);
    add_edge(g, 1, 2, 8);
    add_edge(g, 1, 7, 11);
    add_edge(g, 2, 3, 7);
    add_edge(g, 2, 8, 2);
    add_edge(g, 2, 5, 4);
    add_edge(g, 3, 4, 9);
    add_edge(g, 3, 5, 14);
    add_edge(g, 4, 5, 10);
    add_edge(g, 5, 6, 2);
    add_edge(g, 6, 7, 1);
    add_edge(g, 6, 8, 6);
    add_edge(g, 7, 8, 7);
    print_adjList(g); // ���� ����Ʈ�� �̿��� �׷��� ���
   
    Prim(g, h, 0); // ���� �˰����� ���� ���� 0���� �����մϴ�.
   
    return 0;
}

