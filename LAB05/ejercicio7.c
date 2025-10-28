#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000

typedef int vertex;

typedef struct node* link;
struct node {
    vertex w;
    link next;
};

typedef struct graph {
    int V;
    link adj[MAXV];
} *Graph;

// Variables globales
int pre[MAXV];
int cnt;


link NEW(vertex w, link next) {
    link x = malloc(sizeof *x);
    x->w = w;
    x->next = next;
    return x;
}

// DFS iterativa
void dfsIterative(Graph G, vertex start) {
    vertex stack[MAXV];
    int top = -1;

    stack[++top] = start;  // Apilamos el vértice inicial

    while (top >= 0) {
        vertex v = stack[top--]; // Desapilamos

        if (pre[v] == -1) {     // Si aún no fue descubierto
            pre[v] = cnt++;
        }

        // Apilamos vecinos no visitados (para mantener orden como recursivo, apilar en orden inverso)
        link a;
        // Primero contamos vecinos para invertir el orden
        int deg = 0;
        for (a = G->adj[v]; a != NULL; a = a->next) deg++;
        vertex temp[deg];
        int i = 0;
        for (a = G->adj[v]; a != NULL; a = a->next) temp[i++] = a->w;
        for (i = deg - 1; i >= 0; i--) {
            if (pre[temp[i]] == -1) {
                stack[++top] = temp[i];
            }
        }
    }
}

// GRAPHdfs: recorre todos los vértices
void GRAPHdfs(Graph G) {
    cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;

    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1)
            dfsIterative(G, v);
}

// Función para agregar arco
void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    G->adj[v] = NEW(w, G->adj[v]);
}

// Función para crear grafo
Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

// Función para imprimir el vector pre[]
void printPre(Graph G) {
    printf("v   : ");
    for (vertex v = 0; v < G->V; v++)
        printf("%d ", v);
    printf("\npre : ");
    for (vertex v = 0; v < G->V; v++)
        printf("%d ", pre[v]);
    printf("\n");
}

// MAIN de ejemplo
int main() {
    // Ejemplo: grafo del Ejemplo C
    // Arcos: 2-0 2-3 2-4 0-1 0-4 3-4 3-5 4-1 4-5 5-1
    Graph G = GRAPHinit(6);
    GRAPHinsertArc(G, 2, 0);
    GRAPHinsertArc(G, 2, 3);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 4);
    GRAPHinsertArc(G, 3, 4);
    GRAPHinsertArc(G, 3, 5);
    GRAPHinsertArc(G, 4, 1);
    GRAPHinsertArc(G, 4, 5);
    GRAPHinsertArc(G, 5, 1);

    GRAPHdfs(G);

    printPre(G);

    return 0;
}
