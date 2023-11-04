#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 9 // 최대 정점의 수를 9로 정의합니다.
#define MAX_SIZE 100 // 최대 힙 크기를 100으로 정의합니다.
#define INF 999999 // 무한대를 나타내는 값으로 999999를 사용합니다.

typedef struct Graph {
    int V; // 정점을 나타냅니다.
    int W; // 해당 정점의 가중치를 나타냅니다.
    struct Graph* link; // 다음 인접 정점을 가리키는 포인터입니다.

}Graph;

typedef struct inputGraph {
    int a; // 그래프의 총 정점 수를 나타냅니다.
    Graph* adjList[MAX_VERTICES]; // 인접 리스트 입니다.

}inputGraph;

typedef struct Heap {
    int heap; // 힙에 저장된 현재 요소의 수입니다.
    int size[MAX_SIZE]; // 힙의 크기를 저장하는 배열입니다.
    int distance[MAX_SIZE]; // 각 정점까지의 거리를 저장하는 배열입니다.

}Heap;

Heap* init_Heap() {
    int i;
    Heap* h = (Heap*)malloc(sizeof(Heap)); // 힙을 동적 할당합니다.
    if (h == NULL) {
        // 메모리 할당에 실패한 경우 프로그램을 종료합니다.
        exit(1);
    }
    h->heap = 0; // 힙의 초기 요소 수를 0으로 설정합니다.
    for (i = 0; i < MAX_SIZE; i++) {
        h->distance[i] = INF; // 거리 배열을 무한대로 초기화합니다.
    }
    return h; // 초기화된 힙을 반환합니다.
}

void add_heap(Heap* h, int size, int dist) {
    h->heap += 1; // 힙에 요소를 하나 추가합니다.
    h->size[h->heap] = size; // 힙의 마지막 위치에 새 요소를 추가합니다.
    h->distance[size] = dist; // 해당 요소의 거리 값을 업데이트합니다.

    int child = h->heap; // 추가된 요소의 위치입니다.
    int parent = child / 2; // 부모 요소의 위치입니다.

    while (parent) {
        // 자식이 부모보다 작으면 스왑합니다.
        if (h->distance[h->size[parent]] > h->distance[h->size[child]]) {
            int n = h->size[parent];
            h->size[parent] = h->size[child];
            h->size[child] = n;
            child = parent;
            parent = child / 2;
        }
        else
            break; // 부모가 자식보다 작거나 같으면 반복을 중단합니다.
    }
}

int empty(Heap* h) {
    // 힙이 비어있으면 1을, 그렇지 않으면 0을 반환합니다.
    return (h->heap ? 0 : 1);
}

int delete_min_heap(Heap* h) {
    if (h->heap == 0) {
        // 힙이 비어있으면 오류 메시지를 출력하고 -1을 반환합니다.
        printf("heap empty\n");
        return -1;
    }
    int root = h->size[1]; // 힙의 루트 요소(가장 작은 값)를 가져옵니다.
    h->size[1] = h->size[h->heap]; // 힙의 마지막 요소를 루트로 이동합니다.

    h->heap--; // 힙 크기를 1 감소시킵니다.

    int parent = 1; // 루트부터 시작합니다.
    int child = 2 * parent; // 루트의 자식 위치입니다.

    while (child <= h->heap) {
        // 오른쪽 자식이 있고, 왼쪽 자식보다 작으면 오른쪽 자식을 선택합니다.
        if (child + 1 <= h->heap && h->distance[h->size[child]] > h->distance[h->size[child + 1]]) {
            child++;
        }
        // 부모보다 작은 자식을 부모와 교환합니다.
        if (h->distance[h->size[parent]] > h->distance[h->size[child]]) {
            int temp = h->size[parent];
            h->size[parent] = h->size[child];
            h->size[child] = temp;

            parent = child;
            child = 2 * parent;
        }
        else {
            break; // 부모가 자식보다 작거나 같으면 반복을 중단합니다.
        }
    }
    return root; // 제거된 루트 요소를 반환합니다.
}

void init_adjList(inputGraph* g) {
    int i;
    g->a = 0; // 그래프의 정점 수를 0으로 초기화합니다.
    for (i = 0; i < MAX_VERTICES; i++) {
        g->adjList[i] = NULL; // 인접 리스트를 NULL로 초기화합니다.
    }
}
void add_vertex(inputGraph* g, int v) {
    if ((g->a) >= MAX_VERTICES) {
        // 정점의 수가 최대 정점 수를 초과하면 오류 메시지를 출력하고 함수를 종료합니다.
        fprintf(stderr, "정점 개수 초과");
        return;
    }
    g->a++; // 그래프의 정점 수를 1 증가시킵니다.
}


void add_edge(inputGraph* g, int u, int v, int w) {
    if (u >= MAX_VERTICES || v >= MAX_VERTICES) {
        fprintf(stderr, "간선 오류"); // u 또는 v가 최대 정점 수를 초과하면 오류 메시지를 출력합니다.
        return;
    }
    Graph* n1 = (Graph*)malloc(sizeof(Graph)); // u에서 v로 가는 간선을 위한 메모리를 할당합니다.
    Graph* n2 = (Graph*)malloc(sizeof(Graph)); // v에서 u로 가는 간선을 위한 메모리를 할당합니다.
    if (n1 == NULL || n2 == NULL) {
        fprintf(stderr, "메모리 할당 실패"); // 메모리 할당에 실패하면 오류 메시지를 출력하고 프로그램을 종료합니다.
        exit(1);
    }
    // u에서 v로의 간선 추가
    n1->V = v;
    n1->W = w;
    n1->link = g->adjList[u];
    g->adjList[u] = n1;

    // v에서 u로의 간선 추가, 무방향 그래프이기 때문에 양쪽으로 추가해줍니다.
    n2->V = u;
    n2->W = w;
    n2->link = g->adjList[v];
    g->adjList[v] = n2;
}

void print_adjList(inputGraph* g) {
    int i;
    printf("-------인접 리스트를 사용한 그래프 출력---------\n\n");
    for (i = 0; i < g->a; i++) {
        Graph* pg = g->adjList[i];
        printf("정점 %d: ", i);
        while (pg != NULL) {
            if (i < pg->V) {
                // 간선과 가중치를 출력합니다.
                printf("%d -> %d (가중치: %d) \t", i, pg->V, pg->W);
            }
            pg = pg->link;
        }
        printf("\n");
    }
    printf("\n");
    printf("----------------- key 값 출력 ------------------\n\n");
}

void decrease_key(Heap* h, int v, int* distance) {
    int i;
    int prevDistance = h->distance[v]; // 변경 전의 거리 값을 저장합니다.

    h->distance[v] = distance[v];  // 힙의 거리 값을 갱신합니다.
    for (i = 1; i <= h->heap; i++) {
        if (h->size[i] == v) {
            int child = i;
            int parent = i / 2;
            // 부모와 자식의 거리 값을 비교하여, 필요한 경우 위치를 교환합니다.
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
            // 거리 값이 변경되었으면, 변경된 거리 값을 출력합니다.
            if (prevDistance != h->distance[v]) {
                printf("정점 %d의 가중치가 %d에서 %d로 변경되었습니다.\n", v, prevDistance, h->distance[v]);
            }
            break;
        }
    }
}

// 프림 알고리즘 구현
void Prim(inputGraph* g, Heap *heap, int root) {
    int distance[MAX_VERTICES]; // 각 정점까지의 거리를 저장하는 배열
    int nearest[MAX_VERTICES]; // 가장 가까운 정점을 저장하는 배열
    int MST[MAX_VERTICES] = { 0, }; // 최소 신장 트리에 포함된 정점을 표시하는 배열
    int Weight = 0; // 최소 신장 트리의 총 가중치
    int i;

    // 모든 정점에 대해 거리를 무한대로 초기화하고, 최소 힙에 추가합니다.
    for (i = 0; i < g->a; i++) {
        distance[i] = INF;
        nearest[i] = root;
        add_heap(heap, i, distance[i]);
    }
    // 시작 정점의 거리를 0으로 설정하고 키 값을 감소시킵니다.
    distance[root] = 0;
    decrease_key(heap, root, distance);

    // 모든 정점을 순회하며 최소 신장 트리를 구성합니다.
    for (i = 0; i <= g->a - 2; i++) {
        int u = delete_min_heap(heap); // 최소 힙에서 최소 거리 정점을 추출합니다.
        MST[u] = 1; // 추출된 정점을 최소 신장 트리에 포함시킵니다.

        // 추출된 정점과 인접한 정점들에 대해 거리를 갱신합니다.
        for (Graph* v = g->adjList[u]; v != NULL; v = v->link) {
            int w = v->V;
            if (!MST[w] && v->W < distance[w]) {
                distance[w] = v->W;
                nearest[w] = u;
                decrease_key(heap, w, distance);
            }
        }
    }

    // 최소 신장 트리의 결과를 출력합니다.
    printf("\n");
    printf("----------------최종 가중치 출력----------------\n\n");
    printf("시작 정점은 %d\n", root);
    for (i = 0; i < g->a; i++) {
        if (i != root && distance[i] != INF) {
            printf("정점 %d에서 %d | 가중치: %d\n", nearest[i], i, distance[i]);
            Weight += distance[i]; // 총 가중치를 계산합니다.
        }
    }
    printf("\n");
    printf("최소 가중치 값은 %d이다.\n", Weight);  // 총 가중치를 출력합니다.
}

//main 함수
int main() {
    inputGraph* g;
    g = (inputGraph*)malloc(sizeof(inputGraph)); // 그래프를 위한 메모리 할당

    Heap* h = init_Heap(); // 힙 초기화
    init_adjList(g); // 인접 리스트 초기화
    int i;
    // 그래프에 정점들을 추가합니다.
    for (i = 0; i < 9; i++) {
        add_vertex(g, i);
    }
    // 그래프에 간선들을 추가합니다. 각 간선은 두 정점과 가중치를 가집니다.
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
    print_adjList(g); // 인접 리스트를 이용한 그래프 출력
   
    Prim(g, h, 0); // 프림 알고리즘을 시작 정점 0부터 실행합니다.
   
    return 0;
}

