#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 9 //최대 정점의 수를 9개로 지정
#define MAX_SIZE 100

typedef struct Graph {
    int V; //정점
    int W; //가중치
    struct Graph* link;

}Graph;

typedef struct inputGraph {
    int a;  //총 정점의 개수
    Graph* adjList[MAX_VERTICES];

}inputGraph;

typedef struct Heap {
    int heap;
    int size[MAX_SIZE];
}Heap;

void init_Heap(Heap* h) {
    h = (Heap*)malloc(sizeof(Heap));
    h->heap = 0;
    return h;
}

void add_heap(Heap* h, int size) {
    h->heap += 1;
    h->size[h->heap] = size;

    int child = h->heap;
    int parent = child / 2;

    while (parent) {
        if (h->size[parent] > h->size[child]) {
            int n = h->size[parent];
            h->size[parent] = h->size[child];
            h->size[child] = n;
            child = parent;
            parent = child / 2;
        }
        else
            break;
    }
    return;
}

int empty(Heap* h) {
    return (h->heap ? 0 : 1);
}

int delete_min_heap(Heap* h) {
    if (h->heap == 0) {
        printf("heap empty\n");
        return -1;
    }
    int root = h->size[1];
    h->size[1] = h->size[h->heap--];

    int parent = 1;
    int child = 2;

    while (child <= h->heap) {
        if (child + 1 <= h->heap && h->size[child] < h->size[child + 1]) {
            child += 1;
   
        }
        if (h->size[parent] < h->size[child]) {
            int n = h->size[parent];
            h->size[parent] = h->size[child];
            h->size[child] = n;

            parent = child;
            child = parent * 2;

        }
        else
            break;
    }
    return root;
}
void init_adjList(inputGraph* g) {
    int i;
    g->a = 0;
    for (i = 0; i <= MAX_VERTICES; i++) {  //MAX_VERTICES가 9으로 설정되어 있으므로 0부터 9까지 하나씩 증가시키면서 정점의 인접 리스트를 NULL로 초기화 한다.
        g->adjList[i] = NULL;
    }
}

void add_vertex(inputGraph* g, int v) {
    if ((g->a) >= MAX_VERTICES) {
        fprintf(stderr, "정점 개수 초과");
        return;
    }
    g->a++;
}

void add_edge(inputGraph* g, int u, int v, int w) {
    if (u >= g->a || v >= g->a) {
        fprintf(stderr, "간선 오류");
        return;
    }
    Graph* n = (Graph*)malloc(sizeof(Graph));
    if (n == NULL) {
        fprintf(stderr, "메모리 할당 실패");
        exit(1);
    }
    n->V = v;
    n->W = w;
    n->link = g->adjList[u];
    g->adjList[u] = n;
}

void print_adjList(inputGraph* g) {
    printf("그래프 출력");
    printf("\n\n");
    for (int i = 0; i < g->a; i++) {
        Graph* pg = g->adjList[i];
        printf("정점 %d의 인접리스트: ", i);
        while (pg != NULL) {
            printf("%d -> %d (가중치: %d) \t",i, pg->V, pg->W);
            pg = pg->link;
        }
        printf("\n");
    }
}

//main 함수
int main() {
    inputGraph* g;
    g = (inputGraph*)malloc(sizeof(inputGraph));
    Heap* h = NULL;
    init_Heap(h);
    init_adjList(g);

    for (int i = 0; i < 9; i++) {
        add_vertex(g, i);
    }
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
    print_adjList(g);

    add_heap(h, 0);
    add_heap(h, 1);
    add_heap(h, 2);
    add_heap(h, 3);
    add_heap(h, 4);
    add_heap(h, 5);
    add_heap(h, 6);
    add_heap(h, 7);
    add_heap(h, 8);

    while (!empty(h)) {
        printf("%d", delete_min_heap(h));
    }
}

