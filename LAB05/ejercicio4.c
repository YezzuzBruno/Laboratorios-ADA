#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;
struct node {
    int v;
    link next;
};

typedef struct {
    int V;
    int A;
    link *adj;
} *Graph;

int cnt = 0;
int *pre;
int indent = 0; // para sangría

link NEW(int v, link next) {
    link x = malloc(sizeof *x);
    x->v = v;
    x->next = next;
    return x;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (int v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertA(Graph G, int v, int w) {
    G->adj[v] = NEW(w, G->adj[v]);
    G->adj[w] = NEW(v, G->adj[w]); // grafo no dirigido
    G->A++;
}

// DFS con rastreo y sangría
void dfsR(Graph G, int v) {
    for (int i = 0; i < indent; i++) printf(". ");
    printf("%d dfsR(G,%d)\n", v, v);

    pre[v] = cnt++;
    indent++;

    for (link a = G->adj[v]; a != NULL; a = a->next) {
        int w = a->v;
        for (int i = 0; i < indent; i++) printf(". ");
        printf("%d-%d ", v, w);
        if (pre[w] == -1) {
            printf("dfsR(G,%d)\n", w);
            dfsR(G, w);
        } else {
            printf("\n");
        }
    }

    indent--;
}

void GRAPHdfs(Graph G) {
    pre = malloc(G->V * sizeof(int));
    for (int v = 0; v < G->V; v++)
        pre[v] = -1;

    cnt = 0;
    for (int v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR(G, v);
}

int main() {
    // El grafo tiene 10 vértices (0..9)
    Graph G = GRAPHinit(10);

    // Insertamos las aristas: 3-7, 1-4, 7-8, 0-5, 5-2, 3-8, 2-9, 0-6, 4-9, 2-6, 6-4
    GRAPHinsertA(G, 3, 7);
    GRAPHinsertA(G, 1, 4);
    GRAPHinsertA(G, 7, 8);
    GRAPHinsertA(G, 0, 5);
    GRAPHinsertA(G, 5, 2);
    GRAPHinsertA(G, 3, 8);
    GRAPHinsertA(G, 2, 9);
    GRAPHinsertA(G, 0, 6);
    GRAPHinsertA(G, 4, 9);
    GRAPHinsertA(G, 2, 6);
    GRAPHinsertA(G, 6, 4);

    printf("Rastreo de GRAPHdfs(G):\n");
    GRAPHdfs(G);

    free(pre);
    return 0;
}
