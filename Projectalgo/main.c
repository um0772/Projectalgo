#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 9 //�ִ� ������ ���� 9���� ����


typedef struct Graph {
    int V; //����
    struct Graph* link;

}Graph;

typedef struct inputGraph {
    int a;  //�� ������ ����
    Graph* adjList[MAX_VERTICES];

}inputGraph;

void init_adjList(inputGraph* g) {
    int i;
    g->a = 0;
    for (i = 0; i <= MAX_VERTICES; i++) {  //MAX_VERTICES�� 9���� �����Ǿ� �����Ƿ� 0���� 9���� �ϳ��� ������Ű�鼭 ������ ���� ����Ʈ�� NULL�� �ʱ�ȭ �Ѵ�.
        g->adjList[i] = NULL;
    }
}

void add_vertex(inputGraph* g, int v) {
    if ((g->a) + 1 > MAX_VERTICES) {
        fprintf(stderr, "���� ���� �ʰ�");
        return;
    }
    g->a++;
}

void add_edge(inputGraph* g, int u, int v) {
    if (u >= g->a || v >= g->a) {
        fprintf(stderr, "���� ����");
        return;
    }
    Graph* n = (Graph*)malloc(sizeof(Graph));
    n->V = i;
    n->link = g->adjList[u];
    g->adjList[u] = n;
}

void print_adjList(inputGraph* g) {
    for (int i = 0; i < g->a; i++) {
        Graph* pg = g->adjList[i];
        printf("���� %d�� ��������Ʈ: ", i);
        while (pg != NULL) {
            printf("-> %d ", pg->V);
            pg = p->link;
        }
        printf("\n");
    }
}


void main() {
    inputGraph* g;
    g = (inputGraph*)malloc(sizeof(inputGraph));

    init_adjList(g);

    for (int i = 0; i < 9; i++) {
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
        free(g);
    }


}

