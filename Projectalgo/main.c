#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 9 //최대 정점의 수를 9개로 지정
#define MAX_SIZE 100
#define INF 999999

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
    int distance[MAX_SIZE];
}Heap;

Heap* init_Heap() {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    if (h == NULL) {
        // 메모리 할당 실패 처리
        exit(1);
    }
    h->heap = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        h->distance[i] = INF;  // 처음에는 모든 거리를 무한대로 설정
    }
    return h;
}

void add_heap(Heap* h, int size, int dist) {
    h->heap += 1;
    h->size[h->heap] = size;
    h->distance[size] = dist;

    int child = h->heap;
    int parent = child / 2;

    while (parent) {
        if (h->distance[h->size[parent]] > h->distance[h->size[child]]) {
            int n = h->size[parent];
            h->size[parent] = h->size[child];
            h->size[child] = n;
            child = parent;
            parent = child / 2;
        }
        else
            break;
    }
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
    h->size[1] = h->size[h->heap];
    h->distance[root] = INF;  // 제거된 정점의 거리는 무한대로 설정
    h->heap--;

    int parent = 1;
    int child = 2;

    while (child <= h->heap) {
        if (child + 1 <= h->heap && h->distance[h->size[child]] > h->distance[h->size[child + 1]]) {
            child += 1;
        }
        if (h->distance[h->size[parent]] > h->distance[h->size[child]]) {
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

void decrease_key(Heap* h, int v, int distance[]) {
    h->distance[v] = distance[v];  // 힙의 거리 값을 갱신
    for (int i = 1; i <= h->heap; i++) {
        if (h->size[i] == v) {
            int child = i;
            int parent = i / 2;
            while (parent) {
                if (h->distance[h->size[parent]] > h->distance[h->size[child]]) {
                    int n = h->size[parent];
                    h->size[parent] = h->size[child];
                    h->size[child] = n;
                    child = parent;
                    parent = child / 2;
                }
                else
                    break;
            }
            break;
        }
    }
}

void Prim(inputGraph* g, int start) {
    int distance[MAX_VERTICES];
    int nearest[MAX_VERTICES];
    int MST[MAX_VERTICES] = { 0, };  // false로 초기화
    Heap* heap = init_Heap();
    int totalWeight = 0; // 추가: 전체 가중치를 저장하기 위한 변수

    for (int i = 0; i < g->a; i++) {
        distance[i] = INF;
        nearest[i] = start;
        add_heap(heap, i, distance[i]);
    }
    distance[start] = 0;
    decrease_key(heap, start, distance);

    for (int i = 0; i < g->a - 2; i++) {  // n-2번 반복
        int u = delete_min_heap(heap);
        MST[u] = 1;  // true로 설정

        for (Graph* v = g->adjList[u]; v != NULL; v = v->link) {
            int w = v->V;
            if (!MST[w]) {
                if (v->W < distance[w]) {
                    distance[w] = v->W;
                    nearest[w] = u;
                    decrease_key(heap, w, distance);
                }
            }
        }
    }
    printf("\n");
    printf("시작 정점: %d\n", start);
    for (int i = 0; i < g->a; i++) {
        if (i != start && distance[i] != INT_MAX) {
            printf("정점 %d에서 %d | 가중치: %d\n", nearest[i], i, distance[i]);
            totalWeight += distance[i];
        }
    }
    printf("\n");
    printf("최소 가중치 값은 %d이다.\n", totalWeight);  // 총 가중치 출력
}



//main 함수
int main() {
    inputGraph* g;
    g = (inputGraph*)malloc(sizeof(inputGraph));
    
    Heap* h = init_Heap();
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

    add_heap(h, 0, INF);
    add_heap(h, 1, INF);
    add_heap(h, 2, INF);
    add_heap(h, 3, INF);
    add_heap(h, 4, INF);
    add_heap(h, 5, INF);
    add_heap(h, 6, INF);
    add_heap(h, 7, INF);
    add_heap(h, 8, INF);


    Prim(g, 0);
   
    return 0;
}

